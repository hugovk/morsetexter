/*
MorseTexterDocument.h

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

#ifndef MORSETEXTERDOCUMENT_H
#define MORSETEXTERDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CMorseTexterDocument application class.
*/
class CMorseTexterDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        * @param aApp Reference to Application class object
        */
        static CMorseTexterDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CMorseTexterDocument();

    public: // New functions

    public: // Functions from base classes

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * C++ default constructor.
        * @param aApp Reference to Application class object
        */
        CMorseTexterDocument(CEikApplication& aApp);

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CMorseTexterAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif    // MORSETEXTERDOCUMENT_H

// End of File

