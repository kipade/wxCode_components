/////////////////////////////////////////////////////////////////////////////
// Name:        awx/awx.h
// Purpose:
// Author:      Joachim Buermann
// Id:          $Id$
// Copyright:   (c) 2003,2006 Joachim Buermann
// Licence:     wxWindows
/////////////////////////////////////////////////////////////////////////////

/*!
  \mainpage awx overview

  AWX is a wxWindows enhancement, which offers the following additional classes:

  \li \c awxButton
  \li \c awxCheckButton
  \li \c awxRadioButton
  \li \c awxSeparator
  \li \c awxRadioButtonBox
  \li \c awxLed
  \li \c awxToolbar

  \section wxOutbarDialog wxOutbarDialog class
  This class is derived from wxDialog. It offers an outlook like
  dialog and manages any number of 'dialog pages' via an icon panel
  instead of riders that are used in wxNotebook.  The single pages can
  be generated by wxDesigner or manually generated and inserted.  The
  icon panel to select the respective page is scrollable. Therefore any
  number of dialog pages can be inserted.  awxOutbarDialog always owns
  an OK and Quit button. Additionally as a style flag a Help and a Use
  button can be displayed.
 
  \section awxButton awxButton class
  Inspired by the nice 'Audacity' Buttons. A bitmap button class where
  an own wxBitmap can be defined for each of the four states: not
  pressed (up), Mouse over, pressed (down) and disabled.
  In addition a text string can be defined. awxButton alignes its size
  automatically according to the Text size. The text can be optionally
  switched on or off.
  From awxButton these classes are derived: 
  \subsection awxRadioButton
  Multiple awxRadioButton are used to select a certain state with
  mutual exclusion. The behaviour is like that of wxRadioButton.
  \subsection awxCheckButton
  This Button has two States. Pressed and not pressed. In contrary to
  awxButton awxCheckButton keeps its pressed or not pressed condition
  until it changes back to its original condition by clicking the
  button again.

  \section awxToolBar awxToolBar class
  A wxToolbar like class which together with awxButton realizes
  transparent toolbar buttons with any (fixed coded) background.
  This implementation was initiated by the insufficient display of
  deactivated toolbar buttons in windows. (Possibly someone can extend
  awxToolbar with a GTK2 theme support - I am not a GTK expert
  myself).
  The text labelling can be optionally switched on and off.
*/

#ifndef __AWX_H
#define __AWX_H

#include "wx/awx-0.3/button.h"
#include "wx/awx-0.3/led.h"
#include "wx/awx-0.3/obdlg.h"
#include "wx/awx-0.3/outbar.h"
#include "wx/awx-0.3/toolbar.h"

#endif
