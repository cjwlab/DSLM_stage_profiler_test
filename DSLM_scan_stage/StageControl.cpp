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
	String^ fileName = "D:\\profiler_log_file.txt";
	profiler_log_file = gcnew StreamWriter(fileName);
}

Stage::~Stage()
{
	profiler_log_file->Close();
}

int main(){
	Stage stage;	
	stage.Initialize();
	
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

	char *AxisZ = "1";
	char *AxisX = "2";
	char *AxisY = "3";
	char *AxisZX = "12";

// profile definition
	XPOStoP[0]=0.0;	// first stage position
	XPOStoP[1]=2.0; // second stage position
	XVELtoP[0]=0.2*4; // stage velocity
	XVELtoP[1]=0.0;	// zero velocity in the end by definition

	EvaluateProfile();
	int errorCount=0;

// a loop for iterating the profile
	int iteration_index=0;
	while((iteration_index++)<100){
		std::clock_t    start;
		start = std::clock();
		profiler_log_file->WriteLine("Iteration: {0}", iteration_index);

// move to initial position
		MoveStageBlocking(AxisX, XPOStoP[0]);		
		profiler_log_file->WriteLine("Stage position before the profile (X,Z)=({0},{1})",Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));				
// clear, generate and run the profile
		ClearOldProfile();
		GenerateProfile(AxisX);
		profiler_log_file->WriteLine("");
		ReadProfileConfiguration(AxisX);
		profiler_log_file->WriteLine("");

		RunProfile(AxisX);
// wait user profile mode to terminate
		bool UserProfileActive=true;
		while(UserProfileActive==true){			
			UserProfileActive=IsUserProfileActive(AxisX);
		}
		if ((Stage::GetPosition(AxisX)-36050/7200)<(-0.1)){
			profiler_log_file->WriteLine("ERROR");
			errorCount++;
		}

		std::clock_t    end;
		end = std::clock();
		double millisec = (end - start)/(double)(CLOCKS_PER_SEC / 1000);

		profiler_log_file->WriteLine("Stage position after the profile (X,Z)=({0},{1})",Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));
		profiler_log_file->WriteLine("Time elapsed={0}",millisec);
		profiler_log_file->WriteLine("");
		profiler_log_file->Flush();
	}
	profiler_log_file->WriteLine("Total error count={0}",errorCount);

	return 0;
}
// ask profile parameters
void Stage::ReadProfileConfiguration(const char *Axis){
	long iPararray[1];
	long iCmdarray[1];
	char AxisTemp[]="2";

	HandleError(C843_qUPC(ID, "A",AxisTemp,iCmdarray, iPararray),"C843_qUPC ");
	profiler_log_file->WriteLine("qUPC: cluster A=({0}, {1})",iCmdarray[0],iPararray[0]);

	long dValarray0[1];
	iCmdarray[0]=0;
	for (int i=1;i<4;i++){
		iPararray[0]=i;
		HandleError(C843_qUPB(ID, "A",iCmdarray, iPararray,dValarray0),"C843_qUPB ");
		profiler_log_file->WriteLine("qUPB: cluster A, block 0, value{0}={1}",iPararray[0],dValarray0[0]);
	}

	for (int i=0;i<2;i++){
		iCmdarray[0]=i;
		HandleError(C843_qUPA(ID, "A",iCmdarray, iPararray),"C843_qUPA ");
		profiler_log_file->WriteLine("qUPA: cluster A, {0}={1}",iCmdarray[0],iPararray[0]);
	}



	iCmdarray[0]=0;
	iPararray[0]=0;	
	double dValarray[4];

	for (int i=1;i<5;i++){
		HandleError(C843_qUPD(ID, "A",iCmdarray, iPararray,dValarray),"C843_qUPD ");
		iPararray[0]=i;	
		profiler_log_file->WriteLine("qUPD cA b{0} d{1} = {2},{3},{4},{5}",iCmdarray[0],iPararray[0],dValarray[0],dValarray[1],dValarray[2],dValarray[3]);
	}
	 
	
}

