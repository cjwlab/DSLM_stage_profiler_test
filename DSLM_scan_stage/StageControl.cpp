#include "stdafx.h"
#include <Windows.h>
#include "C843_GCS_DLL.H"
#include "StageControl.h"
#include "winmcl32_api.h"
#include <math.h>
#include <stdio.h>
#include <ctime>

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;

Stage::Stage()
{
}

Stage::~Stage()
{

}


int main(){
	
	Stage::Initialize();

	Sleep(2000);

	String^ fileName = "Textfile.txt";
	StreamWriter^ sw = gcnew StreamWriter(fileName);
	sw->WriteLine("             Profiler experiment              ");
	sw->WriteLine("");
	
	String^ fileName2 = "Number_of_correct_Profiles.txt";
	StreamWriter^ swww = gcnew StreamWriter(fileName2);
	swww->WriteLine("             Profilers Correctly executed            ");
	swww->WriteLine("");
	swww->WriteLine("Timepoint  \tabs(Xf-XPOStoP[4]) \tabs(Zf-ZPOStoP[4]) \tCorrect Profile");

	const char *AxisZ = "1";
	const char *AxisX = "2";
	const char *AxisY = "3";
	const char *AxisZX = "12";
	int Counting_number_off_correct_Profiles = 0;	//To count the number of corrected profiles performed
	double Dif_x0_xf, Dif_z0_zf;					//To verify the number of corrected profiles performed is correct
	double ZPOStoP[5], ZVELtoP[5];
	double XPOStoP[5], XVELtoP[5];
	double xf = 0.0, zf = 0.0;
	double positionreader = 0.0, positionreader2 = 0.0;
	bool Profiler2AxisActive = false, ProfilerClearer = false, RunProfiler = false;
	int counter = 0;
	bool UPActiveForZAxis, UPActiveForXAxis;
	double DifInX, DifInZ;
	bool ProfileFailed = false;						//To break the time points loop if the Profile fails
	bool AxisXIsMoving = false;
	bool AxisZIsMoving = false;

	String^ ReadError_0 = "No error";
	String^ ReadError_1;
	

	Stage::ControllerIsReady();
	Stage::MoveStage(AxisX, 0.0);
	Stage::MoveStage(AxisZ, 0.0);
	
	//Z Positions and Velocities
	ZPOStoP[0] = positionreader2;
	ZPOStoP[1] = positionreader2 - 1.5;
	ZPOStoP[2] = positionreader2 - 2.5;
	ZPOStoP[3] = positionreader2 - 3.5;
	ZPOStoP[4] = positionreader2 + 1.5;

	ZVELtoP[0] = (ZPOStoP[1] - ZPOStoP[0])/3.0; //3.0 seconds
	ZVELtoP[1] = (ZPOStoP[2] - ZPOStoP[1])/2.0;	//2.0 seconds
	ZVELtoP[2] = (ZPOStoP[3] - ZPOStoP[2])/5.0;	//5.0 seconds
	ZVELtoP[3] = (ZPOStoP[4] - ZPOStoP[3])/5.0;	//5.0 seconds
	ZVELtoP[4] = 0.0;							//Last one is not expected to move for a next position.


	//X Positions and Velocities
	XPOStoP[0] = positionreader;
	XPOStoP[1] = positionreader + 1.5;
	XPOStoP[2] = positionreader + 2.5;
	XPOStoP[3] = positionreader + 5.0;
	XPOStoP[4] = positionreader + 6.25;

	XVELtoP[0] = (XPOStoP[1] - XPOStoP[0])/3.0; //3.0 seconds
	XVELtoP[1] = (XPOStoP[2] - XPOStoP[1])/2.0;	//2.0 seconds
	XVELtoP[2] = (XPOStoP[3] - XPOStoP[2])/5.0;	//5.0 seconds
	XVELtoP[3] = (XPOStoP[4] - XPOStoP[3])/5.0;	//5.0 seconds
	XVELtoP[4] = 0.0;							//Last one is not expected to move for a next position.

	//Loop to run the Profiler
	for (int l=1; l<=50 && ProfileFailed == false; l++)
	{
		Stage::ControllerIsReady();
		positionreader = Stage::GetPosition(AxisX);
		positionreader2 = Stage::GetPosition(AxisZ);

		sw->WriteLine("Time point: {0}", l);
		sw->WriteLine(" {0} \t {1}\n", positionreader, positionreader2);

		std::clock_t    start;
		start = std::clock();

		//Profiler activation and Profiler Run functions are performed here
		Stage::ControllerIsReady();
		Profiler2AxisActive = Stage::Profiler2Axis(AxisZX, AxisZ, AxisX, XPOStoP, ZPOStoP, XVELtoP, ZVELtoP, l);
		RunProfiler = Stage::RunProfilerFor2Axis(AxisZX, l);
		sw->WriteLine(" Profiler error after run profile command: " + Stage::ReadError());
		if(Profiler2AxisActive == true)
		{
			AxisXIsMoving = Stage::IsMoving(AxisX);
			AxisZIsMoving = Stage::IsMoving(AxisZ);
			Sleep(5000);

			while(AxisXIsMoving == true || AxisZIsMoving == true)
			{
				AxisXIsMoving = Stage::IsMoving(AxisX);
				AxisZIsMoving = Stage::IsMoving(AxisZ);
				Sleep(500);
			}
		}
		sw->WriteLine(" Profiler is Activated: " + Profiler2AxisActive);
		sw->WriteLine(" Profiler is set to run: " + RunProfiler);

		std::clock_t    end;
		end = std::clock();
		double millisec = (end - start)/(double)(CLOCKS_PER_SEC / 1000);

		Stage::ControllerIsReady();
		xf = Stage::GetPosition(AxisX);
		zf = Stage::GetPosition(AxisZ);
		sw->WriteLine(" {0} \t {1}\n", xf, zf);
		sw->WriteLine(" {0}\n ", millisec);
		sw->WriteLine("");
	
		
		Dif_x0_xf = abs(xf - XPOStoP[4]);
		Dif_z0_zf = abs(zf - ZPOStoP[4]);	

		if((Dif_x0_xf < 0.001) && (Dif_z0_zf < 0.001))
		{
			Counting_number_off_correct_Profiles++;
		}
		swww->WriteLine("{0} \t\t{1:0.000000000000000} \t{2:0.000000000000000} \t{3}", l, Dif_x0_xf, Dif_z0_zf, Counting_number_off_correct_Profiles);

		Stage::ControllerIsReady();
		Stage::MoveStage(AxisX, 0.0);
		Stage::MoveStage(AxisZ, 0.0);
		while(Stage::IsMoving(AxisX) == true || Stage::IsMoving(AxisZ) == true){Sleep(500);};
		
		DifInX = abs(xf - 0.0);
		DifInZ = abs(zf - 0.0);

		//To ensure that the stage is moved to it initial position X0 and Z0
		while( (DifInX > 0.0000000001) && (DifInZ > 0.0000000001) || (DifInX > 0.0000000001) && (DifInZ < 0.0000000001) || (DifInX < 0.0000000001) && (DifInZ > 0.0000000001))
		{
			Stage::MoveStage(AxisX, 0.0);
			Stage::MoveStage(AxisZ, 0.0);
			while(Stage::IsMoving(AxisX) == true || Stage::IsMoving(AxisZ) == true){Sleep(500);};
			
			xf = Stage::GetPosition(AxisX);
			zf = Stage::GetPosition(AxisZ);
			DifInX = abs(xf - 0.0);
		    DifInZ = abs(zf - 0.0);

			counter++;
			
			Stage::ControllerIsReady();
			
			Sleep(1000);
		}
		DifInX = abs(xf - 0.0);
		DifInZ = abs(zf - 0.0);
		sw->WriteLine("Dif in X and Z: {0} and {1}.", DifInX, DifInZ);
		sw->WriteLine("Elapsed time until stage move to it initial positions: {0}.\n", counter);

		//To assure that before the Profile is cleared no error is in the queue
		Stage::ControllerIsReady();
		ReadError_1 = Stage::ReadError();
		while(ReadError_1 != ReadError_0)
		{
			UPActiveForZAxis = Stage::UserProfileIsActive(AxisZ);
			UPActiveForXAxis = Stage::UserProfileIsActive(AxisX);
			ReadError_1 = Stage::ReadError();

			sw->WriteLine("Error message after asking if UP mode is active:" + ReadError_1);
			sw->WriteLine("For Axis Z: " + UPActiveForZAxis + "\t For Axis X: " + UPActiveForXAxis);
			sw->WriteLine(" ");
			
			Stage::ControllerIsReady();

			Sleep(1000);
		}

		//To exit the code if the profile is not correctly performed		
		if(Counting_number_off_correct_Profiles != l)
		{
			sw->WriteLine(" ");
			sw->WriteLine("End of experiment before all the iterations, due to wrong profile!");
			ProfileFailed = true;
		}

		//To clear the Profile clusters, avoiding some memory issue
		Stage::ControllerIsReady();
		ProfilerClearer = Stage::ProfilerClearer();
		sw->WriteLine("End of time point, Profile Clear: " + ProfilerClearer);
		if(ProfilerClearer == false)
		{
			Stage::ControllerIsReady();
			sw->WriteLine("Error message after set Controller to be ready:" + Stage::ReadError());
			ProfilerClearer = Stage::ProfilerClearer();
			sw->WriteLine("Profile Clearing second time: " + ProfilerClearer);
		}

		counter = 0;
		sw->WriteLine(" ");
		sw->WriteLine(" ");
		sw->WriteLine(" ");

		Sleep(1000);
	}
	//end of the loop to run the profiler

	swww->WriteLine("");
	swww->Close();

	sw->WriteLine("");
	sw->Close();

	return 0;

}


