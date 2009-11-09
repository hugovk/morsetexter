/*
MorseTexterContainer.cpp

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
#include <apgcli.h>	// RApaLsSession
#include <aknnavide.h>	// CAknNavigationDecorator
#include <badesca.h>	// CDesC16ArrayFlat
#include <barsread.h>
#include <eiklabel.h>	// label control
#include <f32file.h>	// RFs
#include <txtfrmat.h>	// CParaFormat, TParaFormatMask

#include "beep.h"
#include <MorseTexter.rsg>
#include "MorseTexterContainer.h"
#include "MorseTexterview.h"
#include "MorseTexter.hrh"

// CONSTANTS
////const TInt KNumberOfComponentView = 3;
const TInt KNumberOfComponentView = 1;
const TInt KTimeslot = 100000;	// ms

//ENUMERATION
enum TPointerToComponentView
	{
////	EMorseText = 0,
////	EPreviewText,
	ELowerText = 0
	};

#define KMorseTexterWhite TRgb(0xffffff)

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CMorseTexterContainer::ConstructL(const TRect& aRect, CMorseTexterView* aParent)
	{
	CreateWindowL();


	TResourceReader reader;
/*	// Comment out iMorseText...
//	iMorseText = new(ELeave) CEikEdwin;
	iMorseText = new(ELeave) CEikGlobalTextEditor;
	iMorseText->SetContainerWindowL(*this);
	iCoeEnv->CreateResourceReaderLC(reader, R_MORSETEXTER_TEXT_VIEW);
	iMorseText->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
//	iMorseText->SetNonFocusing();
//	iMorseText->SetTextL(&(aParent->iMorseMsg));
	iMorseText->SetTextL(&(aParent->iPreviewMsg)); // blank
*/
/*	// Comment out iPreviewText...
//	iPreviewText = new(ELeave) CEikEdwin;
	iPreviewText = new(ELeave) CEikGlobalTextEditor;
	iPreviewText->SetContainerWindowL(*this);
	iCoeEnv->CreateResourceReaderLC(reader, R_MORSETEXTER_TEXT_VIEW);
	iPreviewText->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
//	iPreviewText->SetNonFocusing();
	iPreviewText->SetTextL(&(aParent->iPreviewMsg));
*/

//	iLowerText = new(ELeave) CEikEdwin;
	iLowerText = new(ELeave) CEikGlobalTextEditor;
	iLowerText->SetContainerWindowL(*this);
	iCoeEnv->CreateResourceReaderLC(reader, R_MORSETEXTER_TEXT_VIEW);
	iLowerText->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
//	iLowerText->SetNonFocusing();
	iLowerText->SetTextL(&(aParent->iLowerMsg));

	iSendUi = CSendAppUi::NewL(EMorseTexterSendViaBt, NULL);

//	iLowerText->SetFocus(ETrue);
	SetRect(aRect);

	// todo align and center upper text, make bigger or bolder
	// todo add short n long key press input

/*	todo this bit should align the upper text, but it's not working...
	// Set alignment to control. Must be called after SetExtent() or SetRect() etc is called.
	CParaFormat     paraFormat;
	TParaFormatMask paraFormatMask;

	paraFormatMask.SetAttrib(EAttAlignment);    // set mask
	paraFormat.iHorizontalAlignment = CParaFormat::ECenterAlign;

	paraFormatMask.SetAttrib(EAttVerticalAlignment);    // set mask
	paraFormat.iVerticalAlignment = CParaFormat::ECenterAlign;

	iMorseText->ApplyParaFormatL(&paraFormat, paraFormatMask);
	iLowerText->ApplyParaFormatL(&paraFormat, paraFormatMask);
*/

	iOpenParenthesis = EFalse;
	TTimeIntervalMicroSeconds dit(KTimeslot);
	TTimeIntervalMicroSeconds dah(3*KTimeslot);
	iDit=CBeep::NewL(880, dit);
	iDah=CBeep::NewL(880, dah);
	iBeepOn = EFalse;
	ActivateL();

	// Title pane for showing Morse code
	CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
	iTitlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

	// Navi pane for showing the preview
	iNaviPane = (CAknNavigationControlContainer*)sp->ControlL( TUid::Uid(EEikStatusPaneUidNavi) );
	iNaviDecorator = iNaviPane->CreateNavigationLabelL(aParent->iMorseMsg);
	iNaviPane->PushL(*iNaviDecorator);

	//todo something like this should make the dits and dahs bigger
	/*
	TCharFormat charFormat;
	TCharFormatMask charFormatMask;

	const CFont* editorFont=iEikonEnv->AnnotationFont();
	charFormat.iFontSpec=editorFont->FontSpecInTwips();
	charFormat.iFontSpec.iHeight=480;
	charFormatMask.ClearAll();
	charFormatMask.SetAttrib(EAttFontTypeface);      
	charFormatMask.SetAttrib(EAttFontHeight);
	iMorseText->ApplyCharFormatL(charFormat, charFormatMask); 
	// iMorseText is a pointer to a CEikGlobalTextEditor
	*/
	}

