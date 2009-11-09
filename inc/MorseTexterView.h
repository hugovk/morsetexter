/*
MorseTexterView.h

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

#ifndef MORSETEXTERVIEW_H
#define MORSETEXTERVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewId = {1};
const TInt KLengthOfMsgStringInView = 1024;

// FORWARD DECLARATIONS
class CMorseTexterContainer;

// CLASS DECLARATION

/**
*  CMorseTexterView view class.
* 
*/
class CMorseTexterView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        * @param aResId Resource ID used to create the view
        */
        void ConstructL(TInt aResId);

        /**
        * Destructor.
        */
        virtual ~CMorseTexterView();

    public: // Functions from base classes
        
        /**
        * From CAknView, return Uid.
        * @return Uid Uid value
        */
        TUid Id() const;

        /**
        * From CAknView, takes care of command handling.
        * @param aCommand Command
        */
        void HandleCommandL(TInt aCommand);

    public:
        /** 
        * From MEikMenuObserver
        * @param aResourceId Menu pane resource ID
        * @param aMenuPane Menu pane pointer
        */
        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

    private:

        /**
        * From CAknExView, activate an AknView.
        * @param aPrevViewId Specified TVwsViewId
        * @param aCustomMessageId Specified TUid
        * @param aCustomMessage Specified TDesC8
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From AknView, deactivate an AknView
        */
        void DoDeactivate();

    public:
        TBuf<KLengthOfMsgStringInView>            iMorseMsg;
        TBuf<KLengthOfMsgStringInView>            iPreviewMsg;
        TBuf<KLengthOfMsgStringInView>            iLowerMsg;
    private: // Data
        CMorseTexterContainer* iContainer;

    };

#endif    // MORSETEXTERVIEW_H

// End of File
