// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormUnit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeePolar"
#pragma link "VCLTee.TeePoin3"
#pragma link "VCLTee.TeeSurfa"
#pragma resource "*.dfm"

TForm1 *Form1;
#include "string.h"

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	Nec_Wires = NULL;
	const int startArrays = 1;
	Nec_Counts = new nec_counts[startArrays];
	Nec_Ground = new nec_wire_ground[startArrays];
	Nec_Loads = new nec_loads[startArrays];
	Nec_Grounds = new nec_grounds[startArrays];
	Nec_Excitation = new nec_excitation[startArrays];
	Nec_Frequency = new nec_frequency[startArrays];
	Nec_Radiation = new nec_radiation[startArrays];
}

__fastcall TForm1::~TForm1() {
	delete[]Nec_Counts;
	delete[]Nec_Ground;
	delete[]Nec_Loads;
	delete[]Nec_Grounds;
	delete[]Nec_Excitation;
	delete[]Nec_Frequency;
	delete[]Nec_Radiation;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::OpenClick(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		nec_file_results results;
		OpenNECFile(OpenDialog1->FileName, &results, true);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject * Sender) {
	Timer1->Enabled = false;
	Series1->Clear();
	PolarSeries1->Clear();
	PolarSeries2->Clear();
	PolarSeries3->Clear();
	PolarSeries4->Clear();
	Series2->Clear();
	Series3->Clear();
	Series4->Clear();
}

int __fastcall TForm1::OpenNECFile(AnsiString Filename, nec_file_results* file_results, bool UpdateSegmentGraph) {
	// open the file
	char nada[] = "dummyname.exe";
	char namein[MAX_PATH];
	char nameout[MAX_PATH];
	AnsiString newinName = Filename;
	AnsiString newoutName = "-o" + ChangeFileExt(Filename, ".out");
	strcpy(namein, newinName.c_str());
	strcpy(nameout, newoutName.c_str());
	char option[] = "-i";
	char* atname[4];
	atname[0] = nada;
	atname[1] = option;
	atname[2] = namein;
	atname[3] = nameout;
	StatusCaption->Caption = "Run Target File: " + Filename;
	StatusCaption->Update();
	Application->ProcessMessages();
	FILE* input_fp = NULL, *output_fp = NULL;
	mainforNEC(4, atname, &s_context, input_fp, output_fp);
	if (UpdateSegmentGraph) {
		// clear the graphs
		Series2->Clear();
	}
	// clear the SWR series
	if (UpdateSegmentGraph) {
		Series3->Clear();
	}
	Series4->Clear();
	// set pointer to dummy value just to enter the while loop
	nec_radiation_pattern* radiation = (nec_radiation_pattern*)0x01;
	// long index = 0;
	// get the count of how many results there are
	nec_results* results = &s_context.m_results;
	/*TODO : Why would the n count be three times the frequencies asked for?
	 Is it the cube?*/
	unsigned int NumberOfResults = results->count() / 3;
	unsigned int CenterFrequency;
	// if the number of results is odd the center frequency is 1 plus half
	if (NumberOfResults > 1) {
		if ((NumberOfResults & 0x01) == 0x01) {
			// result is odd
			CenterFrequency = NumberOfResults / 2;
		}
		else {
			// result is even
			CenterFrequency = NumberOfResults / 2 - 1;
		}
	}
	else {
		CenterFrequency = 0;
	}
	// loop through the results and fill up the SWR chart
	unsigned int loop = 0;
	for (; loop < NumberOfResults; loop++) {
		// get the radiation pattern
		radiation = s_context.get_radiation_pattern(loop);
		// display the R, X and VSWR
		// frequency
		nec_float frequency = radiation->get_frequency();
		nec_float R = s_context.get_impedance_real(loop/*frequency index*/);
		nec_float X = s_context.get_impedance_imag(loop/*frequency index*/);
		file_results->R = R;
		file_results->X = X;
		// calculate the SWR
		// for now the load is always 50 ohms
		std::complex<double>Z0 = {50, 0};
		std::complex<double>Z1 = {R, X};
		std::complex<double>t, v;
		t = (Z1 - Z0) / (Z1 + Z0);
		v = (1 + abs(t)) / (1 - abs(t));
		// if this is the center frequency then update the captions
		if (loop == CenterFrequency) {
			VSWRLabel->Caption = FormatFloat("0.00", v.real());
			/*TODO : this needs to check the entire band to see if SWR is good*/
			// check for bad SWR
			if (v.real() < 0) {
				// negative SWR is not real change to large positive
				file_results->VSWR = 9.99E+9;
			}
			else {
				// swr should be good copy it
				file_results->VSWR = v.real();
			}
			RLabel->Caption = FormatFloat("0.00", R);
			XLabel->Caption = FormatFloat("0.00", X);
			FreqLabel->Caption = FormatFloat("0.00", frequency / 1.0E+6);
		}
		// add the result to the graph
		if (UpdateSegmentGraph) {
			Series3->AddXY(frequency / 1.0E+6, v.real());
		}
		double maxFrequencyTotalGaindB = -999;
		unsigned int maxTotaldBGainThetaIndex, maxTotaldBGainPhiIndex;
		// find the maximum gain for this frequency
		int thetaAngleCount = radiation->get_ntheta();
		int phiAngleCount = radiation->get_nphi();
		for (unsigned int thetaIndex = 0; thetaIndex < thetaAngleCount; thetaIndex++) {
			for (unsigned int phiIndex = 0; phiIndex < phiAngleCount; phiIndex++) {
				nec_float phiAngle = radiation->get_phi(phiIndex);
				nec_float thetaAngle = radiation->get_theta(thetaIndex);
				// get the total gain for these angles
				nec_float gain;
				gain = radiation->get_power_gain_tot(thetaIndex, phiIndex);
				// if the gain is bigger than the last update the gain
				// and theta / phi index
				if (gain > maxFrequencyTotalGaindB) {
					maxFrequencyTotalGaindB = gain;
					maxTotaldBGainThetaIndex = thetaIndex;
					maxTotaldBGainPhiIndex = phiIndex;
				}
			}
		}
		// now have the maximum gain total for this frequency
		// display it in the graph
		if (UpdateSegmentGraph) {
			Series4->AddXY(frequency / 1.0E+6, maxFrequencyTotalGaindB);
		}
	}
	// get the middle radiation pattern
	loop = CenterFrequency;
	radiation = s_context.get_radiation_pattern(loop);
	// display the R, X and VSWR
	// frequency
	nec_float frequency = radiation->get_frequency();
	nec_float R = s_context.get_impedance_real(loop/*frequency index*/);
	nec_float X = s_context.get_impedance_imag(loop/*frequency index*/);
	// add the points to the chart
	// the first radiation pattern is index 0 and the next radiation pattern
	// would be 1 and so on when more than one radiation pattern exist
	/*TODO : Add coding for more than one radiation pattern*/
	unsigned int stepAngle = 5;
	double segX, segY, segZ;
	if (UpdateSegmentGraph) {
		// get geometery center points and display them to the graph
		for (int geoIndex = 0; geoIndex < s_context.get_geometry()->n_segments; geoIndex++) {
			s_context.get_geometry()->get_xyzSegmentOrignalAbsolute(geoIndex, &segX, &segY, &segZ);
			std::vector<nec_float> *test = &s_context.get_geometry()->XCenterSeg;
			// calculte from wavelength to frequency (speed of light)
			// start dipole 0,0,20
			Series2->AddXYZ(segX, segZ, segY, "", clGreen);
		}
	}
	if (radiation != NULL) {
		// get the horizontal radiation
		// get the number of theta angles which is equal to the index count
		int thetaAngleCount = radiation->get_ntheta();
		int phiAngleCount = radiation->get_nphi();
		// find the maximum gain
		int maxTotaldBGainThetaIndex = 0, maxTotaldBGainPhiIndex = 0;
		double maxTotalGaindB = -999;
		int maxVertdBGainThetaIndex = 0, maxVertdBGainPhiIndex = 0;
		double maxVertGaindB = -999;
		int maxHorzdBGainThetaIndex = 0, maxHorzdBGainPhiIndex = 0;
		double maxHorzGaindB = -999;
		const double ThetaTarget = 0;
		for (unsigned int thetaIndex = 0; thetaIndex < thetaAngleCount; thetaIndex++) {
			for (unsigned int phiIndex = 0; phiIndex < phiAngleCount; phiIndex++) {
				nec_float phiAngle = radiation->get_phi(phiIndex);
				nec_float thetaAngle = radiation->get_theta(thetaIndex);
				// get the total gain for these angles
				nec_float gain;
				gain = radiation->get_power_gain_tot(thetaIndex, phiIndex);
				// if the gain is bigger than the last update the gain
				// and theta / phi index
				if (gain > maxTotalGaindB) {
					maxTotalGaindB = gain;
					maxTotaldBGainThetaIndex = thetaIndex;
					maxTotaldBGainPhiIndex = phiIndex;
				}
				// get the vertical gain
				gain = radiation->get_power_gain_vert(thetaIndex, phiIndex);
				// if the gain is bigger than the last update the gain
				// and theta / phi index
				if (gain > maxVertGaindB) {
					maxVertGaindB = gain;
					maxVertdBGainThetaIndex = thetaIndex;
					maxVertdBGainPhiIndex = phiIndex;
				}
				// get the horizontal gain
				gain = radiation->get_power_gain_horiz(thetaIndex, phiIndex);
				// if the gain is bigger than the last update the gain
				// and theta / phi index
				/*TODO : Have to break this up by desired angle for now a hard 0*/
				if ((gain > maxHorzGaindB) && (ThetaTarget == 0)) {
					maxHorzGaindB = gain;
					maxHorzdBGainThetaIndex = thetaIndex;
					maxHorzdBGainPhiIndex = phiIndex;
				}
			}
		}
		// only do if more than 1 radiation angle
		if ((phiAngleCount > 1) && (thetaAngleCount > 1)) {
			// display the results for maximum gains in the display
			// display max gains
			TotalGaindBLabel->Caption = FormatFloat("0.00", maxTotalGaindB);
			VertGaindBLabel->Caption = FormatFloat("0.00", maxVertGaindB);
			HorzGaindBLabel->Caption = FormatFloat("0.00", maxHorzGaindB);
			file_results->BestHorzGain = maxHorzGaindB;
			file_results->BestVertGain = maxVertGaindB;
			file_results->BestTotalGain = maxTotalGaindB;
			// display max gains phi angle
			double angle;
			angle = radiation->get_phi(maxTotaldBGainPhiIndex);
			TotalGainPhiLabel->Caption = FormatFloat("0.0", FMod(angle + 180, 360));
			angle = radiation->get_phi(maxVertdBGainPhiIndex);
			VertPhiLabel->Caption = FormatFloat("0.0", FMod(angle + 180, 360));
			angle = radiation->get_phi(maxHorzdBGainPhiIndex);
			HorzPhiLabel->Caption = FormatFloat("0.0", FMod(angle + 180, 360));
			file_results->BestHorzGainPhiAngle = FMod(angle + 180, 360);
			// display max gains theta angle
			/*TODO :
			 probably need to check here what 90 deree segment of phi angle
			 before assuming the circle is the 0-90 degree one. Maybe it' s just
			 best to check each chart to see what the best angle is by the
			 maximum radius*/
			/*update the captions for the best radiation angles horz and vert
			 */
			double testA = radiation->get_theta(maxTotaldBGainThetaIndex);
			double newAngle = fabs(-radiation->get_theta(maxTotaldBGainThetaIndex) - 90);
			TotalGainThetaLabel->Caption = FormatFloat("0.0", newAngle);
			newAngle = fabs(-radiation->get_theta(maxVertdBGainThetaIndex) - 90);
			VertThetaLabel->Caption = FormatFloat("0.0", newAngle);
			file_results->BestVertGainAngle = newAngle;
			newAngle = fabs(-radiation->get_theta(maxHorzdBGainThetaIndex) - 90);
			HorzThetaLabel->Caption = FormatFloat("0.0", newAngle);
			file_results->BestHorzGainAngle = newAngle;
			// first pass
			// display the charts
			// phi 0 - 360 degrees
			// clear the graphs
			Series1->Clear();
			PolarSeries1->Clear();
			PolarSeries2->Clear();
			PolarSeries3->Clear();
			PolarSeries4->Clear();
			for (unsigned int phiIndex = 0; phiIndex < phiAngleCount; phiIndex++) {
				// theta generally -180 - 0 degrees
				for (unsigned int thetaIndex = 0; thetaIndex < thetaAngleCount; thetaIndex++) {
					nec_float phiAngle = radiation->get_phi(phiIndex);
					nec_float thetaAngle = radiation->get_theta(thetaIndex);
					nec_float gain;
					gain = radiation->get_power_gain_vert(thetaIndex, phiIndex);
					if (gain < -50)
						gain = -50;
					Series1->AddPolar(phiAngle + 180, gain, "", clTeeColor);
					gain = radiation->get_power_gain_horiz(thetaIndex, phiIndex);
					if (gain < -50)
						gain = -50;
					PolarSeries1->AddPolar(phiAngle + 180, gain, "", clTeeColor);
					if (maxTotaldBGainThetaIndex == thetaIndex) {
						gain = radiation->get_power_gain_tot(thetaIndex, phiIndex);
						if (gain < -50)
							gain = -50;
						PolarSeries2->AddPolar(phiAngle + 180, gain, "", clTeeColor);
					}
					// display output for gain slice
					if (maxHorzdBGainPhiIndex == phiIndex) {
						gain = radiation->get_power_gain_horiz(thetaIndex, phiIndex);
						if (gain < -50)
							gain = -50;
						PolarSeries4->AddPolar(-thetaAngle, gain, "", clTeeColor);
					}
					if (maxVertdBGainPhiIndex == phiIndex) {
						gain = radiation->get_power_gain_vert(thetaIndex, phiIndex);
						if (gain < -50)
							gain = -50;
						PolarSeries3->AddPolar(-thetaAngle, gain, "", clTeeColor);
					}
				}
			}
			// second pass
			// display the charts
			// phi 0 - 360 degrees
			for (unsigned int phiIndex = 0; phiIndex < phiAngleCount; phiIndex++) {
				// theta generally -180 - 0 degrees
				for (unsigned int thetaIndex = 0; thetaIndex < thetaAngleCount; thetaIndex++) {
					nec_float phiAngle = radiation->get_phi(phiIndex);
					nec_float thetaAngle = radiation->get_theta(thetaIndex);
					nec_float gain;
					if (maxHorzdBGainPhiIndex == phiIndex) {
						// now need the inverse angle (the opposite side)
						double oppositeAngle = FMod(phiAngle + 180, 360);
						// now search for the index for this angle
						unsigned int findPhiAngleIndex = 0;
						bool found = false;
						for (; findPhiAngleIndex < phiAngleCount; findPhiAngleIndex++) {
							if (oppositeAngle == radiation->get_phi(findPhiAngleIndex)) {
								found = true;
								break;
							}
						}
						// display output for gain slice
						// now have the index to the opposite angle
						if (!found) {
							// throw Exception
							// ("Angle not found in horz graph side shot.");
						}
						else {
							gain = radiation->get_power_gain_horiz(thetaIndex, findPhiAngleIndex);
							if (gain < -40)
								gain = -40;
							double newAngle = /*-*/thetaAngle;
							PolarSeries4->AddPolar(newAngle/*+ 180*/, gain, "", clTeeColor);
						}
					}
					if (maxVertdBGainPhiIndex == phiIndex) {
						// now need the inverse angle (the opposite side)
						double oppositeAngle = FMod(phiAngle + 180, 360);
						// now search for the index for this angle
						unsigned int findPhiAngleIndex = 0;
						bool found = false;
						for (; findPhiAngleIndex < phiAngleCount; findPhiAngleIndex++) {
							if (oppositeAngle == radiation->get_phi(findPhiAngleIndex)) {
								found = true;
								break;
							}
						}
						// now have the index to the opposite angle
						if (!found) {
							// throw Exception
							// ("Angle not found in horz graph side shot.");
						}
						else {
							gain = radiation->get_power_gain_vert(thetaIndex, findPhiAngleIndex);
							if (gain < -50)
								gain = -50;
							double newAngle = /*-*/thetaAngle;
							PolarSeries3->AddPolar(newAngle/*+ 180*/, gain, "", clTeeColor);
						}
					}
				}
			}
			// find the minimum and maximum series values of all the charts
			double chartMaxY = -999; // set for value that will be too high
			double chartMinY = 999; // set for value that will be too low
			if (Series1->MinYValue() < chartMinY) {
				chartMinY = Series1->MinYValue();
			}
			if (PolarSeries1->MinYValue() < chartMinY) {
				chartMinY = PolarSeries1->MinYValue();
			}
			if (PolarSeries2->MinYValue() < chartMinY) {
				chartMinY = PolarSeries2->MinYValue();
			}
			if (Series1->MaxYValue() > chartMaxY) {
				chartMaxY = Series1->MaxYValue();
			}
			if (PolarSeries1->MaxYValue() > chartMaxY) {
				chartMaxY = PolarSeries1->MaxYValue();
			}
			if (PolarSeries2->MaxYValue() > chartMaxY) {
				chartMaxY = PolarSeries2->MaxYValue();
			}
			// check if the minimum value is greater than zero, if it is make it zero
			if (chartMinY > 0) {
				chartMinY = 0;
			}
			double setMax = 999;
			double setMin = -999;
			// reset the axis so errors on min and max don't occur
			Chart1->Axes->Left->Automatic = false;
			Chart1->Axes->Right->Automatic = false;
			Chart1->Axes->Top->Automatic = false;
			Chart1->Axes->Bottom->Automatic = false;
			Chart1->Axes->Left->Maximum = setMax;
			Chart1->Axes->Right->Maximum = setMax;
			Chart1->Axes->Top->Maximum = setMax;
			Chart1->Axes->Bottom->Maximum = setMax;
			Chart1->Axes->Left->Minimum = setMin;
			Chart1->Axes->Right->Minimum = setMin;
			Chart1->Axes->Top->Minimum = setMin;
			Chart1->Axes->Bottom->Minimum = setMin;
			// chart2
			Chart2->Axes->Left->Automatic = false;
			Chart2->Axes->Right->Automatic = false;
			Chart2->Axes->Top->Automatic = false;
			Chart2->Axes->Bottom->Automatic = false;
			Chart2->Axes->Left->Maximum = setMax;
			Chart2->Axes->Right->Maximum = setMax;
			Chart2->Axes->Top->Maximum = setMax;
			Chart2->Axes->Bottom->Maximum = setMax;
			Chart2->Axes->Left->Minimum = setMin;
			Chart2->Axes->Right->Minimum = setMin;
			Chart2->Axes->Top->Minimum = setMin;
			Chart2->Axes->Bottom->Minimum = setMin;
			// chart3
			Chart3->Axes->Left->Automatic = false;
			Chart3->Axes->Right->Automatic = false;
			Chart3->Axes->Top->Automatic = false;
			Chart3->Axes->Bottom->Automatic = false;
			Chart3->Axes->Left->Maximum = setMax;
			Chart3->Axes->Right->Maximum = setMax;
			Chart3->Axes->Top->Maximum = setMax;
			Chart3->Axes->Bottom->Maximum = setMax;
			Chart3->Axes->Left->Minimum = setMin;
			Chart3->Axes->Right->Minimum = setMin;
			Chart3->Axes->Top->Minimum = setMin;
			Chart3->Axes->Bottom->Minimum = setMin;
			// chart5
			Chart5->Axes->Left->Automatic = false;
			Chart5->Axes->Right->Automatic = false;
			Chart5->Axes->Top->Automatic = false;
			Chart5->Axes->Bottom->Automatic = false;
			Chart5->Axes->Left->Maximum = setMax;
			Chart5->Axes->Right->Maximum = setMax;
			Chart5->Axes->Top->Maximum = setMax;
			Chart5->Axes->Bottom->Maximum = setMax;
			Chart5->Axes->Left->Minimum = setMin;
			Chart5->Axes->Right->Minimum = setMin;
			Chart5->Axes->Top->Minimum = setMin;
			Chart5->Axes->Bottom->Minimum = setMin;
			// chart5
			Chart6->Axes->Left->Automatic = false;
			Chart6->Axes->Right->Automatic = false;
			Chart6->Axes->Top->Automatic = false;
			Chart6->Axes->Bottom->Automatic = false;
			Chart6->Axes->Left->Maximum = setMax;
			Chart6->Axes->Right->Maximum = setMax;
			Chart6->Axes->Top->Maximum = setMax;
			Chart6->Axes->Bottom->Maximum = setMax;
			Chart6->Axes->Left->Minimum = setMin;
			Chart6->Axes->Right->Minimum = setMin;
			Chart6->Axes->Top->Minimum = setMin;
			Chart6->Axes->Bottom->Minimum = setMin;
			// chart 1
			Chart1->Axes->Left->Maximum = chartMaxY;
			Chart1->Axes->Right->Maximum = chartMaxY;
			Chart1->Axes->Top->Maximum = chartMaxY;
			Chart1->Axes->Bottom->Maximum = chartMaxY;
			Chart1->Axes->Left->Minimum = chartMinY;
			Chart1->Axes->Right->Minimum = chartMinY;
			Chart1->Axes->Top->Minimum = chartMinY;
			Chart1->Axes->Bottom->Minimum = chartMinY;
			// chart2
			Chart2->Axes->Left->Maximum = chartMaxY;
			Chart2->Axes->Right->Maximum = chartMaxY;
			Chart2->Axes->Top->Maximum = chartMaxY;
			Chart2->Axes->Bottom->Maximum = chartMaxY;
			Chart2->Axes->Left->Minimum = chartMinY;
			Chart2->Axes->Right->Minimum = chartMinY;
			Chart2->Axes->Top->Minimum = chartMinY;
			Chart2->Axes->Bottom->Minimum = chartMinY;
			// chart3
			Chart3->Axes->Left->Automatic = false;
			Chart3->Axes->Right->Automatic = false;
			Chart3->Axes->Top->Automatic = false;
			Chart3->Axes->Bottom->Automatic = false;
			Chart3->Axes->Left->Maximum = chartMaxY;
			Chart3->Axes->Right->Maximum = chartMaxY;
			Chart3->Axes->Top->Maximum = chartMaxY;
			Chart3->Axes->Bottom->Maximum = chartMaxY;
			Chart3->Axes->Left->Minimum = chartMinY;
			Chart3->Axes->Right->Minimum = chartMinY;
			Chart3->Axes->Top->Minimum = chartMinY;
			Chart3->Axes->Bottom->Minimum = chartMinY;
			// chart5
			Chart5->Axes->Left->Maximum = chartMaxY;
			Chart5->Axes->Right->Maximum = chartMaxY;
			Chart5->Axes->Top->Maximum = chartMaxY;
			Chart5->Axes->Bottom->Maximum = chartMaxY;
			Chart5->Axes->Left->Minimum = chartMinY;
			Chart5->Axes->Right->Minimum = chartMinY;
			Chart5->Axes->Top->Minimum = chartMinY;
			Chart5->Axes->Bottom->Minimum = chartMinY;
			// chart5
			Chart6->Axes->Left->Maximum = chartMaxY;
			Chart6->Axes->Right->Maximum = chartMaxY;
			Chart6->Axes->Top->Maximum = chartMaxY;
			Chart6->Axes->Bottom->Maximum = chartMaxY;
			Chart6->Axes->Left->Minimum = chartMinY;
			Chart6->Axes->Right->Minimum = chartMinY;
			Chart6->Axes->Top->Minimum = chartMinY;
			Chart6->Axes->Bottom->Minimum = chartMinY;
		}
	}
	// if all done delete the radiation pattern class
	// loop through the results and fill up the SWR chart
	for (unsigned int loop = 0; loop < NumberOfResults; loop++) {
		// get the radiation pattern
		radiation = s_context.get_radiation_pattern(loop);
		delete radiation;
	}
	// the last thing to do is give the option to save the output file
	// check if the file name already has an .nec extension if so we aren't going to save this
	// file it already has been done
	AnsiString extension = ExtractFileExt(Filename);
	if ((ExtractFileExt(Filename)) == ".tmp" && (Done == true)) {
		if (SaveDialog1->Execute() == ID_OK) {
			RenameFile(Filename, SaveDialog1->FileName);
			RenameFile(ChangeFileExt(Filename, ".out"), ChangeFileExt(SaveDialog1->FileName, ".out"));
		}
		else {
			// delete the file
			// otherwise delete the temp file and output file
			for (int loop = 0; loop < 10; loop++) {
				bool result = DeleteFile(Filename);
				if (result)
					break;
				if (loop == 9) {
					ErrorMemo->Lines->Add("Failed delete temp file " + Filename);
					ShowMessage("Unable to delete temp file " + Filename);
					Close();
					return 1;
				}
				Sleep(1500);
				Application->ProcessMessages();
			}
			AnsiString outfile = ChangeFileExt(Filename, ".out");
			for (int loop = 0; loop < 10; loop++) {
				bool result = DeleteFile(outfile);
				if (result)
					break;
				if (loop == 9) {
					ErrorMemo->Lines->Add("Failed delete output file " + outfile);
					ShowMessage("Unable to delete output file");
					Close();
					return 1;
				}
				Sleep(1500);
				Application->ProcessMessages();
			}
		}
	}
	StatusCaption->Caption = "Ready";
	StatusCaption->Update();
	// everything is okay
	file_results->Error = false;
	file_results->SegmentErrorType = nec_exception::NoSegmentError;
	return 0;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::MakeClick(TObject *Sender) {
	bool UpdateSegmentGraph = true;
	// reset the cancel button
	Done = false;
	Cancel->Tag = 0;
	// reset the last swr to a terrible result
	LastVSWR = 9.99E+9;
	LastHorGain = -9.99E+9;
	// force SWR calc to numbers which will intially be beat
	SWRCompare = 9.99E+9;
	SWRRCompare = 9.99E+9;
	SWRXCompare = -9.99E+9;
	Iteration = 0;
	Series5->Clear();
	Series6->Clear();
	Series7->Clear();
	Series8->Clear();
	Series11->Clear();
	// clear target values
	RecentHorzGainTarget = LastHorGain;
	RecentSWRTarget = LastVSWR;
	// for keeping running count of tried segments for finding solution
	triedDisable.clear();
	triedEnable.clear();
	// used to keep track of the mode, either disable wire segment or enable
	// mode will flip flop as all combinations get tried
	ModeEnable = true;
	// set first optimization mode to SWR
	OptimizationOperatingMode = OptimizeSWR;
	OptimizeCurrentWireID = -1;
	// SWR_Optimize_SWR_R.clear();
	// SWR_Optimize_SWR_X.clear();
	SWRXCompare = -9.99E+0;
	// Optimize_HorzGain.clear();
	graphUpdateFlag = false;
	// set for no last wire disabled
	// LastChangedWire = -1;
	// set up rand generator
	randomize();
	// clear previous error results
	ErrorMemo->Lines->Clear();
	// make a new antenna
	// display the dialog box
	TDesignForm* Designform = new TDesignForm(this);
	if (Designform->ShowModal() == ID_OK) {
		// get the target SWR
		double TargetSWR;
		switch (Designform->TunerOptions->ItemIndex) {
		case 0: {
				TargetSWR = 2;
				break;
			}
		case 1: {
				TargetSWR = 3;
				break;
			}
		case 2: {
				TargetSWR = 10;
				break;
			}
		case 3: {
				TargetSWR = 100;
				break;
			}
		}
		// select the frequecy middle for the band
		double Frequency, BandBottom, BandLength, resolution, WireDiameter;
		// scale = 1 for meters and 0.1 for centimeters
		double Scale = SCALE_M;
		double MaxHeightMeters = (double)Designform->MaxHeight->Position;
		double CenterXMeters = (double)Designform->MaxXSize->Position / 2;
		double CenterYMeters = (double)Designform->MaxYSize->Position / 2;
		unsigned int BandNumber = Designform->BandList->ItemIndex;

		/*
		 // make sizes large and small so no error
		 Chart4->Axes->Left->Maximum = 9.99E+9;
		 Chart4->Axes->Bottom->Maximum = 9.99E+9;
		 Chart4->Axes->DepthTop->Maximum = 9.99E+9;
		 Chart4->Axes->Depth->Maximum = 9.99E+9;
		 Chart4->Axes->Left->Minimum = -9.99E+9;
		 Chart4->Axes->Bottom->Minimum = -9.99E+9;
		 Chart4->Axes->DepthTop->Minimum = -9.99E+9;
		 Chart4->Axes->Depth->Minimum = -9.99E+9;

		 // now set sizes to user sizes
		 Chart4->Axes->Left->Automatic = false;
		 Chart4->Axes->Depth->Automatic = false;
		 Chart4->Axes->Bottom->Automatic = false;
		 Chart4->Axes->Left->Maximum = Designform->MaxHeight->Position;
		 Chart4->Axes->Left->Minimum = 0;
		 Chart4->Axes->Bottom->Maximum = (double)Designform->MaxXSize->Position / 2;
		 Chart4->Axes->Bottom->Minimum = -(double)Designform->MaxXSize->Position / 2;
		 // Chart4->Axes->DepthTop->Automatic = false;
		 // Chart4->Axes->DepthTop->Maximum = Designform->MaxYSize->Position;
		 // Chart4->Axes->DepthTop->Minimum = -Designform->MaxYSize->Position;
		 Chart4->Axes->Depth->Maximum = (double)Designform->MaxYSize->Position / 2;
		 Chart4->Axes->Depth->Minimum = -(double)Designform->MaxYSize->Position / 2;
		 */
		// prepare the nec input file
		unsigned int FeedpointWireID;
		unsigned int WireID = 0;
		// options
		OnlyAttached = Designform->NoStraysAllowed->Checked;
		// set kick off sub loop state machines
		OptimizeWireType optimizewiretype = FindAllAttachedWires;
		double MaxHeight = Designform->MaxHeight->Position; // max height
		double MinHeight = Designform->MinHeight->Position; // min height
		double MaxXPosition = Designform->MaxXSize->Position; // max width
		double MaxYPosition = Designform->MaxYSize->Position; // max depth
		double MaxFeedHeightPosition = Designform->FeedHeight->Position;

		if (Designform->AntennaType->ItemIndex == 0) {
			// dipole selected
			bool Error = BuildDipoleModel(&MaxHeight, &MinHeight, &MaxXPosition, &MaxYPosition,
			  &resolution/*resolution*/, &MaxFeedHeightPosition, &Frequency, &WireDiameter, &Scale, BandNumber,
			  &BandBottom, &BandLength);
			if (Error)
				return;
		}
		// check for cube etch model
		else if (Designform->AntennaType->ItemIndex == 1) {
			/*TODO : Check that the feed point height is within or at the minimum and
			 maximum height otherwise it will never be found in the cube middle check*/
			// build cube model
			bool testAxis = BuildCube(&MaxHeight, &MinHeight, &MaxXPosition, &MaxYPosition, &resolution/*resolution*/,
			  &MaxFeedHeightPosition, &Frequency, &WireDiameter, &Scale, BandNumber, &BandBottom, &BandLength);
			if (testAxis) {
				// error exit
				return;
			}
		}
		double wavelength = em::speed_of_light() / (Nec_Frequency[0].FrequencyMHz * 1.0E+6);
		// set flag in case user cancels
		double minSegmentLength = wavelength / 5;
		bool cancel = false;
		// set flag to delete the file when done with it (normally true)
		// except for when the SWR optimization is complete before
		// we go to do the SWR band sweep
		bool DeleteFileWhenDone = true;
		// keep a running count of the number of enabled and disabled wires
		unsigned int enabledCount = 0;
		unsigned int disabledCount = 0;
		// flag attached wire is used to skip past calculating for wires which aren't
		// attached in the cube matrix or always if checking for attached wires isn't opted for
		// optimize the file
		bool firsttime = true;
		do {
			// build the nec file
			// push the structures to the file creating function
			WideString tempfilename;
			nec_file_results file_results;
			// only create a new NEC file when a wire has been added (SWR needs checked)
			if ((optimizewiretype == VerifySWRChange) || firsttime) {
				firsttime = false;
				tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds, Nec_Excitation,
				  Nec_Frequency, Nec_Radiation);
				// when doing attached always update the segment graph
				// UpdateSegmentGraph = true;
				if (tempfilename == "") {
					// error during file rename unable to continue so stop
					ErrorMemo->Lines->Add("Failure to rename file. Have to halt.");
					ShowMessage("Rename file error. Terminating");
					return;
				}
				// we created a temp file, we will need to delete later
				DeleteFileWhenDone = true;
				try {
					int intresult = OpenNECFile(tempfilename, &file_results, UpdateSegmentGraph);
				}

				catch (Exception &E) {
					ErrorMemo->Lines->Add(AnsiString(E.Message));
					ShowMessage("Unexpected program error. See status log. Terminating");
					Close();
					return;
				}
				// otherwise delete the temp file and output file
				if (DeleteFileWhenDone) {
					for (int loop = 0; loop < 10; loop++) {
						bool result = DeleteFile(tempfilename);
						if (result)
							break;
						if (loop == 9) {
							ErrorMemo->Lines->Add("Failed delete temp file " + tempfilename);
							ShowMessage("Unable to delete temp file " + tempfilename);
							Close();
							return;
						}
						Sleep(1500);
						Application->ProcessMessages();
					}
					AnsiString outfile = ChangeFileExt(tempfilename, ".out");
					for (int loop = 0; loop < 10; loop++) {
						bool result = DeleteFile(outfile);
						if (result)
							break;
						if (loop == 9) {
							ErrorMemo->Lines->Add("Failed delete output file " + outfile);
							ShowMessage("Unable to delete output file");
							Close();
							return;
						}
						Sleep(1500);
						Application->ProcessMessages();
					}
				} // update displays
				// updte wire count display
				TotalCount->Caption = IntToStr((__int64)(Nec_Counts[0].WireCount) / 2);
				// check for segment errors
				// this first time at this point there is only the feedpoint
				// in the first temporary file
				if (file_results.SegmentErrorType == nec_exception::SegmentTooShortForWavelength) {
					// display the message
					ErrorMemo->Lines->Add(AnsiString(file_results.ErrorMessage));
					// correct segment length and try again
					// loop through the wires and find the offending segment
					unsigned int totalizeSegments = 0;
					for (int loop = 0; loop < Nec_Counts[0].WireCount; loop++) {
						totalizeSegments += Nec_Wires[loop].Segments;
						if (totalizeSegments > file_results.SegmentNumber) {
							// this wire contains the offending segment
							// this wire number of segments needs to be corrected
							// get the wire length
							double points = Power(abs(Nec_Wires[loop].X1 - Nec_Wires[loop].X2), 2) +
							  Power(abs(Nec_Wires[loop].Y1 - Nec_Wires[loop].Y2), 2) +
							  Power(abs(Nec_Wires[loop].Z1 - Nec_Wires[loop].Z2), 2);
							double wirelength = Sqrt(points);
							double segmentlength = wirelength / Nec_Wires[loop].Segments;
							double segmentnumwavelengths =
							  segmentlength / (em::speed_of_light() / (Nec_Frequency[0].FrequencyMHz * 1.0E+6));
							double spdLight = em::speed_of_light();
							// correct this wires number of segments to
							// be within the spec of the limitation
							int NumberOfSegmentsNeeded = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
							  &wirelength);
							ErrorMemo->Lines->Add("Corrected number of segments from:" + FormatFloat("0.000",
							  Nec_Wires[loop].Segments) + " to: " + IntToStr((int)NumberOfSegmentsNeeded));
							Nec_Wires[loop].Segments = NumberOfSegmentsNeeded;
							// go ahead and try again
							break;
						}
					}
				}
				else if (file_results.Error) {
					// add the error message to the memo box
					ErrorMemo->Lines->Add(AnsiString(file_results.ErrorMessage) + " in file: " + tempfilename);
					break;
				}
			}
			// check if the SWR is not within range
			if ((TargetSWR <= file_results.VSWR) || (Cancel->Tag != 1)) {
				// process windows messages
				Application->ProcessMessages();

				//
				// dipole model
				//

				if (Designform->AntennaType->ItemIndex == 0) {
					// first time here the feedpoint and the first two wires are enabled
					// we need to update the SWR and update the displays
					Nec_Radiation[0].ThetaAngleCount = 1;
					Nec_Radiation[0].PhiAngleCount = 1;
					ProgressBar1->Max = (Nec_Counts[0].WireCount - 1) / 2;

					// loop through one less (the feed point)
					// divide by 2 to account for wires will be enabled as pairs
					unsigned int totalwires = Nec_Counts[0].WireCount;
					for (unsigned int wireloop = 1; ; wireloop += 2) {
						ProgressBar1->Position = wireloop;
						unsigned int iteration = wireloop / 2;
						// update the graphs
						// check if this delta X is closer to zero
						double deltaSWR = file_results.VSWR - 50;
						// update the new best wire ID
						if (deltaSWR < SWRCompare) {
							SWRCompare = deltaSWR;
							BestWireID = wireloop;
							SWRTarget->Caption = FormatFloat("0.00", file_results.VSWR);
							// add this SWR to the running SWR plot graph
							Series5->AddXY(iteration, file_results.VSWR, "", clTeeColor);
							// need to add the X and R graphs point here too
							Series6->AddXY(iteration, file_results.R, "", clTeeColor);
							Series7->AddXY(iteration, file_results.X, "", clTeeColor);
							UpdateSegmentGraph = true;
						}
						else {
							UpdateSegmentGraph = true; // always show antenna model during debug
						}
						// disable these wires
						Nec_Wires[wireloop].Enabled = false;
						Nec_Wires[wireloop + 1].Enabled = false;
						unsigned int loopplus2 = wireloop + 2;
						unsigned int comparedone = (totalwires - 1) / 2;
						// check if there are more wire sets
						if (loopplus2 <= comparedone) {
							// prepare the next wires
							Nec_Wires[wireloop + 2].Enabled = true;
							Nec_Wires[wireloop + 3].Enabled = true;
						}
						else {
							// exit we are done
							break;
						}
						// create the new NEC file
						// save the file
						WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads,
						  Nec_Grounds, Nec_Excitation, Nec_Frequency, Nec_Radiation);
						// and evaluate it
						if (tempfilename == "") {
							// error during file rename unable to continue so stop
							ErrorMemo->Lines->Add("Failure to rename file. Have to halt.");
							ShowMessage("Rename file error. Terminating");
							return;
						}
						// we created a temp file, we will need to delete later
						DeleteFileWhenDone = true;
						try {
							int intresult = OpenNECFile(tempfilename, &file_results, UpdateSegmentGraph);
						}

						catch (Exception &E) {
							ErrorMemo->Lines->Add(AnsiString(E.Message));
							ShowMessage("Unexpected program error. See status log. Terminating");
							Close();
							return;
						}
						// otherwise delete the temp file and output file
						if (DeleteFileWhenDone) {
							for (int loop = 0; loop < 10; loop++) {
								bool result = DeleteFile(tempfilename);
								if (result)
									break;
								if (loop == 9) {
									ErrorMemo->Lines->Add("Failed delete temp file " + tempfilename);
									ShowMessage("Unable to delete temp file " + tempfilename);
									Close();
									return;
								}
								Sleep(1500);
								Application->ProcessMessages();
							}
							AnsiString outfile = ChangeFileExt(tempfilename, ".out");
							for (int loop = 0; loop < 10; loop++) {
								bool result = DeleteFile(outfile);
								if (result)
									break;
								if (loop == 9) {
									ErrorMemo->Lines->Add("Failed delete output file " + outfile);
									ShowMessage("Unable to delete output file");
									Close();
									return;
								}
								Sleep(1500);
								Application->ProcessMessages();
							}
						} // update displays
						// check if user cancelled
						if (Cancel->Tag == 1) {
							ErrorMemo->Lines->Add("Cancel detected. Will show best find.");
							break; // exit
						}
						Application->ProcessMessages();
					}
					if (SWRCompare > 100) {
						ErrorMemo->Lines->Add("No good model found yet, exiting.");
						return;
					}
					ProgressBar1->Position = ProgressBar1->Max;
					// clear the wire graph display
					Series2->Clear(); // design green dots
					Series9->Clear(); // swr red dots
					// select the best wire set
					Nec_Wires[BestWireID].Enabled = true;
					Nec_Wires[BestWireID + 1].Enabled = true;
					// run the sweep we are done
					Done = true;
					ErrorMemo->Lines->Add(AnsiString("Run Band Sweep"));
					Nec_Radiation[0].ThetaAngleCount = 19;
					Nec_Radiation[0].PhiAngleCount = 73;
					Nec_Frequency[0].FrequencyMHz = BandBottom;
					ErrorMemo->Lines->Add(AnsiString("Band Bottom:" + FormatFloat("0.00", BandBottom)));
					Nec_Frequency[0].BandWidth = BandLength;
					ErrorMemo->Lines->Add(AnsiString("Band Length:" + FormatFloat("0.00", BandLength)));
					Nec_Frequency[0].FrequencyStepSize = BandLength / 7;
					ErrorMemo->Lines->Add(AnsiString("Band Step Size:" + FormatFloat("0.00",
					  Nec_Frequency[0].FrequencyStepSize)));
					Nec_Frequency[0].FrequencySteps =
					  Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
					ErrorMemo->Lines->Add(AnsiString("Band Steps:" + FormatFloat("0.00",
					  Nec_Frequency[0].FrequencySteps)));
					// save the file
					WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds,
					  Nec_Excitation, Nec_Frequency, Nec_Radiation);
					ErrorMemo->Lines->Add("Display Results");
					try {
						int intresult = OpenNECFile(tempfilename, &file_results, UpdateSegmentGraph);
					}

					catch (Exception &E) {
						ErrorMemo->Lines->Add(AnsiString(E.Message));
						ShowMessage("Unexpected program error. See status log. Terminating");
						Close();
						return;
					}
					Cancel->Tag = 1;
					break;
				}
				// check for cube etch model
				else if (Designform->AntennaType->ItemIndex == 1) {
					// cube model
					switch (OptimizationOperatingMode) {
					case OptimizeSWR: {
							DeleteFileWhenDone = true;
							UpdateSegmentGraph = false;
							// use reduced signal radiation area for SWR calcs
							Nec_Radiation[0].ThetaAngleCount = 1;
							Nec_Radiation[0].PhiAngleCount = 1;
							LastOptimizationMode = OptimizeSWR;
							OptimizationMode->Caption = "Optimize SWR Calculate";
							// use new SWR calculation but only if flagged attached is set
							// store the last calculated result if not
							// the first time in this state
							double resultSWR = file_results.VSWR;
							// old way was just check SWR this is not what we really want
							// we want points which move R closer to 50 and X closer to 0
							// for a base model
							// unless impedance desired is something other than 50
							// R can never be negative so check if value is closer to 50
							if (file_results.R) {
							}
							EnableWireLB->Caption = IntToStr((__int64)OptimizeCurrentWireID);
							EnableWireLB->Update();
							switch (optimizewiretype) {
							case VerifySWRChange: {
									UpdateSegmentGraph = true;
									// set next evaluation back to just SWR
									Nec_Radiation[0].ThetaAngleCount = 1;
									Nec_Radiation[0].PhiAngleCount = 1;
									// clear the possible update graph
									Series9->Clear();
									Series10->Clear();
									// add this SWR to the running SWR plot graph
									Series5->AddXY(Iteration, SWRCompare, "", clTeeColor);
									// need to add the X and R graphs point here too
									Series6->AddXY(Iteration, file_results.R, "", clTeeColor);
									Series7->AddXY(Iteration, file_results.X, "", clTeeColor);
									// need to add the Horz and Vert Max Gain too
									Series8->AddXY(Iteration, file_results.BestHorzGain, "", clTeeColor);
									Series11->AddXY(Iteration, file_results.BestVertGain, "", clTeeColor);
									optimizewiretype = FindAllAttachedWires;
									break;
								} // end case
							case FindAllAttachedWires: {
									unsigned int Additions = 0;
									bool foundAWire = false;
									// loop for all enabled wires
									unsigned int enabledVecSize = triedEnable.size();
									triedNew.clear();
									for (unsigned int thisEnabledWireID = 0; thisEnabledWireID < enabledVecSize;
									thisEnabledWireID++) {
										unsigned int enabledWireID = triedEnable[thisEnabledWireID];
										EnableWireLB->Caption = StrToInt((__int64)enabledWireID);
										bool ignoreFlag = false;
										double X1c, Y1c, Z1c, X2c, Y2c, Z2c;
										X1c = Nec_Wires[enabledWireID].X1;
										Y1c = Nec_Wires[enabledWireID].Y1;
										Z1c = Nec_Wires[enabledWireID].Z1;
										X2c = Nec_Wires[enabledWireID].X2;
										Y2c = Nec_Wires[enabledWireID].Y2;
										Z2c = Nec_Wires[enabledWireID].Z2;
										if (!ignoreFlag) {
											// check to make sure this wire wasn't added from the inner
											// loop which will place it in the newly enabled list
											// this is why it's also placed in the ignore list
											for (unsigned int thisWireID = 0; thisWireID < Nec_Counts[0].WireCount;
											thisWireID++) {
												// check if this Enabled wire Id is in the ignored list
												// only ignore itself
												if (thisWireID != enabledWireID) {
													// check if this wire is already attached to an already enabled
													// wire
													bool attached = false;
													// get all the X's Y's and Z's
													// XYZ to compare (c)
													// XYZ this (t)
													double X1t, Y1t, Z1t, X2t, Y2t, Z2t;
													X1t = Nec_Wires[thisWireID].X1;
													Y1t = Nec_Wires[thisWireID].Y1;
													Z1t = Nec_Wires[thisWireID].Z1;
													X2t = Nec_Wires[thisWireID].X2;
													Y2t = Nec_Wires[thisWireID].Y2;
													Z2t = Nec_Wires[thisWireID].Z2;
													EnableWireLB->Caption = IntToStr((__int64)thisWireID);
													EnableWireLB->Update();
													Application->ProcessMessages();
													// check XYZ1 against other XYZ1
													bool match1 = false;
													if ((X1c == X1t) && (Y1c == Y1t) && (Z1c == Z1t)) {
														match1 = true;
													}
													// check XYZ2 against other XYZ2
													bool match2 = false;
													if ((X2c == X2t) && (Y2c == Y2t) && (Z2c == Z2t)) {
														match2 = true;
													}
													// check XYZ2 against other XYZ1
													bool match3 = false;
													if ((X1c == X2t) && (Y1c == Y2t) && (Z1c == Z2t)) {
														match3 = true;
													}
													bool match4 = false;
													if ((X2c == X1t) && (Y2c == Y1t) && (Z2c == Z1t)) {
														match4 = true;
													}
													if (match1 || match2 || match3 || match4) {
														// this wire is attached
														// we are going to calcuate for it
														triedNew.push_back(thisWireID);
														// increase the number of potential
														// finds
														Additions++;
														foundAWire = true;
													}
												} // end if
											} // end for
										} // end for
									} // for
									if (foundAWire) {
										unsigned int BestWireID = 0;
										bool foundBest = false;
										// now have additional wires which could be connected to
										// the previous enabled wires without including the new
										// wires
										// add these points to the potential points graph
										// add this point to the chart for list of potential points
										double segX, segY, segZ;
										try {
											// get the XYZ location of this potential wire
											// loop through the number of additions
											for (unsigned int newloop = 0; newloop < triedNew.size(); newloop++) {
												WireID = triedNew[newloop];
												ErrorMemo->Lines->Add("Wire to try: " + IntToStr((__int64)WireID));
												double segX = abs(Nec_Wires[WireID].X1 - Nec_Wires[WireID].X2);
												double segY = abs(Nec_Wires[WireID].Y1 - Nec_Wires[WireID].Y2);
												double segZ = abs(Nec_Wires[WireID].Z1 - Nec_Wires[WireID].Z2);
												segX = Nec_Wires[WireID].X1 + (segX / 2);
												segY = Nec_Wires[WireID].Y1 + (segY / 2);
												segZ = Nec_Wires[WireID].Z1 + (segZ / 2);
												Series9->AddXYZ(segX, segZ, segY, "", clRed);
											}
											// now run that calcs for each possible choice
											for (unsigned int newloop = 0; newloop < triedNew.size(); newloop++) {
												// enable this choice
												Nec_Wires[WireID].Enabled = true;
												// run the calculations
												tempfilename =
												  CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads,
												  Nec_Grounds, Nec_Excitation, Nec_Frequency, Nec_Radiation);
												if (tempfilename == "") {
													// error during file rename unable to continue so stop
													ErrorMemo->Lines->Add("Failure to rename file. Have to halt.");
													ShowMessage("Rename file error. Terminating");
													return;
												}
												// we created a temp file, we will need to delete later
												DeleteFileWhenDone = true;
												try {
													int intresult =
													  OpenNECFile(tempfilename, &file_results, UpdateSegmentGraph);
												}

												catch (Exception &E) {
													ErrorMemo->Lines->Add(AnsiString(E.Message));
													ShowMessage(
													  "Unexpected program error. See status log. Terminating");
													Close();
													return;
												}
												// store the results for comparison
												ErrorMemo->Lines->Add
												  ("WireID: " + IntToStr((__int64)WireID) + " calculated R=" +
												  FormatFloat("0.000", file_results.R) + " and X=" +
												  FormatFloat("0.000", file_results.X) + " with SWR=" +
												  FormatFloat("0.000E+0", file_results.VSWR));
												// measure the R delta from 50
												double RDelta = abs(file_results.R - 50);
												double XDelta = abs(file_results.X);
												bool flagWorse = true;
												if (file_results.VSWR <= SWRCompare) {
													// check if this RDelta is the best so far
													if (RDelta < SWRRCompare) {
														// this is definately better more true R
														// closer to desired impedance
														// compare this SWR to the last one in the vector
														ErrorMemo->Lines->Add("SWR run better or same");
														SWRRCompare = RDelta;
														SWRXCompare = XDelta;
														SWRCompare = file_results.VSWR;
														BestWireID = WireID;
														foundBest = true;
														flagWorse = false;
													}
												} // end if
												if (flagWorse) {
													// if this wire is not better
													ErrorMemo->Lines->Add("SWR run worse");
												} // end else
												// disable the wire
												Nec_Wires[WireID].Enabled = false;
												// otherwise delete the temp file and output file
												if (DeleteFileWhenDone) {
													for (int loop = 0; loop < 10; loop++) {
														bool result = DeleteFile(tempfilename);
														if (result)
															break;
														if (loop == 9) {
															ErrorMemo->Lines->Add
															  ("Failed delete temp file " + tempfilename);
															ShowMessage("Unable to delete temp file " + tempfilename);
															Close();
															return;
														}
														Sleep(1500);
														Application->ProcessMessages();
													}
													AnsiString outfile = ChangeFileExt(tempfilename, ".out");
													for (int loop = 0; loop < 10; loop++) {
														bool result = DeleteFile(outfile);
														if (result)
															break;
														if (loop == 9) {
															ErrorMemo->Lines->Add
															  ("Failed delete output file " + outfile);
															ShowMessage("Unable to delete output file");
															Close();
															return;
														}
														Sleep(1500);
														Application->ProcessMessages();
													}
												}
											} // end for
											// enable the wireID with the best SWR
											if (foundBest) {
												ErrorMemo->Lines->Add("WireID " + IntToStr((__int64)BestWireID) +
												  " has been chosen");
												// enable the wire
												Nec_Wires[BestWireID].Enabled = true;
												// add it too the enabled vector list
												triedEnable.push_back(BestWireID);
												// setup to plot this chart
												// set next evaluation for radiation pattern
												// since this was just SWR check to help optimize time
												Nec_Radiation[0].ThetaAngleCount = 19;
												Nec_Radiation[0].PhiAngleCount = 73;
												optimizewiretype = VerifySWRChange;
											}
											else {
												// didn't find a better wire we either have to
												// remove wires or be done
												// for now be done
												ShowMessage("No new best wire found");
												OptimizationOperatingMode = DisplayResults;
											}
											Sleep(2000);
											Application->ProcessMessages();
											break;
										} // end try
										catch (Exception &E) {
										}
									} // end if foundawire
									else {
										ShowMessage("No new wires found");
										OptimizationOperatingMode = DisplayResults;
										break;
									}
									OptimizationOperatingMode = OptimizeSWR;
								} // end case
							} // end switch
							break;
						} // end case
					case ChooseBestWire: {
							ErrorMemo->Lines->Add("Choose Best Wire");
							DeleteFileWhenDone = false;
							ErrorMemo->Lines->Add(AnsiString("Run Band Sweep"));
							Nec_Radiation[0].ThetaAngleCount = 19;
							Nec_Radiation[0].PhiAngleCount = 73;
							Nec_Frequency[0].FrequencyMHz = BandBottom;
							Nec_Frequency[0].BandWidth = BandLength;
							Nec_Frequency[0].FrequencyStepSize = BandLength / 7;
							Nec_Frequency[0].FrequencySteps =
							  Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
							OptimizationOperatingMode = DisplayResults;
							Done = true;
							break;
						}
					case DisplayResults: {
							ErrorMemo->Lines->Add("Display Results");
							Cancel->Tag = 1;
							// save the file
							WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads,
							  Nec_Grounds, Nec_Excitation, Nec_Frequency, Nec_Radiation);
							break;
						}
					case OptimizeHorzGain: {
							ErrorMemo->Lines->Add("Optimize Horz Gain");
							LastOptimizationMode = OptimizeHorzGain;
							OptimizationMode->Caption = "Optimize Horz Gain";
							ErrorMemo->Lines->Add("Optimize Horz Gain " + DateTimeToStr(Now()));
							Nec_Radiation[0].ThetaAngleCount = 19;
							Nec_Radiation[0].PhiAngleCount = 73;
							// check that the horz gain is better than the last
							// and that is also within the desired range
							// this needs to check the difference in angle
							// not necessarily the gain
							if (((file_results.BestHorzGain < LastHorGain) || ((file_results.BestHorzGainPhiAngle >
							  45) && (file_results.BestHorzGainPhiAngle < 360))) || (file_results.VSWR > TargetSWR)) {
								OptimizationOperatingMode = OptimizeChangedBack;
							}
							// if all good just continue on
							break;
						}
					case OptimizeStripUncessesarySWRWires: {
							OptimizationMode->Caption = "Stripping SWR";
							ErrorMemo->Lines->Add("Stripping SWR " + DateTimeToStr(Now()));
							Nec_Radiation[0].ThetaAngleCount = 1;
							Nec_Radiation[0].PhiAngleCount = 1;
							// check if the mode has changed to enable wires
							if (ModeEnable) {
								// we are done optimizing because everything else
								// matters
								// set the starting target for LastHorGain
								LastHorGain = -9.99E+9;
								OptimizationOperatingMode = OptimizeHorzGain;
							}
							LastOptimizationMode = OptimizeStripUncessesarySWRWires;
							// check if the last change made SWR worse
							if (file_results.VSWR > LastVSWR) {
								// if so change it back
								OptimizationOperatingMode = OptimizeChangedBack;
							}
							break;
						} // end case
					} // end switch
					// update the target values based on the mode
					switch (OptimizationOperatingMode) {
					case OptimizeSWR: {
							// ErrorMemo->Lines->Add("OptimizeSWR");
							SWRTarget->Caption = FormatFloat("0.000000E+0", SWRCompare);
							HorzGainTarget->Caption = "Don't care";
							break;
						}
					case OptimizeHorzGain: {
							ErrorMemo->Lines->Add("OptimizeHorzGain");
							SWRTarget->Caption = FormatFloat("0.0000E+0", SWRCompare);
							HorzGainTarget->Caption = FormatFloat("0.000E+0", LastHorGain);
							break;
						}
					case OptimizeStripUncessesarySWRWires: {
							ErrorMemo->Lines->Add("OptimizeStripUncessesarySWRWires");
							SWRTarget->Caption = FormatFloat("0.0000E+0", SWRCompare);
							HorzGainTarget->Caption = "Don't care";
							break;
						}
					}
					// set don't update graph flag so we don't update
					// the graph with a bad value if it is time to update
					// the graph
					bool dontUpdateGraph = false;
					// pick another random wire and disable it
					// get the wire count
					int numarrayWires = Nec_Counts[0].WireCount - 1;
					int numWires = numarrayWires + 1;
					// check if the vector sizes are already maximum
					if ((triedEnable.size() == numarrayWires) && (triedDisable.size() == numarrayWires)) {
						// there is no solution, all combinations tried
						triedEnable.clear();
						triedDisable.clear();
						// cancel the routine
						Cancel->Tag = 1;
					}
					// count the number of enabled wires
					enabledCount = 0;
					for (int enabled = 0; enabled < numarrayWires; enabled++) {
						if (Nec_Wires[enabled].Enabled) {
							enabledCount++;
						}
					}
					// count the number of disabled wires
					disabledCount = 0;
					for (int disabled = 0; disabled < numarrayWires; disabled++) {
						if (!Nec_Wires[disabled].Enabled) {
							disabledCount++;
						}
					}
					EnabledWireCountLB->Caption = IntToStr((__int64)enabledCount);
					DisabledWireCountLB->Caption = IntToStr((__int64)disabledCount);
					IgnoredWireCountLB->Caption = IntToStr((__int64)triedNew.size());
					EnabledVWireCountLB->Caption = IntToStr((__int64)triedEnable.size());
					DisabledVWireCountLB->Caption = IntToStr((__int64)triedDisable.size());
					SWRVectorLB->Caption = IntToStr((__int64)SWR_Optimize_SWR_R.size());
					// update the vector list
					AnsiString enabledList = IntToStr((__int64)triedEnable.size()) + " List enabled: ";
					for (int l = 0; l < triedEnable.size(); l++) {
						enabledList += IntToStr((__int64)triedEnable[l]) + ", ";
					}
					AnsiString ignoredList = IntToStr((__int64)triedNew.size()) + " List new: ";
					for (int l = 0; l < triedNew.size(); l++) {
						ignoredList += IntToStr((__int64)triedNew[l]) + ", ";
					}
					EnabledListLB->Caption = enabledList.SubString(0, enabledList.Length() - 2);
					IgnoredListLB->Caption = ignoredList.SubString(0, ignoredList.Length() - 2);

					Iteration++;
					// if a change was set back set the mode back to the last mode
					if (OptimizationOperatingMode == OptimizeChangedBack) {
						OptimizationMode->Caption = "Optimize Change Back";
						OptimizationOperatingMode = LastOptimizationMode;
					}
				}
			}
			Application->ProcessMessages();
		} // end do
		while (Cancel->Tag != 1);
		// report the results
		// delete the wires structure array
		delete[]Nec_Wires;
		Nec_Wires = NULL;
	}
	delete Designform;
	StatusCaption->Caption = "Complete";
}

