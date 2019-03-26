//---------------------------------------------------------------------------
#include "Unit1.h"
#ifndef UnitParametrsH
#define UnitParametrsH
//---------------------------------------------------------------------------
class ParametrFClass{
protected:
	bool IsOn;
	bool IsAuto;
	float F;
	float Fzd,Fmax;
	int Klapan,KlapanMax;
	void Simulation();
public:
	ParametrFClass();
	~ParametrFClass();
	void OneMoreMoment();

	float GetF();
	float GetFzd();
	bool GetAutoMode();
	int GetKlapan();
	void SetFzd(float newFzd);
	void SetKlapan(int newKlapan);
	void SetAutoMode(bool newIsAuto);
	void SetFmax(float newFmax);
	void SetIsOn(bool newIsOn);
};
//---------------------------------------------------------------------------
class ParametrFKoefClass:public ParametrFClass{
protected:
	float KoefZd;
public:
	ParametrFKoefClass();
	~ParametrFKoefClass();

	void OneMoreMoment(float Fvoda);
	void SetKoefzd(float newKoefzd);
};
#endif
