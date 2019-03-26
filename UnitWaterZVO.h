//---------------------------------------------------------------------------
#include "Unit1.h"
#include <vector>
#ifndef UnitWaterZVOH
#define UnitWaterZVOH
//---------------------------------------------------------------------------
class WaterDropClass{
protected:
	bool Exist;
    float t;
	int StartTop,StartLeft;
	float X,Y,Angle,Speed;
	float DistanceAll;
public:
	int Top,Left;
	TColor Color;
	WaterDropClass();
	~WaterDropClass();
	bool GetExist();
	void OneMoreMoment(bool gravity);
	void StartToFly(int RGBlue,float newAngle,float newSpeed,float newDistanceAll,int newStartLeft,int newStartTop);
};
//---------------------------------------------------------------------------
class WaterSpawnPointClass{
protected:
	float Angle,AngleDiapazone;
	float DistanceMin,DistanceMax;
	int RGBlueRange;

public:
	std::vector<WaterDropClass> *WaterDropVector;
	int Top,Left;
	WaterSpawnPointClass();
	~WaterSpawnPointClass();
	void OneMoreMoment(int NumberDropsCreate);
	void SetParams(int newRGBlueRange,float newAngle,float newAngleDiapazone,float newDistanceMin,float newDistanceMax);
};
//---------------------------------------------------------------------------
#endif