// function to build the cube model for etching
bool TForm1::BuildCube(double *MaxHeightMeters, double *MinHeightMeters, double *MaxWidthMeters, double *MaxDepthMeters,
  double* resolution, double *FeedPointHeight, double* Frequency, double* WireDiameter, double* Scale,
  unsigned int BandSelection, double* BandBottom, double* BandLength) {
	unsigned int numXRows, numYRows, numZRows;
	GetInitialBandResolution(BandSelection, resolution, Scale);
	/*TODO :
	 The resolution should be calculated based on the user's area provided
	 to improve scaling and calculation effeciency*/
	/*DONE : Add the scale to accomodate for cm input (Scale = 0.1)*/
	AdjustUserInputSizeByScale(MaxWidthMeters, MaxDepthMeters, MaxHeightMeters, MinHeightMeters, FeedPointHeight,
	  Scale);
	// get the number of rows in each axis
	numXRows = (*MaxWidthMeters / *resolution);
	numYRows = (*MaxDepthMeters / *resolution);
	numZRows = ((*MaxHeightMeters - *MinHeightMeters) / *resolution);
	// check that number of rows is at least 1 in two axis
	int NumDimensions = 0;
	if (numXRows > 0)
		NumDimensions++;
	if (numYRows > 0)
		NumDimensions++;
	if (numZRows > 0)
		NumDimensions++;
	// calculate the dimension size
	unsigned int DimensionSize = (numXRows + 1) * (numYRows + 1) * (numZRows + 1);

	// set the band width parameters used later for band sweep
	// update resolution if needed

	SetBandParameters(BandSelection, BandBottom, BandLength, Frequency, resolution, WireDiameter, Scale);

	/*TODO :
	 Check X, Y, Z sizes against the resolution. Either correct it or warn the user that
	 the selected size won't be used. */

	/*TODO :
	 Tried using just one axis here (straight dipole) but the problem in the 160 meter model
	 is that the resolution is so large the SWR model can't get better when the
	 antenna goes off balance so far on one side (left or right). 2M works fine
	 with just one dimension*/
	if (!NumDimensions) {
		ShowMessage("One axis with area to evolve the antenna at minimum must be provided.");
		return true;
	}
	// calcuate wire struct array size
	// compensate for any row equaling zero
	unsigned long numberofwiresNeeded = (numXRows + 1) * (numYRows + 1) * (numZRows + 1) * 3;
	// if the wire array already exists delete it
	if (Nec_Wires != NULL) {
		delete[]Nec_Wires;
		Nec_Wires = NULL;
	}
	// now create the new array
	Nec_Wires = new nec_wires[numberofwiresNeeded];
	// create the frequency
	// set for frequency sweep
	Nec_Frequency[0].StepType = 0;
	const double Diameter = *WireDiameter;
	/*TODO : Make sure to set the correct frequency choices*/Nec_Frequency[0].FrequencyMHz = *Frequency;
	Nec_Frequency[0].BandWidth = 0.0;
	Nec_Frequency[0].FrequencyStepSize = 1.00;
	if (Nec_Frequency[0].FrequencyStepSize) {
		Nec_Frequency[0].FrequencySteps = Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
	}
	else {
		Nec_Frequency[0].FrequencySteps = 1;
	}
	unsigned int arrayCounter = 0;
	// do if all are more than 1 we have a cube
	// now loop through the X, Y and Z making the wires
	// force into loop
	double x = 0;
	double y = 0;
	double z = 0;
	do /*for (; x < MaxWidthMeters; x += resolution)*/ {
		do /*for (; y < MaxDepthMeters; y += resolution)*/ {
			do /*for (; z < (MaxHeightMeters - MinHeightMeters); z += resolution)*/ {
				double zheightCorrected = z + *MinHeightMeters;
				// for each wire need to go in three directions
				// the X,Y and Z resolution and create those wires
				if (x < *MaxWidthMeters) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x + *resolution;
					Nec_Wires[arrayCounter].Y2 = y;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected;
					double wirelength = WireLength(x, y, zheightCorrected, x + *resolution, y, zheightCorrected);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  &wirelength);
					Nec_Wires[arrayCounter].Diameter = Diameter;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
				if (y < *MaxDepthMeters) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x;
					Nec_Wires[arrayCounter].Y2 = y + *resolution;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected;
					double wirelength = WireLength(x, y, zheightCorrected, x, y + *resolution, zheightCorrected);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  &wirelength);
					Nec_Wires[arrayCounter].Diameter = Diameter;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
				if (z < (MaxHeightMeters - MinHeightMeters)) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].Segments = 1;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x;
					Nec_Wires[arrayCounter].Y2 = y;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected + *resolution;
					double wirelength = WireLength(x, y, zheightCorrected, x, y, zheightCorrected + *resolution);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  &wirelength);
					Nec_Wires[arrayCounter].Diameter = Diameter;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
				if ((MaxHeightMeters - MinHeightMeters) != 0) {
					z += *resolution;
				}
			}
			while ((z <= (MaxHeightMeters - MinHeightMeters)) && ((MaxHeightMeters - MinHeightMeters) != 0));
			if (*MaxDepthMeters != 0) {
				y += *resolution;
				z = 0;
			}
		}
		while ((y <= *MaxDepthMeters) && (*MaxDepthMeters != 0));
		if (*MaxWidthMeters != 0) {
			x += *resolution;
			y = 0;
			z = 0;
		}
	}
	while ((x <= *MaxWidthMeters) && (*MaxWidthMeters != 0));

	// update display counters
	EnableVectorCountLB->Caption = IntToStr((int)numberofwiresNeeded);
	DisableVectorCountLB->Caption = IntToStr((int)arrayCounter);

	// create the wire grounds (if Z=0 is ground)
	Nec_Ground[0].Z0ground = true;
	// create the ground type
	Nec_Grounds[0].GroundType = 2;
	Nec_Grounds[0].NumberOfRadials = 0;
	Nec_Grounds[0].RelativeDielectricConstant = 4;
	Nec_Grounds[0].GroundConductivity = 0.003; // mhoms/m
	// create the excitation
	// set the wire which the feedpoint is attached to
	// loop through the wires and find the center point
	/*TODO : Not the ideal way to do this user should select feed point*/
	// problem here when calc not in tenths
	int xCtr = (double) * MaxWidthMeters / *resolution / 2;
	int yCtr = (double) * MaxDepthMeters / *resolution / 2;
	double xCenter = xCtr * *resolution;
	double yCenter = yCtr * *resolution;
	double X1, Y1, Z1, X2, Y2, Z2;
	bool Feednotfound = true;
	for (int findFeed1 = 0; findFeed1 < (arrayCounter - 2); findFeed1++) {
		double cubesegX1, cubesegY1, cubesegZ1, cubesegX2, cubesegY2, cubesegZ2, fdHeight;
		cubesegX1 = Nec_Wires[findFeed1].X1;
		cubesegY1 = Nec_Wires[findFeed1].Y1;
		cubesegZ1 = Nec_Wires[findFeed1].Z1;
		cubesegX2 = Nec_Wires[findFeed1].X2;
		cubesegY2 = Nec_Wires[findFeed1].Y2;
		cubesegZ2 = Nec_Wires[findFeed1].Z2;
		fdHeight = *FeedPointHeight;
		// check if this point is on or in between the X
		if ((cubesegX1 <= xCenter) && (cubesegX2 >= xCenter) && (cubesegY1 == yCenter) && (cubesegY2 == yCenter) &&
		  (cubesegZ1 == fdHeight) && (cubesegZ2 == fdHeight)) {
			Feednotfound = false;
		}
		// check if this point is on or in between the Y
		else if ((cubesegX1 == xCenter) && (cubesegX2 == xCenter) && (cubesegY1 <= yCenter) && (cubesegY2 >= yCenter) &&
		  (cubesegZ1 == fdHeight) && (cubesegZ2 == fdHeight)) {
			Feednotfound = false;
		}
		// check if this point is on or in between the Z
		else if ((cubesegX1 == xCenter) && (cubesegX2 == xCenter) && (cubesegY1 == yCenter) && (cubesegY2 == yCenter) &&
		  (cubesegZ1 <= fdHeight) && (cubesegZ2 >= fdHeight)) {
			Feednotfound = false;
		}
		// check if flag was set for finding wire
		if (!Feednotfound) {
			Nec_Excitation[0].WireID = findFeed1;
			Nec_Excitation[0].SourceTag = Nec_Wires[findFeed1].Segments / 2;
			Nec_Wires[findFeed1].Enabled = true;
			// push the feedpoint onto the list of enabled wire IDs
			triedEnable.push_back(findFeed1);
			// get the two wires which would be attached to this point
			X1 = Nec_Wires[findFeed1].X1;
			X2 = Nec_Wires[findFeed1].X2;
			Y1 = Nec_Wires[findFeed1].Y1;
			Y2 = Nec_Wires[findFeed1].Y2;
			Z1 = Nec_Wires[findFeed1].Z1;
			Z2 = Nec_Wires[findFeed1].Z2;
			break;
		}
	}
	// if error choose any wire point for feed for debug in 4NEC2
	if (Feednotfound) {
		Nec_Excitation[0].SourceTag = 0;
		Nec_Excitation[0].WireID = 0;
	}
	// chose the middle segment
	Nec_Excitation[0].ExcitationType = 0;
	Nec_Excitation[0].VoltageReal = 1;
	Nec_Excitation[0].VoltageImag = 0;
	Nec_Excitation[0].RelativeAdmittanceType = 0;
	// create the radiation requirements
	Nec_Radiation[0].Mode = 0;
	Nec_Radiation[0].ThetaAngleCount = 1; // 19
	Nec_Radiation[0].PhiAngleCount = 1; // 73;
	Nec_Radiation[0].ThetaStartAngle = 0;
	Nec_Radiation[0].PhiStartAngle = 0;
	Nec_Radiation[0].ThetaStepAngle = 5; // 5
	Nec_Radiation[0].PhiStepAngle = 5; // 5
	// set the total counts
	Nec_Counts[0].WireCount = arrayCounter;
	Nec_Counts[0].LoadsCount = 0;
	Nec_Counts[0].GroundsCount = 1;
	Nec_Counts[0].ExcitationsCount = 1;
	Nec_Counts[0].FrequenciesCount = 1;
	// save the base file
	WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds, Nec_Excitation,
	  Nec_Frequency, Nec_Radiation);
	// RenameFile(tempfilename, "CubeBase" + tempfilename);
	// check to make sure the feed point was found
	unsigned int FeedLineID = Nec_Excitation[0].WireID;
	if (Feednotfound) {
		ShowMessage("Feedline not found in cube matrix.");
		return true;
	}
	// disable the cube elements
	// now loop through the X, Y and Z making the wires
	for (int disablearrayCounter = 0; disablearrayCounter < arrayCounter; disablearrayCounter++) {
		if (Nec_Wires[disablearrayCounter].ID != Nec_Excitation[0].WireID) {
			Nec_Wires[disablearrayCounter].Enabled = false;
		}
	}
	/*TODO : NEC will fault if we don't have at least 2 active segments*/
	/*TODO :
	 With the cube layout if only one axis like x=30 X2 will match X1, Y2 and Y1 etc etc.
	 Have to watch for this; This certainly creates a possible mess for other
	 directions*/
	/*
	 for (int findFeed2 = 0; findFeed2 < arrayCounter; findFeed2++) {
	 if ((Nec_Wires[findFeed2].X2 == X1) && ((Nec_Wires[findFeed2].Y2 == Y2) && (Nec_Wires[findFeed2].Y1 == Y2)) &&
	 ((Nec_Wires[findFeed2].Z2 == Z2) && (Nec_Wires[findFeed2].Z1 == Z2)) &&
	 (Nec_Excitation[0].WireID != findFeed2)) {
	 Nec_Wires[findFeed2].Enabled = true;
	 break;
	 }
	 }
	 for (int findFeed3 = 0; findFeed3 < arrayCounter; findFeed3++) {
	 if ((Nec_Wires[findFeed3].X1 == X2) && ((Nec_Wires[findFeed3].Y2 == Y1) && (Nec_Wires[findFeed3].Y1 == Y1)) &&
	 ((Nec_Wires[findFeed3].Z2 == Z1) && (Nec_Wires[findFeed3].Z1 == Z1)) &&
	 (Nec_Excitation[0].WireID != findFeed3)) {
	 Nec_Wires[findFeed3].Enabled = true;
	 break;
	 }
	 }
	 */return false;
}

