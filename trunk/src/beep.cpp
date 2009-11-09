// From http://www2.symbian.com/faq.nsf/0/0F1464EE96E737E780256D5E00503DD1?OpenDocument

#include "beep.h"

CBeep::~CBeep()
	{
	delete iToneUtil;
	}

CBeep* CBeep::NewL(TInt aFrequency, TTimeIntervalMicroSeconds aDuration)
	{
	CBeep* self=new (ELeave) CBeep();
	CleanupStack::PushL(self);
	self->ConstructL(aFrequency, aDuration);
	CleanupStack::Pop();
	return self;
	};

void CBeep::ConstructL(TInt aFrequency, TTimeIntervalMicroSeconds aDuration)
	{
	iToneUtil=CMdaAudioToneUtility::NewL(*this);
	iState=EBeepNotPrepared;
	iFrequency=aFrequency;
	iDuration=aDuration;
	iToneUtil->PrepareToPlayTone(iFrequency,iDuration);
	}

void CBeep::Play()
	{
	if (iState!=EBeepNotPrepared)
		{
		if (iState==EBeepPlaying) 
			{
			iToneUtil->CancelPlay();
			iState=EBeepPrepared;
			}
		}
		iToneUtil->Play();
		iState=EBeepPlaying;
	}

void CBeep::MatoPrepareComplete(TInt aError)
	{
	if (aError==KErrNone)
		iState=EBeepPrepared;
	}

void CBeep::MatoPlayComplete(TInt aError)
	{
	iState=EBeepPrepared;
	}

// End of file
