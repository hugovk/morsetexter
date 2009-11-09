/*
MorseTexterDocument.cpp

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
#include "MorseTexterDocument.h"
#include "MorseTexterAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can not contain any code, that 
// might leave.
//
CMorseTexterDocument::CMorseTexterDocument(CEikApplication& aApp)
                       : CEikDocument(aApp)
    {
    }

// EPOC default constructor can leave.
void CMorseTexterDocument::ConstructL()
    {
    }

// Two-phased constructor.
CMorseTexterDocument* CMorseTexterDocument::NewL(CEikApplication& aApp)     // CMorseTexterApp reference
    {
    CMorseTexterDocument* self = new (ELeave) CMorseTexterDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// destructor
CMorseTexterDocument::~CMorseTexterDocument()
    {
    }

// ----------------------------------------------------
// CMorseTexterDocument::CreateAppUiL()
// constructs CMorseTexterAppUi
//
// ----------------------------------------------------
CEikAppUi* CMorseTexterDocument::CreateAppUiL()
    {
    return new(ELeave) CMorseTexterAppUi;
    }

// End of File  
