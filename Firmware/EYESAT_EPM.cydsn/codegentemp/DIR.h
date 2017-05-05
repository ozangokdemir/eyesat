/*******************************************************************************
* File Name: DIR.h  
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

#if !defined(CY_PINS_DIR_H) /* Pins DIR_H */
#define CY_PINS_DIR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DIR_Write(uint8 value) ;
void    DIR_SetDriveMode(uint8 mode) ;
uint8   DIR_ReadDataReg(void) ;
uint8   DIR_Read(void) ;
uint8   DIR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DIR_DRIVE_MODE_BITS        (3)
#define DIR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIR_DRIVE_MODE_BITS))
#define DIR_DRIVE_MODE_SHIFT       (0x00u)
#define DIR_DRIVE_MODE_MASK        (0x07u << DIR_DRIVE_MODE_SHIFT)

#define DIR_DM_ALG_HIZ         (0x00u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_DIG_HIZ         (0x01u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_RES_UP          (0x02u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_RES_DWN         (0x03u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_OD_LO           (0x04u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_OD_HI           (0x05u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_STRONG          (0x06u << DIR_DRIVE_MODE_SHIFT)
#define DIR_DM_RES_UPDWN       (0x07u << DIR_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define DIR_MASK               DIR__MASK
#define DIR_SHIFT              DIR__SHIFT
#define DIR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIR_PS                     (* (reg32 *) DIR__PS)
/* Port Configuration */
#define DIR_PC                     (* (reg32 *) DIR__PC)
/* Data Register */
#define DIR_DR                     (* (reg32 *) DIR__DR)
/* Input Buffer Disable Override */
#define DIR_INP_DIS                (* (reg32 *) DIR__PC2)


#if defined(DIR__INTSTAT)  /* Interrupt Registers */

    #define DIR_INTSTAT                (* (reg32 *) DIR__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins DIR_H */


/* [] END OF FILE */
