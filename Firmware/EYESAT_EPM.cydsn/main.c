/* ========================================
 *
 * Copyright le CNES, 2014
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF le CNES.
 * Redactors : Camille Demasson et Quang Viet NGUYEN 
 *
 * ========================================
*/

#include <project.h>  
#include <cyPm.h> 

#define CAS_ARRET             0     //cas où le moteur est arrêté
#define CAS_POSITION_INITIALE 1     //cas où le moteur tourne jusqu'à la position initiale
#define CAS_POSITION_X        2     //cas où le moteur tourne jusqu'à une position X


volatile uint8 commande_ODB;        //octet de commande de position
volatile uint8 registre=0x00;       //octet de commande du moteur : bit0=DIR ; bit1=enable
volatile uint8 commande_avant_reset;//octet sur lequel est recopiée la dernière commande de l'ODB
                                    //enregistrée sur la mémoire avant un reset    

volatile int   CAS_ACTUEL=CAS_ARRET;
volatile int8  POSITION_ACTUELLE=0, POSITION_SUIVANTE, NBR_CHANGEMENTS_POSITION=0;   
                                    /*POSITION_ACTUELLE : position actuelle des roues 
                                    par rapport à la position initiale où
                                    POSITION_ACTUELLE=0.
                                    POSITION_SUIVANTE : position commandée par l'ODB 
                                    qui n'est pas encore atteinte.
                                    NB_CHANGEMENT_POSITION : nombre de changements de 
                                    position à effectuer pour aller de
                                    POSITION_ACTUELLE à POSITION_SUIVANTE*/
                                    
static const uint8 CYCODE eepromArray[]={0xFF,0xFF,0xFF}; //Trois octets stockés en mémoire Eeprom
                                    
uint8 array[]={0x00,0x00,0x00};     /*Trois octets à recopier dans la mémoire 
                                    1er octet : POSITION_ACTUELLE
                                    2ème octet : rBuffer[0]
                                    3ème octet : commande_ODB*/

uint8 wBuffer[1];                   // Buffer d'écriture I2C
uint8 rBuffer[1]={0xFF};            /* Buffer de lecture I2C contenant la position actuelle; 
                                    0xFF=position inconnue*/ 
int   position_connue=0;            /* 0 si la position n'a pas encore été initialisée
                                    1 si la position a déjà été initialisée une fois*/
int   pblm_reset=0;                 /* 1 si un reset a eu lieu alors que les roues étaient en rotation
                                    0 sinon. */
cystatus status;


uint8 fonction_I2C (void);
uint8 calcul_PDS_position(void);
void Changer_position (void);
void automate (void);


int main()  
{
    CyGlobalIntEnable;              // Interruptions autorisées
    I2CS_Start();
    Control_Reg_Write(registre);    //enable=0 avant le démarrage de la PWM
    PWM_Start();
    Counter_1_Start();
    EEPROM_Start();
    I2CS_I2CSlaveInitWriteBuf(wBuffer,1);    // Initialisation des Buffers de l'esclave I2C 
    I2CS_I2CSlaveInitReadBuf(rBuffer,1); 
    
    //WATCHDOG
    //initialisation des compteurs du watchdog
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK); //enable counter0
    //Génère des interruptions et un reset après la 3ème interruption sans retour
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0,CY_SYS_WDT_MODE_INT_RESET); 
    //200us d'attente pour confirmer la configuration du Watchdog 
    CyDelayUs(200);
    
    if (eepromArray[0]!=0xFF)               //Réécriture de la valeur de la position actuelle 
    POSITION_ACTUELLE=eepromArray[0]-12;    //après un reset si elle est connue
    
    if (eepromArray[1]!= 0xFF)
    {                                      
        if(eepromArray[1] != 0xEE)
        {                                   //Réécriture de la valeur du PDS de la position actuelle
            position_connue=1;              //si elle est connue dans rBuffer[0] après un reset
            rBuffer[0]=calcul_PDS_position();
            array[1]=rBuffer[0];
            status = EEPROM_Write(array,eepromArray,3u);
        }
        else                                //cas où le reset est arrivé alors que les roues tournaient
        {
            pblm_reset=1;
            rBuffer[0]=0xFF;
            commande_avant_reset=eepromArray[2];
        }
    }
    
    for(;;)
    {
        automate();
        
        //feed the dog
  	    //remise à 0 du compteur counter0
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);  
        //efface les dernières interruptions et empêche le reset du watchdog
        CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);    
    }  
} 										



