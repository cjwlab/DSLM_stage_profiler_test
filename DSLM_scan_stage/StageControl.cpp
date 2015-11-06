#include "stdafx.h"
#include <Windows.h>
#include "C843_GCS_DLL.H"
#include "StageControl.h"
//#include "winmcl32_api.h"
#include <math.h>
#include <ctime>

using namespace System::IO;
using namespace stageNameSpace;


Stage::Stage()
{
// initialise and open log file
	String^ fileName = "profiler_log_file.txt";
	profiler_log_file = gcnew StreamWriter(fileName);
}

Stage::~Stage()
{
	profiler_log_file->Close();
}

int main(){
	Stage stage;	
	stage.PerformProfilerTest();
}

// compute profile parameters (time and velocity) based on positions and x-velocity
void Stage::EvaluateProfile()
{
// evaluate times between profile points
	for(int i=0;i<(numElementsInProfile-1);i++){
		ProfileIntervalTimes[i]=(XPOStoP[i+1]-XPOStoP[i])/XVELtoP[i];
	}
// last time is zero by definition (terminates the profile)
	ProfileIntervalTimes[numElementsInProfile-1]=0;

	/*
// evaluate z-velocities between profile points
	for(int i=0;i<(numElementsInProfile-1);i++){
		ZVELtoP[i]=(ZPOStoP[i+1]-ZPOStoP[i])/ProfileIntervalTimes[i];
	}
// last velocity is zero by definition
	ZVELtoP[numElementsInProfile-1]=0;
*/
}

void Stage::AllocateProfileArrays()
{
	ProfileIntervalTimes = gcnew array< double >(numElementsInProfile);
	XPOStoP = gcnew array< double >(numElementsInProfile);
	XVELtoP = gcnew array< double >(numElementsInProfile);

//	ZPOStoP = gcnew array< double >(numElementsInProfile);
//	ZVELtoP = gcnew array< double >(numElementsInProfile);
}

