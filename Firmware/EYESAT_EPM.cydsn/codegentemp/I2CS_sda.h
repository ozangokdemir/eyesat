/*******************************************************************************
* File Name: I2CS_sda.h  
* Version 2.0
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

#if !defined(CY_PINS_I2CS_sda_H) /* Pins I2CS_sda_H */
#define CY_PINS_I2CS_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "I2CS_sda_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    I2CS_sda_Write(uint8 value) ;
void    I2CS_sda_SetDriveMode(uint8 mode) ;
uint8   I2CS_sda_ReadDataReg(void) ;
uint8   I2CS_sda_Read(void) ;
uint8   I2CS_sda_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define I2CS_sda_DRIVE_MODE_BITS        (3)
#define I2CS_sda_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - I2CS_sda_DRIVE_MODE_BITS))
#define I2CS_sda_DRIVE_MODE_SHIFT       (0x00u)
#define I2CS_sda_DRIVE_MODE_MASK        (0x07u << I2CS_sda_DRIVE_MODE_SHIFT)

#define I2CS_sda_DM_ALG_HIZ         (0x00u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_DIG_HIZ         (0x01u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_RES_UP          (0x02u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_RES_DWN         (0x03u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_OD_LO           (0x04u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_OD_HI           (0x05u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_STRONG          (0x06u << I2CS_sda_DRIVE_MODE_SHIFT)
#define I2CS_sda_DM_RES_UPDWN       (0x07u << I2CS_sda_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define I2CS_sda_MASK               I2CS_sda__MASK
#define I2CS_sda_SHIFT              I2CS_sda__SHIFT
#define I2CS_sda_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define I2CS_sda_PS                     (* (reg32 *) I2CS_sda__PS)
/* Port Configuration */
#define I2CS_sda_PC                     (* (reg32 *) I2CS_sda__PC)
/* Data Register */
#define I2CS_sda_DR                     (* (reg32 *) I2CS_sda__DR)
/* Input Buffer Disable Override */
#define I2CS_sda_INP_DIS                (* (reg32 *) I2CS_sda__PC2)


#if defined(I2CS_sda__INTSTAT)  /* Interrupt Registers */

    #define I2CS_sda_INTSTAT                (* (reg32 *) I2CS_sda__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins I2CS_sda_H */


/* [] END OF FILE */