double __fastcall TForm1::WireLength(double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
	double points = Power(abs(X1 - X2), 2) + Power(abs(Y1 - Y2), 2) + Power(abs(Z1 - Z2), 2);
	double wirelength = Sqrt(points);
	return wirelength;
}

unsigned int __fastcall TForm1::CalculateMinimumNumSegments(double FrequencyMHz, double* wirelength) {
	// check wire length to see if 1 segment would even work
	double fr = (1.0e+6 * FrequencyMHz) / em::speed_of_light();
	double SegLengthNeeded = 0.020 * (em::speed_of_light() / (FrequencyMHz * 1.0E+6));
	if (*wirelength * fr < 0.02) {
		/*TODO :
		 this needs further investigation as to why factoring additional 1% is needed*/ *wirelength = SegLengthNeeded;
		// * 1.05;
		return 0; // return indication that wire size needs to change
	}

	double NumberOfSegmentsNeeded = double(*wirelength / SegLengthNeeded);
	int NumSegmentsNeeded = NumberOfSegmentsNeeded;
	if (NumSegmentsNeeded < NumberOfSegmentsNeeded) {
		NumSegmentsNeeded++;
	}
	double SegLenCheck = *wirelength / NumSegmentsNeeded * fr;
	/*
	 if (NumSegmentsNeeded < 2) {
	 throw Exception("Segment length too small in CalculateMinimumNumSegments");
	 }
	 // all should be scaled for 2 segments (hopefully)
	 NumSegmentsNeeded = 2;
	 */return NumSegmentsNeeded;
}

