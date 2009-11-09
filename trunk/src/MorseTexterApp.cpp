/*
MorseTexterApp.cpp

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
#include    "MorseTexterApp.h"
#include    "MorseTexterDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CMorseTexterApp::CreateDocumentL()
// Creates CMorseTexterDocument object
// ---------------------------------------------------------
//
CApaDocument* CMorseTexterApp::CreateDocumentL()
    {
    return CMorseTexterDocument::NewL(*this);
    }

// ---------------------------------------------------------
// CMorseTexterApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CMorseTexterApp::AppDllUid() const
    {
    return KUidMorseTexter;
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CMorseTexterApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CMorseTexterApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

// End of File  