// Destructor
CMorseTexterContainer::~CMorseTexterContainer()
	{
////	delete iMorseText;
////	delete iPreviewText;
	delete iLowerText;

	delete iSendUi;
	iSendUi = NULL;

	delete iDit;
	iDit = NULL;
	delete iDah;
	iDah = NULL;

	if(iNaviDecorator)
		{
		iNaviPane->Pop(iNaviDecorator);
		delete iNaviDecorator;
		}
	}

// ---------------------------------------------------------
// CMorseTexterContainer::SizeChanged()
// Called by framework when the view size is changed
//  
// ---------------------------------------------------------
//
void CMorseTexterContainer::SizeChanged()
	{
/*	TInt fraction = 8;	// iMorseText (& iPreviewText) are 1/8 of the height, iLowerText is 7/8
	// Control resize code etc.
	TRect rect = Rect();
	TSize size;
	size.iWidth = (rect.iBr.iX - rect.iTl.iX)/2;	// = 1/2 rect width
	size.iHeight = (rect.iBr.iY - rect.iTl.iY) / fraction;	// =1/n
////	iMorseText->SetExtent(rect.iTl, size);
////	iPreviewText->SetExtent(TPoint((rect.iBr.iX - rect.iTl.iX)/2, rect.iTl.iY), size);


	// SriniC 18.09.2001: Fixed a minor layout problem. Adding 1 to the height 
	// but also that 1 has to be deducted from the size.iHeight otherwise 
	// it the exceeds the total height. Commented out the following line and
	// added next two lines

	//iLowerText->SetExtent(TPoint(rect.iTl.iX, size.iHeight + 1), size);

	size.iWidth = rect.iBr.iX - rect.iTl.iX;		// = one rect width
	size.iHeight*=(fraction-1);	// (n-1)/n
	size.iHeight-=1;
	iLowerText->SetExtent(TPoint(rect.iTl.iX, (rect.iBr.iY/fraction)+1), size); // from 1/n down
*/
	iLowerText->SetExtentToWholeScreen();
	}

// ---------------------------------------------------------
// CMorseTexterContainer::CountComponentControls() const
// return nbr of controls inside this container.
//  
// ---------------------------------------------------------
//
TInt CMorseTexterContainer::CountComponentControls() const
    {
    return KNumberOfComponentView;
    }

// ---------------------------------------------------------
// CMorseTexterContainer::ComponentControl(TInt aIndex) const
// return pointer of controls inside this container
// ---------------------------------------------------------
//
CCoeControl* CMorseTexterContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
////	case EMorseText:
////		return iMorseText;
////	case EPreviewText:
////		return iPreviewText;
        case ELowerText:
		return iLowerText;
	default:
		return NULL;
		}
	}

// ---------------------------------------------------------
// CMorseTexterContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CMorseTexterContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

// ---------------------------------------------------------
// CMorseTexterContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CMorseTexterContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KMorseTexterWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