int Stage::PerformProfilerTest(){

// number of points in the desired profile
	numElementsInProfile=2;
	AllocateProfileArrays();

// profile definition
	XPOStoP[0]=0.0;	// first stage position
	XPOStoP[1]=1.0; // second stage position
	XVELtoP[0]=0.2; // stage velocity
	XVELtoP[1]=0.0;	// zero velocity in the end by definition

// this needs to be checked	
	Initialize();

	Sleep(2000);

// a loop for iterating the profile
	int iteration_index=0;
	while((iteration_index++)<50){
		profiler_log_file->WriteLine("Iteration: {0}", iteration_index);
		ClearOldProfile();		
		EvaluateProfile();

// move to initial position
		MoveStageBlocking(AxisX, XPOStoP[0]);
		MoveStageBlocking(AxisZ, ZPOStoP[0]);
		profiler_log_file->WriteLine("Stage position before the profile (X,Z)=({0},{1})",Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));
		
		std::clock_t start;
		start = std::clock();
		GenerateProfile();		
		RunProfile();
		profiler_log_file->WriteLine("Stage position after the profile (X,Z)=({0},{1})",Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));
		std::clock_t end;
		end = std::clock();
		double millisec = (end - start)/(double)(CLOCKS_PER_SEC / 1000);
		profiler_log_file->WriteLine("Time passed: {0} ms",millisec);
		profiler_log_file->WriteLine("");
	}

	int Counting_number_off_correct_Profiles = 0;	//To count the number of corrected profiles performed
	double Dif_x0_xf, Dif_z0_zf;					//To verify the number of corrected profiles performed is correct

	double xf = 0.0, zf = 0.0;
	double positionreader = 0.0, positionreader2 = 0.0;
	bool Profiler2AxisActive = false, ProfilerClearer = false;
	int counter = 0;
	bool UPActiveForZAxis, UPActiveForXAxis;
	double DifInX, DifInZ;
	bool ProfileFailed = false;						//To break the time points loop if the Profile fails
	bool AxisXIsMoving = false;
	bool AxisZIsMoving = false;

	String^ ReadError_0 = "No error";
	String^ ReadError_1;	

	Stage::WaitControllerToGetReady();
	Stage::MoveStage(AxisX, XPOStoP[0]);
	Stage::MoveStage(AxisZ, ZPOStoP[0]);

	//Loop to run the Profiler
	for (int l=1; l<=50 && ProfileFailed == false; l++)
	{
		Stage::WaitControllerToGetReady();
		positionreader = Stage::GetPosition(AxisX);
		positionreader2 = Stage::GetPosition(AxisZ);

		profiler_log_file->WriteLine("Time point: {0}", l);
		profiler_log_file->WriteLine(" {0} \t {1}\n", positionreader, positionreader2);

		std::clock_t    start;
		start = std::clock();

		//Profiler activation and Profiler Run functions are performed here
		Stage::WaitControllerToGetReady();
//		Profiler2AxisActive = Stage::Profiler2Axis(AxisZX, AxisZ, AxisX, XPOStoP, ZPOStoP, XVELtoP, ZVELtoP, l);
		RunProfilerFor2Axis(AxisZX);

		AxisXIsMoving = Stage::IsMoving(AxisX);
		AxisZIsMoving = Stage::IsMoving(AxisZ);
		Sleep(5000);

		while(AxisXIsMoving == true || AxisZIsMoving == true)
		{
			AxisXIsMoving = Stage::IsMoving(AxisX);
			AxisZIsMoving = Stage::IsMoving(AxisZ);
			Sleep(500);
		}

		profiler_log_file->WriteLine(" Profiler is Activated: " + Profiler2AxisActive);

		std::clock_t    end;
		end = std::clock();
		double millisec = (end - start)/(double)(CLOCKS_PER_SEC / 1000);

		Stage::WaitControllerToGetReady();
		xf = Stage::GetPosition(AxisX);
		zf = Stage::GetPosition(AxisZ);
		profiler_log_file->WriteLine(" {0} \t {1}\n", xf, zf);
		profiler_log_file->WriteLine(" {0}\n ", millisec);
		profiler_log_file->WriteLine("");
	
		
		Dif_x0_xf = abs(xf - XPOStoP[4]);
//		Dif_z0_zf = abs(zf - ZPOStoP[4]);	

		if((Dif_x0_xf < 0.001) && (Dif_z0_zf < 0.001))
		{
			Counting_number_off_correct_Profiles++;
		}
		profiler_log_file->WriteLine("{0} \t\t{1:0.000000000000000} \t{2:0.000000000000000} \t{3}", l, Dif_x0_xf, Dif_z0_zf, Counting_number_off_correct_Profiles);

		Stage::WaitControllerToGetReady();
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
			
			Stage::WaitControllerToGetReady();
			
			Sleep(1000);
		}
		DifInX = abs(xf - 0.0);
		DifInZ = abs(zf - 0.0);
		profiler_log_file->WriteLine("Dif in X and Z: {0} and {1}.", DifInX, DifInZ);
		profiler_log_file->WriteLine("Elapsed time until stage move to it initial positions: {0}.\n", counter);

		WaitControllerToGetReady();

		while(ReadError_1 != ReadError_0)
		{
			UPActiveForZAxis = Stage::IsUserProfileActive(AxisZ);
			UPActiveForXAxis = Stage::IsUserProfileActive(AxisX);
			ReadError_1 = Stage::ReadError();

			profiler_log_file->WriteLine("Error message after asking if UP mode is active:" + ReadError_1);
			profiler_log_file->WriteLine("For Axis Z: " + UPActiveForZAxis + "\t For Axis X: " + UPActiveForXAxis);
			profiler_log_file->WriteLine(" ");
			
			Stage::WaitControllerToGetReady();

			Sleep(1000);
		}

		//To exit the code if the profile is not correctly performed		
		if(Counting_number_off_correct_Profiles != l)
		{
			profiler_log_file->WriteLine(" ");
			profiler_log_file->WriteLine("End of experiment before all the iterations, due to wrong profile!");
			ProfileFailed = true;
		}

		//To clear the Profile clusters, avoiding some memory issue
		Stage::WaitControllerToGetReady();
		ProfilerClearer = Stage::ProfilerClearer();
		profiler_log_file->WriteLine("End of time point, Profile Clear: " + ProfilerClearer);
		if(ProfilerClearer == false)
		{
			Stage::WaitControllerToGetReady();
			profiler_log_file->WriteLine("Error message after set Controller to be ready:" + Stage::ReadError());
			ProfilerClearer = Stage::ProfilerClearer();
			profiler_log_file->WriteLine("Profile Clearing second time: " + ProfilerClearer);
		}

		counter = 0;
		profiler_log_file->WriteLine(" ");
		profiler_log_file->WriteLine(" ");
		profiler_log_file->WriteLine(" ");

		Sleep(1000);
	}
	//end of the loop to run the profiler

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
	
	
	HandleError(C843_qPOS(ID, "1", &position),"C843_qPOS");
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
	double Position;
	HandleError(C843_qPOS(ID, Axis, &Position),"C843_qPOS");
	return Position;
}

void Stage::MoveStageBlocking(const char *Axis, double Position)
{
	MoveStage(Axis, Position);
	bool bIsMoving = true;
	while(bIsMoving == TRUE) {
		bIsMoving=IsMoving(Axis);		
	}	
	return Position;
}

