/*******************************************************************************
* File Name: nSLEEP.h  
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

#if !defined(CY_PINS_nSLEEP_H) /* Pins nSLEEP_H */
#define CY_PINS_nSLEEP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "nSLEEP_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    nSLEEP_Write(uint8 value) ;
void    nSLEEP_SetDriveMode(uint8 mode) ;
uint8   nSLEEP_ReadDataReg(void) ;
uint8   nSLEEP_Read(void) ;
uint8   nSLEEP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define nSLEEP_DRIVE_MODE_BITS        (3)
#define nSLEEP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - nSLEEP_DRIVE_MODE_BITS))
#define nSLEEP_DRIVE_MODE_SHIFT       (0x00u)
#define nSLEEP_DRIVE_MODE_MASK        (0x07u << nSLEEP_DRIVE_MODE_SHIFT)

#define nSLEEP_DM_ALG_HIZ         (0x00u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_DIG_HIZ         (0x01u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_RES_UP          (0x02u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_RES_DWN         (0x03u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_OD_LO           (0x04u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_OD_HI           (0x05u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_STRONG          (0x06u << nSLEEP_DRIVE_MODE_SHIFT)
#define nSLEEP_DM_RES_UPDWN       (0x07u << nSLEEP_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define nSLEEP_MASK               nSLEEP__MASK
#define nSLEEP_SHIFT              nSLEEP__SHIFT
#define nSLEEP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define nSLEEP_PS                     (* (reg32 *) nSLEEP__PS)
/* Port Configuration */
#define nSLEEP_PC                     (* (reg32 *) nSLEEP__PC)
/* Data Register */
#define nSLEEP_DR                     (* (reg32 *) nSLEEP__DR)
/* Input Buffer Disable Override */
#define nSLEEP_INP_DIS                (* (reg32 *) nSLEEP__PC2)


#if defined(nSLEEP__INTSTAT)  /* Interrupt Registers */

    #define nSLEEP_INTSTAT                (* (reg32 *) nSLEEP__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins nSLEEP_H */


/* [] END OF FILE */
