/*
MorseTexterView.cpp

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

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <eikmenub.h>
#include <aknviewappui.h>
#include <avkon.hrh>

#include <MorseTexter.rsg>
#include "MorseTexterView.h"
#include "MorseTexterContainer.h" 
#include "MorseTexter.hrh"
#include "MorseTexterappui.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CMorseTexterView::ConstructL(TInt aResId)
    {
    BaseConstructL(aResId);
    iCoeEnv->ReadResource(iMorseMsg,   R_MORSETEXTER_MORSE_TEXT);
    iCoeEnv->ReadResource(iPreviewMsg, R_MORSETEXTER_PREVIEW_TEXT);
    iCoeEnv->ReadResource(iLowerMsg,   R_MORSETEXTER_LOW_TEXT);
    }

// Destructor
CMorseTexterView::~CMorseTexterView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CMorseTexterView::Id()
// return Uid
// ---------------------------------------------------------
TUid CMorseTexterView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CMorseTexterView::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ---------------------------------------------------------
void CMorseTexterView::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
		case EMorseTexterDot:
			{
			iContainer->DotL();
			break;
			}

		case EMorseTexterDash:
			{
			iContainer->DashL();
			break;
			}

		case EMorseTexterSpace:
			{
			iContainer->SpaceL();
			break;
			}

		case EMorseTexterClearAll:
			{
			iContainer->ClearAllL();
			break;
			}

		case EMorseTexterSendViaSms:
			{
			iContainer->SendViaSmsL();
			break;
			}

		case EMorseTexterViewMorseGuide:
			{
			iContainer->ShowMorseCodeGuideL();
			break;
			}

		case EMorseTexterToggleSound:
			{
			iContainer->ToggleSound();
			break;
			}

		case EMorseTexterSendViaBt:
			{
			iContainer->SendViaBtL();
			break;
			}

	case EAknSoftkeyBack:
	case EAknSoftkeyExit:
            {
            AppUi()->HandleCommandL(EAknCmdExit);
            break;
            }
        default:
            {
            AppUi()->HandleCommandL(aCommand);
            break;
            }
        }
    }

// ------------------------------------------------------------------------------
// CMorseTexterView::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CMorseTexterView::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
	{
	if (aResourceId == R_MORSETEXTER_SYSTEM_MENU)
		{
		if (iContainer->IsSoundOn())
			aMenuPane->SetItemTextL(EMorseTexterToggleSound,	_L("Sound off"));
		else
			aMenuPane->SetItemTextL(EMorseTexterToggleSound,	_L("Sound on"));

		TFileName sisFile( KSisFilename );
#ifndef __WINS__
		CompleteWithAppPath(sisFile);
#endif
		if (iContainer->CheckForFile(sisFile) != KErrNone)
			{
			aMenuPane->SetItemDimmed(EMorseTexterSendViaBt,	ETrue); // dim option to send
			}

		if (iContainer->CheckForFile(KHtmlFilename) != KErrNone)
			{
			aMenuPane->SetItemDimmed(EMorseTexterViewMorseGuide,	ETrue); // dim option to send
			}
		}
	}

// ---------------------------------------------------------
// CMorseTexterView::DoActivateL(...)
// activate an AknView
// ---------------------------------------------------------
void CMorseTexterView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CMorseTexterContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect(), this);
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CMorseTexterView::DoDeactivate(TInt aCommand)
// deactivate an AknView
// ---------------------------------------------------------
void CMorseTexterView::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }




// End of File