TKeyResponse CMorseTexterContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	// Different keys represent dot/dash/space

	// We only want the key press, not the key up/down event
	if (aType == EEventKey)
		{
		// Check if a key was pressed
		switch (aKeyEvent.iCode)
			{
		case EKeyLeftArrow:
		case '1':
		case '4':
		case '7':
		case '*':
			DotL();
			return EKeyWasConsumed;
			break;

		case EKeyDevice3:		// OK key
		case '2':
		case '5':
		case '8':
		case '0':
			SpaceL();
			return EKeyWasConsumed;
			break;

		case EKeyRightArrow:
		case '3':
		case '6':
		case '9':
		case '#':
			DashL();
			return EKeyWasConsumed;
			break;

		case EKeyBackspace:	// C key
			// if there are any dits or dahs, delete one of these
			if (iMorseChar.Length() > 0)
				DeleteDotOrDashL();
			// otherwise delete a letter
			else // if (iText.Length() > 0)
				DeleteLetterL();
			return EKeyWasConsumed;
			break;

		case EKeyYes:		// Green key / dial key / call key
			SendViaSmsL();
			return EKeyWasConsumed;
			break;
			}
		}

	// Return the default functionality
	return CCoeControl::OfferKeyEventL(aKeyEvent, aType);
	}


TCoeInputCapabilities CMorseTexterContainer::InputCapabilities() const
	{
	// This class implements any left/right/ok/c input capabilities
	return TCoeInputCapabilities::ENavigation;
	}



void CMorseTexterContainer::DotL()
	{
	if (iMorseChar.Length() < KMorseChar)
		{
		iSpaces = 0;
		iMorseChar.Append('·');
		if (iBeepOn)
			iDit->Play();
		}
////	iMorseText->SetTextL(&(iMorseChar));
	iTitlePane->SetTextL(iMorseChar);
//	iLowerText->SetTextL(&(iText));

	UpdatePreview();
////	iPreviewText->SetTextL(&(iPreview));

	DrawNow();
	}

void CMorseTexterContainer::DashL()
	{
	if (iMorseChar.Length() < KMorseChar)
		{
		iSpaces = 0;
		iMorseChar.Append('-');
		if (iBeepOn)
			iDah->Play();
		}
////	iMorseText->SetTextL(&(iMorseChar));
	iTitlePane->SetTextL(iMorseChar);
//	iLowerText->SetTextL(&(iText));

	UpdatePreview();
////	iPreviewText->SetTextL(&(iPreview));

	DrawNow();
	}


