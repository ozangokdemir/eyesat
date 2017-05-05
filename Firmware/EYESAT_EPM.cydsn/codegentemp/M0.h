/*******************************************************************************
* File Name: M0.h  
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

#if !defined(CY_PINS_M0_H) /* Pins M0_H */
#define CY_PINS_M0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "M0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    M0_Write(uint8 value) ;
void    M0_SetDriveMode(uint8 mode) ;
uint8   M0_ReadDataReg(void) ;
uint8   M0_Read(void) ;
uint8   M0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M0_DRIVE_MODE_BITS        (3)
#define M0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - M0_DRIVE_MODE_BITS))
#define M0_DRIVE_MODE_SHIFT       (0x00u)
#define M0_DRIVE_MODE_MASK        (0x07u << M0_DRIVE_MODE_SHIFT)

#define M0_DM_ALG_HIZ         (0x00u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_DIG_HIZ         (0x01u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_RES_UP          (0x02u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_RES_DWN         (0x03u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_OD_LO           (0x04u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_OD_HI           (0x05u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_STRONG          (0x06u << M0_DRIVE_MODE_SHIFT)
#define M0_DM_RES_UPDWN       (0x07u << M0_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define M0_MASK               M0__MASK
#define M0_SHIFT              M0__SHIFT
#define M0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M0_PS                     (* (reg32 *) M0__PS)
/* Port Configuration */
#define M0_PC                     (* (reg32 *) M0__PC)
/* Data Register */
#define M0_DR                     (* (reg32 *) M0__DR)
/* Input Buffer Disable Override */
#define M0_INP_DIS                (* (reg32 *) M0__PC2)


#if defined(M0__INTSTAT)  /* Interrupt Registers */

    #define M0_INTSTAT                (* (reg32 *) M0__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins M0_H */


/* [] END OF FILE */
