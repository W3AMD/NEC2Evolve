// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Design.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDesignForm *DesignForm;

// ---------------------------------------------------------------------------
__fastcall TDesignForm::TDesignForm(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TDesignForm::BandListClick(TObject *Sender) {
	// change the selections based on the band selection
	switch (BandList->ItemIndex) {
	case BAND_160: {
		}
	case BAND_80: {
		}
	case BAND_60: {
		}
	case BAND_40: {
		}
	case BAND_30: {
		}
	case BAND_20: {
		}
	case BAND_17: {
		}
	case BAND_15: {
		}
	case BAND_12: {
		}
	case BAND_10: {
		}
	case BAND_6: {
			// defaults for longer bands
			MinimumHeightLB->Caption = "Minimum Height (m):";
			MaxHeightLB->Caption = "Maximum Height (m):";
			MaxYardSizeLB->Caption = "Max Yard Size (m): x, y";
			FeedPointHeightLB->Caption = "Feed Point Height (m):";
			MinHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			MinHeight->Position = MIN_HEIGHT_M;
			MaxHeight->Position = MAX_HEIGHT_M;
			FeedHeight->Min = MIN_HEIGHT_M;
			FeedHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MinHeight->Position;
			break;
		}
	case BAND_2: {
		}
	case BAND_1_25: {
		}
	case BAND_70cm: {
		}
	case BAND_33cm: {
		}
	case BAND_23cm: {
			// defaults for shorter bands
			MinimumHeightLB->Caption = "Minimum Height (cm):";
			MaxHeightLB->Caption = "Maximum Height (cm):";
			MaxYardSizeLB->Caption = "Max Yard Size (cm): x, y";
			FeedPointHeightLB->Caption = "Feed Point Height (cm):";
			MinHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			FeedHeight->Min = MIN_HEIGHT_CM;
			FeedHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = MIN_HEIGHT_CM;
			MaxHeight->Position = MAX_HEIGHT_CM;
			FeedHeight->Position = MinHeight->Position;
			break;
		}
	}

	// band specific settings
	switch (BandList->ItemIndex) {
	case BAND_160: {
			/*TODO : 160M needs to start with more than one wire leg to get going. */
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxXSize->Max = 320;
			MaxYSize->Min = 0;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Position = MIN_HEIGHT_M;
			MaxHeight->Position = MAX_HEIGHT_M;
			FeedHeight->Position = 10;
			MaxXSize->Position = 160;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_80: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 320;
			MaxYSize->Max = MaxXSize->Max;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = 10;
			MaxXSize->Position = 80;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_60: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 60;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = 40;
			MaxXSize->Position = FeedHeight->Position;
			MaxYSize->Position = FeedHeight->Position;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = 60;
			MaxXSize->Position = 60;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_40: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 40;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = 20;
			MaxHeight->Position = 40;
			MaxXSize->Position = 20;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_30: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 30;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = 30;
			MaxXSize->Position = 15;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_20: { // SET FOR DEVELOPMENT TESTING
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 20;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = 10;
			MaxHeight->Position = 20;
			MaxXSize->Position = 10;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_17: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 17;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = MIN_HEIGHT_M + 17;
			MaxXSize->Position = 9;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_15: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 15;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = MIN_HEIGHT_M + 15;
			MaxXSize->Position = 15;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_12: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 12;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = MIN_HEIGHT_M + 12;
			MaxXSize->Position = 12;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_10: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 10;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = 5;
			MaxHeight->Position = MIN_HEIGHT_M + 10;
			MaxXSize->Position = 5;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_6: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 6;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_M;
			MaxHeight->Min = MIN_HEIGHT_M;
			MinHeight->Max = MAX_HEIGHT_M;
			MaxHeight->Max = MAX_HEIGHT_M;
			FeedHeight->Position = MAX_HEIGHT_M-1;
			MaxHeight->Position = MAX_HEIGHT_M;
			MinHeight->Position = MAX_HEIGHT_M-2;
			MaxXSize->Position = 3;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_2: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 2000;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = 3000;
			FeedHeight->Position = 5000;
			MaxHeight->Position = 10000;
			MaxXSize->Position = 1000;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_1_25: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 1250;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = 3000;
			FeedHeight->Position = MinHeight->Position;
			MaxHeight->Position = 3500;
			MaxXSize->Position = 1250;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_70cm: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 300;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = 3000;
			FeedHeight->Position = 3150;
			MaxHeight->Position = 3300;
			MaxXSize->Position = 300;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_33cm: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 100;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = 3000;
			FeedHeight->Position = 3150;
			MaxHeight->Position = 3300;
			MaxXSize->Position = 100;
			MaxYSize->Position = 0;
			break;
		}
	case BAND_23cm: {
			// yard size guess for bands
			MaxXSize->Min = 0;
			MaxYSize->Min = 0;
			MaxXSize->Max = 75;
			MaxYSize->Max = MaxXSize->Max;
			MinHeight->Min = MIN_HEIGHT_CM;
			MaxHeight->Min = MIN_HEIGHT_CM;
			MinHeight->Max = MAX_HEIGHT_CM;
			MaxHeight->Max = MAX_HEIGHT_CM;
			MinHeight->Position = 3000;
			FeedHeight->Position = 3150;
			MaxHeight->Position = 3300;
			MaxXSize->Position = 75;
			MaxYSize->Position = 0;
			break;
		}
	}

}
// ---------------------------------------------------------------------------
