//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "UnitParametrs.h"
#include "UnitWaterZVO.h"
#include <fstream.h>
#include <Vcl.Graphics.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabeledEdit *LabeledEdit1;
	TLabel *Label2;
	TTrackBar *TrackBar1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TTrackBar *TrackBar2;
	TLabel *Label3;
	TLabeledEdit *LabeledEdit2;
	TLabel *Label4;
	TGroupBox *GroupBox2;
	TRadioGroup *RadioGroup1;
	TLabel *Label5;
	TLabeledEdit *LabeledEdit3;
	TLabel *Label6;
	TTrackBar *TrackBar3;
	TCheckBox *CheckBox3;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox3;
	TTrackBar *TrackBar4;
	TLabel *Label7;
	TTimer *Timer1;
	TLabel *Label8;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TRadioGroup *RadioGroup2;
	TRadioGroup *RadioGroup3;
	TLabel *Label9;
	TButton *Button4;
	TImage *Image1;
	TImage *Image2;
	TButton *Button3;
	TChart *Chart1;
	TLineSeries *Series1;
	TCheckBox *CheckBox6;
	TRadioGroup *RadioGroup4;
	TLineSeries *Series2;
	TCheckBox *CheckBox7;
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall TrackBar4Change(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall LabeledEdit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit3KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall RadioGroup4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
