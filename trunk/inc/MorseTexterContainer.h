/*
MorseTexterContainer.h

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

#ifndef MORSETEXTERCONTAINER_H
#define MORSETEXTERCONTAINER_H

// INCLUDES
#include <aknnavi.h>	// navi pane
#include <akntitle.h> 	// title pane
#include <aknview.h>
//#include <eikedwin.h>
#include <eikgted.h>
#include <sendui.h>
#include <aknnotewrappers.h>
//#include <badesca.h>	// CDesC16Array
//#include <e32keys.h>
//#include <eikmobs.h>
//#include <eikmenub.h>
//#include <f32file.h>
//#include <mmsconst.h>               // for KUidMsgTypeMultimedia
#include <sendnorm.rsg>	// SendUi
#include <senduimtmuids.h>
#include <smut.h>                   // for message type UIDs
#include <txtrich.h>                // for CRichText

const TInt KMorseChar = 6;
const TInt KText = 1024;
const TInt KPreview = 5;

#ifdef __WINS__
_LIT (KSisFilename,         "C:\\System\\Apps\\MorseTexter\\MorseTexter.sis_");
#else
_LIT (KSisFilename,         "\\System\\Apps\\MorseTexter\\morsetexter.sis_");
#endif
_LIT (KHtmlFilename,        "C:\\System\\Apps\\MorseTexter\\morsecode.html");

// FORWARD DECLARATIONS
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CMorseTexterView;
class CBeep;

// CLASS DECLARATION

/**
*  CMorseTexterContainer  container control class.
*  
*/
class CMorseTexterContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        * @param aParent Pointer of parent view for container.
        */
        void ConstructL(const TRect& aRect, CMorseTexterView* aParent);

        /**
        * Destructor.
        */
        ~CMorseTexterContainer();

    public: // New functions

    public: // Functions from base classes

    private: // Functions from base classes CoeControl

       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        * @return Nbr of controls inside this container.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        * @param Index number of the control.
        * @return Pointer of controls inside this container.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

       /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw( const TRect& aRect ) const;

    private: // Functions from base classes MCoeControlObserver
       /**
        * From MCoeControlObserver Handles an event of type aEventType
        * @param aControl Pointer to component control
        * @param aEventType Event code
        */
        // event handling section
        // e.g Listbox events
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
    private: //data
//		CEikEdwin*      iMorseText;
//		CEikEdwin*      iLowerText;
////		CEikGlobalTextEditor*      iMorseText;
////		CEikGlobalTextEditor*      iPreviewText;
		CEikGlobalTextEditor*      iLowerText;

		// Beeps
		TBool iBeepOn;
		CBeep* iDit;
		CBeep* iDah;


public:  // from CCoeControl

/*!
  @function OfferKeyEventL
  
  @discussion Handle any user keypresses
  @param aKeyEvent holds the data for the event that occurred
  @param aType holds the type of key event that occured
  @result a TKeyResponse indicating if the key was consumed or not
  */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

/*!
  @function InputCapabilities
  
  @discussion Return the capabilities of the OfferKeyEventL 
              method for this class
  @result a TCoeInputCapabilities indicating the capabilities 
          for this class
  */
	TCoeInputCapabilities InputCapabilities() const;




public: // new functions

        /**
        * User entered a dot.
        */
        void DotL();

        /**
        * User entered a dash.
        */
        void DashL();

        /**
        * User entered a space.
        */
        void SpaceL();

        /**
        * Delete last dot or dash.
        */
        void DeleteDotOrDashL();

        /**
        * User pressed C key.
        */
        void DeleteLetterL();

        /**
        * Clears all dots, dahbes and text.
        */
        void ClearAllL();

        /**
        * Match some Morse to a character
        */
        void UpdatePreview();

        /**
        * Update the navipane with the preview
        */
	  void UpdateNavipane();

		/*!
		* Send the text via SMS
		*/
		void SendViaSmsL();

		/*!
		@discussion Send the text file via an MTM
		@param aMtmUid UID of the MTM
		*/
		//	void SendViaL(TInt aMtmUid);

        /**
        * Launch local HTML file showing Morse code
        */
        void ShowMorseCodeGuideL();

        /**
        * Toggle the beeps
        */
        void ToggleSound();

        /**
        * Gets beep status
        */
        TBool IsSoundOn();

		/*!
		* Send the app via Bluetooth
	    */
		void SendViaBtL();

		/*!
		@function CheckForFile
  
		@discussion Utility function to check if a file is present
		@param aFileName The file to check
		@result KErrNone means file was found okay
		*/
		TInt CheckForFile(const TDesC& aFileName);

private: // data

	// The dots and dashes of a single character
	TBuf<KMorseChar>  iMorseChar;

	// Tracks how many spaces entered in a row
	TInt iSpaces;

	// To decide when to use opening or closing parentheses
	TBool iOpenParenthesis;

	// The complete alphanumeric text
	TBuf<KText> iText;

	// A preview of character being entered
	TBuf<KPreview> iPreview;

	// Send UI
	CSendAppUi* iSendUi;

	// Title pane to show Morse code
	CAknTitlePane* iTitlePane;

	// Navi pane to show preview
	CAknNavigationControlContainer* iNaviPane;
	CAknNavigationDecorator*        iNaviDecorator;
    };

#endif  // MORSETEXTERCONTAINER_H

// End of File