void CMorseTexterContainer::SpaceL()
	{
	if (iText.Length() < KText)
		{
		iSpaces++;
		// for a single space, don't do owt
		if (iSpaces > 1)
			iText.Append(' ');

	// Char is complete, so match up
	if ( iMorseChar.CompareF(_L("·-")) == 0 )
		iText.Append('a');
	else if ( iMorseChar.CompareF(_L("-···")) == 0 )
		iText.Append('b');
	else if ( iMorseChar.CompareF(_L("-·-·")) == 0 )
		iText.Append('c');
	else if ( iMorseChar.CompareF(_L("-··")) == 0 )
		iText.Append('d');
	else if ( iMorseChar.CompareF(_L("·")) == 0 )
		iText.Append('e');
	else if ( iMorseChar.CompareF(_L("··-·")) == 0 )
		iText.Append('f');
	else if ( iMorseChar.CompareF(_L("--·")) == 0 )
		iText.Append('g');
	else if ( iMorseChar.CompareF(_L("····")) == 0 )
		iText.Append('h');
	else if ( iMorseChar.CompareF(_L("··")) == 0 )
		iText.Append('i');
	else if ( iMorseChar.CompareF(_L("·---")) == 0 )
		iText.Append('j');
	else if ( iMorseChar.CompareF(_L("-·-")) == 0 )
		iText.Append('k');
	else if ( iMorseChar.CompareF(_L("·-··")) == 0 )
		iText.Append('l');
	else if ( iMorseChar.CompareF(_L("--")) == 0 )
		iText.Append('m');
	else if ( iMorseChar.CompareF(_L("-·")) == 0 )
		iText.Append('n');
	else if ( iMorseChar.CompareF(_L("---")) == 0 )
		iText.Append('o');
	else if ( iMorseChar.CompareF(_L("·--·")) == 0 )
		iText.Append('p');
	else if ( iMorseChar.CompareF(_L("--·-")) == 0 )
		iText.Append('q');
	else if ( iMorseChar.CompareF(_L("·-·")) == 0 )
		iText.Append('r');
	else if ( iMorseChar.CompareF(_L("···")) == 0 )
		iText.Append('s');
	else if ( iMorseChar.CompareF(_L("-")) == 0 )
		iText.Append('t');
	else if ( iMorseChar.CompareF(_L("··-")) == 0 )
		iText.Append('u');
	else if ( iMorseChar.CompareF(_L("···-")) == 0 )
		iText.Append('v');
	else if ( iMorseChar.CompareF(_L("·--")) == 0 )
		iText.Append('w');
	else if ( iMorseChar.CompareF(_L("-··-")) == 0 )
		iText.Append('x');
	else if ( iMorseChar.CompareF(_L("-·--")) == 0 )
		iText.Append('y');
	else if ( iMorseChar.CompareF(_L("--··")) == 0 )
		iText.Append('z');
	else if ( iMorseChar.CompareF(_L("-----")) == 0 )
		iText.Append('0');
	else if ( iMorseChar.CompareF(_L("·----")) == 0 )
		iText.Append('1');
	else if ( iMorseChar.CompareF(_L("··---")) == 0 )
		iText.Append('2');
	else if ( iMorseChar.CompareF(_L("···--")) == 0 )
		iText.Append('3');
	else if ( iMorseChar.CompareF(_L("····-")) == 0 )
		iText.Append('4');
	else if ( iMorseChar.CompareF(_L("·····")) == 0 )
		iText.Append('5');
	else if ( iMorseChar.CompareF(_L("-····")) == 0 )
		iText.Append('6');
	else if ( iMorseChar.CompareF(_L("--···")) == 0 )
		iText.Append('7');
	else if ( iMorseChar.CompareF(_L("---··")) == 0 )
		iText.Append('8');
	else if ( iMorseChar.CompareF(_L("----·")) == 0 )
		iText.Append('9');
	else if ( iMorseChar.CompareF(_L("·-·-·-")) == 0 )
		iText.Append('.');
	else if ( iMorseChar.CompareF(_L("--··--")) == 0 )
		iText.Append(',');
	else if ( iMorseChar.CompareF(_L("··--··")) == 0 )
		iText.Append('!');
	else if ( iMorseChar.CompareF(_L("-·-·--")) == 0 )
		iText.Append('!');
	else if ( iMorseChar.CompareF(_L("-··-·")) == 0 )
		iText.Append('/');

	// This is the Morse for both opening & closing parentheses:
	//Parentheses ( )	-·--·-	
	else if ( iMorseChar.CompareF(_L("-·--·-")) == 0 )
		{
		if (iOpenParenthesis)
			iText.Append(')');
		else
			iText.Append('(');
		iOpenParenthesis = !iOpenParenthesis;
		}

	//Ampersand [&]	· ···	// contains a space so omitted for now
	else if ( iMorseChar.CompareF(_L("·----·")) == 0 )
		iText.Append('\'');
	else if ( iMorseChar.CompareF(_L("---··")) == 0 )
		iText.Append(':');
	else if ( iMorseChar.CompareF(_L("-·-·-·")) == 0 )
		iText.Append(';');
	else if ( iMorseChar.CompareF(_L("-···-")) == 0 )
		iText.Append('=');
	//Fraction bar	-··-·	 // omitted
	else if ( iMorseChar.CompareF(_L("-···-")) == 0 )
		iText.Append('-');
	else if ( iMorseChar.CompareF(_L("··--·-")) == 0 )
		iText.Append('_');
	else if ( iMorseChar.CompareF(_L("·-··-·")) == 0 )
		iText.Append('"');
	else if ( iMorseChar.CompareF(_L("·--·-·")) == 0 )
		iText.Append('@');
	else if ( iMorseChar.CompareF(_L("·-·-")) == 0 )
		iText.Append('ä');
	else if ( iMorseChar.CompareF(_L("·--·-")) == 0 )
		iText.Append('à');
	else if ( iMorseChar.CompareF(_L("-·-··")) == 0 )
		iText.Append('?');
	else if ( iMorseChar.CompareF(_L("----")) == 0 )
		{
		iText.Append('c');
		iText.Append('h');
		}
	else if ( iMorseChar.CompareF(_L("··-··")) == 0 )
		iText.Append('é');
	else if ( iMorseChar.CompareF(_L("--·-·")) == 0 )
		iText.Append('?');
	else if ( iMorseChar.CompareF(_L("-·--·")) == 0 )
		iText.Append('?');
	else if ( iMorseChar.CompareF(_L("·---·")) == 0 )
		iText.Append('?');
	else if ( iMorseChar.CompareF(_L("---·")) == 0 )
		iText.Append('ö');
	else if ( iMorseChar.CompareF(_L("···-·")) == 0 )
		iText.Append('?');
	else if ( iMorseChar.CompareF(_L("··--")) == 0 )
		iText.Append('ü');
	else if ( iMorseChar.CompareF(_L("·-··-·")) == 0 )
		iText.Append('"');
	else if ( iMorseChar.CompareF(_L("··--·")) == 0 )
		iText.Append('!');
//	else if ( iMorseChar.CompareF(_L("")) == 0 )
//		iText.Append('');
	else if ( iMorseChar.CompareF(_L("······")) == 0 ) 	// Error, correct word follows (six or more dots in a row)
		DeleteLetterL();						// Do same as user pressed C key
	else if ( iMorseChar.CompareF(_L("")) != 0 ) 	// for unknown chars (except plain space)
		iText.Append('?');				// show '?'

		iMorseChar.Zero();
		}
	iPreview.Zero();
	UpdateNavipane();
////	iPreviewText->SetTextL(&(iPreview));
////	iMorseText->SetTextL(&(iMorseChar));
	iTitlePane->SetTextL(iMorseChar);
	iLowerText->SetTextL(&(iText));

	DrawNow();
	}

