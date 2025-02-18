/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIConf.h
Purpose     : Configures abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_OS                    (0)  /* Compile with multitasking support */
#define GUI_SUPPORT_TOUCH         (0)  /* Support a touch screen (req. win-manager) */
#define GUI_SUPPORT_UNICODE       (1)  /* Support mixed ASCII/UNICODE strings */

#define GUI_DEFAULT_FONT        &GUI_Font6x8
#define GUI_ALLOC_SIZE          1024*10  /* Size of dynamic memory ... For WM and memory devices*/

/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            0  /* Window manager package available */
#define GUI_SUPPORT_MEMDEV        0  /* Memory devices available */
#define GUI_SUPPORT_AA            1  /* Anti aliasing available */

#endif  /* Avoid multiple inclusion */



