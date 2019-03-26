//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <deque>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
ParametrFClass MagistralVoda;
ParametrFKoefClass MagistralVozduh;
ParametrFClass ZonaZVO[18];//1r 1R 2r 2R 3r 3R 4r 4R 5r 5R 6r 6R 7r 7R 8r 8R 9r 9R
bool IsOn=0, ReadDataOk=0;
unsigned int t=0,MaxDots=100;
float Ftabldata[18][21][3][3];//зона/скорость/марк ст/режим/

struct GrafArhSTR{
	int t;
	float dataF[18];
	float dataZD[18];
};
std::deque<GrafArhSTR> GrafDeque;

std::vector<WaterDropClass>WaterDropVector;
WaterSpawnPointClass WaterSpawnPoints[18];

void FormingZD();
void UpdateUI();
float CalcTZgot();
void fixKey(TObject *Sender, System::WideChar &Key);
bool read_data();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
DoubleBuffered=1;
randomize();
if(FileExists("zvo.bmp")){
	Form1->Image2->Picture->LoadFromFile("data/img/zvo.bmp");
}
for(int i=0;i<18;i++){
	ZonaZVO[i].SetFmax(4);
	ZonaZVO[i].SetFzd(1);
	WaterSpawnPoints[i].WaterDropVector=&WaterDropVector;
	WaterSpawnPoints[i].SetParams(100, i%2==0?270:90, 60, 40, 50);
//(int newRGBlueRange,float newAngle,float newAngleDiapazone,
//float newDistanceMin,float newDistanceMax)
}

WaterSpawnPoints[0].Left=110;
WaterSpawnPoints[0].Top=67;
WaterSpawnPoints[1].Left=5;
WaterSpawnPoints[1].Top=67;
WaterSpawnPoints[2].Left=110;
WaterSpawnPoints[2].Top=95;
WaterSpawnPoints[3].Left=5;
WaterSpawnPoints[3].Top=95;
WaterSpawnPoints[4].Left=120;
WaterSpawnPoints[4].Top=127;
WaterSpawnPoints[5].Left=12;
WaterSpawnPoints[5].Top=153;
WaterSpawnPoints[6].Left=147;
WaterSpawnPoints[6].Top=147;
WaterSpawnPoints[7].Left=57;
WaterSpawnPoints[7].Top=227;
WaterSpawnPoints[8].Left=180;
WaterSpawnPoints[8].Top=154;
WaterSpawnPoints[9].Left=180;
WaterSpawnPoints[9].Top=257;
WaterSpawnPoints[10].Left=222;
WaterSpawnPoints[10].Top=154;
WaterSpawnPoints[11].Left=226;
WaterSpawnPoints[11].Top=257;
WaterSpawnPoints[12].Left=261;
WaterSpawnPoints[12].Top=154;
WaterSpawnPoints[13].Left=260;
WaterSpawnPoints[13].Top=257;
WaterSpawnPoints[14].Left=298;
WaterSpawnPoints[14].Top=154;
WaterSpawnPoints[15].Left=297;
WaterSpawnPoints[15].Top=257;
WaterSpawnPoints[16].Left=333;
WaterSpawnPoints[16].Top=154;
WaterSpawnPoints[17].Left=335;
WaterSpawnPoints[17].Top=257;

WaterSpawnPoints[0].SetParams(100, 180, 40, 40, 50);
WaterSpawnPoints[2].SetParams(100, 180, 40, 40, 50);
WaterSpawnPoints[4].SetParams(100, 225, 90, 40, 50);

WaterSpawnPoints[1].SetParams(100, 0, 40, 40, 50);
WaterSpawnPoints[3].SetParams(100, 0, 40, 40, 50);
WaterSpawnPoints[5].SetParams(100, 25, 90, 40, 50);
WaterSpawnPoints[7].SetParams(100, 45, 90, 40, 50);