// ---------------------------------------------------------------------------
WideString TForm1::CreateNECFile(nec_counts * inNec_Counts, nec_wires * inNec_Wires, nec_wire_ground * inNec_Ground,
  nec_loads * inNec_Loads, nec_grounds * inNec_Grounds, nec_excitation * inNec_Excitation,
  nec_frequency * inNec_Frequency, nec_radiation * inNec_Radiation) {
	// choose a file name
	WideString filename = "dipole";
	WideString directory = ".";
	LPTSTR ptrfilename = filename.c_bstr();
	LPTSTR ptrdirectory = directory.c_bstr();
	TCHAR ptrtempname[MAX_PATH];
	/*TODO :
	 MAX_PATH has some kind of trouble here causing access violations
	 for 64 bit Windows at function so just using constant*/
	int result = GetTempFileName(ptrdirectory, ptrfilename, 0, &ptrtempname[0]);
	AnsiString outfileName(ptrtempname);
	if (result != 0) {
		// create a TStringList for the output file
		char file[MAX_PATH];
		AnsiString tempname(ptrtempname);
		strcpy(file, tempname.c_str());
		TFileStream* outFile = new TFileStream(tempname, fmOpenWrite);
		AnsiString line;
		// write the number of wires to the file
		for (int loop = 0; loop < inNec_Counts->WireCount; loop++) {
			// only add this wire line if it is enabled
			if (inNec_Wires[loop].Enabled) {
				line = "GW,";
				line += IntToStr((int)inNec_Wires[loop].ID) + ",";
				line += IntToStr((int)inNec_Wires[loop].Segments) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].X1) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].Y1) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].Z1) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].X2) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].Y2) + ",";
				line += FormatFloat("0.000", inNec_Wires[loop].Z2) + ",";
				line += FormatFloat("0.0000", inNec_Wires[loop].Diameter);
				line += "\r\n";
				try {
					outFile->Write(line.c_str(), line.Length());
				}
				catch (Exception &E) {
					ShowMessage("Line fault " + IntToStr(loop));
				}
			}
		}
		// write the wire ground information
		line = "GE," + IntToStr((int)inNec_Ground->Z0ground);
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		// write the loads
		// write the ground network information
		line = "GN,";
		line += IntToStr((int)inNec_Grounds->GroundType) + ",";
		line += IntToStr((int)inNec_Grounds->NumberOfRadials) + ",";
		line += IntToStr((int)inNec_Grounds->Unused1) + ",";
		line += IntToStr((int)inNec_Grounds->Unused2) + ",";
		line += FormatFloat("0.0000", inNec_Grounds->RelativeDielectricConstant) + ",";
		line += FormatFloat("0.0000", inNec_Grounds->GroundConductivity);
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		// write the excitation information
		line = "EX,";
		line += IntToStr((int)inNec_Excitation->ExcitationType) + ",";
		line += IntToStr((int)inNec_Excitation->WireID) + ",";
		line += IntToStr((int)inNec_Excitation->SourceTag) + ",";
		line += IntToStr((int)inNec_Excitation->RelativeAdmittanceType) + ",";
		line += FormatFloat("0.0000", inNec_Excitation->VoltageReal) + ",";
		line += FormatFloat("0.0000", inNec_Excitation->VoltageImag) + ",";
		line += FormatFloat("0", inNec_Excitation->RatioOfPolarization);
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		// write the frequency information
		line = "FR,";
		line += IntToStr((int)inNec_Frequency->StepType) + ",";
		line += IntToStr((int)inNec_Frequency->FrequencySteps) + ",";
		line += IntToStr((int)inNec_Frequency->Unused1) + ",";
		line += IntToStr((int)inNec_Frequency->Unused2) + ",";
		line += FormatFloat("0.0000", inNec_Frequency->FrequencyMHz) + ",";
		line += FormatFloat("0.0000", inNec_Frequency->FrequencyStepSize);
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		// use the extended kernal
		line = "EK";
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		// write the radiation information
		line = "RP,";
		line += IntToStr((int)inNec_Radiation->Mode) + ",";
		line += IntToStr((int)inNec_Radiation->ThetaAngleCount) + ",";
		line += IntToStr((int)inNec_Radiation->PhiAngleCount) + ",";
		line += IntToStr((int)inNec_Radiation->AxisType);
		line += IntToStr((int)inNec_Radiation->NormalizedGainType);
		line += IntToStr((int)inNec_Radiation->PowerGain);
		line += IntToStr((int)inNec_Radiation->Averaging) + ",";
		line += IntToStr((int)inNec_Radiation->ThetaStartAngle) + ",";
		line += IntToStr((int)inNec_Radiation->PhiStartAngle) + ",";
		line += IntToStr((int)inNec_Radiation->ThetaStepAngle) + ",";
		line += IntToStr((int)inNec_Radiation->PhiStepAngle);
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		WideString wtempfilename(ptrtempname);
		line = "EN";
		line += "\r\n";
		outFile->Write(line.c_str(), line.Length());
		delete outFile;
		/*
		 AnsiString extension = ExtractFileExt(wtempfilename);
		 int extPosition = wtempfilename.Pos(extension);
		 AnsiString newName = wtempfilename.SubString(1, extPosition) + "nec";
		 for (int loop = 0; loop < 100; loop++) {
		 bool result = RenameFile(wtempfilename, newName);
		 Application->ProcessMessages();
		 if (!result) {
		 Sleep(300);
		 ErrorMemo->Lines->Add("Failed rename " + newName + " from " + wtempfilename);
		 if (loop == 8) {
		 ShowMessage("Error: Trouble renaming temporary file");
		 }
		 if (loop == 8) {
		 return "";
		 }
		 }
		 else {
		 // success renaming file
		 break;
		 }
		 }
		 newName = newName.SubString(3, newName.Length() - 1);
		 return newName;
		 */return tempname;
	}
	return "";
}

