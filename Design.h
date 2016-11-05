//---------------------------------------------------------------------------

#ifndef DesignH
#define DesignH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

//defines used for radio group band choice
#define BAND_160 0
#define BAND_80 1
#define BAND_60 2
#define BAND_40 3
#define BAND_30 4
#define BAND_20 5
#define BAND_17 6
#define BAND_15 7
#define BAND_12 8
#define BAND_10 9
#define BAND_6 10
#define BAND_2 11
#define BAND_1_25 12
#define BAND_70cm 13
#define BAND_33cm 14
#define BAND_23cm 15

#define MIN_HEIGHT_M 3
#define MIN_HEIGHT_CM  3000
#define MAX_HEIGHT_M 30
#define MAX_HEIGHT_CM  30000
//---------------------------------------------------------------------------
class TDesignForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TGroupBox *GroupBox1;
	TCheckBox *Band160;
	TCheckBox *Band80;
	TCheckBox *Band60;
	TCheckBox *Band40;
	TCheckBox *Band30;
	TCheckBox *Band20;
	TCheckBox *Band17;
	TCheckBox *Band15;
	TCheckBox *Band10;
	TCheckBox *Band6;
	TCheckBox *Band2;
	TCheckBox *Band1;
	TCheckBox *Band70cm;
	TRadioGroup *AntennaType;
	TGroupBox *SupportPoints;
	TEdit *NumberSupports;
	TUpDown *MaxSupports;
	TRadioGroup *RadioGroup1;
	TRadioGroup *TunerOptions;
	TLabel *Label1;
	TLabel *MaxHeightLB;
	TEdit *Edit1;
	TUpDown *MaxHeight;
	TLabel *MaxYardSizeLB;
	TEdit *Edit2;
	TUpDown *MaxXSize;
	TEdit *Edit3;
	TUpDown *MaxYSize;
	TEdit *Edit4;
	TUpDown *MinHeight;
	TLabel *MinimumHeightLB;
	TUpDown *FeedHeight;
	TEdit *Edit5;
	TLabel *FeedPointHeightLB;
	TRadioGroup *BandList;
	TCheckBox *NoStraysAllowed;
	void __fastcall BandListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDesignForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDesignForm *DesignForm;
//---------------------------------------------------------------------------
#endif
