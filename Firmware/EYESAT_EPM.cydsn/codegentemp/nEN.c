/*******************************************************************************
* File Name: nEN.c  
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
#include "nEN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        nEN_PC =   (nEN_PC & \
                                (uint32)(~(uint32)(nEN_DRIVE_MODE_IND_MASK << (nEN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (nEN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: nEN_Write
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
void nEN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(nEN_DR & (uint8)(~nEN_MASK));
    drVal = (drVal | ((uint8)(value << nEN_SHIFT) & nEN_MASK));
    nEN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: nEN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  nEN_DM_STRONG     Strong Drive 
*  nEN_DM_OD_HI      Open Drain, Drives High 
*  nEN_DM_OD_LO      Open Drain, Drives Low 
*  nEN_DM_RES_UP     Resistive Pull Up 
*  nEN_DM_RES_DWN    Resistive Pull Down 
*  nEN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  nEN_DM_DIG_HIZ    High Impedance Digital 
*  nEN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void nEN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(nEN__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: nEN_Read
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
*  Macro nEN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 nEN_Read(void) 
{
    return (uint8)((nEN_PS & nEN_MASK) >> nEN_SHIFT);
}


/*******************************************************************************
* Function Name: nEN_ReadDataReg
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
uint8 nEN_ReadDataReg(void) 
{
    return (uint8)((nEN_DR & nEN_MASK) >> nEN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(nEN_INTSTAT) 

    /*******************************************************************************
    * Function Name: nEN_ClearInterrupt
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
    uint8 nEN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(nEN_INTSTAT & nEN_MASK);
		nEN_INTSTAT = maskedStatus;
        return maskedStatus >> nEN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