//**********************************************************
//description des fonctions

//**********************************************************
// fonction de lecture, écriture du master I2C
uint8 fonction_I2C (void)
{ 
    uint8 commande=0xFF;
    
    if(I2CS_I2CSlaveStatus()&I2CS_I2C_SSTAT_RD_CMPLT) // Si le buffer est lu par le maître (ODB)
  
    {  
        //Efface le statut et le buffer de lecture
        I2CS_I2CSlaveClearReadBuf();  
        I2CS_I2CSlaveClearReadStatus(); 
    }  
        
    
    if(I2CS_I2CSlaveStatus()&I2CS_I2C_SSTAT_WR_CMPLT) // Si le buffer est écrit par le maître (ODB)

    {           
        // Efface le statut d'écriture 
        I2CS_I2CSlaveClearWriteStatus(); 
        // Efface les buffers pour aider la transmission         
        I2CS_I2CSlaveClearWriteBuf();   
        I2CS_I2CSlaveClearReadBuf();
        
        commande=wBuffer[0];    //commande=premier octet écrit par le master
        array[2]=commande;
        status = EEPROM_Write(array,eepromArray,3u);
    }
            
    return commande;
}


//**********************************************************
//fonction de calcul du PDS position à écrire sur le Buffer de lecture I2C
uint8 calcul_PDS_position(void)
{
    uint8 PDS_position=0;
    PDS_position = (POSITION_ACTUELLE + 12) % 4;        //Calcul du filtre polarisant
    if (PDS_position == 0x03) PDS_position = 0x04;
    
    PDS_position |= (abs(POSITION_ACTUELLE - 7) % 3) << 4;//Calcul du filtre spectral
    return PDS_position;
}


//**********************************************************
//fonction de calcul du nombre de changement de positions à effectuer selon 
//la position voulue
void Changer_position (void)
{  
    NBR_CHANGEMENTS_POSITION=POSITION_SUIVANTE-POSITION_ACTUELLE;
    if (NBR_CHANGEMENTS_POSITION>6)             //permet d'avoir toujours |nbr_chang_pos|<=6

    {                           
        NBR_CHANGEMENTS_POSITION=POSITION_SUIVANTE-12-POSITION_ACTUELLE;
    }
    if (NBR_CHANGEMENTS_POSITION<-6)
    {
        NBR_CHANGEMENTS_POSITION=POSITION_SUIVANTE+12-POSITION_ACTUELLE;
    }
    if (NBR_CHANGEMENTS_POSITION != 0)
    {
        if (NBR_CHANGEMENTS_POSITION < 0)           
        {
            registre=0x03;          //enable=1 démarrage moteur ; DIR=0
            NBR_CHANGEMENTS_POSITION=-NBR_CHANGEMENTS_POSITION;     //nombre de tour à faire positif 

        } 
        else registre=0x02;         //enable=1 démarrage moteur ; DIR=1
        CAS_ACTUEL=CAS_POSITION_X;  //moteur tourne jusqu'à la position X des roues
        rBuffer[0]=0xEE;
        array[1]=rBuffer[0];
        status = EEPROM_Write(array,eepromArray,3u);
    }
}

