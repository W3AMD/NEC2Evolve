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
	TLabel *Label2;
	TEdit *Edit1;
	TUpDown *MaxHeight;
	TLabel *Label3;
	TEdit *Edit2;
	TUpDown *MaxXSize;
	TEdit *Edit3;
	TUpDown *MaxYSize;
	TEdit *Edit4;
	TUpDown *MinHeight;
	TLabel *Label4;
	TUpDown *FeedHeight;
	TEdit *Edit5;
	TLabel *Label5;
private:	// User declarations
public:		// User declarations
	__fastcall TDesignForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDesignForm *DesignForm;
//---------------------------------------------------------------------------
#endif