MagistralVoda.SetFmax(800);
MagistralVoda.SetFzd(72);
MagistralVozduh.SetFmax(800*25);
MagistralVozduh.SetFzd(72*23);
ReadDataOk=read_data();
Form1->CheckBox5->Checked=ReadDataOk;
Form1->CheckBox5->Enabled=ReadDataOk;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
MagistralVoda.OneMoreMoment();
MagistralVozduh.OneMoreMoment(MagistralVoda.GetF());

float FmaxZone=MagistralVoda.GetF()/18;
for(int i=0;i<18;i++){
	ZonaZVO[i].SetFmax(FmaxZone);
}

if(IsOn){
	GrafArhSTR GrafArh;
	GrafArh.t=t++;
	for(int i=0;i<18;i++){
		ZonaZVO[i].OneMoreMoment();
		WaterSpawnPoints[i].OneMoreMoment(ZonaZVO[i].GetF()/45*30);
		GrafArh.dataF[i]=ZonaZVO[i].GetF();
		GrafArh.dataZD[i]=ZonaZVO[i].GetFzd();
	}
	GrafDeque.push_back(GrafArh);

	while(GrafDeque.size()>MaxDots){
		GrafDeque.pop_front();
	}
}

for(std::vector<WaterDropClass>::iterator it = WaterDropVector.begin() ; it != WaterDropVector.end(); ++it){
	it->OneMoreMoment(Form1->CheckBox7->Checked);
}

