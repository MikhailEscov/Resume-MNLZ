//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitWaterZVO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
WaterDropClass::WaterDropClass(){
this->Exist=0;
this->Speed=1;
this->t=0;
this->Top=this->StartTop=0;
this->Left=this->StartLeft=0;
this->X=0;
this->Y=0;
this->Angle=45;
this->DistanceAll=5;
this->Color=(TColor)RGB(0,0,255);
}
//---------------------------
WaterDropClass::~WaterDropClass(){
}
//---------------------------------------------------------------------------
void WaterDropClass::OneMoreMoment(bool gravity){
if(this->Exist){
	this->X+=this->Speed*cos(this->Angle*3.14159265358979f/180);
	this->Y-=this->Speed*sin(this->Angle*3.14159265358979f/180)-(gravity?this->t*9.8:0);
	this->Top=this->Y;
	this->Left=this->X;
	float tempX,tempY;
	tempX=this->Left-this->StartLeft;
	tempY=this->Top-this->StartTop;
	if(sqrt(tempX*tempX+tempY*tempY)>this->DistanceAll+(1e-8)){
		this->Exist=0;
		this->Color=(TColor)RGB(255,255,255);
	}
	this->t+=0.01;
}
}
//---------------------------------------------------------------------------
void WaterDropClass::StartToFly(int RGBlue,float newAngle,float newSpeed,float newDistanceAll,int newStartLeft,int newStartTop){
this->Exist=1;
this->t=0;
this->Y=this->StartTop=newStartTop;
this->X=this->StartLeft=newStartLeft;
this->Color=(TColor)RGB(0,0,RGBlue);
this->Angle=newAngle;
this->Speed=newSpeed*1.5;
this->DistanceAll=newDistanceAll;
}
//---------------------------------------------------------------------------
bool WaterDropClass::GetExist(){
return this->Exist;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
WaterSpawnPointClass::WaterSpawnPointClass(){
this->Angle=0;
this->AngleDiapazone=30;
this->DistanceMin=5;
this->DistanceMax=25;
this->RGBlueRange=100;
}
//----------------------------
WaterSpawnPointClass::~WaterSpawnPointClass(){
}
//---------------------------------------------------------------------------
void WaterSpawnPointClass::OneMoreMoment(int NumberDropsCreate){
int NeedCreate=NumberDropsCreate;
if(NeedCreate>0){
int RGBlue;
float Angle,Speed,Distance;
	for(std::vector<WaterDropClass>::iterator it = this->WaterDropVector->begin() ; it != this->WaterDropVector->end(); ++it){
		if(!it->GetExist()){
			RGBlue=255-random(this->RGBlueRange);
			Angle=this->Angle-this->AngleDiapazone/2+random(this->AngleDiapazone);
			Speed=random(10)<7 ? 0.5+(float)random(10)/10 : 1;
			Distance=this->DistanceMin+(1.5-Speed)/1.5*(this->DistanceMax-this->DistanceMin);
			it->StartToFly(RGBlue,Angle,Speed,Distance,this->Left,this->Top);
			NeedCreate--;
		}
		if(NeedCreate<=0){
			break;
		}
	}
	while(NeedCreate>0){
		RGBlue=255-random(this->RGBlueRange);
		Angle=this->Angle-this->AngleDiapazone/2+random(this->AngleDiapazone);
		Speed=random(10)<3 ? 0.5+(float)random(20)/10 : 1;
		Distance=this->DistanceMin+random(this->DistanceMax-this->DistanceMin);
		WaterDropClass WaterDrop;
		WaterDrop.StartToFly(RGBlue,Angle,Speed,Distance,this->Left,this->Top);
		this->WaterDropVector->push_back(WaterDrop);
		NeedCreate--;
	}
}
}
//---------------------------------------------------------------------------
void WaterSpawnPointClass::SetParams(int newRGBlueRange,float newAngle,float newAngleDiapazone,float newDistanceMin,float newDistanceMax){
this->RGBlueRange=newRGBlueRange;
this->Angle=newAngle;
this->AngleDiapazone=newAngleDiapazone;
if((newDistanceMax>newDistanceMin-(1e-8))&&(newDistanceMin>(1e-8))){
	this->DistanceMin=newDistanceMin;
	this->DistanceMax=newDistanceMax;
}
}
//---------------------------------------------------------------------------