//**********************************************************
//automate de fonctionnement
void automate (void)
{   
    typedef enum 
    {
        commande_master=0, position_init=1, noir_X=2, visible_1=3, visible_2=4, 
        visible_3=5, nir_1=6, nir_2=7, nir_3=8, nir_neutre=9, commande_moteur=10, SleepMode=11,
        init_reset=12
    } type_etat;
    
    type_etat etat_actuel;  //structure de l'état présent 
    static type_etat etat_futur=commande_master;    /*structure de l'état à venir
                                                    initialisé à commande_master*/    
    etat_actuel=etat_futur;
    
    //gestion des entrées
    
    commande_ODB=fonction_I2C();     //commande_ODB = nouvel ordre de l'ordinateur de bord
    
    switch (etat_actuel)
    {
        case commande_master:  
            if (pblm_reset==1) etat_futur=init_reset;
            else if (commande_ODB==0x10) etat_futur=position_init;    //gestion de l'état futur
            else if (commande_ODB==0x00) etat_futur=noir_X;      //en fonction de la
            else if (commande_ODB==0x11) etat_futur=visible_1;   //commande de l'ODB
            else if (commande_ODB==0x12) etat_futur=visible_2;
            else if (commande_ODB==0x14) etat_futur=visible_3;
            else if (commande_ODB==0x21) etat_futur=nir_1;
            else if (commande_ODB==0x22) etat_futur=nir_2;
            else if (commande_ODB==0x24) etat_futur=nir_3;
            else if (commande_ODB==0x20) etat_futur=nir_neutre;
            else etat_futur=SleepMode;  //mode veille
            break;
            
        case position_init:  
            etat_futur=commande_moteur;
            break;
            
        case noir_X:
            etat_futur=commande_moteur;
            break;
            
        case visible_1:
            etat_futur=commande_moteur;
            break;
            
        case visible_2:
            etat_futur=commande_moteur;
            break;
            
        case visible_3:
            etat_futur=commande_moteur;
            break;
            
        case nir_1:
            etat_futur=commande_moteur;
            break;
            
        case nir_2:
            etat_futur=commande_moteur;
            break;
            
        case nir_3:
            etat_futur=commande_moteur;
            break;
            
        case nir_neutre:
            etat_futur=commande_moteur;
            break;
            
        case commande_moteur:
            if (CAS_ACTUEL==CAS_ARRET) 
            {
                etat_futur=SleepMode;
                if (pblm_reset==1) etat_futur=init_reset;
            }            
            else etat_futur=commande_moteur;
            break;
            
        case SleepMode:
            etat_futur=commande_master;
            break;
            
        case init_reset:
            etat_futur=position_init;
            if (hall_Read()==0)
            {
                if (commande_avant_reset==0x10) etat_futur=position_init;    //gestion de l'état futur
                else if (commande_avant_reset==0x00) etat_futur=noir_X;      //en fonction de la
                else if (commande_avant_reset==0x11) etat_futur=visible_1;   //commande de l'ODB mise en
                else if (commande_avant_reset==0x12) etat_futur=visible_2;   //mémoire
                else if (commande_avant_reset==0x14) etat_futur=visible_3;
                else if (commande_avant_reset==0x21) etat_futur=nir_1;
                else if (commande_avant_reset==0x22) etat_futur=nir_2;
                else if (commande_avant_reset==0x24) etat_futur=nir_3;
                else if (commande_avant_reset==0x20) etat_futur=nir_neutre;
                else etat_futur=SleepMode;
            }
            break;
    }
    
    //gestion des sorties
    switch (etat_actuel)
    { 
        case commande_master:   
            break;
        
        case position_init:
            if (hall_Read()==0) 
            {
                registre=0x01;         //enable=0 ; le moteur reste à l'arrêt
                rBuffer[0]=0x10;
            }
            else 
            {
                if (POSITION_ACTUELLE < 0) registre=0x02;  //enable=1 démarrage moteur ; DIR=1
                else registre=0x03;                        //enable=1 ; DIR=0
                rBuffer[0]=0xEE;
                POSITION_SUIVANTE=0;                       
                CAS_ACTUEL=CAS_POSITION_INITIALE;          //moteur tourne jusqu'à la position initiale
            }
            
            array[1]=rBuffer[0];                       //mise en mémoire de la position actuelle
            status = EEPROM_Write(array,eepromArray,3u);
            break;
        
        case noir_X:
            NBR_CHANGEMENTS_POSITION = 0;   //cas où les roues sont déjà la position   noir_X

            if((POSITION_ACTUELLE+1)%3==-1 || (POSITION_ACTUELLE+1)%3==2) 
            {
                NBR_CHANGEMENTS_POSITION=-1; //calcul du nombre de changements de   position minimal

            }
            else if ((POSITION_ACTUELLE+1)%3==-2 || (POSITION_ACTUELLE+1)%3==1) 
            {
                NBR_CHANGEMENTS_POSITION=1; 
            }
            POSITION_SUIVANTE=POSITION_ACTUELLE+NBR_CHANGEMENTS_POSITION;
            Changer_position();
            break;
            
        case visible_1:
            POSITION_SUIVANTE=-3;
            Changer_position();   
            break;

        case visible_2:
            POSITION_SUIVANTE=6;
            Changer_position();
            break;
            
        case visible_3:
            POSITION_SUIVANTE=3;
            Changer_position();
            break;
            
        case nir_1:
            POSITION_SUIVANTE=5;
            Changer_position();
            break;
            
        case nir_2:
            POSITION_SUIVANTE=2;
            Changer_position();
            break;
            
        case nir_3:
            POSITION_SUIVANTE=-1;
            Changer_position();
            break;
            
        case nir_neutre:
            POSITION_SUIVANTE=-4;
            Changer_position();
            break;
            
        case commande_moteur:
            if(((CAS_ACTUEL==CAS_POSITION_INITIALE)&&(hall_Read()==0))  |  
               ((CAS_ACTUEL==CAS_POSITION_X)&&(Counter_1_ReadCounter() >= 96 * NBR_CHANGEMENTS_POSITION)))
            {      
                POSITION_ACTUELLE=POSITION_SUIVANTE;        //Actualisation de POSITION_ACTUELLE
                array[0]=POSITION_ACTUELLE+12;
                status = EEPROM_Write(array,eepromArray,3u);

                if (position_connue==0)                     
                {                                           //Actualisation de la position enregistrée

                    if (CAS_ACTUEL==CAS_POSITION_INITIALE)  //sur le Buffer de lecture I2C

                    {
                        rBuffer[0]=0x10;
                        position_connue=1;      //Le système est en position initiale, la position est 
                    }                           //donc certaine
                    else rBuffer[0]=0xFF;
                }

                else                            //Actualisation de la position enregistrée sur le Buffer 
                {                               //de lecture I2C si la position est connue
                    rBuffer[0]=calcul_PDS_position();       
                }  
                array[1]=rBuffer[0];
                status = EEPROM_Write(array,eepromArray,3u);
                CAS_ACTUEL=CAS_ARRET;
                registre=0x01;  //arrêt du moteur si les capteurs à effet hall ont
                                //détecté la position initiale ou si le moteur a fait 
                                //le bon nombre de pas pour arriver à la position   voulue 
            }                   
            break;                  
            
        case SleepMode:     //mode veille
           
            if(!(I2CS_I2CSlaveStatus()&  
                (I2CS_I2C_SSTAT_RD_BUSY|I2CS_I2C_SSTAT_RD_BUSY|  
                    I2CS_I2C_SSTAT_WR_BUSY|I2CS_I2C_SSTAT_WR_CMPLT|  
                    I2CS_I2C_SSTAT_RD_CMPLT))) // Pas d'activité sur le bus I2C  
            {  
                I2CS_Sleep();       //I2C Module Sleep 
                CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);//désactive le reset du watchdog

                CySysPmSleep();     // Mise en veille (sleep)  
                I2CS_Wakeup();      // Réveil (Wakeup) sur une interruption générée par l'I2C  
                CyGlobalIntEnable;  // Interruptions autorisées
                CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK); //réactive le watchdog
            }
            break; 
            
        case init_reset:
            if (POSITION_ACTUELLE==0) pblm_reset=0;
            break;
    }
    Control_Reg_Write(registre);    //écriture des valeurs de enable et DIR
    array[1]=rBuffer[0];
}

/* [] END OF FILE */