int Stage::Initialize()
{
	char stages[1024]; 
	char axes[10];  
	double movr = 0.0;
	ID = C843_Connect(1); 
	C843_CST(ID,"1234","DSLM.STAGE\nDSLM.STAGE\nDSLM.STAGE");
	C843_qCST(ID, "1234", stages, 1024);
	System::String^ stageID = gcnew System::String(stages);
	C843_qSAI(ID, axes, 9);
	System::String^ axesID = gcnew System::String(axes);
	C843_INI(ID,axes);
	bool bFlag = FALSE;
	C843_FPL(ID,"1");
	bFlag = FALSE;
	while(bFlag != TRUE){
		C843_IsControllerReady(ID, (long*)&bFlag);
	}
	C843_FPL(ID,"2");
	bFlag = FALSE;
	while(bFlag != TRUE){
		C843_IsControllerReady(ID, (long*)&bFlag);
	}
	C843_FNL(ID,"3");
	bFlag = FALSE;
	while(bFlag != TRUE){
		 C843_IsControllerReady(ID, (long*)&bFlag);
	}

	BOOL movement = C843_MOV(ID, "1", &movr);
	C843_MOV(ID, "2", &movr);
	C843_MOV(ID, "3", &movr);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE){
		C843_IsMoving(ID, "1", &bIsMoving);
	}
	while(bIsMoving == TRUE){
		C843_IsMoving(ID, "2", &bIsMoving);
	}
	while(bIsMoving == TRUE){
		C843_IsMoving(ID, "3", &bIsMoving);
	}

	double position, velocity;
	
	C843_qPOS(ID, "1", &position);
	posZ = position;
	C843_qPOS(ID, "2", &position);
	posX = position;
	C843_qPOS(ID, "3", &position);
	posY = position;

	C843_qVEL(ID, "1", &velocity);
	velZ = velocity;
	C843_qVEL(ID, "2", &velocity);
	velX = velocity;
	C843_qVEL(ID, "3", &velocity);
	velY = velocity;

	if (movement ==TRUE){
		//this->lblStagesStatus->Text=L"moved";

		return 0;
	}else{
		return 1;
	}
}