void CMorseTexterContainer::DeleteDotOrDashL()
	{
	// Chop last char but only for current Morse char

	// If Morse char hasn't been processed
	// (i.e. space not yet input, so iMorseChar not yet zeroed),
	// then we can delete the last dot or dash.
	if (iMorseChar.Length() > 0)
		{
		iMorseChar.Delete(iMorseChar.Length()-1, 1);
		}

	// Need to update the preview now
	UpdatePreview();

	// Other cases e.g. If Morse char has just been processed
	// (i.e. space is last char, and iMorseChar has been zeroed),
	// then delete final space from iText
	// todo

////	iMorseText->SetTextL(&(iMorseChar));
	iTitlePane->SetTextL(iMorseChar);
////	iPreviewText->SetTextL(&(iPreview));
//	iLowerText->SetTextL(&(iText));
	DrawNow();
	}


void CMorseTexterContainer::DeleteLetterL()
	{
	// Chop last from iText, and delete any unfinished Morse char
	// Only do this if they're not empty, so we don't remove the default text too early.
	if (iPreview.Length() > 0)
		{
		iPreview.Zero();
////		iPreviewText->SetTextL(&(iPreview));
		}
	if (iMorseChar.Length() > 0)
		{
		iMorseChar.Zero();
////		iMorseText->SetTextL(&(iMorseChar));
		iTitlePane->SetTextL(iMorseChar);
		}
	if (iText.Length() > 0)
		{
		iText.Delete(iText.Length()-1, 1);
		iLowerText->SetTextL(&(iText));
		}
	DrawNow();
	}


void CMorseTexterContainer::ClearAllL()
	{
	// Clear all dots, dashes and text.
	CAknQueryDialog* dlg = new (ELeave) CAknQueryDialog(/**text,*/ CAknQueryDialog::ENoTone);    
	if( dlg->ExecuteLD( R_MORSETEXTER_CLEARALL_QUERY) )
		{
		// LSK = OK
		iPreview.Zero();
		iMorseChar.Zero();
		iSpaces = 0;
		iText.Zero();

////		iPreviewText->SetTextL(&(iPreview));
////		iMorseText->SetTextL(&(iMorseChar));
		iTitlePane->SetTextL(_L("Morse Texter"));

		TBuf<256> text;
		UpdateNavipane();
		iCoeEnv->ReadResource(text, R_MORSETEXTER_LOW_TEXT);
		iLowerText->SetTextL(&(text));
		DrawNow();
		}
	}