// Initialise stage
void Stage::Initialize()
{
	char stages[1024]; 
	char axes[10];  
	double movr = 0.0;
	ID = C843_Connect(1); 
	if(ID==-1)
	{
		profiler_log_file->WriteLine("Error: stage not connected");
		return;
	}

	HandleError(C843_CST(ID,"1234","DSLM.STAGE\nDSLM.STAGE\nDSLM.STAGE\nNOSTAGE"),"initialisation C843_CST");
	HandleError(C843_qCST(ID, "1234", stages, 1024),"initialisation C843_qCST");
	System::String^ stageID = gcnew System::String(stages);
	HandleError(C843_qSAI(ID, axes, 9),"initialisation C843_qSAI");
	System::String^ axesID = gcnew System::String(axes);	
	HandleError(C843_INI(ID,axes),"initialisation C843_INI");
	
	bool bFlag = FALSE;
	HandleError(C843_FPL(ID,"1"),"initialisation C843_FPL");
	bFlag = FALSE;
	while(bFlag != TRUE){
		HandleError(C843_IsControllerReady(ID, (long*)&bFlag),"initialisation C843_IsControllerReady");
	}
	HandleError(C843_FPL(ID,"2"),"initialisation C843_FPL");
	bFlag = FALSE;
	while(bFlag != TRUE){
		HandleError(C843_IsControllerReady(ID, (long*)&bFlag),"initialisation C843_IsControllerReady");
	}
	HandleError(C843_FNL(ID,"3"),"initialisation C843_FNL");
	bFlag = FALSE;
	while(bFlag != TRUE){
		 HandleError(C843_IsControllerReady(ID, (long*)&bFlag),"initialisation C843_IsControllerReady");
	}

	HandleError(C843_MOV(ID, "1", &movr),"initialisation C843_MOV");
	HandleError(C843_MOV(ID, "2", &movr),"initialisation C843_MOV");
	HandleError(C843_MOV(ID, "3", &movr),"initialisation C843_MOV");
	BOOL bIsMoving = TRUE;
	while(bIsMoving == TRUE){
		HandleError(C843_IsMoving(ID, "1", &bIsMoving),"initialisation C843_IsMoving");
	}
	while(bIsMoving == TRUE){
		HandleError(C843_IsMoving(ID, "2", &bIsMoving),"initialisation C843_IsMoving");
	}
	while(bIsMoving == TRUE){
		HandleError(C843_IsMoving(ID, "3", &bIsMoving),"initialisation C843_IsMoving");
	}
	
}

// ask stage position
double Stage::GetPosition(const char *Axis)
{
	double Position;
	HandleError(C843_qPOS(ID, Axis, &Position),"C843_qPOS");
	return Position;
}

// move along one axis and wait that the motion is executed 
void Stage::MoveStageBlocking(const char *Axis, double Position)
{
	MoveStage(Axis, Position);
	WaitStageToStopMoving(Axis);
}

// wait stage to stop moving
void Stage::WaitStageToStopMoving(const char *Axis)
{	
	bool bIsMoving = true;
	while(bIsMoving == true) {
		Sleep(100);
		bIsMoving=IsMoving(Axis);		
	}	
}

// check is stage is moving
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

// check is stage is on target
bool Stage::IsOnTarget(const char *Axis)
{
	BOOL bIsOnTarget;
	
	HandleError(C843_qONT(ID, Axis, &bIsOnTarget),"C843_qONT");
	
	if (bIsOnTarget == TRUE)
	{
		return true;
	}else{
		return false;
	}
}

// Move stage
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

// wait user profile to become non active
void Stage::WaitUserProfileModeToFinish(const char *Axis)
{
	bool isActive=true;
	while (isActive==true){
		Sleep(100);
		isActive=IsUserProfileActive(Axis);
	}
}