bool Stage::IsMoving(const char *Axis)
{
	BOOL bIsMoving;
	
	HandleError(C843_IsMoving(ID, Axis, &bIsMoving),"C843_IsMoving");
	
	if (bIsMoving == TRUE)
	{
		return true;
	}else{
		return false;
	}
}

double Stage::MoveStage(const char *Axis, double Position)
{
	HandleError(C843_MOV(ID, Axis, &Position),"C843_MOV");
	return 0;
}

// check if user profile is active
bool Stage::IsUserProfileActive(const char *Axis)
{
	BOOL Active;
	HandleError(C843_IsUserProfileActive(ID, Axis, &Active),"C843_IsUserProfileActive");

	if(Active == TRUE)
		return true;
	else
		return false;

}

bool Stage::GenerateProfile(const char *Axis)
{
	long DatasetPerblock[1] = {numElementsInProfile};		//UPC
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

bool Stage::Profiler2Axis(const char *Axis2, const char *Axis0, const char *Axis1, array< double>^ InitialPosX, array< double>^ InitialPosZ, array< double>^ XVel, array< double>^ ZVel, int Iteration)
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

	Stage::WaitControllerToGetReady();
	if(errorreader1 != errorreader0)
	{
		timeWriterP->WriteLine("Error message before asking if UP mode is active:" + errorreader1);
		Stage::WaitControllerToGetReady();
		UPActiveZAxis = Stage::IsUserProfileActive(Axis0);
		UPActiveXAxis = Stage::IsUserProfileActive(Axis1);
		timeWriterP->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);

		while(errorreader1 != errorreader0)
		{
			Stage::WaitControllerToGetReady();
			UPActiveZAxis = Stage::IsUserProfileActive(Axis0);
			UPActiveXAxis = Stage::IsUserProfileActive(Axis1);
			errorreader1 = Stage::ReadError();
			timeWriterP->WriteLine("Error message after asking if UP mode is active:" + errorreader1);
			timeWriterP->WriteLine("For Axis Z: " + UPActiveZAxis + "\t For Axis X: " + UPActiveXAxis);
			timeWriterP->WriteLine(" ");

			Sleep(200);
		}
	}

	timeWriterP->WriteLine(" ");

	Stage::WaitControllerToGetReady();
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

	Stage::WaitControllerToGetReady();
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

// clear profile
bool Stage::ClearOldProfile()
{
	long DatasetToClear[] = {-1};
	const char* Clearer = "$";	
	HandleError(C843_UPC(ID, Clearer, Clearer, DatasetToClear, DatasetToClear),"C843_UPC Clear profile");
	WaitControllerToGetReady();
}

// read GCS error 
String^ Stage::ReadError()
{	
	long errorId;
	char errorMessage[1001] = "";
	String^ error;

	errorId=C843_GetError(ID);
	if (errorId != 0)
    {
        C843_TranslateError (errorId, errorMessage, 1000);
		error = gcnew String(errorMessage);
    }
	else	
		String^ error = "No error";
	return error;
}

// check if an error was encountered by GCS command and write it to the log file with message
void Stage::HandleErrorAndWriteMessage(BOOL error,String^ message)
{
	String^ errorString="No error";
	if (error==TRUE){
		errorString=ReadError();
	}
	profiler_log_file->WriteLine(message+": "+errorString);
}

// check if an error was encountered by GCS command and write it to the log file
void Stage::HandleError(BOOL error,String^ message)
{
	String^ errorString;
	if (error==TRUE){
		errorString=ReadError();
		profiler_log_file->WriteLine(message+": "+errorString);		
	}	
}

// check if an error was encountered by GCS command and return it
bool Stage::DidErrorOccur(BOOL error, String^ errorString)
{
	errorString="No error";
	if (error==TRUE){
		errorString=ReadError();
		return true;
	}	
	return false;
}

// poll until controller is ready
void Stage::WaitControllerToGetReady()
{
	bool bFlag = FALSE;
	
	profiler_log_file->WriteLine("Polling with C843_IsControllerReady");
	while(bFlag != TRUE){
		HandleError(C843_IsControllerReady(ID, (long*)&bFlag),"C843_IsControllerReady");
		Sleep(200);
	}
	profiler_log_file->WriteLine("Controller is ready.");	
}

// run profiler for two axis
void Stage::RunProfilerFor2Axis(const char *Axis2)
{
	const char* Cluster = "AB";
	long DatasetsTostart[2]={0,0};

	HandleError(C843_UPR(ID, Axis2, Cluster, DatasetsTostart),"C843_UPR");
}