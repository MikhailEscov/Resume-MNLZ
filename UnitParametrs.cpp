//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitParametrs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ParametrFClass::ParametrFClass(){
this->IsAuto=1;
this->F=0;
this->Fmax=10;
this->Fzd=5;
this->Klapan=0;
this->KlapanMax=10000;
}
ParametrFClass::~ParametrFClass(){
}
//---------------------------------------------------------------------------
void ParametrFClass::OneMoreMoment(){
if((this->IsAuto)&&(this->IsOn)){
	/*if(this->Klapan<=0){
		//this->Klapan=this->F/this->Fmax*1000;
		this->Klapan=1;
	}*/

	int i=1, temp=this->KlapanMax/10;
	float gisterezis;
	while(temp>=1){
		gisterezis=this->Fmax/pow(10,(float)i++);
		gisterezis*=temp==1?0.7:1;
		if((this->F>this->Fzd+gisterezis+(1e-8))&&
		(this->Klapan>=temp)){
			this->Klapan-=temp;
			break;
		}else if((this->F<this->Fzd-gisterezis-(1e-8))&&
		(this->Klapan<=this->KlapanMax-temp)){
			this->Klapan+=temp;
			break;
		}
		temp/=10;
	}
}
this->Simulation();
}
//---------------------------------------------------------------------------
void ParametrFClass::Simulation(){
if((this->Klapan>0)&&(this->IsOn)){
	this->F=((float)this->Klapan/10000*this->Fmax);//+(std::random(2)==1?1:-1)*((float)std::random(100)/10000000);
	if(this->F<0-(1e-8)){
		this->F=((float)std::random(100)/10000);
	}else if(this->F>this->Fmax+(1e-8)){
		this->F=this->Fmax-((float)std::random(100)/10000);
	}
}else{
	this->F=0;
}
}
//---------------------------------------------------------------------------
float ParametrFClass::GetF(){
return this->F;
}
//---------------------------------------------------------------------------
float ParametrFClass::GetFzd(){
return this->Fzd;
}
//---------------------------------------------------------------------------
int ParametrFClass::GetKlapan(){
return this->Klapan;
}
//---------------------------------------------------------------------------
bool ParametrFClass::GetAutoMode(){
return this->IsAuto;
}
//---------------------------------------------------------------------------
void ParametrFClass::SetFzd(float newFzd){
if(newFzd>0-(1e-8)){
	this->Fzd=newFzd;
}
}
//---------------------------------------------------------------------------
void ParametrFClass::SetKlapan(int newKlapan){
if((newKlapan>=0)&&(newKlapan<=10000)){
	this->Klapan=newKlapan;
}
}
//---------------------------------------------------------------------------
void ParametrFClass::SetAutoMode(bool newIsAuto){
this->IsAuto=newIsAuto;
}
//---------------------------------------------------------------------------
void ParametrFClass::SetFmax(float newFmax){
if(newFmax>0-(1e-8)){
	this->Fmax=newFmax;
}
}
//---------------------------------------------------------------------------
void ParametrFClass::SetIsOn(bool newIsOn){
/*if((!this->IsOn)&&(newIsOn)){//вкл
}else if((this->IsOn)&&(!newIsOn)){//выкл
}*/
this->IsOn=newIsOn;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
ParametrFKoefClass::ParametrFKoefClass(){
this->IsAuto=1;
this->F=0;
this->Fmax=80;
this->Fzd=0;
this->KoefZd=23;
this->Klapan=0;
}
ParametrFKoefClass::~ParametrFKoefClass(){
}
//---------------------------------------------------------------------------
void ParametrFKoefClass::OneMoreMoment(float Fvoda){
if((this->IsAuto)&&(this->IsOn)){
//float Koef=this->F/Fvoda;
this->Fzd=Fvoda*this->KoefZd;

	if(this->Klapan<=0){
		//this->Klapan=this->F/this->Fmax*1000;
		this->Klapan=1;
	}

	int i=1, temp=this->KlapanMax/10;
	float gisterezis;
	while(temp>=1){
		gisterezis=this->Fmax/pow(10,(float)i++);
		if((this->F>this->Fzd+gisterezis+(1e-8))&&
		(this->Klapan>temp)){
			this->Klapan-=temp;
			break;
		}else if((this->F<this->Fzd-gisterezis-(1e-8))&&
		(this->Klapan<this->KlapanMax-temp)){
			this->Klapan+=temp;
			break;
		}
		temp/=10;
	}
}
this->Simulation();
}
//---------------------------------------------------------------------------
void ParametrFKoefClass::SetKoefzd(float newKoefzd){
this->KoefZd=newKoefzd;
}
//---------------------------------------------------------------------------


