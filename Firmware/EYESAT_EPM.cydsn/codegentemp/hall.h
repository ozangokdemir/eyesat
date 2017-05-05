/*******************************************************************************
* File Name: hall.h  
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

#if !defined(CY_PINS_hall_H) /* Pins hall_H */
#define CY_PINS_hall_H

#include "cytypes.h"
#include "cyfitter.h"
#include "hall_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    hall_Write(uint8 value) ;
void    hall_SetDriveMode(uint8 mode) ;
uint8   hall_ReadDataReg(void) ;
uint8   hall_Read(void) ;
uint8   hall_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define hall_DRIVE_MODE_BITS        (3)
#define hall_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - hall_DRIVE_MODE_BITS))
#define hall_DRIVE_MODE_SHIFT       (0x00u)
#define hall_DRIVE_MODE_MASK        (0x07u << hall_DRIVE_MODE_SHIFT)

#define hall_DM_ALG_HIZ         (0x00u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_DIG_HIZ         (0x01u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_RES_UP          (0x02u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_RES_DWN         (0x03u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_OD_LO           (0x04u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_OD_HI           (0x05u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_STRONG          (0x06u << hall_DRIVE_MODE_SHIFT)
#define hall_DM_RES_UPDWN       (0x07u << hall_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define hall_MASK               hall__MASK
#define hall_SHIFT              hall__SHIFT
#define hall_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define hall_PS                     (* (reg32 *) hall__PS)
/* Port Configuration */
#define hall_PC                     (* (reg32 *) hall__PC)
/* Data Register */
#define hall_DR                     (* (reg32 *) hall__DR)
/* Input Buffer Disable Override */
#define hall_INP_DIS                (* (reg32 *) hall__PC2)


#if defined(hall__INTSTAT)  /* Interrupt Registers */

    #define hall_INTSTAT                (* (reg32 *) hall__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins hall_H */


/* [] END OF FILE */
