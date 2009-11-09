// From http://www2.symbian.com/faq.nsf/0/0F1464EE96E737E780256D5E00503DD1?OpenDocument

#ifndef BEEP_H
#define BEEP_H

#include <MdaAudioTonePlayer.h>

class CBeep : public CBase, public MMdaAudioToneObserver
	{
public:
	static CBeep* NewL(TInt aFrequency,  TTimeIntervalMicroSeconds iDuration);
	void Play();
	~CBeep();

private:
	void ConstructL(TInt aFrequency,  TTimeIntervalMicroSeconds iDuration);
	void MatoPrepareComplete(TInt aError);
	void MatoPlayComplete(TInt aError);

private:
	typedef enum TBeepState
		{
		EBeepNotPrepared,
		EBeepPrepared,
		EBeepPlaying
		};

private:
	CMdaAudioToneUtility* iToneUtil;
	TBeepState iState;
	TInt iFrequency;
	TTimeIntervalMicroSeconds iDuration;
};


#endif  // BEEP_H

// End of file