void CMorseTexterContainer::UpdatePreview()
	{
	// todo UpdatePreview() and SpaceL() should really share the Morse mappings.
	// need a function that will take a TBuf, check it against the Morse, 
	// and return a TChar. Of course there are some exceptions to handle separately.

	iPreview.Zero();

	// Match up some Morse
	if ( iMorseChar.CompareF(_L("·-")) == 0 )
		iPreview.Append('a');
	else if ( iMorseChar.CompareF(_L("-···")) == 0 )
		iPreview.Append('b');
	else if ( iMorseChar.CompareF(_L("-·-·")) == 0 )
		iPreview.Append('c');
	else if ( iMorseChar.CompareF(_L("-··")) == 0 )
		iPreview.Append('d');
	else if ( iMorseChar.CompareF(_L("·")) == 0 )
		iPreview.Append('e');
	else if ( iMorseChar.CompareF(_L("··-·")) == 0 )
		iPreview.Append('f');
	else if ( iMorseChar.CompareF(_L("--·")) == 0 )
		iPreview.Append('g');
	else if ( iMorseChar.CompareF(_L("····")) == 0 )
		iPreview.Append('h');
	else if ( iMorseChar.CompareF(_L("··")) == 0 )
		iPreview.Append('i');
	else if ( iMorseChar.CompareF(_L("·---")) == 0 )
		iPreview.Append('j');
	else if ( iMorseChar.CompareF(_L("-·-")) == 0 )
		iPreview.Append('k');
	else if ( iMorseChar.CompareF(_L("·-··")) == 0 )
		iPreview.Append('l');
	else if ( iMorseChar.CompareF(_L("--")) == 0 )
		iPreview.Append('m');
	else if ( iMorseChar.CompareF(_L("-·")) == 0 )
		iPreview.Append('n');
	else if ( iMorseChar.CompareF(_L("---")) == 0 )
		iPreview.Append('o');
	else if ( iMorseChar.CompareF(_L("·--·")) == 0 )
		iPreview.Append('p');
	else if ( iMorseChar.CompareF(_L("--·-")) == 0 )
		iPreview.Append('q');
	else if ( iMorseChar.CompareF(_L("·-·")) == 0 )
		iPreview.Append('r');
	else if ( iMorseChar.CompareF(_L("···")) == 0 )
		iPreview.Append('s');
	else if ( iMorseChar.CompareF(_L("-")) == 0 )
		iPreview.Append('t');
	else if ( iMorseChar.CompareF(_L("··-")) == 0 )
		iPreview.Append('u');
	else if ( iMorseChar.CompareF(_L("···-")) == 0 )
		iPreview.Append('v');
	else if ( iMorseChar.CompareF(_L("·--")) == 0 )
		iPreview.Append('w');
	else if ( iMorseChar.CompareF(_L("-··-")) == 0 )
		iPreview.Append('x');
	else if ( iMorseChar.CompareF(_L("-·--")) == 0 )
		iPreview.Append('y');
	else if ( iMorseChar.CompareF(_L("--··")) == 0 )
		iPreview.Append('z');
	else if ( iMorseChar.CompareF(_L("-----")) == 0 )
		iPreview.Append('0');
	else if ( iMorseChar.CompareF(_L("·----")) == 0 )
		iPreview.Append('1');
	else if ( iMorseChar.CompareF(_L("··---")) == 0 )
		iPreview.Append('2');
	else if ( iMorseChar.CompareF(_L("···--")) == 0 )
		iPreview.Append('3');
	else if ( iMorseChar.CompareF(_L("····-")) == 0 )
		iPreview.Append('4');
	else if ( iMorseChar.CompareF(_L("·····")) == 0 )
		iPreview.Append('5');
	else if ( iMorseChar.CompareF(_L("-····")) == 0 )
		iPreview.Append('6');
	else if ( iMorseChar.CompareF(_L("--···")) == 0 )
		iPreview.Append('7');
	else if ( iMorseChar.CompareF(_L("---··")) == 0 )
		iPreview.Append('8');
	else if ( iMorseChar.CompareF(_L("----·")) == 0 )
		iPreview.Append('9');
	else if ( iMorseChar.CompareF(_L("·-·-·-")) == 0 )
		iPreview.Append('.');
	else if ( iMorseChar.CompareF(_L("--··--")) == 0 )
		iPreview.Append(',');
	else if ( iMorseChar.CompareF(_L("··--··")) == 0 )
		iPreview.Append('!');
	else if ( iMorseChar.CompareF(_L("-·-·--")) == 0 )
		iPreview.Append('!');
	else if ( iMorseChar.CompareF(_L("-··-·")) == 0 )
		iPreview.Append('/');

	// This is the Morse for both opening & closing parentheses:
	//Parentheses ( )	-·--·-	
	else if ( iMorseChar.CompareF(_L("-·--·-")) == 0 )
		{
		if (iOpenParenthesis)
			iPreview.Append(')');
		else
			iPreview.Append('(');
		// Only toggle iOpenParenthesis in SpaceL()
		}

	//Ampersand [&]	· ···	// contains a space so omitted for now
	else if ( iMorseChar.CompareF(_L("·----·")) == 0 )
		iPreview.Append('\'');
	else if ( iMorseChar.CompareF(_L("---··")) == 0 )
		iPreview.Append(':');
	else if ( iMorseChar.CompareF(_L("-·-·-·")) == 0 )
		iPreview.Append(';');
	else if ( iMorseChar.CompareF(_L("-···-")) == 0 )
		iPreview.Append('=');
	//Fraction bar	-··-·	 // omitted
	else if ( iMorseChar.CompareF(_L("-···-")) == 0 )
		iPreview.Append('-');
	else if ( iMorseChar.CompareF(_L("··--·-")) == 0 )
		iPreview.Append('_');
	else if ( iMorseChar.CompareF(_L("·-··-·")) == 0 )
		iPreview.Append('"');
	else if ( iMorseChar.CompareF(_L("·--·-·")) == 0 )
		iPreview.Append('@');
	else if ( iMorseChar.CompareF(_L("·-·-")) == 0 )
		iPreview.Append('ä');
	else if ( iMorseChar.CompareF(_L("·--·-")) == 0 )
		iPreview.Append('à');
	else if ( iMorseChar.CompareF(_L("-·-··")) == 0 )
		iPreview.Append('?');
	else if ( iMorseChar.CompareF(_L("----")) == 0 )
		{
		iPreview.Append('c');
		iPreview.Append('h');
		}
	else if ( iMorseChar.CompareF(_L("··-··")) == 0 )
		iPreview.Append('é');
	else if ( iMorseChar.CompareF(_L("--·-·")) == 0 )
		iPreview.Append('?');
	else if ( iMorseChar.CompareF(_L("-·--·")) == 0 )
		iPreview.Append('?');
	else if ( iMorseChar.CompareF(_L("·---·")) == 0 )
		iPreview.Append('?');
	else if ( iMorseChar.CompareF(_L("---·")) == 0 )
		iPreview.Append('ö');
	else if ( iMorseChar.CompareF(_L("···-·")) == 0 )
		iPreview.Append('?');
	else if ( iMorseChar.CompareF(_L("··--")) == 0 )
		iPreview.Append('ü');
	else if ( iMorseChar.CompareF(_L("·-··-·")) == 0 )
		iPreview.Append('"');
	else if ( iMorseChar.CompareF(_L("··--·")) == 0 )
		iPreview.Append('!');
	else if ( iMorseChar.CompareF(_L("······")) == 0 ) 	// Error, correct word follows (six or more dots in a row)
		{
		iPreview.Append('<');
		iPreview.Append('d');
		iPreview.Append('e');
		iPreview.Append('l');
		iPreview.Append('>');
		}
//	else if ( iMorseChar.CompareF(_L("")) == 0 )
//		iPreview.Append('');
	else if ( iMorseChar.CompareF(_L("")) != 0 ) 	// for unknown chars (except plain space)
		iPreview.Append('?');				// show '?'

	// Update the navipane with the preview
	UpdateNavipane();
	}


