/*******************************************************************************
* File Name: hall.c  
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
#include "hall.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        hall_PC =   (hall_PC & \
                                (uint32)(~(uint32)(hall_DRIVE_MODE_IND_MASK << (hall_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (hall_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: hall_Write
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
void hall_Write(uint8 value) 
{
    uint8 drVal = (uint8)(hall_DR & (uint8)(~hall_MASK));
    drVal = (drVal | ((uint8)(value << hall_SHIFT) & hall_MASK));
    hall_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: hall_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  hall_DM_STRONG     Strong Drive 
*  hall_DM_OD_HI      Open Drain, Drives High 
*  hall_DM_OD_LO      Open Drain, Drives Low 
*  hall_DM_RES_UP     Resistive Pull Up 
*  hall_DM_RES_DWN    Resistive Pull Down 
*  hall_DM_RES_UPDWN  Resistive Pull Up/Down 
*  hall_DM_DIG_HIZ    High Impedance Digital 
*  hall_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void hall_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(hall__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: hall_Read
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
*  Macro hall_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 hall_Read(void) 
{
    return (uint8)((hall_PS & hall_MASK) >> hall_SHIFT);
}


/*******************************************************************************
* Function Name: hall_ReadDataReg
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
uint8 hall_ReadDataReg(void) 
{
    return (uint8)((hall_DR & hall_MASK) >> hall_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(hall_INTSTAT) 

    /*******************************************************************************
    * Function Name: hall_ClearInterrupt
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
    uint8 hall_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(hall_INTSTAT & hall_MASK);
		hall_INTSTAT = maskedStatus;
        return maskedStatus >> hall_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