double Stage::GetPosition(const char *Axis)
{
	double Position = 0.0;
	C843_qPOS(ID, Axis, &Position);
	return Position;
}

double Stage::MoveStageBlocking(const char *Axis, double Position)
{
	C843_MOV(C843_Connect(1), Axis, &Position);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE) {
		C843_IsMoving(C843_Connect(1), Axis, &bIsMoving);
	}
	
	return Position;
}

bool Stage::IsMoving(const char *Axis)
{
	BOOL bIsMoving;
	
	C843_IsMoving(ID, Axis, &bIsMoving);
	
	if (bIsMoving == TRUE)
	{
		return true;
	}else{
		return false;
	}
}

double Stage::MoveRelative(const char *Axis, double Position)
{
	C843_MVR(ID, Axis, &Position);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE) {
		C843_IsMoving(ID, Axis, &bIsMoving);
	}
	C843_qPOS(ID, Axis, &Position);
	return Position;
}

double Stage::MoveStage(const char *Axis, double Position)
{
	C843_MOV(ID, Axis, &Position);
	return 0;
}

int Stage::GetStageID()
{
	return ID;
}

int Stage::setPosX(double position)
{
	C843_MVR(ID, "2", &position);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE) {
		C843_IsMoving(ID, "2", &bIsMoving);
	}
	C843_qPOS(ID, "2", &position);
	posX = position;
	return 0;
}

