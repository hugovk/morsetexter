/*
MorseTexterApp.h

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

#ifndef MORSETEXTERAPP_H
#define MORSETEXTERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// Release UID from Symbian
const TUid KUidMorseTexter = { 0x102078D4 };

// CLASS DECLARATION

/**
* CMorseTexterApp application class.
* Provides factory to create concrete document object.
* 
*/
class CMorseTexterApp : public CAknApplication
    {
    
    private:

        /**
        * From CApaApplication, creates CMorseTexterDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidMorseTexter).
        * @return The value of KUidMorseTexter.
        */
        TUid AppDllUid() const;
    };

#endif    // MORSETEXTERAPP_H

// End of File

