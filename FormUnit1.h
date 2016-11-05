// ---------------------------------------------------------------------------

#ifndef FormUnit1H
#define FormUnit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "nec2cpp.h"
#include "VCLTee.TeePolar.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "nec_context.h"
#include "VCLTee.TeePoin3.hpp"
#include "VCLTee.TeeSurfa.hpp"
#include "c_geometry.h"
#include <System.Math.hpp>
#include "Design.h"
#include <System.hpp>
#include <Vcl.ComCtrls.hpp>

#define SCALE_CM 0.001
#define SCALE_M 1

struct nec_file_results {
	bool Error;
	char ErrorMessage[MAX_PATH];
	double VSWR;
	double X;
	double R;
	double BestHorzGain;
	double BestVertGain;
	double BestHorzGainAngle;
	double BestVertGainAngle;
	double BestTotalGain;
	double BestHorzGainPhiAngle;

	nec_exception::segment_error_type SegmentErrorType;

	unsigned int SegmentNumber;
} Nec_File_Results;

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TButton *Open;
	TOpenDialog *OpenDialog1;
	TLabel *StatusCaption;
	TChart *Chart1;
	TPolarSeries *Series1;
	TChart *Chart2;
	TPolarSeries *PolarSeries1;
	TChart *Chart3;
	TPolarSeries *PolarSeries2;
	TChart *Chart4;
	TPoint3DSeries *Series2;
	TTimer *Timer1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *TotalGaindBLabel;
	TLabel *TotalGainPhiLabel;
	TLabel *TotalGainThetaLabel;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *VertGaindBLabel;
	TLabel *VertPhiLabel;
	TLabel *VertThetaLabel;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *HorzGaindBLabel;
	TLabel *HorzPhiLabel;
	TLabel *HorzThetaLabel;
	TChart *Chart5;
	TPolarSeries *PolarSeries3;
	TChart *Chart6;
	TPolarSeries *PolarSeries4;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *VSWRLabel;
	TLabel *Label16;
	TLabel *XLabel;
	TLabel *Label18;
	TLabel *RLabel;
	TLabel *Label17;
	TLabel *FreqLabel;
	TChart *Chart7;
	TButton *Make;
	TMemo *ErrorMemo;
	TButton *Cancel;
	TTreeView *ResultTree;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TChart *Chart8;
	TLineSeries *Series5;
	TChart *Chart9;
	TLineSeries *Series6;
	TLineSeries *Series7;
	TLineSeries *Series8;
	TLabel *OptMode;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *EnableVectorCountLB;
	TLabel *DisableVectorCountLB;
	TLabel *Label21;
	TLabel *TotalCount;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *SWRTarget;
	TLabel *HorzGainTarget;
	TLabel *OptimizationMode;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *EnabledWireCountLB;
	TLabel *DisabledWireCountLB;
	TPoint3DSeries *Series9;
	TPoint3DSeries *Series10;
	TLineSeries *Series11;
	TSaveDialog *SaveDialog1;
	TLabel *Label1;
	TLabel *Label26;
	TLabel *EnableWireLB;
	TLabel *Label27;
	TLabel *IgnoredWireCountLB;
	TLabel *Label28;
	TLabel *EnabledVWireCountLB;
	TLabel *Label30;
	TLabel *DisabledVWireCountLB;
	TLabel *Label29;
	TLabel *SWRVectorLB;
	TLabel *EnabledListLB;
	TLabel *IgnoredListLB;
	TLabel *SWRListLB;
	TProgressBar *ProgressBar1;

	void __fastcall OpenClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall MakeClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private: // User declarations

	struct nec_counts {
		unsigned int WireCount;
		unsigned int LoadsCount;
		unsigned int GroundsCount;
		unsigned int ExcitationsCount;
		unsigned int FrequenciesCount;
	};

	struct nec_wires {
		unsigned int ID;
		bool Enabled;
		unsigned int Segments;
		double X1;
		double Y1;
		double Z1;
		double X2;
		double Y2;
		double Z2;
		double Diameter;
		bool Support;
		// the vectors below are used to keep track of which other wires are connected to
		// this wire on either side
		//std::vector<unsigned int>AttachedToX1Y1Z1ID;
		//std::vector<unsigned int>AttachedToX2Y2Z2ID;
	};

	struct nec_wire_ground {
		bool Z0ground; // true make Z = 0 (segments at 0 are grounded to earth)
	};

	struct nec_loads {
		unsigned int ID;
		unsigned int WireID;
		unsigned int Unknown1;
		unsigned int Unknown2;
		double Conductivity;
	};

	struct nec_grounds {
		unsigned int GroundType;
		unsigned int NumberOfRadials;

		unsigned int Unused1 = 0;
		unsigned int Unused2 = 0;

		double RelativeDielectricConstant;
		double GroundConductivity; // mhoms/m
	};

	struct nec_excitation {
		unsigned int ID;
		unsigned int ExcitationType;
		unsigned int SourceTag;
		unsigned int Unused1;
		unsigned int WireID;
		unsigned int RelativeAdmittanceType;
		unsigned int VoltageSourcesBeforeCurrent;
		unsigned int IncendentPlaneWaveNumThetaAngles;
		unsigned int IncendentPlaneWaveNumPhiAngles;
		unsigned int IncendentPlaneWaveNumEtaAngles;
		unsigned int MaxRelativeAdmittanceMatrix;
		double VoltageReal;
		double VoltageImag;

		double RatioOfPolarization = 0;
	};

	struct nec_frequency {
		unsigned int StepType;
		unsigned int FrequencySteps;
		unsigned int Unused1;
		unsigned int Unused2;
		double FrequencyMHz;
		double BandWidth;
		double FrequencyStepSize;
	};

	struct nec_radiation {
		unsigned int ID;
		unsigned __int8 Mode;
		unsigned int ThetaAngleCount;
		unsigned int PhiAngleCount;

		unsigned __int8 AxisType = 1;
		unsigned __int8 NormalizedGainType = 0;
		unsigned __int8 PowerGain = 0;
		unsigned __int8 Averaging = 0;

		int ThetaStartAngle;
		int PhiStartAngle;
		int ThetaStepAngle;
		int PhiStepAngle;
	};

	// create a new context
	nec_context s_context;

	// the NEC file structures
	nec_counts* Nec_Counts;
	nec_wires* Nec_Wires;
	nec_wire_ground* Nec_Ground;
	nec_loads* Nec_Loads;
	nec_grounds* Nec_Grounds;
	nec_excitation* Nec_Excitation;
	nec_frequency* Nec_Frequency;
	nec_radiation* Nec_Radiation;

	// optimization variables
	double LastVSWR;
	double LastHorGain;
	// int LastChangedWire;
	unsigned int Iteration;
	bool Done;
	bool OnlyAttached;
	double SWRCompare;
	double SWRRCompare;
	double SWRXCompare;
	unsigned int BestWireID;

	int __fastcall OpenNECFile(AnsiString Filename, nec_file_results* file_results, bool UpdateSegmentGraph = false);

	// model build functions
	void __fastcall GetInitialBandResolution(unsigned int BandSelection, double* resolution, double* Scale);

	bool __fastcall BuildDipoleModel(double* MaxHeightMeters, double* MinHeightMeters, double *MaxWidthMeters,
	  double* MaxDepthMeters, double* resolution, double *FeedPointHeight, double* Frequency, double* WireDiameter,
	  double* Scale, unsigned int BandSelection, double* BandBottom, double* BandLength);

	bool BuildCube(double *MaxHeightMeters, double *MinHeightMeters, double *MaxWidthMeters, double* MaxDepthMeters,
	  double* resolution, double *FeedPointHeight, double* Frequency, double* WireDiameter, double* Scale,
	  unsigned int BandSelection, double* BandBottom, double* BandLength);

	WideString CreateNECFile(nec_counts* inNec_Counts, nec_wires* inNec_Wires, nec_wire_ground* inNec_Ground,
	  nec_loads* inNec_Loads, nec_grounds* inNec_Grounds, nec_excitation* inNec_Excitation,
	  nec_frequency* inNec_Frequency, nec_radiation* inNec_Radiation);

	// calculation functions
	unsigned int __fastcall CalculateMinimumNumSegments(double FrequencyMHz, double* wirelength);
	double __fastcall WireLength(double X1, double Y1, double Z1, double X2, double Y2, double Z2);
	void AdjustUserInputSizeByScale(double* MaxWidthMeters, double* MaxDepthMeters, double* MaxHeightMeters,
	  double* MinHeightMeters, double* FeedPointHeight, double* Scale);
	void SetBandParameters(unsigned int BandSelection, double* BandBottom, double*BandLength, double* Frequency,
	  double* resolution, double* WireDiameter, double* Scale);

	  bool graphUpdateFlag;

	vector<unsigned int>triedDisable;
	vector<unsigned int>triedEnable;
	vector<unsigned int>triedNew;

	std::vector<unsigned int>PossibleWireIDs;
	// std::vector<unsigned int>SWR_R;
	// std::vector<unsigned int>SWR_X;

	bool ModeEnable;

	enum OptimizeModeType {
		OptimizeSWR = 0, ChooseBestWire, DisplayResults, OptimizeHorzGain, OptimizeChangedBack,
		OptimizeStripUncessesarySWRWires
	};

	enum OptimizeWireType {
		VerifySWRChange = 0, FindAllAttachedWires
	};

	OptimizeModeType OptimizationOperatingMode;
	OptimizeModeType LastOptimizationMode;

	std::vector<double>SWR_Optimize_SWR_R;
	std::vector<double>SWR_Optimize_SWR_X;
	std::vector<double>SWR_Optimize_SWR;
	// std::vector<double>Optimize_HorzGain;

	double RecentHorzGainTarget;
	double RecentSWRTarget;

	int OptimizeCurrentWireID;

public: // User declarations

	__fastcall TForm1(TComponent* Owner);
	__fastcall ~TForm1();
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
