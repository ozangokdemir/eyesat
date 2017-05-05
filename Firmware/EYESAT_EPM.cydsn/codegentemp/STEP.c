/*******************************************************************************
* File Name: STEP.c  
* Version 2.5
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "STEP.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        STEP_PC =   (STEP_PC & \
                                (uint32)(~(uint32)(STEP_DRIVE_MODE_IND_MASK << (STEP_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (STEP_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: STEP_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void STEP_Write(uint8 value) 
{
    uint8 drVal = (uint8)(STEP_DR & (uint8)(~STEP_MASK));
    drVal = (drVal | ((uint8)(value << STEP_SHIFT) & STEP_MASK));
    STEP_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: STEP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  STEP_DM_STRONG     Strong Drive 
*  STEP_DM_OD_HI      Open Drain, Drives High 
*  STEP_DM_OD_LO      Open Drain, Drives Low 
*  STEP_DM_RES_UP     Resistive Pull Up 
*  STEP_DM_RES_DWN    Resistive Pull Down 
*  STEP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  STEP_DM_DIG_HIZ    High Impedance Digital 
*  STEP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void STEP_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(STEP__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: STEP_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro STEP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 STEP_Read(void) 
{
    return (uint8)((STEP_PS & STEP_MASK) >> STEP_SHIFT);
}


/*******************************************************************************
* Function Name: STEP_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 STEP_ReadDataReg(void) 
{
    return (uint8)((STEP_DR & STEP_MASK) >> STEP_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(STEP_INTSTAT) 

    /*******************************************************************************
    * Function Name: STEP_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 STEP_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(STEP_INTSTAT & STEP_MASK);
		STEP_INTSTAT = maskedStatus;
        return maskedStatus >> STEP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
