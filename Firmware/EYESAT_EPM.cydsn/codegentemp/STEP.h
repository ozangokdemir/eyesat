/*******************************************************************************
* File Name: STEP.h  
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

#if !defined(CY_PINS_STEP_H) /* Pins STEP_H */
#define CY_PINS_STEP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "STEP_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    STEP_Write(uint8 value) ;
void    STEP_SetDriveMode(uint8 mode) ;
uint8   STEP_ReadDataReg(void) ;
uint8   STEP_Read(void) ;
uint8   STEP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define STEP_DRIVE_MODE_BITS        (3)
#define STEP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - STEP_DRIVE_MODE_BITS))
#define STEP_DRIVE_MODE_SHIFT       (0x00u)
#define STEP_DRIVE_MODE_MASK        (0x07u << STEP_DRIVE_MODE_SHIFT)

#define STEP_DM_ALG_HIZ         (0x00u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_DIG_HIZ         (0x01u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_RES_UP          (0x02u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_RES_DWN         (0x03u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_OD_LO           (0x04u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_OD_HI           (0x05u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_STRONG          (0x06u << STEP_DRIVE_MODE_SHIFT)
#define STEP_DM_RES_UPDWN       (0x07u << STEP_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define STEP_MASK               STEP__MASK
#define STEP_SHIFT              STEP__SHIFT
#define STEP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define STEP_PS                     (* (reg32 *) STEP__PS)
/* Port Configuration */
#define STEP_PC                     (* (reg32 *) STEP__PC)
/* Data Register */
#define STEP_DR                     (* (reg32 *) STEP__DR)
/* Input Buffer Disable Override */
#define STEP_INP_DIS                (* (reg32 *) STEP__PC2)


#if defined(STEP__INTSTAT)  /* Interrupt Registers */

    #define STEP_INTSTAT                (* (reg32 *) STEP__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins STEP_H */


/* [] END OF FILE */