void CMorseTexterContainer::UpdateNavipane()
	{
	// Show preview in navipane
	CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
	iNaviPane = (CAknNavigationControlContainer*)sp->ControlL( TUid::Uid(EEikStatusPaneUidNavi) );
	iNaviPane ->Pop();

	if (iNaviDecorator) delete iNaviDecorator;
	iNaviDecorator = NULL;

	iNaviDecorator = iNaviPane->CreateNavigationLabelL(iPreview);
	iNaviPane->PushL(*iNaviDecorator);
	}


void CMorseTexterContainer::SendViaSmsL()
	{
	if(iSendUi)
		{
		CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
		CleanupStack::PushL(paraFormatLayer);

		CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
		CleanupStack::PushL(charFormatLayer);

		CRichText* messageBodyContent = CRichText::NewL(paraFormatLayer, charFormatLayer); 
		CleanupStack::PushL(messageBodyContent);

		// this is the content of the message
		TRAPD(error, messageBodyContent->InsertL(0, iText));

		iSendUi->CreateAndSendMessageL(KUidMsgTypeSMS, messageBodyContent);
		CleanupStack::PopAndDestroy(3); // messageBodyContent, charFormatLayer, paraFormatLayer
		}
	}


/*
void CMorseTexterContainer::SendViaL(TInt aMtmUid)
	{
#ifdef __WINS__
	_LIT (KTempDir,"\\System\\Apps\\MorseTexter\\");
	TFileName tempDir( KTempDir );
#else
	_LIT (KTempDir,"C:\\System\\Apps\\MorseTexter\\");
	TFileName tempDir( KTempDir );
	CompleteWithAppPath(tempDir);
#endif

	RFs fs; 
	fs.Connect();
	CleanupClosePushL(fs);

	// Write text to a temporary file
	RFile tempFile;
	TFileName uniqueFilename;
	TInt error = tempFile.Temp(fs, KTempDir, uniqueFilename, EFileWrite);
        if ( KErrNone == error )
		{
		error = tempFile.Write(iText);
		if ( KErrNone == error )
			error = tempFile.Flush();
		tempFile.Close();
		}
	CleanupStack::PopAndDestroy(); // RFs 

	CDesC16ArrayFlat *array = new (ELeave) CDesC16ArrayFlat(1);
	CleanupStack::PushL(array);

	// Apend the full pathname
	array->AppendL(uniqueFilename);

	iSendUi->CreateAndSendMessageL (aMtmUid, 0, array);

	CleanupStack::PopAndDestroy(); // array
	}
*/


