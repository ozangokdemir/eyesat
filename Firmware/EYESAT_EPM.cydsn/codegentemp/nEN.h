/*******************************************************************************
* File Name: nEN.h  
* Version 2.5
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_nEN_H) /* Pins nEN_H */
#define CY_PINS_nEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "nEN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    nEN_Write(uint8 value) ;
void    nEN_SetDriveMode(uint8 mode) ;
uint8   nEN_ReadDataReg(void) ;
uint8   nEN_Read(void) ;
uint8   nEN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define nEN_DRIVE_MODE_BITS        (3)
#define nEN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - nEN_DRIVE_MODE_BITS))
#define nEN_DRIVE_MODE_SHIFT       (0x00u)
#define nEN_DRIVE_MODE_MASK        (0x07u << nEN_DRIVE_MODE_SHIFT)

#define nEN_DM_ALG_HIZ         (0x00u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_DIG_HIZ         (0x01u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_RES_UP          (0x02u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_RES_DWN         (0x03u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_OD_LO           (0x04u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_OD_HI           (0x05u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_STRONG          (0x06u << nEN_DRIVE_MODE_SHIFT)
#define nEN_DM_RES_UPDWN       (0x07u << nEN_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define nEN_MASK               nEN__MASK
#define nEN_SHIFT              nEN__SHIFT
#define nEN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define nEN_PS                     (* (reg32 *) nEN__PS)
/* Port Configuration */
#define nEN_PC                     (* (reg32 *) nEN__PC)
/* Data Register */
#define nEN_DR                     (* (reg32 *) nEN__DR)
/* Input Buffer Disable Override */
#define nEN_INP_DIS                (* (reg32 *) nEN__PC2)


#if defined(nEN__INTSTAT)  /* Interrupt Registers */

    #define nEN_INTSTAT                (* (reg32 *) nEN__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins nEN_H */


/* [] END OF FILE */