void Stage::GenerateProfile(const char *Axis)
{
	long DatasetPerblock[1] = {4};		//UPC
	long Datasetlength[1] ={4};	//UPC length of parameter set
	const char* Cluster = "A";	//UPC, UPB
	
	long DatasetToClear[] = {-1}; // use to clear blocks from a cluster

	long BlocksToconsiderIndex[1] = {0};	//UPB, UPD block index to be used
	long ParameterID[1] = {1};	//UPB used to for UPB
	
// create cluster A
	HandleError(C843_UPC(ID, Axis, Cluster, DatasetPerblock, Datasetlength),"create profile C843_UPC");
// clear blocks from the cluster A	
	HandleError(C843_UPB(ID, Cluster, DatasetToClear, DatasetToClear, DatasetToClear),"create profile C843_UPB clear");
// create blocks into the cluster A
	HandleError(C843_UPB(ID, Cluster, BlocksToconsiderIndex, ParameterID, DatasetPerblock),"create profile C843_UPB create");
	
	long DataSetsPerBlocksIndex[1];	//UPD
	double ValuesToInput[4];	//UPD, Values to input: travel time, abs position, velocity.
/*
	DataSetsPerBlocksIndex[0]=0;
	ValuesToInput[0]=1;
	ValuesToInput[1]=0;
	ValuesToInput[2]=0;
	ValuesToInput[3]=1;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=1;
	ValuesToInput[0]=4;
	ValuesToInput[1]=0.5;
	ValuesToInput[2]=1;
	ValuesToInput[3]=0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=2;
	ValuesToInput[0]=1;
	ValuesToInput[1]=4.5;
	ValuesToInput[2]=1;
	ValuesToInput[3]=-1;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=3;
	ValuesToInput[0]=0;
	ValuesToInput[1]=5;
	ValuesToInput[2]=0;
	ValuesToInput[3]=0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	*/
	DataSetsPerBlocksIndex[0]=0;
	ValuesToInput[0]=5.0/60.0;
	ValuesToInput[1]=0.0;
	ValuesToInput[2]=0.0;
	ValuesToInput[3]=1.0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=1;
	ValuesToInput[0]=60.0;
	ValuesToInput[1]=25.0/7200.0;
	ValuesToInput[2]=5.0/60.0;
	ValuesToInput[3]=0.0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=2;
	ValuesToInput[0]=5.0/60.0;
	ValuesToInput[1]=36025.0/7200.0;
	ValuesToInput[2]=5.0/60.0;
	ValuesToInput[3]=-1.0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	DataSetsPerBlocksIndex[0]=3;
	ValuesToInput[0]=0.0;
	ValuesToInput[1]=36050.0/7200.0;
	ValuesToInput[2]=0.0;
	ValuesToInput[3]=0.0;
	HandleError(C843_UPD(ID, Cluster, BlocksToconsiderIndex, DataSetsPerBlocksIndex, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.



//	WaitStageToStopMoving(Axis);		
}

void Stage::RunProfile(const char *Axis){
	
	const char* Cluster = "A";	//UPC, UPB	
	long BlocksToconsiderIndex[1] = {0};	//UPB, UPD block index to be used		
	long DataSetsPerBlocksIndex[1] = {0};	

	HandleError(C843_UPA(ID, Cluster, BlocksToconsiderIndex),"create profile C843_UPA");	
	HandleError(C843_UPR(ID, Axis, Cluster, DataSetsPerBlocksIndex),"create profile C843_UPR");	
}
// clear profile
void Stage::ClearOldProfile()
{
	long DatasetToClear[] = {-1};
	const char *Clearer = "$";	
	HandleError(C843_UPC(ID, Clearer, Clearer, DatasetToClear, DatasetToClear),"C843_UPC Clear profile");
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
	if (error==FALSE){
		errorString=ReadError();
	}
	profiler_log_file->WriteLine(message+": "+errorString);
}

// check if an error was encountered by GCS command and write it to the log file
void Stage::HandleError(BOOL error,String^ message)
{
	String^ errorString;
	if (error==FALSE){
		errorString=ReadError();
		profiler_log_file->WriteLine(message+": "+errorString);		
	}	
}

// check if an error was encountered by GCS command and return it
bool Stage::DidErrorOccur(BOOL error, String^ errorString)
{
	errorString="No error";
	if (error==FALSE){
		errorString=ReadError();
		return true;
	}	
	return false;
}

// poll until controller is ready
void Stage::WaitControllerToGetReady()
{
	long IsControllerReady=0;
	
	while(IsControllerReady != 1){
		HandleError(C843_IsControllerReady(ID, &IsControllerReady),"C843_IsControllerReady");
		Sleep(100);
	}	
}

// run profiler for two axis
void Stage::RunProfilerFor2Axis(const char *Axis2)
{
	const char* Cluster = "AB";
	long DatasetsTostart[2]={0,0};

	HandleError(C843_UPR(ID, Axis2, Cluster, DatasetsTostart),"C843_UPR");
}