void CMorseTexterContainer::ShowMorseCodeGuideL()
	{
	// todo Check which drive html file is installed on 
	// (i.e. same as app), and load it from there.
	// Then update pkg file to install html to !: and not C:

	if (CheckForFile(KHtmlFilename) == KErrNone)
		{
		// If local file, use file:// and forward slashes
		HBufC* param = HBufC::NewLC( 50 );
		param->Des().Copy( _L( "4 file://c:/system/apps/morsetexter/morsecode.html" ) );

		// Wap Browser's constants UId
		const TInt KWmlBrowserUid = 0x10008D39;
		TUid id( TUid::Uid( KWmlBrowserUid ) );
		TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
		TApaTask task = taskList.FindApp( id );
		if ( task.Exists() )
			{
			HBufC8* param8 = HBufC8::NewLC( param->Length() );
			param8->Des().Append( *param );
			task.SendMessage( TUid::Uid( 0 ), *param8 ); // Uid is not used
			CleanupStack::PopAndDestroy(param8);
			}
		else
			{
			RApaLsSession appArcSession;
			User::LeaveIfError(appArcSession.Connect()); // connect to AppArc server
			TThreadId id;
			appArcSession.StartDocument( *param, TUid::Uid( KWmlBrowserUid ), id );
			appArcSession.Close();
			}
		CleanupStack::PopAndDestroy(param);
		}
	}


void CMorseTexterContainer::ToggleSound()
	{
	if (iBeepOn)
		iBeepOn = EFalse;
	else
		iBeepOn = ETrue;
	}

TBool CMorseTexterContainer::IsSoundOn()
	{
	return iBeepOn;
	}

void CMorseTexterContainer::SendViaBtL()
	{
	if(iSendUi)
		{
		TFileName sisFile( KSisFilename );  
	#ifndef __WINS__
		CompleteWithAppPath(sisFile);
	#endif

		if (CheckForFile(sisFile) == KErrNone)
			{
			CDesC16ArrayFlat *array = new (ELeave) CDesC16ArrayFlat(1);
			CleanupStack::PushL(array);

			// Apend the full pathname
			array->AppendL(sisFile);

			iSendUi->CreateAndSendMessageL (KSenduiMtmBtUid, 0, array);

			CleanupStack::PopAndDestroy(); // array
			}
		}
	}

TInt CMorseTexterContainer::CheckForFile(const TDesC& aFileName)
	{
	RFs fileSession;
	User::LeaveIfError(fileSession.Connect());
	CleanupClosePushL(fileSession);

	TUint dummyAttributes;
	TInt error = fileSession.Att(aFileName, dummyAttributes);

	CleanupStack::PopAndDestroy(); // close fileSession

	return error;
	}

// End of File  
