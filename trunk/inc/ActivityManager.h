/*
* ============================================================================
*  Name     : ActivityManager.h
*  Part of  : MorseTexter
* ============================================================================
*/

#ifndef ACTIVITYMANAGER_H
#define ACTIVITYMANAGER_H

// INCLUDES
#include <e32base.h>	// CActive
#include <e32std.h>


// CLASS DECLARATION

/////class MactivityManagerObserver
class MActivityManagerObserver
	{

	public :

		virtual void ActivityDetected() = 0;
		virtual void InactivityDetected() = 0;

	};



class CActivityManager : public CActive
	{

	public:

		IMPORT_C static CActivityManager* NewL(MActivityManagerObserver* aObserver, TInt aTimeout = 60);

		IMPORT_C ~CActivityManager();

		IMPORT_C void SetTimeout(TInt aTimeout);

		IMPORT_C void Start();

		IMPORT_C void Reset();

 

	protected: // from CActive

		void DoCancel();

		void RunL();

 

	protected:

		CActivityManager(MActivityManagerObserver* aObserver, TInt aTimeout);

		void ConstructL();

 

	protected:

		enum TWatch { ENone = 0, EWaitingForInactivity, EWaitingForActivity };

	protected:

		RTimer iTimer;

		TWatch iWatch;

		MActivityManagerObserver* iObserver; ///The observer of activity status

		TInt iTimeout; ///Current inactivity period

	};

#endif      //  ACTIVITYMANAGER_H