FormingZD();
UpdateUI();
}
//---------------------------------------------------------------------------
void FormingZD(){
if((Form1->CheckBox5->Checked)&&(ReadDataOk)){
	for(int i=0;i<18;i++){
		ZonaZVO[i].SetFzd(0.06*Ftabldata[i][Form1->TrackBar4->Position][Form1->RadioGroup2->ItemIndex][Form1->RadioGroup3->ItemIndex]);
		//Ftabldata[18][20][3][3];//зона/скорость/марк ст/режим/
	}
}
if(Form1->CheckBox4->Checked){
	float ZonsFmax=0;
	for(int i=0;i<18;i++){
		if(ZonaZVO[i].GetFzd()>ZonsFmax+(1e-8)){
			ZonsFmax=ZonaZVO[i].GetFzd();
		}
	}
	MagistralVoda.SetFzd(ZonsFmax*18);
	MagistralVozduh.SetFzd(23*MagistralVoda.GetF());
}
}
//---------------------------------------------------------------------------
void UpdateUI(){
Form1->Label1->Caption=Form1->Label1->Caption.sprintf(L"Fвода (м3/ч) = %0.2f",MagistralVoda.GetF());
Form1->Label4->Caption=Form1->Label4->Caption.sprintf(L"Fвоздух (м3/ч) = %0.2f",MagistralVozduh.GetF());
if(fabs(MagistralVoda.GetF())>(1e-8)){
	Form1->Label9->Caption=Form1->Label9->Caption.sprintf(L"Коэфф возд. = %0.1f",MagistralVozduh.GetF()/MagistralVoda.GetF());
}
Form1->Label2->Caption=L"Клапан Fвода (%) = "+FloatToStr((float)MagistralVoda.GetKlapan()/100);
Form1->Label3->Caption=L"Клапан Fводух (%) = "+FloatToStr((float)MagistralVozduh.GetKlapan()/100);
Form1->TrackBar1->Position=MagistralVoda.GetKlapan();
Form1->TrackBar2->Position=MagistralVozduh.GetKlapan();
Form1->CheckBox1->Checked=MagistralVoda.GetAutoMode();
Form1->CheckBox2->Checked=MagistralVozduh.GetAutoMode();
if(Form1->CheckBox4->Checked){
	Form1->LabeledEdit1->Text=FloatToStrF(MagistralVoda.GetFzd(),ffFixed,9,2);
	if(MagistralVoda.GetFzd()>(1e-8)){
		Form1->LabeledEdit2->Text=FloatToStrF(MagistralVozduh.GetFzd()/MagistralVoda.GetFzd(),ffFixed,9,2);
	}else{
		Form1->LabeledEdit2->Text=FloatToStrF(0,ffFixed,9,2);
	}
}

Form1->Label5->Caption=Form1->Label5->Caption.sprintf(L"Fвода (м3/ч) = %0.4f",ZonaZVO[Form1->RadioGroup1->ItemIndex].GetF());
Form1->Label6->Caption=L"Клапан Fвода (%) = "+FloatToStr((float)ZonaZVO[Form1->RadioGroup1->ItemIndex].GetKlapan()/100);
Form1->TrackBar3->Position=ZonaZVO[Form1->RadioGroup1->ItemIndex].GetKlapan();
Form1->CheckBox3->Checked=ZonaZVO[Form1->RadioGroup1->ItemIndex].GetAutoMode();
Form1->Label8->Caption=L"Температура заготовки после ЗВО (С) = "+FloatToStr(CalcTZgot());

if(Form1->CheckBox5->Checked){
	Form1->LabeledEdit3->Text=FloatToStrF(ZonaZVO[Form1->RadioGroup1->ItemIndex].GetFzd(),ffFixed,9,2);
}

Form1->Image1->Canvas->FillRect(Rect(0,0,Form1->Image1->Width,Form1->Image1->Height));
for(std::vector<WaterDropClass>::iterator it = WaterDropVector.begin() ; it != WaterDropVector.end(); ++it){
	Form1->Image1->Canvas->Pixels[it->Left][it->Top]=it->Color;
}
//Form1->Caption=WaterDropVector.size();
Form1->Chart1->Series[0]->Clear();
Form1->Chart1->Series[1]->Clear();
//Form1->Chart1->Title="График расхода воздухо-воздушной смеси на секцию ЗВО "+AnsiString(Form1->RadioGroup1->Items[Form1->RadioGroup1->ItemIndex]).c_str();
Form1->Chart1->LeftAxis->Maximum=Form1->CheckBox6->Checked ? (ZonaZVO[Form1->RadioGroup1->ItemIndex].GetF()*2<50-(1e-8)) ? (ZonaZVO[Form1->RadioGroup1->ItemIndex].GetF()*2):50:50;
if(!GrafDeque.empty()){
	std::deque<GrafArhSTR>::iterator it=GrafDeque.begin();
	for (;it!=GrafDeque.end();++it){
		Form1->Chart1->Series[1]->AddXY(it->t,it->dataF[Form1->RadioGroup1->ItemIndex]);
		Form1->Chart1->Series[0]->AddXY(it->t,it->dataZD[Form1->RadioGroup1->ItemIndex]);
	}
}

}
//---------------------------------------------------------------------------
float CalcTZgot(){
return 50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
if(Form1->CheckBox4->Checked){
	Form1->LabeledEdit1->Enabled=0;
	Form1->LabeledEdit2->Enabled=0;
	Form1->Button1->Enabled=0;
	Form1->TrackBar1->Enabled=0;
	Form1->TrackBar2->Enabled=0;
	Form1->CheckBox1->Enabled=0;
	Form1->CheckBox2->Enabled=0;
	Form1->CheckBox1->Checked=1;
	Form1->CheckBox2->Checked=1;
}else{
	Form1->LabeledEdit1->Enabled=1;
	Form1->LabeledEdit2->Enabled=1;
	Form1->Button1->Enabled=1;
	Form1->CheckBox1->Enabled=1;
	Form1->CheckBox2->Enabled=1;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox5Click(TObject *Sender)
{
if(Form1->CheckBox5->Checked){
	Form1->LabeledEdit3->Enabled=0;
	Form1->Button2->Enabled=0;
	Form1->TrackBar3->Enabled=0;
	Form1->CheckBox3->Enabled=0;
	Form1->CheckBox3->Checked=1;
	for(int i=0;i<18;i++){
		ZonaZVO[i].SetAutoMode(Form1->CheckBox3->Checked);
	}
}else{
	Form1->LabeledEdit3->Enabled=1;
	Form1->Button2->Enabled=1;
	Form1->CheckBox3->Enabled=1;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Form1->TrackBar1->Enabled=!Form1->CheckBox1->Checked;
MagistralVoda.SetAutoMode(Form1->CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
Form1->TrackBar2->Enabled=!Form1->CheckBox2->Checked;
MagistralVozduh.SetAutoMode(Form1->CheckBox2->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
Form1->TrackBar3->Enabled=!Form1->CheckBox3->Checked;
ZonaZVO[Form1->RadioGroup1->ItemIndex].SetAutoMode(Form1->CheckBox3->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
Form1->Label7->Caption="Скорость вытягивания (м/мин) = "+FloatToStr(StrToFloat(Form1->TrackBar4->Position)/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
IsOn=!IsOn;
t=0;
for(int i=0;i<18;i++){
	ZonaZVO[i].SetIsOn(IsOn);
}
MagistralVoda.SetIsOn(IsOn);
MagistralVozduh.SetIsOn(IsOn);

Form1->RadioGroup2->Enabled=!IsOn;
Form1->RadioGroup3->Enabled=!IsOn;
if(IsOn){
	GrafDeque.clear();
	Form1->Button3->Caption="Стоп";
}else{
	Form1->Button3->Caption="Запуск";
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
MagistralVoda.SetKlapan(Form1->TrackBar1->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
MagistralVozduh.SetKlapan(Form1->TrackBar2->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
ZonaZVO[Form1->RadioGroup1->ItemIndex].SetKlapan(Form1->TrackBar3->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
MagistralVoda.SetFzd(StrToFloat(Form1->LabeledEdit1->Text));
MagistralVozduh.SetKoefzd(StrToFloat(Form1->LabeledEdit2->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
ZonaZVO[Form1->RadioGroup1->ItemIndex].SetFzd(StrToFloat(Form1->LabeledEdit3->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
UpdateUI();
}
//---------------------------------------------------------------------------
void fixKey(TObject *Sender, System::WideChar &Key){
if ((Key >= '0') && (Key <= '9')){  // цифры
}else if (Key == 8){  // <-
}else if ((Key == '.') || (Key == ',')){ // запятая
	if (((TLabeledEdit*)Sender)->Text.Pos(FormatSettings.DecimalSeparator)!=0){ // если запятая уже есть
		Key = 0;
	}else{ // если ещё нет
		if(((TLabeledEdit*)Sender)->GetTextLen()>0){
			Key = FormatSettings.DecimalSeparator;
		}else{
			Key = 0;
		}
	}
}else Key = 0; // не цифра
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit1KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit2KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit3KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
ReadDataOk=read_data();
Form1->CheckBox5->Enabled=ReadDataOk;
}
//---------------------------------------------------------------------------
bool read_data(){
char *dir;
for(int i_file=0;i_file<9;i_file++){
	for(int j_file=0;j_file<2;j_file++){
		dir=AnsiString("data/"+IntToStr(i_file+1)+(j_file==0?"r":"RR")+".txt").c_str();
		FILE *myfile=fopen(dir,"r");
		if(myfile){
			for(int i_speed=0;i_speed<21;i_speed++){
				for(int i_st=0;i_st<3;i_st++){
					for(int i_mode=0;i_mode<3;i_mode++){
						fscanf(myfile, "%f", &Ftabldata[i_file*2+j_file][i_speed][i_mode][i_st]);
					}
				}
			}
			fclose(myfile);
		}else{
			return 0;
		}
	}
}
return 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup4Click(TObject *Sender)
{
MaxDots=100+Form1->RadioGroup4->ItemIndex*250;
}
//---------------------------------------------------------------------------