int Stage::setPosY(double position)
{
	C843_MVR(ID, "3", &position);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE) {
		C843_IsMoving(ID, "3", &bIsMoving);
	}
	C843_qPOS(ID, "3", &position);
	posY = position;
	return 0;
}

int Stage::setPosZ(double position)
{
	C843_MVR(ID, "1", &position);
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE) {
		C843_IsMoving(ID, "1", &bIsMoving);
	}
	C843_qPOS(ID, "1", &position);
	posZ = position;
	return 0;
}

int Stage::setVelX(double velocity)
{
	C843_VEL(ID, "2", &velocity);
	C843_qVEL(ID, "2", &velocity);
	velX = velocity;
	return 0;
}

int Stage::setVelY(double velocity)
{
	C843_VEL(ID, "3", &velocity);
	C843_qVEL(ID, "3", &velocity);
	velY = velocity;
	return 0;
}

int Stage::setVelZ(double velocity)
{
	C843_VEL(ID, "1", &velocity);
	C843_qVEL(ID, "1", &velocity);
	velZ = velocity;
	return 0;
}

bool Stage::UserProfileIsActive(const char *Axis)
{
	BOOL Active;
	C843_IsUserProfileActive(ID, Axis, &Active);

	if(Active == TRUE)
		return true;
	else
		return false;

}

bool Stage::Profiler1Axis(const char *Axis, double InitialPos)
{
	long DatasetPerblock[1] = {5};		//UPC
	long Datasetlength[1] ={2};	//UPC
	const char* Cluster = "A";	//UPC, UPB
	
	long DatasetToClear[] = {-1};

	long BlocksToconsiderIndex[1] = {0};	//UPB, UPD
	long ParameterID[1] = {1};	//UPB

	long DataSetsPerBlocksIndex[5] = {0,1,2,3,4};
	long DataSetsPerBlocksIndex1[1] = {0};	//UPD
	long DataSetsPerBlocksIndex2[1] = {1};	//UPD
	long DataSetsPerBlocksIndex3[1] = {2};	//UPD
	long DataSetsPerBlocksIndex4[1] = {3};	//UPD
	long DataSetsPerBlocksIndex5[1] = {4};	//UPD

	double ValuesToInput1[2] = {5.0,InitialPos};	//UPD, Values to input: travel time, abs position, velocity.
	double ValuesToInput2[2] = {5.0,1.0};	//UPD, Values to input: travel time, abs position, velocity.
	double ValuesToInput3[2] = {5.0,2.0};
	double ValuesToInput4[2] = {5.0,3.0};
	double ValuesToInput5[2] = {0,4.0};	

	long Datasetout[] = {0};
	long Datasetlengthout[] = {1};
	
	BOOL upc_result = C843_UPC(ID, Axis, Cluster, DatasetPerblock, Datasetlength);
	BOOL upb_result = C843_UPB(ID, Cluster, BlocksToconsiderIndex, ParameterID, DatasetPerblock);
	
	BOOL upd1_result = C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex1, ValuesToInput1);	//For cluster A, Block 0, Dataset 0.
	BOOL upd2_result = C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex2, ValuesToInput2);	//For cluster A, Block 0, Dataset 1.
	BOOL upd3_result = C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex3, ValuesToInput3);	//For cluster A, Block 0, Dataset 2.
	BOOL upd4_result = C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex4, ValuesToInput4);	//For cluster A, Block 0, Dataset 3.
	BOOL upd5_result = C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex5, ValuesToInput5);	//For cluster A, Block 0, Dataset 4.
	
	BOOL upa_result = C843_UPA(ID, Cluster, BlocksToconsiderIndex);	
	BOOL upr_result = C843_UPR(ID, Axis, Cluster, DataSetsPerBlocksIndex1);
	
	if(upc_result == TRUE && upb_result == TRUE && upd1_result == TRUE && upd2_result == TRUE && upa_result == TRUE)
		return true;
	else
		return false;
}