void __fastcall TForm1::CancelClick(TObject * Sender) {
	Cancel->Tag = 1;
}

// ---------------------------------------------------------------------------
bool __fastcall TForm1::BuildDipoleModel(double* MaxHeightMeters, double* MinHeightMeters, double* MaxWidthMeters,
  double* MaxDepthMeters, double* resolution, double* FeedPointHeight, double* Frequency, double* WireDiameter,
  double* Scale, unsigned int BandSelection, double* BandBottom, double* BandLength) {

	GetInitialBandResolution(BandSelection, resolution, Scale);

	// adjust the inputs to M. CM is necessary
	AdjustUserInputSizeByScale(MaxWidthMeters, MaxDepthMeters, MaxHeightMeters, MinHeightMeters, FeedPointHeight,
	  Scale);
	// set the band width parameters used later for band sweep
	SetBandParameters(BandSelection, BandBottom, BandLength, Frequency, resolution, WireDiameter, Scale);

	// build the dipole model

	// create the feed points
	double FeedPointX;
	const double FeedPointY = 0;
	switch (BandSelection) {
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
			FeedPointX = 0.06;
			break;
		}
	case BAND_2: {
		}
	case BAND_1_25: {
		}
	case BAND_70cm: {
			FeedPointX = 0.01;
			break;
		}
	case BAND_33cm: {
			FeedPointX = 0.01;
			break;
		}
	case BAND_23cm: {
			FeedPointX = 0.001;
			break;
		}
	}

	AnsiString BandName;
	switch (BandSelection) {
	case BAND_160: {
			BandName = "160M";
			break;
		}
	case BAND_80: {
			BandName = "80M";
			break;
		}
	case BAND_60: {
			BandName = "60M";
			break;
		}
	case BAND_40: {
			BandName = "40M";
			break;
		}
	case BAND_30: {
			BandName = "30M";
			break;
		}
	case BAND_20: {
			BandName = "20M";
			break;
		}
	case BAND_17: {
			BandName = "17M";
			break;
		}
	case BAND_15: {
			BandName = "15M";
			break;
		}
	case BAND_12: {
			BandName = "12M";
			break;
		}
	case BAND_10: {
			BandName = "10M";
			break;
		}
	case BAND_6: {
			BandName = "6M";
			break;
		}
	case BAND_2: {
			BandName = "2M";
			break;
		}
	case BAND_1_25: {
			BandName = "1.25M";
			break;
		}
	case BAND_70cm: {
			BandName = "70cm";
			break;
		}
	case BAND_33cm: {
			BandName = "33cm";
			break;
		}
	case BAND_23cm: {
			BandName = "23cm";
			break;
		}
	}

	unsigned int WireCount = 0; // count for number of wires in array (always 1 starting for feedpoint)
	// if the wire array already exists delete it
	if (Nec_Wires != NULL) {
		delete[]Nec_Wires;
		Nec_Wires = NULL;
	}

	// now create the new array
	Nec_Wires = new nec_wires[1]; // mock array just to check segment sizing for frequency
	Nec_Wires[0].ID = WireCount;
	Nec_Wires[0].Segments = 1;
	Nec_Wires[0].X1 = -FeedPointX;
	Nec_Wires[0].Y1 = 0;
	Nec_Wires[0].Z1 = *FeedPointHeight;
	Nec_Wires[0].X2 = FeedPointX;
	Nec_Wires[0].Y2 = 0;
	Nec_Wires[0].Z2 = *FeedPointHeight;
	Nec_Wires[0].Diameter = *WireDiameter;
	Nec_Wires[0].Enabled = true;

	// measure feedpoint wire length
	double FeedLength = WireLength(Nec_Wires[WireCount].X1, Nec_Wires[WireCount].Y1, Nec_Wires[WireCount].Z1,
	  Nec_Wires[WireCount].X2, Nec_Wires[WireCount].Y2, Nec_Wires[WireCount].Z2);
	// must calculate the segment sizing on the lowest frequency which will be tested
	// which is the low part of the band
	/*TODO :
	 Need to investigate why 1% margin is needed here for the bottom of the band
	 because the model run can work for 60M default until the band sweep
	 is done after which the segment size is <.02*/
	unsigned int FeedMinSegs = CalculateMinimumNumSegments(*BandBottom * 0.95, &FeedLength);
	// check if the feed length is too small
	if (FeedMinSegs == 0) {
		// if it is for now we have no choice but to extend it's size
		// this has to do with limitations on the NEC modeling
		FeedPointX = FeedLength / 2;
		Nec_Wires[0].X1 = -FeedPointX;
		Nec_Wires[0].X2 = FeedPointX;
		FeedMinSegs = 1;
	}

	/*TODO : Check that the user provided X larger than the feedpoint X. */

	ErrorMemo->Lines->Add("Band selected: " + BandName);
	ErrorMemo->Lines->Add("Band Bottom: " + FormatFloat("0.000", *BandBottom));
	// ErrorMemo->Lines->Add("FeedLength: " + FormatFloat("0.000", FeedLength));
	// ErrorMemo->Lines->Add("FeedMinSegs: " + IntToStr((__int64)FeedMinSegs));
	// ErrorMemo->Lines->Add("Resolution Before: " + FormatFloat("0.000", *resolution));
	// ErrorMemo->Lines->Add("Segment Size: " + FormatFloat("0.000", FeedLength / FeedMinSegs));
	// calculate the wire length to segment size ratio needed for the rest of the wires
	// so it's in agreement with the feed point otherwise NEC calcs will fault
	double SegsPerLength = FeedLength * (double)FeedMinSegs;
	if (FeedMinSegs == 1) {
		*resolution = FeedLength;
	}
	else {
		*resolution = FeedLength / FeedMinSegs;
	}
	// ErrorMemo->Lines->Add("Resolution After: " + FormatFloat("0.000", *resolution));

	// find out how many possible combinations there are to set up the wire matrix
	unsigned int MatrixSizeZ = ((*MaxHeightMeters - *MinHeightMeters) / *resolution) + 1;
	unsigned int MatrixSizeY = (*MaxDepthMeters / 2 / *resolution) + 1;
	unsigned int MatrixSizeX = ((*MaxWidthMeters / 2 - (FeedPointX + *resolution)) / *resolution) + 1;
	unsigned int MatrixSize = MatrixSizeX * MatrixSizeY * MatrixSizeZ;
	// ErrorMemo->Lines->Add("Dipole Matrix Size: " + IntToStr((__int64)MatrixSize));

	delete[]Nec_Wires;

	if (MatrixSize == 0) {
		ShowMessage("Unable to calculate X,Y,Z sizes too small provide no grid.");
		return true;
	}

	// if the wire array already exists delete it
	if (Nec_Wires != NULL) {
		delete[]Nec_Wires;
		Nec_Wires = NULL;
	}

	// now create the new array
	Nec_Wires = new nec_wires[(MatrixSize + 1) * 2]; // times 2 for mirrored image
	Nec_Wires[0].ID = WireCount;
	Nec_Wires[0].Segments = 1;
	Nec_Wires[0].X1 = -FeedPointX;
	Nec_Wires[0].Y1 = 0;
	Nec_Wires[0].Z1 = *FeedPointHeight;
	Nec_Wires[0].X2 = FeedPointX;
	Nec_Wires[0].Y2 = 0;
	Nec_Wires[0].Z2 = *FeedPointHeight;
	Nec_Wires[0].Diameter = *WireDiameter;
	Nec_Wires[0].Enabled = true;

	// loop through all the X, Y, and Z combinations
	WireCount++;
	// X and Y are divided by 2 because we are mirroring the image
	for (double Z = *MinHeightMeters; Z <= *MaxHeightMeters; Z += *resolution) {
		for (double Y = 0; Y <= (*MaxDepthMeters / 2); Y += *resolution) {
			// add resolution right away to X to now allow the feedpoint itself
			for (double X = FeedPointX + *resolution; X <= (*MaxWidthMeters / 2); X += *resolution) {
				// need to calculate for proper number of segments needed
				double WireLen = WireLength(FeedPointX, FeedPointY, *FeedPointHeight, X, Y, Z);
				unsigned int FeedMinSegs = CalculateMinimumNumSegments(*BandBottom, &WireLen);
				// check this wire length to make sure it's at least bigger
				// than the minimum segment size otherwise skip it
				if (WireLen >= SegsPerLength) {
					Nec_Wires[WireCount].ID = WireCount;
					// the one XYZ always attached to feedpoint on this side
					Nec_Wires[WireCount].X1 = FeedPointX; // always goes from feedpoint
					Nec_Wires[WireCount].Y1 = FeedPointY;
					Nec_Wires[WireCount].Z1 = *FeedPointHeight;
					// the other side is the variable
					Nec_Wires[WireCount].X2 = X;
					Nec_Wires[WireCount].Y2 = Y;
					Nec_Wires[WireCount].Z2 = Z;
					double MinSegs = WireLen / SegsPerLength;
					unsigned int MinSegsAsint = MinSegs;
					// if (MinSegsAsint < 1) {
					// MinSegsAsint++;
					// }
					// seg size * freq
					Nec_Wires[WireCount].Segments = MinSegsAsint;
					Nec_Wires[WireCount].Diameter = *WireDiameter;
					Nec_Wires[WireCount].Enabled = true;
					// increase the wire counter
					WireCount++;
					// now do the mirror image
					// update the total wire count for the matrix sizing indicator
					// which is the total number of possible wires
					Nec_Wires[WireCount].ID = WireCount;
					// need to calculate for proper number of segments needed
					Nec_Wires[WireCount].Segments = MinSegsAsint;
					// the one XYZ always attached to feedpoint on this side
					Nec_Wires[WireCount].X1 = -FeedPointX; // always goes from feedpoint
					Nec_Wires[WireCount].Y1 = 0;
					Nec_Wires[WireCount].Z1 = *FeedPointHeight;
					// the other side is the variable
					Nec_Wires[WireCount].X2 = -X;
					Nec_Wires[WireCount].Y2 = -Y;
					Nec_Wires[WireCount].Z2 = Z;
					Nec_Wires[WireCount].Diameter = *WireDiameter;
					Nec_Wires[WireCount].Enabled = true;
					// increase the wire counter
					WireCount++;
				}
			}
		}
	}

	// set the remaining NEC parameters
	// create the wire grounds (if Z=0 is ground)
	Nec_Ground[0].Z0ground = true;
	// create the ground type
	Nec_Grounds[0].GroundType = 2;
	Nec_Grounds[0].NumberOfRadials = 0;
	Nec_Grounds[0].RelativeDielectricConstant = 4;
	Nec_Grounds[0].GroundConductivity = 0.003; // mhoms/m
	// create the excitation
	// set the wire which the feedpoint is attached to
	Nec_Excitation[0].WireID = 0; // dipole model feed point wire is always zero
	// chose the middle segment
	Nec_Excitation[0].SourceTag = 1;
	Nec_Excitation[0].ExcitationType = 0;
	Nec_Excitation[0].VoltageReal = 1;
	Nec_Excitation[0].VoltageImag = 0;
	Nec_Excitation[0].RelativeAdmittanceType = 0;
	// create the radiation requirements
	Nec_Radiation[0].Mode = 0;
	Nec_Radiation[0].ThetaAngleCount = 1;
	Nec_Radiation[0].PhiAngleCount = 1;
	Nec_Radiation[0].ThetaStartAngle = 0;
	Nec_Radiation[0].PhiStartAngle = 0;
	Nec_Radiation[0].ThetaStepAngle = 5;
	Nec_Radiation[0].PhiStepAngle = 5;
	// set the total counts
	Nec_Counts[0].WireCount = WireCount;
	Nec_Counts[0].LoadsCount = 0;
	Nec_Counts[0].GroundsCount = 1;
	Nec_Counts[0].ExcitationsCount = 1;
	Nec_Counts[0].FrequenciesCount = 1;
	ErrorMemo->Lines->Add("WireCount " + IntToStr((__int64)WireCount));
	// create the frequency
	// set for frequency sweep
	Nec_Frequency[0].StepType = 0;
	const double Diameter = *WireDiameter;
	/*TODO : Make sure to set the correct frequency choices*/Nec_Frequency[0].FrequencyMHz = *Frequency;
	Nec_Frequency[0].BandWidth = 0.0;
	Nec_Frequency[0].FrequencyStepSize = 1.00;
	if (Nec_Frequency[0].FrequencyStepSize) {
		Nec_Frequency[0].FrequencySteps = Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
	}
	else {
		Nec_Frequency[0].FrequencySteps = 1;
	}
	// create the NEC file
	// save the base file
	// WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds, Nec_Excitation,
	// Nec_Frequency, Nec_Radiation);
	// base model built now disable every wire combo after wires 0-2
	for (unsigned int loopDis = 3; loopDis < WireCount; loopDis++) {
		Nec_Wires[loopDis].Enabled = false;
	}
	return false;
}

