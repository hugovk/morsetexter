/*
MorseTexterAppUi.cpp

Morse Texter: send an SMS using Morse code.

http://code.google.com/p/morsetexter

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>
#include <eikmenub.h>

#include <MorseTexter.rsg>
#include "MorseTexter.hrh"
#include "MorseTexterAppUi.h"
#include "MorseTexterView.h"
#include "MorseTexterContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CMorseTexterAppUi::ConstructL()
    {
    BaseConstructL();

	iView = new(ELeave) CMorseTexterView;
    CleanupStack::PushL(iView);
    iView->ConstructL(R_MORSETEXTER_MENU);
    CleanupStack::Pop();    // iView

    AddViewL(iView);   // transfer ownership to CAknViewAppUi
    }

// Destructor
CMorseTexterAppUi::~CMorseTexterAppUi()
    {
	if (iView)
		{
//		RemoveFromStack(iView);

		delete iView;
		iView = NULL;
		}
    }

// ------------------------------------------------------------------------------
// CMorseTexterAppUi::::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CMorseTexterAppUi::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
	{
	if (aResourceId == R_MORSETEXTER_SYSTEM_MENU)
		{
		iView->DynInitMenuPaneL( aResourceId, aMenuPane );
		}
	}

// ----------------------------------------------------
// CMorseTexterAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ----------------------------------------------------
void CMorseTexterAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	// Exit - confirm first so text not lost
	case EEikCmdExit:
	case EAknCmdExit:
		{
		CAknQueryDialog* dlg = new (ELeave) CAknQueryDialog(/**text,*/ CAknQueryDialog::ENoTone);    
		if( dlg->ExecuteLD(R_MORSETEXTER_DISCARDMESSAGE_QUERY) )
			{
			// LSK = OK
			Exit();
			}
		}
            break;

        // TODO: Add Your command handling code here

        default:
            break;
        }
    }


// End of File  
