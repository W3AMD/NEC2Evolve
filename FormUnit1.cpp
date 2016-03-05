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
	char name[MAX_PATH];
	char option[] = "-i";
	char* atname[3];
	atname[0] = nada;
	atname[1] = option;
	atname[2] = name;
	strcpy(name, Filename.c_str());
	StatusCaption->Caption = "Running";
	StatusCaption->Update();
	Application->ProcessMessages();
	FILE* input_fp = NULL, *output_fp = NULL;
	try {
		mainforNEC(3, atname, &s_context, input_fp, output_fp);
	}
	catch (const char& message) {
		// ShowMessage(AnsiString(message));
		// close the files so they don't stay open
		if (input_fp != NULL) {
			fclose(input_fp);
		}
		if (output_fp != NULL) {
			fclose(output_fp);
		}
		StatusCaption->Caption = "Ready";
		file_results->Error = true;
		strcpy(file_results->ErrorMessage, &message);
		return -1;
		/*nec_error_mode nem(s_output);
		 s_output.line("NEC++ Runtime Error: ");
		 s_output.line(message);
		 */
		// exit(1);
	}
	catch (nec_exception& nex) {
		// ShowMessage(AnsiString(nex.get_message().c_str()));
		if (input_fp != NULL) {
			fclose(input_fp);
		}
		if (output_fp != NULL) {
			fclose(output_fp);
		}
		StatusCaption->Caption = "Ready";
		file_results->Error = true;
		strcpy(file_results->ErrorMessage, nex.get_message().c_str());
		// file_results->ErrorMessage = AnsiString(nex->get_message().c_str());
		file_results->SegmentErrorType = nex.SegmentErrorType;
		file_results->SegmentNumber = nex.segmentnumber;
		return -1;
		/*nec_error_mode nem(s_output);
		 s_output.line("NEC++ Runtime Error: ");
		 s_output.line(nex->get_message().c_str());
		 */
		// exit(1);
	}
	catch (...) {
		// ShowMessage("NEC Unhandled exception");
		StatusCaption->Caption = "Ready";
		if (input_fp != NULL) {
			fclose(input_fp);
		}
		if (output_fp != NULL) {
			fclose(output_fp);
		}
		file_results->Error = true;
		strcpy(file_results->ErrorMessage, "NEC Unhandled exception");
		return -2;
		/*nec_error_mode nem(s_output);
		 s_output.line("NEC++ Runtime Error: ");
		 s_output.line(" Unknown exception");
		 */
		// exit(1);
	}
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
		Series4->AddXY(frequency / 1.0E+6, maxFrequencyTotalGaindB);
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
					if (maxHorzdBGainPhiIndex == phiIndex) {
						gain = radiation->get_power_gain_horiz(thetaIndex, phiIndex);
						if (gain < -50)
							gain = -50;
						PolarSeries4->AddPolar(thetaAngle + 90, gain, "", clTeeColor);
					}
					if (maxVertdBGainPhiIndex == phiIndex) {
						gain = radiation->get_power_gain_vert(thetaIndex, phiIndex);
						if (gain < -50)
							gain = -50;
						PolarSeries3->AddPolar(thetaAngle + 90, gain, "", clTeeColor);
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
						// now have the index to the opposite angle
						if (!found) {
							// throw Exception
							// ("Angle not found in horz graph side shot.");
						}
						else {
							gain = radiation->get_power_gain_horiz(thetaIndex, findPhiAngleIndex);
							if (gain < -50)
								gain = -50;
							double newAngle = -thetaAngle - 90;
							PolarSeries4->AddPolar(newAngle + 180, gain, "", clTeeColor);
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
							double newAngle = -thetaAngle - 90;
							PolarSeries3->AddPolar(newAngle + 180, gain, "", clTeeColor);
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
	Cancel->Tag = 0;
	// reset the last swr to a terrible result
	LastVSWR = 9.99E+9;
	LastHorGain = -9.99E+9;
	Iteration = 0;
	Series5->Clear();
	Series6->Clear();
	Series7->Clear();
	Series8->Clear();
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
	SWR_Optimize_VSWR.clear();
	SWR_Optimize_WireID.clear();
	Optimize_HorzGain.clear();

	graphUpdateFlag = false;
	// set for no last wire disabled
	LastChangedWire = -1;
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
		float MaxHeightMeters = Designform->MaxHeight->Position;
		float CenterXMeters = (float)Designform->MaxXSize->Position / 2;
		float CenterYMeters = (float)Designform->MaxYSize->Position / 2;
		Chart4->Axes->Left->Automatic = false;
		Chart4->Axes->Left->Maximum = MaxHeightMeters;
		Chart4->Axes->Left->Minimum = Designform->MinHeight->Position;
		Chart4->Axes->Bottom->Automatic = false;
		Chart4->Axes->Bottom->Maximum = Designform->MaxXSize->Position;
		Chart4->Axes->Bottom->Minimum = 0;
		Chart4->Axes->DepthTop->Automatic = false;
		Chart4->Axes->DepthTop->Maximum = Designform->MaxYSize->Position;
		Chart4->Axes->DepthTop->Minimum = 0;
		Chart4->Axes->Depth->Automatic = false;
		Chart4->Axes->Depth->Maximum = Designform->MaxYSize->Position;
		Chart4->Axes->Depth->Minimum = 0;
		// prepare the nec input file
		unsigned int FeedpointWireID;
		unsigned int WireID = 0;
		if (Designform->AntennaType->ItemIndex == 0) {
			// dipole selected
			// add wires
			Nec_Wires = new nec_wires[10];
			nec_wires wirestemp;
			// create the frequency
			// set for frequency sweep
			Nec_Frequency[0].StepType = 0;
			Nec_Frequency[0].FrequencyMHz = 7.15;
			Nec_Frequency[0].BandWidth = 0.0;
			Nec_Frequency[0].FrequencyStepSize = 0.00;
			if (Nec_Frequency[0].FrequencyStepSize) {
				Nec_Frequency[0].FrequencySteps = Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
			}
			else {
				Nec_Frequency[0].FrequencySteps = 0;
			}
			// create the feedpoint wire 0
			const double startX1 = CenterXMeters - 0.75;
			const double startX2 = CenterXMeters + 0.75;
			const double startY1 = Designform->MinHeight->Position;
			const double startY2 = Designform->MinHeight->Position;
			const double feedpointheight = Designform->FeedHeight->Position;
			FeedpointWireID = WireID;
			// wire 0 feedpoint wire
			Nec_Wires[WireID].Diameter = 0.001;
			Nec_Wires[WireID].Support = true;
			Nec_Wires[WireID].X1 = startX1;
			Nec_Wires[WireID].Y1 = startY1;
			Nec_Wires[WireID].Z1 = feedpointheight;
			Nec_Wires[WireID].X2 = startX2;
			Nec_Wires[WireID].Y2 = startY2;
			Nec_Wires[WireID].Z2 = feedpointheight;
			double points = Power(abs(Nec_Wires[WireID].X1 - Nec_Wires[WireID].X2), 2) +
			  Power(abs(Nec_Wires[WireID].Y1 - Nec_Wires[WireID].Y2), 2) +
			  Power(abs(Nec_Wires[WireID].Z1 - Nec_Wires[WireID].Z2), 2);
			double wirelength = Sqrt(points);
			Nec_Wires[WireID].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz, wirelength);
			// set the attachment flag to negative one which means
			// is not an end wire and not known to attach to another wire
			// always the last wire in the series is the one which is marked
			// attached
			Nec_Wires[WireID].AttachedToX1Y1Z1ID = -1;
			Nec_Wires[WireID].AttachedToX2Y2Z2ID = -1;
			Nec_Wires[WireID].Enabled = true;
			Nec_Wires[WireID].ID = WireID;
			WireID++;
			// create wire 1
			Nec_Wires[WireID].Diameter = 0.001;
			Nec_Wires[WireID].Support = true;
			Nec_Wires[WireID].X1 = startX1;
			Nec_Wires[WireID].Y1 = startY1;
			Nec_Wires[WireID].Z1 = feedpointheight;
			Nec_Wires[WireID].X2 = 0;
			Nec_Wires[WireID].Y2 = 0;
			Nec_Wires[WireID].Z2 = Designform->MaxHeight->Position;
			Nec_Wires[WireID].AttachedToX1Y1Z1ID = -1;
			Nec_Wires[WireID].AttachedToX2Y2Z2ID = 0;
			Nec_Wires[WireID].Enabled = true;
			Nec_Wires[WireID].ID = WireID;
			points = Power(abs(Nec_Wires[WireID].X1 - Nec_Wires[WireID].X2), 2) +
			  Power(abs(Nec_Wires[WireID].Y1 - Nec_Wires[WireID].Y2), 2) +
			  Power(abs(Nec_Wires[WireID].Z1 - Nec_Wires[WireID].Z2), 2);
			wirelength = Sqrt(points);
			Nec_Wires[WireID].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz, wirelength);
			WireID++;
			// create wire 2
			Nec_Wires[WireID].Diameter = 0.001;
			Nec_Wires[WireID].Support = true;
			Nec_Wires[WireID].X1 = startX2;
			Nec_Wires[WireID].Y1 = startY2;
			Nec_Wires[WireID].Z1 = feedpointheight;
			Nec_Wires[WireID].X2 = Designform->MaxXSize->Position;
			Nec_Wires[WireID].Y2 = Designform->MaxYSize->Position;
			Nec_Wires[WireID].Z2 = Designform->MaxHeight->Position;
			Nec_Wires[WireID].AttachedToX1Y1Z1ID = -1;
			Nec_Wires[WireID].AttachedToX2Y2Z2ID = 0;
			Nec_Wires[WireID].Enabled = true;
			Nec_Wires[WireID].ID = WireID;
			points = Power(abs(Nec_Wires[WireID].X1 - Nec_Wires[WireID].X2), 2) +
			  Power(abs(Nec_Wires[WireID].Y1 - Nec_Wires[WireID].Y2), 2) +
			  Power(abs(Nec_Wires[WireID].Z1 - Nec_Wires[WireID].Z2), 2);
			wirelength = Sqrt(points);
			Nec_Wires[WireID].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz, wirelength);
			WireID++;
			// set the attachment flag to negative one which means
			// is not an end wire and not known to attach to another wire
			// always the last wire in the series is the one which is marked
			// attached
			/*Nec_Wires[WireID].AttachedToX1Y1Z1ID = -1;
			 Nec_Wires[WireID].AttachedToX2Y2Z2ID = -1;
			 Nec_Wires[WireID].ID = WireID;
			 */
			// create the wire grounds (if Z=0 is ground)
			Nec_Ground[0].Z0ground = true;
			// create the ground type
			Nec_Grounds[0].GroundType = 2;
			Nec_Grounds[0].NumberOfRadials = 0;
			Nec_Grounds[0].RelativeDielectricConstant = 4;
			Nec_Grounds[0].GroundConductivity = 0.003; // mhoms/m
			// create the excitation
			// set the wire which the feedpoint is attached to
			Nec_Excitation[0].WireID = FeedpointWireID;
			// chose the middle segment
			Nec_Excitation[0].SourceTag = 1;
			Nec_Excitation[0].ExcitationType = 0;
			Nec_Excitation[0].VoltageReal = 1;
			Nec_Excitation[0].VoltageImag = 0;
			Nec_Excitation[0].RelativeAdmittanceType = 0;
			// create the radiation requirements
			Nec_Radiation[0].Mode = 0;
			Nec_Radiation[0].ThetaAngleCount = 19;
			Nec_Radiation[0].PhiAngleCount = 73;
			Nec_Radiation[0].ThetaStartAngle = -90;
			Nec_Radiation[0].PhiStartAngle = 0;
			Nec_Radiation[0].ThetaStepAngle = 5;
			Nec_Radiation[0].PhiStepAngle = 5;
			// set the total counts
			Nec_Counts[0].WireCount = WireID;
			Nec_Counts[0].LoadsCount = 0;
			Nec_Counts[0].GroundsCount = 1;
			Nec_Counts[0].ExcitationsCount = 1;
			Nec_Counts[0].FrequenciesCount = 1;
		}
		// check for cube etch model
		else if (Designform->AntennaType->ItemIndex == 1) {
			// build cube model
			BuildCube(Designform->MaxHeight->Position, Designform->MinHeight->Position/*min height*/,
			  Designform->MaxXSize->Position, Designform->MaxYSize->Position, 1/*resolution*/,
			  Designform->FeedHeight->Position);
		}
		double wavelength = em::speed_of_light() / (Nec_Frequency[0].FrequencyMHz * 1.0E+6);
		// set flag in case user cancels
		double minSegmentLength = wavelength / 5;
		bool cancel = false;
		/*TODO : Error: Wire 1, seg 1, seg-len (1.969) differs more than
		 5 * seg-len (64.63) for wire 2*/
		// optimize the file
		do {
			// build the nec file
			// push the structures to the file creating function
			WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds,
			  Nec_Excitation, Nec_Frequency, Nec_Radiation);
			nec_file_results file_results;
			// Sleep(2500);
			/*TODO : why does it look like big mem leak here
			 but can't spot with debugger?*/
			int intresult = OpenNECFile(tempfilename, &file_results, UpdateSegmentGraph);
			// Sleep(2500);
			// check for segment errors
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
						/*
						 ErrorMemo->Lines->Add
						 ("Speed Light: " + FormatFloat("0.00E+0",
						 spdLight));
						 ErrorMemo->Lines->Add
						 ("Segment Length: " + FormatFloat("0.000",
						 segmentlength));
						 ErrorMemo->Lines->Add
						 ("Segment Wavelengths: " + FormatFloat("0.000",
						 segmentnumwavelengths));
						 */
						// correct this wires number of segments to
						// be within the spec of the limitation
						int NumberOfSegmentsNeeded = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
						  wirelength);
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
			/*
			 if (file_results.VSWR < TargetSWR) {
			 ResultTree->FullExpand();
			 // save the SWR result to the ttreeview
			 TTreeNode* Node = ResultTree->Items->Item[0];
			 ResultTree->Items->AddChild(Node, "Filename: " + tempfilename);
			 Node = ResultTree->Items->Item[0]->GetLastChild();
			 ResultTree->Items->AddChild(Node, "SWR: " + FormatFloat("0.0", file_results.VSWR));
			 ResultTree->Items->AddChild(Node, "Best Horz Gain: " + FormatFloat("0.0", file_results.BestHorzGain));
			 ResultTree->Items->AddChild(Node, "Best Horz Gain Angle: " + FormatFloat("0.0",
			 file_results.BestHorzGainAngle));
			 ResultTree->Items->AddChild(Node, "Best Vert Gain: " + FormatFloat("0.0", file_results.BestVertGain));
			 ResultTree->Items->AddChild(Node, "Best Vert Gain Angle: " + FormatFloat("0.0",
			 file_results.BestVertGainAngle));
			 ResultTree->Items->AddChild(Node, "Best Total Gain: " + FormatFloat("0.0", file_results.BestTotalGain));
			 Node->Expanded = true;
			 // for now keep on going
			 // force staying in the loop
			 // file_results.VSWR = TargetSWR + 1;
			 // done leave the loop
			 // break;
			 }
			 */// otherwise delete the temp file and output file
			if (1) { // else {
				for (int loop = 0; loop < 10; loop++) {
					bool result = DeleteFile(tempfilename);
					if (result)
						break;
					if (loop == 9) {
						// ShowMessage("Unable to delete temp file " +
						// tempfilename);
						ErrorMemo->Lines->Add("Failed delete " + tempfilename);
					}
					Sleep(1500);

				}
				AnsiString outfile = ChangeFileExt(tempfilename, ".out");
				for (int loop = 0; loop < 10; loop++) {
					bool result = DeleteFile(outfile);
					if (result)
						break;
					if (loop == 9) {
						// ShowMessage("Unable to delete output file");
						ErrorMemo->Lines->Add("Failed delete " + outfile);
					}
					Sleep(1500);
				}
			}
			// check if the SWR is not within range
			if ((TargetSWR <= file_results.VSWR) || (Cancel->Tag != 1)) {
				// process windows messages
				Application->ProcessMessages();
				if (Designform->AntennaType->ItemIndex == 0) {
					// do another calculation
					// create some random numbers for now
					int segmentsCount = 0;
					while (segmentsCount == 0) {
						double randomWire1X2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
						  (CenterXMeters);
						double randomWire1Y2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
						  (CenterYMeters);
						double randomWire1Z2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)
						  * MaxHeightMeters;
						Nec_Wires[1].X2 = randomWire1X2;
						Nec_Wires[1].Y2 = randomWire1Y2;
						Nec_Wires[1].Z2 = randomWire1Z2;
						double points = Power(abs(Nec_Wires[1].X1 - Nec_Wires[1].X2), 2) +
						  Power(abs(Nec_Wires[1].Y1 - Nec_Wires[1].Y2), 2) +
						  Power(abs(Nec_Wires[1].Z1 - Nec_Wires[1].Z2), 2);
						double wirelength = Sqrt(points);
						segmentsCount = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz, wirelength); ;
						Nec_Wires[1].Segments = segmentsCount;
					}
					segmentsCount = 0;
					while (segmentsCount == 0) {
						// calculate random for wire 2
						double randomWire2X2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)
						  * CenterXMeters;
						double randomWire2Y2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)
						  * CenterYMeters;
						double randomWire2Z2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)
						  * MaxHeightMeters;
						Nec_Wires[2].X2 = randomWire2X2 + CenterXMeters;
						Nec_Wires[2].Y2 = randomWire2Y2 + CenterYMeters;
						Nec_Wires[2].Z2 = randomWire2Z2;
						double points = Power(abs(Nec_Wires[2].X1 - Nec_Wires[2].X2), 2) +
						  Power(abs(Nec_Wires[2].Y1 - Nec_Wires[2].Y2), 2) +
						  Power(abs(Nec_Wires[2].Z1 - Nec_Wires[2].Z2), 2);
						double wirelength = Sqrt(points);
						segmentsCount = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz, wirelength); ;
						Nec_Wires[2].Segments = segmentsCount;
					}
				}
				// check for cube etch model
				else if (Designform->AntennaType->ItemIndex == 1) {
					// cube etch model
					// update the mode and vector counts
					if (ModeEnable) {
						OptMode->Caption = "Enable";
					}
					else {
						OptMode->Caption = "Disable";
					}
					EnableCount->Caption = IntToStr((int)triedEnable.size());
					DisableCount->Caption = IntToStr((int)triedDisable.size());
					TotalCount->Caption = IntToStr((int)Nec_Counts[0].WireCount - 1);
					// check if the result is better or worse
					// check the desired target to see what we should be working on
					// first check that the SWR is in range
					switch (OptimizationOperatingMode) {
					case OptimizeSWR: {
							UpdateSegmentGraph = false;
							// use reduced signal radiation area for SWR calcs
							Nec_Radiation[0].ThetaAngleCount = 1;
							Nec_Radiation[0].PhiAngleCount = 1;
							LastOptimizationMode = OptimizeSWR;
							OptimizationMode->Caption = "Optimize SWR Calculate";
							if (OptimizeCurrentWireID < Nec_Counts[0].WireCount) {
								if (OptimizeCurrentWireID != -1) {
									// store the last calculated result if not
									// the first time in this state
									SWR_Optimize_VSWR.push_back(file_results.VSWR);
									SWR_Optimize_WireID.push_back(OptimizeCurrentWireID);
									Optimize_HorzGain.push_back(file_results.BestHorzGain);
									// if this result is better than the last complete interation
									// plot a point for this wire
									if ((file_results.VSWR < LastVSWR) && (file_results.VSWR < (LastVSWR * 0.99)) &&
									  (LastVSWR < 9.99E+9)) {
										// add this point to the chart for list of potential points
										double segX, segY, segZ;
										try {
											int segmentNumber =
											  s_context.get_geometry()->get_segment_number(OptimizeCurrentWireID, 1);
											// get geometery center points and display them to the graph
											s_context.get_geometry()->get_xyzSegmentOrignalAbsolute(segmentNumber - 1,
											  &segX, &segY, &segZ);
											Series9->AddXYZ(segX, segZ, segY, "", clRed);
										}
										catch (Exception &E) {
										}
									}
									/*
									 if ((file_results.BestHorzGain > LastHorGain) && (file_results.BestHorzGain >
									 RecentHorzGainTarget * 1.02) && (LastHorGain > -9.99E+9)) {
									 // add this point to the chart for list of potential points
									 double segX, segY, segZ;
									 try {
									 int segmentNumber =
									 s_context.get_geometry()->get_segment_number(OptimizeCurrentWireID, 1);
									 // get geometery center points and display them to the graph
									 s_context.get_geometry()->get_xyzSegmentOrignalAbsolute(segmentNumber - 1,
									 &segX, &segY, &segZ);
									 Series10->AddXYZ(segX, segZ, segY, "", clPurple);
									 }
									 catch (Exception &E) {
									 }
									 }*/
								}
							}
							// go to the next wire
							bool foundNext = false;
							while (!foundNext) {
								// go to the next wire
								OptimizeCurrentWireID++;
								// check if done
								if (OptimizeCurrentWireID > Nec_Counts[0].WireCount) {
									UpdateSegmentGraph = true;
									Nec_Radiation[0].ThetaAngleCount = 1;
									Nec_Radiation[0].PhiAngleCount = 1;
									// clear the possible update graph
									Series9->Clear();
									Series10->Clear();
									// done check for the best SWR
									double MinimumSWR = 9.99E+9;
									double MaximumHorzGain = -9.99E+9;
									int WireToEnable = -1;
									// loop through all the SWRs and find the best one
									int sizeSWRArray = SWR_Optimize_VSWR.size();
									int sizeHorzGArray = Optimize_HorzGain.size();
									for (int findbestSWR = 0; findbestSWR < sizeSWRArray; findbestSWR++) {
										double checkSWR = SWR_Optimize_VSWR[findbestSWR];
										double checkHGain = Optimize_HorzGain[findbestSWR];
										if ((checkSWR < MinimumSWR) && (checkHGain >= MaximumHorzGain)) {
											WireToEnable = SWR_Optimize_WireID[findbestSWR];
											MinimumSWR = checkSWR;
											MaximumHorzGain = checkHGain;
										}
									}
									/*
									 RecentSWRTarget = MinimumSWR;
									 double MaximumHorzGain = -9.99E+9;
									 int HGainWireToEnable = -1;
									 for (int findbestHorzGain = 0; findbestHorzGain < sizeHorzGArray;
									 findbestHorzGain++) {
									 double checkHGain = Optimize_HorzGain[findbestHorzGain];
									 if ((Nec_Wires[findbestHorzGain].Enabled == false) && (checkHGain >
									 MaximumHorzGain)) {
									 HGainWireToEnable = SWR_Optimize_WireID[findbestHorzGain];
									 MaximumHorzGain = checkHGain;
									 }
									 }
									 RecentHorzGainTarget = MaximumHorzGain;
									 */
									// check if this SWR is better than the last
									// and made a reasonable improvement
									double improvement = LastVSWR - MinimumSWR;
									if ((MinimumSWR < LastVSWR) && (improvement > 0.001)) {
										Series5->AddXY(Iteration, MinimumSWR, "", clTeeColor);
										Nec_Radiation[0].ThetaAngleCount = 19;
										Nec_Radiation[0].PhiAngleCount = 73;
										// this SWR is better so keep continuing to optimize
										LastVSWR = MinimumSWR;
										LastHorGain = file_results.BestHorzGain;
										// now know the best wire to enable
										Nec_Wires[WireToEnable].Enabled = true;
										/*
										 if (HGainWireToEnable != -1) {
										 Nec_Wires[HGainWireToEnable].Enabled = true;
										 }
										 */
										// no reset to the beginning and repeat
										OptimizeCurrentWireID = -1;
										// clear the vectors
										SWR_Optimize_VSWR.clear();
										SWR_Optimize_WireID.clear();
										Optimize_HorzGain.clear();
										break;
									}
									else {
										// this is not a better result so optimization for SWR is
										// completed
										// for now keep going and see what happens
										Series5->AddXY(Iteration, MinimumSWR, "", clTeeColor);
										// clear the vectors
										SWR_Optimize_VSWR.clear();
										SWR_Optimize_WireID.clear();
										Nec_Wires[LastChangedWire].Enabled = false;
										// display the bandwidth chart
										OptimizationOperatingMode = ChooseBestWire;
										break;
									}
									// clear the vectors
									SWR_Optimize_VSWR.clear();
									SWR_Optimize_WireID.clear();
									Optimize_HorzGain.clear();
								}
								else if (Nec_Excitation[0].WireID != OptimizeCurrentWireID) {
									if (Nec_Wires[OptimizeCurrentWireID].Enabled == false) {
										foundNext = true;
										if (LastChangedWire != -1) { // disable the last wire
											Nec_Wires[LastChangedWire].Enabled = false;
										}
										// enable the next wire
										Nec_Wires[OptimizeCurrentWireID].Enabled = true;
										LastChangedWire = OptimizeCurrentWireID;
										break;
									}
								}
							}
							break;
						}
					case ChooseBestWire: {
							Nec_Radiation[0].ThetaAngleCount = 19;
							Nec_Radiation[0].PhiAngleCount = 73;
							Nec_Frequency[0].FrequencyMHz = 7;
							Nec_Frequency[0].BandWidth = 0.3;
							Nec_Frequency[0].FrequencyStepSize = 0.05;
							if (Nec_Frequency[0].FrequencyStepSize) {
								Nec_Frequency[0].FrequencySteps =
								  Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
							}
							OptimizationOperatingMode = DisplayResults;
							break;
						}
					case DisplayResults: {
							Cancel->Tag = 1;
							// save the file
							WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads,
							  Nec_Grounds, Nec_Excitation, Nec_Frequency, Nec_Radiation);
							break;
						}
					case OptimizeHorzGain: {
							LastOptimizationMode = OptimizeHorzGain;
							OptimizationMode->Caption = "Optimize Horz Gain";
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
						}
					} // end switch
					/*
					 if (OptimizationOperatingMode != OptimizeChangedBack) {
					 Series5->AddXY(Iteration, file_results.VSWR, "", clTeeColor);
					 Series6->AddXY(Iteration, file_results.R, "", clTeeColor);
					 Series7->AddXY(Iteration, file_results.X, "", clTeeColor);
					 Series8->AddXY(Iteration, file_results.BestHorzGain, "", clTeeColor);
					 // the last change was an improvement so
					 // update to the new good values
					 // LastVSWR = file_results.VSWR;
					 // LastHorGain = file_results.BestHorzGain;
					 */
				}

				// update the target values based on the mode
				switch (OptimizationOperatingMode) {
				case OptimizeSWR: {
						SWRTarget->Caption = FormatFloat("0.000000E+0", LastVSWR);
						HorzGainTarget->Caption = "Don't care";
						break;
					}
				case OptimizeHorzGain: {
						SWRTarget->Caption = FormatFloat("0.0000E+0", LastVSWR);
						HorzGainTarget->Caption = FormatFloat("0.000E+0", LastHorGain);
						break;
					}
				case OptimizeStripUncessesarySWRWires: {
						SWRTarget->Caption = FormatFloat("0.0000E+0", LastVSWR);
						HorzGainTarget->Caption = "Don't care";
						break;
					}
				}
				// set don't update graph flag so we don't update
				// the graph with a bad value if it is time to update
				// the graph
				bool dontUpdateGraph = true;
				// check is the last change wasn't an improvement
				// if so we change the change back if an improvement was attempted
				// LastChangedWire will be -1 when no changes have been made yet
				if ((OptimizationOperatingMode == OptimizeChangedBack) && (LastChangedWire != -1)) {
					// check to see which mode we are in
					if (ModeEnable) {
						// if we are in mode enable we would have enabled
						// the last wire which made a bad change
						// so change it back
						Nec_Wires[LastChangedWire].Enabled = false;
					}
					else {
						// if we are in mode disable we would have disabled
						// the last wire which made a bad change
						// so change it back
						Nec_Wires[LastChangedWire].Enabled = true;
					}
				}
				else {
					// the last change made was an improvement
					// we can update the graph
					dontUpdateGraph = false;
					// also clear both lists of wire changes since we now
					// have a good change to build further off of
					triedEnable.clear();
					triedDisable.clear();

				}
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
				int enabledCount = 0;
				for (int enabled = 0; enabled < numarrayWires; enabled++) {
					if (Nec_Wires[enabled].Enabled) {
						enabledCount++;
					}
				}
				// count the number of disabled wires
				int disabledCount = 0;
				for (int disabled = 0; disabled < numarrayWires; disabled++) {
					if (!Nec_Wires[disabled].Enabled) {
						disabledCount++;
					}
				}
				EnabledCount->Caption = IntToStr(enabledCount);
				DisabledCount->Caption = IntToStr(disabledCount);
				Iteration++;
				// if a change was set back set the mode back to the last mode
				if (OptimizationOperatingMode == OptimizeChangedBack) {
					OptimizationMode->Caption = "Optimize Change Back";
					OptimizationOperatingMode = LastOptimizationMode;
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
void TForm1::BuildCube(unsigned int MaxHeightMeters, unsigned int MinHeightMeters, unsigned int MaxWidthMeters,
  unsigned int MaxDepthMeters, float resolution, unsigned int FeedPointHeight) {
	unsigned int numXRows, numYRows, numZRows;
	// get the number of rows in each axis
	numXRows = (MaxWidthMeters / resolution);
	numYRows = (MaxDepthMeters / resolution);
	numZRows = ((MaxHeightMeters - MinHeightMeters) / resolution);
	// calcuate wire struct array size
	// compensate for any row equaling zero
	unsigned int numberofwiresNeeded = (numXRows + 1) * (numYRows + 1) * (numZRows + 1) * 3;
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
	Nec_Frequency[0].FrequencyMHz = 7.15;
	Nec_Frequency[0].BandWidth = 0.0;
	Nec_Frequency[0].FrequencyStepSize = 0.00;
	if (Nec_Frequency[0].FrequencyStepSize) {
		Nec_Frequency[0].FrequencySteps = Nec_Frequency[0].BandWidth / Nec_Frequency[0].FrequencyStepSize + 1;
	}
	else {
		Nec_Frequency[0].FrequencySteps = 0;
	}
	unsigned int arrayCounter = 0;
	// do if all are more than 1 we have a cube
	// now loop through the X, Y and Z making the wires
	for (unsigned int x = 0; x <= numXRows; x++) {
		for (unsigned int y = 0; y <= numYRows; y++) {
			for (unsigned int z = 0; z <= numZRows; z++) {
				double zheightCorrected = z + MinHeightMeters;
				// for each wire need to go in three directions
				// the X,Y and Z resolution and create those wires
				if (x < numXRows) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x + resolution;
					Nec_Wires[arrayCounter].Y2 = y;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected;
					double wirelength = WireLength(x, y, zheightCorrected, x + resolution, y, zheightCorrected);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  wirelength);
					Nec_Wires[arrayCounter].Diameter = 0.001;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].AttachedToX1Y1Z1ID = -1;
					Nec_Wires[arrayCounter].AttachedToX2Y2Z2ID = -1;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
				if (y < numYRows) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x;
					Nec_Wires[arrayCounter].Y2 = y + resolution;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected;
					double wirelength = WireLength(x, y, zheightCorrected, x, y + resolution, zheightCorrected);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  wirelength);
					Nec_Wires[arrayCounter].Diameter = 0.001;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].AttachedToX1Y1Z1ID = -1;
					Nec_Wires[arrayCounter].AttachedToX2Y2Z2ID = -1;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
				if (z < numZRows) {
					Nec_Wires[arrayCounter].ID = arrayCounter;
					Nec_Wires[arrayCounter].Segments = 1;
					Nec_Wires[arrayCounter].X1 = x;
					Nec_Wires[arrayCounter].Y1 = y;
					Nec_Wires[arrayCounter].Z1 = zheightCorrected;
					Nec_Wires[arrayCounter].X2 = x;
					Nec_Wires[arrayCounter].Y2 = y;
					Nec_Wires[arrayCounter].Z2 = zheightCorrected + resolution;
					double wirelength = WireLength(x, y, zheightCorrected, x, y, zheightCorrected + resolution);
					Nec_Wires[arrayCounter].Segments = CalculateMinimumNumSegments(Nec_Frequency[0].FrequencyMHz,
					  wirelength);
					Nec_Wires[arrayCounter].Diameter = 0.001;
					Nec_Wires[arrayCounter].Support = false;
					Nec_Wires[arrayCounter].AttachedToX1Y1Z1ID = -1;
					Nec_Wires[arrayCounter].AttachedToX2Y2Z2ID = -1;
					Nec_Wires[arrayCounter].Enabled = true;
					arrayCounter++;
				}
			}
		}
	}
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
	int zCenter = numZRows / 2;
	int yCenter = numYRows / 2;
	int xCenter = numXRows / 2;
	if ((numZRows % 2) && (numZRows > 1)) {
		// zCenter++;
	}
	if ((numYRows % 2) && (numYRows > 1)) {
		// yCenter++;
	}
	if ((numXRows % 2) && (numXRows > 1)) {
		// xCenter++;
	}
	double X1, Y1, Z1, X2, Y2, Z2;
	for (int findFeed1 = 0; findFeed1 < arrayCounter; findFeed1++) {
		if ((Nec_Wires[findFeed1].X1 == xCenter) && (Nec_Wires[findFeed1].Y1 == yCenter) &&
		  (Nec_Wires[findFeed1].Z1 == FeedPointHeight/*(zCenter + MinHeightMeters)*/)) {
			Nec_Excitation[0].WireID = findFeed1;
			Nec_Wires[findFeed1].Enabled = true;
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
	// chose the middle segment
	Nec_Excitation[0].SourceTag = 1;
	Nec_Excitation[0].ExcitationType = 0;
	Nec_Excitation[0].VoltageReal = 1;
	Nec_Excitation[0].VoltageImag = 0;
	Nec_Excitation[0].RelativeAdmittanceType = 0;
	// create the radiation requirements
	Nec_Radiation[0].Mode = 0;
	Nec_Radiation[0].ThetaAngleCount = 19;
	Nec_Radiation[0].PhiAngleCount = 73;
	Nec_Radiation[0].ThetaStartAngle = 0;
	Nec_Radiation[0].PhiStartAngle = 0;
	Nec_Radiation[0].ThetaStepAngle = 5;
	Nec_Radiation[0].PhiStepAngle = 5;
	// set the total counts
	Nec_Counts[0].WireCount = arrayCounter;
	Nec_Counts[0].LoadsCount = 0;
	Nec_Counts[0].GroundsCount = 1;
	Nec_Counts[0].ExcitationsCount = 1;
	Nec_Counts[0].FrequenciesCount = 1;
	// save the base file
	WideString tempfilename = CreateNECFile(Nec_Counts, Nec_Wires, Nec_Ground, Nec_Loads, Nec_Grounds, Nec_Excitation,
	  Nec_Frequency, Nec_Radiation);
	RenameFile(tempfilename, "CubeBase" + tempfilename);
	// disable the cube elements
	// now loop through the X, Y and Z making the wires
	arrayCounter = 0;
	for (unsigned int x = 0; x <= numXRows; x++) {
		for (unsigned int y = 0; y <= numYRows; y++) {
			for (unsigned int z = 0; z <= numZRows; z++) {
				double zheightCorrected = z + MinHeightMeters;
				// for each wire need to go in three directions
				// the X,Y and Z resolution and create those wires
				if (x < numXRows) {
					if (Nec_Wires[arrayCounter].ID != Nec_Excitation[0].WireID) {
						Nec_Wires[arrayCounter].Enabled = false;
					}
					arrayCounter++;
				}
				if (y < numYRows) {
					if (Nec_Wires[arrayCounter].ID != Nec_Excitation[0].WireID) {
						Nec_Wires[arrayCounter].Enabled = false;
					}
					arrayCounter++;
				}
				if (z < numZRows) {
					if (Nec_Wires[arrayCounter].ID != Nec_Excitation[0].WireID) {
						Nec_Wires[arrayCounter].Enabled = false;
					}
					arrayCounter++;
				}
			}
		}
	}
	/*TODO : NEC will fault if we don't have at least 2 active segments*/
	/*TODO :
	 With the cube layout if only one axis like x=30 X2 will match X1, Y2 and Y1 etc etc.
	 Have to watch for this; This certainly creates a possible mess for other
	 directions*/
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
}

double __fastcall TForm1::WireLength(double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
	double points = Power(abs(X1 - X2), 2) + Power(abs(Y1 - Y2), 2) + Power(abs(Z1 - Z2), 2);
	double wirelength = Sqrt(points);
	return wirelength;
}

unsigned int __fastcall TForm1::CalculateMinimumNumSegments(double FrequencyMHz, double wirelength) {
	/*TODO :
	 Need to make sure the number of segments never is zero
	 The model seems to go and go if this is the case*/
	double SegLengthNeeded = 0.020 * (em::speed_of_light() / (FrequencyMHz * 1.0E+6));
	double NumberOfSegmentsNeeded = double(wirelength / SegLengthNeeded);
	int NumSegmentsNeeded = NumberOfSegmentsNeeded;
	/*
	if (NumSegmentsNeeded != NumberOfSegmentsNeeded)
		NumSegmentsNeeded++;
	*/
	return NumSegmentsNeeded;
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
		AnsiString extension = ExtractFileExt(wtempfilename);
		int extPosition = wtempfilename.Pos(extension);
		AnsiString newName = wtempfilename.SubString(1, extPosition) + "nec";
		for (int loop = 0; loop < 10; loop++) {
			bool result = RenameFile(wtempfilename, newName);
			if (!result) {
				Sleep(1500);
				if (loop == 9) {
					// ShowMessage("Error: Trouble renaming temporary file");
					ErrorMemo->Lines->Add("Failed rename " + wtempfilename);
				}
			}
			else {
				// success renaming file
				break;
			}
		}
		newName = newName.SubString(3, newName.Length() - 1);
		return newName;
	}
	return "";
}

void __fastcall TForm1::CancelClick(TObject * Sender) {
	Cancel->Tag = 1;
}
// ---------------------------------------------------------------------------