// this function gets the resolution of the grids used based on the radio band
// default starting condition
void __fastcall TForm1::GetInitialBandResolution(unsigned int BandSelection, double* resolution, double* Scale) {
	// first try the default resolution and scale
	switch (BandSelection) {
	case BAND_160: {
			*resolution = 1;
			break;
		}
	case BAND_80: {
			*resolution = 1;
			break;
		}
	case BAND_60: {
			*resolution = 1;
			break;
		}
	case BAND_40: {
			*resolution = 1;
			break;
		}
	case BAND_30: {
			*resolution = 1;
			break;
		}
	case BAND_20: {
			*resolution = 1;
			break;
		}
	case BAND_17: {
			*resolution = 1;
			break;
		}
	case BAND_15: {
			*resolution = 1;
			break;
		}
	case BAND_12: {
			*resolution = 1;
			break;
		}
	case BAND_10: {
			*resolution = 1;
			break;
		}
	case BAND_6: {
			*resolution = 0.6;
			break;
		}
	case BAND_2: {
			*resolution = 0.1;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_1_25: {
			*resolution = 0.1;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_70cm: {
			*resolution = 0.033;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_33cm: {
			*resolution = 0.003;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_23cm: {
			*resolution = 0.010;
			*Scale = SCALE_CM;
			break;
		}
	}
}

void TForm1::AdjustUserInputSizeByScale(double* MaxWidthMeters, double* MaxDepthMeters, double* MaxHeightMeters,
  double* MinHeightMeters, double* FeedPointHeight, double* Scale) {
	*MaxWidthMeters *= *Scale;
	*MaxDepthMeters *= *Scale;
	*MaxHeightMeters *= *Scale;
	*MinHeightMeters *= *Scale;
	*FeedPointHeight *= *Scale;
}

void TForm1::SetBandParameters(unsigned int BandSelection, double* BandBottom, double*BandLength, double* Frequency,
  double* resolution, double* WireDiameter, double* Scale) {
	// adjust the resolution based on the number of dimensions
	switch (BandSelection) {
	case BAND_160: {
			*BandBottom = 1.8;
			*BandLength = 0.2;
			*Frequency = 1.9;
			*resolution = 1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_80: {
			*BandBottom = 3.5;
			*BandLength = 0.5;
			*Frequency = 3.75;
			*resolution = 1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_60: {
			*BandBottom = 5.3305;
			*BandLength = 0.073;
			*Frequency = 5.4035;
			*resolution = 1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_40: {
			*BandBottom = 7.0;
			*BandLength = 0.3;
			*Frequency = 7.15;
			*resolution = 1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_30: {
			*BandBottom = 10.1;
			*BandLength = 0.15;
			*Frequency = 10.125;
			*resolution = 1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_20: {
			*BandBottom = 14.0;
			*BandLength = 0.35;
			*Frequency = 14.175;
			*resolution = 0.5;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_17: {
			*BandBottom = 18.068;
			*BandLength = 0.1;
			*Frequency = 18.118;
			*resolution = 0.5;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_15: {
			*BandBottom = 21.0;
			*BandLength = 0.45;
			*Frequency = 21.225;
			*resolution = 0.5;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_12: {
			*BandBottom = 24.89;
			*BandLength = 0.1;
			*Frequency = 24.94;
			*resolution = 0.5;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_10: {
			*BandBottom = 28.0;
			*BandLength = 1.7;
			*Frequency = 28.85;
			*resolution = 0.5;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_6: {
			*BandBottom = 50.0;
			*BandLength = 4.0;
			*Frequency = 52;
			*resolution = 0.1;
			*WireDiameter = 0.00205;
			break;
		}
	case BAND_2: {
			*BandBottom = 144.0;
			*BandLength = 4.0;
			*Frequency = 146;
			*resolution = 0.1;
			*WireDiameter = 0.00205;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_1_25: {
			*BandBottom = 219.0;
			*BandLength = 6.0;
			*Frequency = 222;
			*resolution = 0.1;
			*WireDiameter = 0.00205;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_70cm: {
			*BandBottom = 420.0;
			*BandLength = 30.0;
			*Frequency = 435;
			*resolution = 0.033;
			*WireDiameter = 0.00205;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_33cm: {
			*BandBottom = 902.0;
			*BandLength = 26.0;
			*Frequency = 915;
			*resolution = 0.024;
			*WireDiameter = 0.00205;
			*Scale = SCALE_CM;
			break;
		}
	case BAND_23cm: {
			*BandBottom = 1240.0;
			*BandLength = 60.0;
			*Frequency = 1270;
			*resolution = 0.010;
			*WireDiameter = 0.00205;
			*Scale = SCALE_CM;
			break;
		}
	}
}

void __fastcall TForm1::FormShow(TObject * Sender) {
#ifdef _WIN64
	Caption = "NECEvolve Alpha Development Version 0.1.10 Win64";
#else
	Caption = "NECEvolve Alpha Development Version 0.1.10 Win32";
#endif

}
// ---------------------------------------------------------------------------