bool Stage::Profiler2Axis(const char *Axis2, const char *Axis0, const char *Axis1, double InitialPosX[5], double InitialPosZ[5], double XVel[5], double ZVel[5], int Iteration)
{
	//Profiler txt file creation
	StreamWriter ^timeWriterP;
	FileInfo ^timeFileP = gcnew FileInfo("Profiler_info.txt");
	FileStream ^timeSaveP = timeFileP->Open(FileMode::Append, FileAccess::Write);
	timeWriterP = gcnew StreamWriter(timeSaveP);
	
	String^ errorreader0 = "No error";
	String^ errorreader1;
	errorreader1 = Stage::ReadError();
	
	timeWriterP->WriteLine(" ");
	timeWriterP->WriteLine(" ");
	timeWriterP->WriteLine(" ");
	timeWriterP->WriteLine(" ");
	timeWriterP->WriteLine("Iteration: {0}", Iteration);
	timeWriterP->WriteLine("Error message before any profile command:" + errorreader1);

	long Dataset[2] = {5,5};		//UPC - Because each move needs two datasets, I want to perform fourmoves
	long Datasetlength[2] ={3,3};	//UPC
	const char* Cluster = "AB";	//UPC, UPB
	const char* ClusterZ = "A";	//UPD
	const char* ClusterX = "B";	//UPD


	long BlocksToconsiderIndex[2] = {0,0};	//UPB
	long BlocksToconsiderIndexZ[1] = {0};	//UPD
	long BlocksToconsiderIndexX[1] = {0};	//UPD
	long DataSetsPerBlocks[2] = {5,5};	//UPB 
	long ParameterID[2] = {1,1};	//UPB

	long ParameterIDZ[] = {1};
	long ParameterIDX[] = {1};
	long DataSetsPerBlocksX[1] = {5};

	long DataSetsPerBlocksIndexZ0[] = {0};	//UPD For Z
	long DataSetsPerBlocksIndexZ1[] = {1};	
	long DataSetsPerBlocksIndexZ2[] = {2};	
	long DataSetsPerBlocksIndexZ3[] = {3};	
	long DataSetsPerBlocksIndexZ4[] = {4};	
	double ValuesToInputZ0[3] = {3.0,InitialPosZ[0],ZVel[0]};	
	double ValuesToInputZ1[3] = {2.0,InitialPosZ[1],ZVel[1]};
	double ValuesToInputZ2[3] = {5.0,InitialPosZ[2],ZVel[2]};
	double ValuesToInputZ3[3] = {5.0,InitialPosZ[3],ZVel[3]};
	double ValuesToInputZ4[3] = {0.0,InitialPosZ[4],ZVel[4]};

	long DataSetsPerBlocksIndexX0[] = {0};	//UPD For X
	long DataSetsPerBlocksIndexX1[] = {1};	
	long DataSetsPerBlocksIndexX2[] = {2};	
	long DataSetsPerBlocksIndexX3[] = {3};	
	long DataSetsPerBlocksIndexX4[] = {4};	
	double ValuesToInputX0[3] = {3.0,InitialPosX[0],XVel[0]};	
	double ValuesToInputX1[3] = {2.0,InitialPosX[1],XVel[1]};
	double ValuesToInputX2[3] = {5.0,InitialPosX[2],XVel[2]};
	double ValuesToInputX3[3] = {5.0,InitialPosX[3],XVel[3]};
	double ValuesToInputX4[3] = {0.0,InitialPosX[4],XVel[4]};

	long DatasetsTostart[2]={0,0};

	bool UPActiveXAxis = false;
	bool UPActiveZAxis = false;
	bool ProfilerIsClear = false;

	Stage::ControllerIsReady();
	if(errorreader1 != errorreader0)
	{
		timeWriterP->WriteLine("Error message before asking if UP mode is active:" + errorreader1);
		Stage::ControllerIsReady();
		UPActiveZAxis = Stage::UserProfileIsActive(Axis0);
		UPActiveXAxis = Stage::UserProfileIsActive(Axis1);
		timeWriterP->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);

		while(errorreader1 != errorreader0)
		{
			Stage::ControllerIsReady();
			UPActiveZAxis = Stage::UserProfileIsActive(Axis0);
			UPActiveXAxis = Stage::UserProfileIsActive(Axis1);
			errorreader1 = Stage::ReadError();
			timeWriterP->WriteLine("Error message after asking if UP mode is active:" + errorreader1);
			timeWriterP->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);
			timeWriterP->WriteLine(" ");

			Sleep(200);
		}
	}

	timeWriterP->WriteLine(" ");

	Stage::ControllerIsReady();
	BOOL upc_result = C843_UPC(ID, Axis2,	Cluster, Dataset, Datasetlength);
	BOOL upb_result = C843_UPB(ID, Cluster, BlocksToconsiderIndex, ParameterID, Dataset);
	
	BOOL updZ0_result = C843_UPD(ID, ClusterZ, BlocksToconsiderIndexZ, DataSetsPerBlocksIndexZ0, ValuesToInputZ0);	//For cluster A, Block 0, Dataset 0 of Block 0.
	BOOL updZ1_result = C843_UPD(ID, ClusterZ, BlocksToconsiderIndexZ, DataSetsPerBlocksIndexZ1, ValuesToInputZ1);
	BOOL updZ2_result = C843_UPD(ID, ClusterZ, BlocksToconsiderIndexZ, DataSetsPerBlocksIndexZ2, ValuesToInputZ2);
	BOOL updZ3_result = C843_UPD(ID, ClusterZ, BlocksToconsiderIndexZ, DataSetsPerBlocksIndexZ3, ValuesToInputZ3);
	BOOL updZ4_result = C843_UPD(ID, ClusterZ, BlocksToconsiderIndexZ, DataSetsPerBlocksIndexZ4, ValuesToInputZ4);

	BOOL updX0_result = C843_UPD(ID, ClusterX, BlocksToconsiderIndexX, DataSetsPerBlocksIndexX0, ValuesToInputX0);	//For cluster B, Block 0, Dataset 1 of Block 0.
	BOOL updX1_result = C843_UPD(ID, ClusterX, BlocksToconsiderIndexX, DataSetsPerBlocksIndexX1, ValuesToInputX1);
	BOOL updX2_result = C843_UPD(ID, ClusterX, BlocksToconsiderIndexX, DataSetsPerBlocksIndexX2, ValuesToInputX2);
	BOOL updX3_result = C843_UPD(ID, ClusterX, BlocksToconsiderIndexX, DataSetsPerBlocksIndexX3, ValuesToInputX3);
	BOOL updX4_result = C843_UPD(ID, ClusterX, BlocksToconsiderIndexX, DataSetsPerBlocksIndexX4, ValuesToInputX4);

	if(Iteration == 1)
	{
		timeWriterP->WriteLine("\tTime \t\t\tXPos \t\t\tXVel \t\t\tZPos \t\t\tZVel \t\t\tXUPD \tZUPD");
		timeWriterP->WriteLine("\t{0:0.000000000000000} \t{1:0.000000000000000} \t{2:0.000000000000000} \t{3:0.000000000000000} \t{4:0.000000000000000} \t{5} \t{6}", 3.0, InitialPosX[0], XVel[0], InitialPosZ[0], ZVel[0], updZ0_result, updX0_result);
		timeWriterP->WriteLine("\t{0:0.000000000000000} \t{1:0.000000000000000} \t{2:0.000000000000000} \t{3:0.000000000000000} \t{4:0.000000000000000} \t{5} \t{6}", 2.0, InitialPosX[1], XVel[1], InitialPosZ[1], ZVel[1], updZ1_result, updX1_result);
		timeWriterP->WriteLine("\t{0:0.000000000000000} \t{1:0.000000000000000} \t{2:0.000000000000000} \t{3:0.000000000000000} \t{4:0.000000000000000} \t{5} \t{6}", 5.0, InitialPosX[2], XVel[2], InitialPosZ[2], ZVel[2], updZ2_result, updX2_result);
		timeWriterP->WriteLine("\t{0:0.000000000000000} \t{1:0.000000000000000} \t{2:0.000000000000000} \t{3:0.000000000000000} \t{4:0.000000000000000} \t{5} \t{6}", 5.0, InitialPosX[3], XVel[3], InitialPosZ[3], ZVel[3], updZ3_result, updX3_result);
		timeWriterP->WriteLine("\t{0:0.000000000000000} \t{1:0.000000000000000} \t{2:0.000000000000000} \t{3:0.000000000000000} \t{4:0.000000000000000} \t{5} \t{6}", 0.0, InitialPosX[4], XVel[4], InitialPosZ[4], ZVel[4], updZ4_result, updX4_result);
		timeWriterP->WriteLine(" ");
	}

	timeWriterP->WriteLine("Error message after UPC and UPB commands:" + Stage::ReadError());
	timeWriterP->WriteLine("\tUPC \tUPB ");
	timeWriterP->WriteLine("\t" + upc_result + "\t" + upb_result);

	Stage::ControllerIsReady();
	BOOL upa_result = C843_UPA(ID, Cluster, BlocksToconsiderIndex);
	
	timeWriterP->WriteLine("Error message after UPA command:" + Stage::ReadError());
	timeWriterP->WriteLine("\tUPA ");
	timeWriterP->WriteLine("\t" + upa_result);
	timeWriterP->WriteLine(" ");
	
	timeWriterP->Close();
	timeSaveP->Close();

	if(upa_result == TRUE)
		return true;
	else
		return false;

}

