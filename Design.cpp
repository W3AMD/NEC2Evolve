//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Design.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDesignForm *DesignForm;
//---------------------------------------------------------------------------
__fastcall TDesignForm::TDesignForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
