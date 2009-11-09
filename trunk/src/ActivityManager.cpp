/*
* ============================================================================
*  Name     : CActivityManager
*  Part of  : MorseTexter
* ============================================================================
*/

// INCLUDE FILES
#include "ActivityManager.h"

EXPORT_C CActivityManager* CActivityManager::NewL(MActivityManagerObserver* aObserver, TInt aTimeout)
	{
	CActivityManager* self = new (ELeave) CActivityManager(aObserver, aTimeout);

	CleanupStack::PushL(self);

	self->ConstructL();

	CleanupStack::Pop(self);

	return self;
	}

 

 

CActivityManager::CActivityManager(MActivityManagerObserver* aObserver, TInt aTimeout)

: CActive(CActive::EPriorityHigh), iObserver(aObserver), iTimeout(aTimeout)
	{
	CActiveScheduler::Add(this);
	}

 

 

EXPORT_C CActivityManager::~CActivityManager()
	{
	Cancel();

	iTimer.Close();
	}

 

void CActivityManager::ConstructL()
	{
	iTimer.CreateLocal();
	}

 

EXPORT_C void CActivityManager::SetTimeout(TInt aTimeout)
	{
	iTimeout = aTimeout;

	Reset();
	}

 

EXPORT_C void CActivityManager::Reset()
	{
	Cancel();

	Start();
	}

 

void CActivityManager::DoCancel()
	{

	iTimer.Cancel();

	iWatch = ENone;
	}

EXPORT_C void CActivityManager::Start() 
	{ 

	if (!IsActive()) 
		{ 
		iWatch = EWaitingForInactivity; 

		iTimer.Inactivity(iStatus, iTimeout); 

		SetActive(); 
		} 
	}



void CActivityManager::RunL()
	{
	if (iStatus == KErrNone)
		{
		if (iWatch == EWaitingForInactivity)
			{
			TInt inactivity = User::InactivityTime().Int();

			if (inactivity >= iTimeout)
				{

				if (iObserver)
					iObserver->InactivityDetected();

				if (!IsActive()) //observer might have called a Reset()
					{
					iTimer.Inactivity(iStatus,0);

					iWatch = EWaitingForActivity;
					}
				}
			else
				{
				iTimer.Inactivity(iStatus,iTimeout);
				}

			}

		else if (iWatch == EWaitingForActivity)
			{
			if (iObserver)
				iObserver->ActivityDetected();

			if (!IsActive()) //observer might have called a Reset()
				{
				iTimer.Inactivity(iStatus,iTimeout);

				iWatch = EWaitingForInactivity;
				}

			}

		if (!IsActive()) //observer might have called a Reset()
			{
			SetActive();
			}

		}
	else
		{
		iWatch = ENone;
		}

	}