bool Stage::ProfilerClearer()
{
	//Profiler txt file creation
	StreamWriter ^timeWriterP2;
	FileInfo ^timeFileP2 = gcnew FileInfo("Profiler_info.txt");
	FileStream ^timeSaveP2 = timeFileP2->Open(FileMode::Append, FileAccess::Write);
	timeWriterP2 = gcnew StreamWriter(timeSaveP2);

	long DatasetToClear[] = {-1};
	const char* Clearer = "$";
	const char* Axis0 = "1";
	const char* Axis1 = "2";
	const char* Axis2 = "3";
	bool UPActiveXAxis = false;
	bool UPActiveZAxis = false;

	String^ errorreaderUPC0 = "No error";
	String^ errorreaderUPC1;
	errorreaderUPC1 = Stage::ReadError();

	timeWriterP2->WriteLine("Error message before any clearing profile:" + errorreaderUPC1);

	Stage::ControllerIsReady();
	if(errorreaderUPC1 != errorreaderUPC0)
	{
		timeWriterP2->WriteLine("Error message before asking if UP mode is active:" + errorreaderUPC1);
		Stage::ControllerIsReady();
		UPActiveZAxis = Stage::UserProfileIsActive(Axis0);
		UPActiveXAxis = Stage::UserProfileIsActive(Axis1);
		timeWriterP2->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);

		while(errorreaderUPC1 != errorreaderUPC0)
		{
			Stage::ControllerIsReady();
			UPActiveZAxis = Stage::UserProfileIsActive(Axis0);
			UPActiveXAxis = Stage::UserProfileIsActive(Axis1);
			errorreaderUPC1 = Stage::ReadError();
			timeWriterP2->WriteLine("Error message after asking if UP mode is active:" + errorreaderUPC1);
			timeWriterP2->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);
			timeWriterP2->WriteLine(" ");

			Sleep(200);
		}
	}

	Stage::ControllerIsReady();
	BOOL upc0_result = C843_UPC(ID, Clearer, Clearer, DatasetToClear, DatasetToClear);

	timeWriterP2->WriteLine("Error message after clearing profile:" + Stage::ReadError());
	timeWriterP2->WriteLine("\tUPC0");
	timeWriterP2->WriteLine("\t " + upc0_result);
	timeWriterP2->WriteLine(" ");
	timeWriterP2->WriteLine(" ");
	timeWriterP2->WriteLine(" ");
	
	timeWriterP2->Close();
	timeSaveP2->Close();

	if(upc0_result == TRUE)
		return true;
	else
		return false;
}

String^ Stage::ReadError()
{
	BOOL qerr_result;
	long errorId = 0;
	char errorMessage[1001] = "";

	qerr_result = C843_qERR(ID, &errorId);
	if (errorId != 0)
    {
        C843_TranslateError (errorId, errorMessage, 1000);
		int a = 1; // PIsupport: set your breakpoint here
		String^ error = gcnew String(errorMessage);
		return error;
    }
	else
	{
		String^ error = "No error";
		return error;
	}
}

bool Stage::ControllerIsReady()
{
	bool bFlag = FALSE;
	
	while(bFlag != TRUE){
		C843_IsControllerReady(ID, (long*)&bFlag);
		Sleep(200);
	}
	return true;
}

bool Stage::RunProfilerFor2Axis(const char *Axis2, int Iteration)
{
	const char* Cluster = "AB";
	long DatasetsTostart[2]={0,0};

	BOOL upr_result = C843_UPR(ID, Axis2, Cluster, DatasetsTostart);

	if(upr_result == TRUE)
		return true;
	else
		return false;
}