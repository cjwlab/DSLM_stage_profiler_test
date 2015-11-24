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
	profiler_log_file->AutoFlush = true;
	MaxAcceleration=8; // [mm per s^2]
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

// compute profile parameters (time, position, velocity, acceleration) based on positions and x-velocity
void Stage::EvaluateProfile()
{
	double ConstantXVelocity=ScannerFrameRate*StepSize; // [mm/s]
	double TimePerStep=1.0/ScannerFrameRate;
	double TotalTravelTimeX=(PathPointsX[numElementsInPath-1]-PathPointsX[0]) / ConstantXVelocity + TimePerStep; // [s]	
	
// times of the x profile
	ProfileIntervalTimesX[0]=TimePerStep; // one step
	ProfileIntervalTimesX[1]=TotalTravelTimeX-TimePerStep*2.0;
	ProfileIntervalTimesX[2]=TimePerStep; // one step
	ProfileIntervalTimesX[3]=0.0; // 0 to stop the motion

// accelerations of the x profile
	XACCtoP[0]=ConstantXVelocity/TimePerStep;
	XACCtoP[1]=0;	// constant velocity
	XACCtoP[2]=-ConstantXVelocity/TimePerStep;
	XACCtoP[3]=0; // 0 to stop the motion

// velocities of the x profile
	XVELtoP[0]=0;
	XVELtoP[1]=ConstantXVelocity;
	XVELtoP[2]=ConstantXVelocity;
	XVELtoP[3]=0;

// positions of the x profile
	XPOStoP[0]=PathPointsX[0];
	XPOStoP[1]=PathPointsX[0]+0.5*(ConstantXVelocity/TimePerStep)*TimePerStep*TimePerStep;
	XPOStoP[2]=PathPointsX[numElementsInPath-1]-0.5*(ConstantXVelocity/TimePerStep)*TimePerStep*TimePerStep;
	XPOStoP[3]=PathPointsX[numElementsInPath-1];

//  Z data sets
	double v1=0; // velocity in the beginning of acceleration, initially this is zero
	for(int ZPathElement=0;ZPathElement<(numElementsInPath-1);ZPathElement++){

		double t0;	// absolute time in the beginning of acceleration
		if (ZPathElement==0)
			t0=0.0; // zero in the beginning of the whole profile
		else
			t0=TimePerStep/2.0+(PathPointsX[ZPathElement]-PathPointsX[0])/ConstantXVelocity; // calculated from the X path positions and x velocity

		double t2;
		if (ZPathElement==(numElementsInPath-2))
			t2=TotalTravelTimeX; // absolute time after the constant velocity motion
		else
			t2=TimePerStep/2.0+(PathPointsX[ZPathElement+1]-PathPointsX[0])/ConstantXVelocity; // absolute time after the constant velocity motion

		double dz=PathPointsZ[ZPathElement+1]-PathPointsZ[ZPathElement]; // change of the z path coordinate

		double k; // sign of the acceleration
		if (dz>(v1*(t2-t0)))
			k=1;
		else
			k=-1;

		double a=MaxAcceleration; // used acceleration

		double t1=t2-sqrt((t2-t0)*(t2-t0)+(2*v1*(t2-t0)-2*dz)/a/k); // absolute intermediate time between the acceleration and the constant velocity
		double vc=v1+a*k*(t1-t0); // the constant velocity 

// z acceleration
		ProfileIntervalTimesZ[ZPathElement*2]=t1-t0;
		ZACCtoP[ZPathElement*2]=MaxAcceleration*k;
		ZVELtoP[ZPathElement*2]=v1;
		ZPOStoP[ZPathElement*2]=PathPointsZ[ZPathElement];
// z constant velocity
		ProfileIntervalTimesZ[ZPathElement*2+1]=t2-t1;
		ZACCtoP[ZPathElement*2+1]=0;
		ZVELtoP[ZPathElement*2+1]=vc;
		ZPOStoP[ZPathElement*2+1]=PathPointsZ[ZPathElement]+v1*(t1-t0)+a*k/2*(t1-t0)*(t1-t0);
		
		v1=vc;
	}	
// z final deacceleration
		double AccelerationSign;
		if (v1>0)
			AccelerationSign=-1;
		else
			AccelerationSign=1;
		
		ProfileIntervalTimesZ[numElementsInProfileZ-2]=-v1/(MaxAcceleration*AccelerationSign);
		ZACCtoP[numElementsInProfileZ-2]=MaxAcceleration*AccelerationSign;
		ZVELtoP[numElementsInProfileZ-2]=v1;
		ZPOStoP[numElementsInProfileZ-2]=PathPointsZ[numElementsInPath-1];
// z halt
		ProfileIntervalTimesZ[numElementsInProfileZ-1]=0; // 0 to stop the motion
		ZACCtoP[numElementsInProfileZ-1]=0;
		ZVELtoP[numElementsInProfileZ-1]=0;
		ZPOStoP[numElementsInProfileZ-1]=PathPointsZ[numElementsInPath-1]+ProfileIntervalTimesZ[numElementsInProfileZ-2]*ZVELtoP[numElementsInProfileZ-2]+ProfileIntervalTimesZ[numElementsInProfileZ-2]*ProfileIntervalTimesZ[numElementsInProfileZ-2]/2*ZACCtoP[numElementsInProfileZ-2];
}

void Stage::AllocateProfileArrays()
{	
	PathPointsX = gcnew array< double >(numElementsInPath);
	PathPointsZ = gcnew array< double >(numElementsInPath);

	numElementsInProfileX=4; // acceleration + constant velocity + deacceleration + stop
	numElementsInProfileZ=2*numElementsInPath;

	ProfileIntervalTimesX = gcnew array< double >(numElementsInProfileX);
	XPOStoP = gcnew array< double >(numElementsInProfileX);
	XVELtoP = gcnew array< double >(numElementsInProfileX);
	XACCtoP = gcnew array< double >(numElementsInProfileX);

	ProfileIntervalTimesZ = gcnew array< double >(numElementsInProfileZ);
	ZPOStoP = gcnew array< double >(numElementsInProfileZ);
	ZVELtoP = gcnew array< double >(numElementsInProfileZ);
	ZACCtoP = gcnew array< double >(numElementsInProfileZ);
}

void Stage::PathSimulator(double TimeResolution){

	String^ fileName = "D:\\simulator_log_file.txt";
	StreamWriter^ simulator_log_file = gcnew StreamWriter(fileName);

	simulator_log_file->WriteLine("Scanner frame rate = {0}",ScannerFrameRate);
	simulator_log_file->WriteLine("Step size = {0}\n",StepSize);
	simulator_log_file->WriteLine("Path points X,Z");

	for (int PathElementIndex=0;PathElementIndex<numElementsInPath;PathElementIndex++)
		simulator_log_file->WriteLine("{0}\t{1}",PathPointsX[PathElementIndex],PathPointsZ[PathElementIndex]);

	simulator_log_file->WriteLine("X profile parameters");
	simulator_log_file->WriteLine("t\t\t\tcum t\t\ts\t\t\tv\t\t\ta");
	double CumulativeTime=0;
	for (int ProfileElementIndex=0;ProfileElementIndex<numElementsInProfileX;ProfileElementIndex++){
		CumulativeTime+=ProfileIntervalTimesX[ProfileElementIndex];
		simulator_log_file->WriteLine("{0:0.000000}\t{1:0.000000}\t{2:0.000000}\t{3:0.000000}\t{4:0.000000}",ProfileIntervalTimesX[ProfileElementIndex],CumulativeTime,XPOStoP[ProfileElementIndex],XVELtoP[ProfileElementIndex],XACCtoP[ProfileElementIndex]);
	}

	simulator_log_file->WriteLine("Z profile parameters");
	simulator_log_file->WriteLine("t\t\t\tcum t\t\ts\t\t\tv\t\t\ta");
	CumulativeTime=0;
	for (int ProfileElementIndex=0;ProfileElementIndex<numElementsInProfileZ;ProfileElementIndex++){
		CumulativeTime+=ProfileIntervalTimesZ[ProfileElementIndex];
		simulator_log_file->WriteLine("{0:0.000000}\t{1:0.000000}\t{2:0.000000}\t{3:0.000000}\t{4:0.000000}",ProfileIntervalTimesZ[ProfileElementIndex],CumulativeTime,ZPOStoP[ProfileElementIndex],ZVELtoP[ProfileElementIndex],ZACCtoP[ProfileElementIndex]);
	}

	double MaxTimeX=0;
	double MaxTimeZ=0;
	for(int DataSetIndex=0;DataSetIndex<numElementsInProfileX;DataSetIndex++)
		MaxTimeX+=ProfileIntervalTimesX[DataSetIndex];
	for(int DataSetIndex=0;DataSetIndex<numElementsInProfileZ;DataSetIndex++)
		MaxTimeZ+=ProfileIntervalTimesZ[DataSetIndex];

	int CurrentDataSetX=0;
	int CurrentDataSetZ=0;
	double CurrentCumulativeTimeX=ProfileIntervalTimesX[0];
	double CurrentCumulativeTimeZ=ProfileIntervalTimesZ[0];
	bool UseMaxTimeX=false;

	simulator_log_file->WriteLine("t\t\tx\t\tz\t\tvx\t\tvz\t\tax\t\taz");
	for(double time=0.0;time<=MaxTimeZ;time+=TimeResolution){
		
		while((time>CurrentCumulativeTimeX) & (UseMaxTimeX==false)){
			CurrentDataSetX++;
			if(CurrentDataSetX==numElementsInProfileX)
			{
				CurrentDataSetX--;
				UseMaxTimeX=true;
			}
			else
				CurrentCumulativeTimeX+=ProfileIntervalTimesX[CurrentDataSetX];
		}
		while((time>CurrentCumulativeTimeZ) & (CurrentDataSetZ<(numElementsInProfileZ-1))){
			CurrentDataSetZ++;
			CurrentCumulativeTimeZ+=ProfileIntervalTimesZ[CurrentDataSetZ];
		}

		double TimeX=time;
		if(UseMaxTimeX)
			TimeX=MaxTimeX;
		double TimeZ=time;

		double TimeDeltaX=TimeX-(CurrentCumulativeTimeX-ProfileIntervalTimesX[CurrentDataSetX]);
		double TimeDeltaZ=TimeZ-(CurrentCumulativeTimeZ-ProfileIntervalTimesZ[CurrentDataSetZ]);

		double VelocityX=XVELtoP[CurrentDataSetX]+XACCtoP[CurrentDataSetX]*TimeDeltaX;
		double VelocityZ=ZVELtoP[CurrentDataSetZ]+ZACCtoP[CurrentDataSetZ]*TimeDeltaZ;

		double PositionX=XPOStoP[CurrentDataSetX]+XVELtoP[CurrentDataSetX]*TimeDeltaX+XACCtoP[CurrentDataSetX]*TimeDeltaX*TimeDeltaX/2.0;
		double PositionZ=ZPOStoP[CurrentDataSetZ]+ZVELtoP[CurrentDataSetZ]*TimeDeltaZ+ZACCtoP[CurrentDataSetZ]*TimeDeltaZ*TimeDeltaZ/2.0;

		simulator_log_file->WriteLine("{0:0.0000}\t{1:0.0000}\t{2:0.0000}\t{3:0.0000}\t{4:0.0000}\t{5:0.0000}\t{6:0.0000}",time,PositionX,PositionZ,VelocityX,VelocityZ,XACCtoP[CurrentDataSetX],ZACCtoP[CurrentDataSetZ]); 

	}

	simulator_log_file->Close();	
}

int Stage::PerformProfilerTest(){

	long TriggerLines[3];
	TriggerLines[0]=1;
	TriggerLines[1]=1;
	TriggerLines[2]=1;
	long TriggerParameterIDs[3];
	TriggerParameterIDs[0]=2;
	TriggerParameterIDs[1]=3;
	TriggerParameterIDs[2]=7;

	char out[20];

	HandleError(C843_qCTO(ID,TriggerLines,TriggerParameterIDs,out,3,20),"C843_qCTO");

	HandleError(C843_CTO(ID,&(TriggerLines[0]),&(TriggerParameterIDs[0]),"2",1),"C843_CTO2");
	HandleError(C843_CTO(ID,&(TriggerLines[1]),&(TriggerParameterIDs[1]),"6",1),"C843_CTO6");
	HandleError(C843_CTO(ID,&(TriggerLines[2]),&(TriggerParameterIDs[2]),"1",1),"C843_CTO1");

	HandleError(C843_qCTO(ID,TriggerLines,TriggerParameterIDs,out,3,20),"C843_qCTO");

	BOOL TriggerOn[1];
	TriggerOn[0]=FALSE;
	HandleError(C843_TRO(ID,&(TriggerLines[0]),TriggerOn,1),"C843_TRO");

	char *AxisX = "2";
/*	while(1){
		Sleep(200);
		MoveStageBlocking(AxisX, 6.0);
		Sleep(200);
		MoveStageBlocking(AxisX, 6.5);
	}
	*/

// number of points in the desired profile
	numElementsInPath=2;
	AllocateProfileArrays();

	char *AxisZ = "1";

	char *AxisY = "3";
	char *AxisZX = "12";

// path defition definition [mm]
	PathPointsX[0]=0.0;
	PathPointsX[1]=0.2;

	PathPointsZ[0]=0.0;
	PathPointsZ[1]=0.05;

	ScannerFrameRate=50; // [steps per second]
	StepSize=0.00184; // [mm per step]

	EvaluateProfile();
	PathSimulator(1/ScannerFrameRate);

	int errorCount=0;
// a loop for iterating the profile
	int iteration_index=0;
	while((iteration_index++)<200){

		profiler_log_file->WriteLine("Iteration: {0}", iteration_index);

// move to initial position
		profiler_log_file->WriteLine("Move Stage Blocking X...");
		Sleep(1000);
		MoveStageBlocking(AxisX, PathPointsX[0]);		
		profiler_log_file->WriteLine("Move Stage Blocking X...done.");
		profiler_log_file->WriteLine("Move Stage Blocking Z...");
		MoveStageBlocking(AxisZ, PathPointsZ[0]);		
		profiler_log_file->WriteLine("Move Stage Blocking Z...done.");
		profiler_log_file->WriteLine("Stage position before the profile (X,Z)=({0},{1})",Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));				
		Sleep(1000);
// clear, generate and run the profile
		ClearOldProfile();
		GenerateProfile();
		profiler_log_file->WriteLine("");
		ReadProfileConfiguration();
		profiler_log_file->WriteLine("");

		std::clock_t start;
		start = std::clock();
/*
		TriggerOn[0]=TRUE;
		HandleError(C843_TRO(ID,&(TriggerLines[0]),TriggerOn,1),"C843_TRO");
		Sleep(100);*/
		RunProfile();
/*		Sleep(1000);
		TriggerOn[0]=FALSE;
		HandleError(C843_TRO(ID,&(TriggerLines[0]),TriggerOn,1),"C843_TRO");*/
		

// wait user profile mode to terminate
/*		bool UserProfileActive=true;
		while(UserProfileActive==true){			
			UserProfileActive=IsUserProfileActive(AxisX);
		}
		*/

		std::clock_t TimerEnd;
		bool UserProfileActiveX=true;
		bool UserProfileActiveZ=true;
		profiler_log_file->WriteLine("Stage position (t,X,Z)");
		while((UserProfileActiveX==true) | (UserProfileActiveZ==true)){			
			UserProfileActiveX=IsUserProfileActive(AxisX);
			UserProfileActiveZ=IsUserProfileActive(AxisZ);
			
			TimerEnd = std::clock();
			double SecRange = (TimerEnd - start)/(double)(CLOCKS_PER_SEC);
			
			profiler_log_file->WriteLine("{0:0.00000}\t\t{1:0.00000}\t\t{2:0.00000}",SecRange,Stage::GetPosition(AxisX),Stage::GetPosition(AxisZ));
			Sleep(20);
		}

		if ((Stage::GetPosition(AxisX)-PathPointsX[numElementsInPath-1])<(-0.1)){
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
void Stage::ReadProfileConfiguration(){
// query the cluster configuration
	char AxisInCluster[2];
	long NumberOfDataSets[2];
	long LengthOfDataSets[2];

	HandleError(C843_qUPC(ID, "AB",AxisInCluster,NumberOfDataSets, LengthOfDataSets),"C843_qUPC ");
	profiler_log_file->WriteLine("qUPC: cluster A=({0}, {1}, {2})",AxisInCluster[0],NumberOfDataSets[0],LengthOfDataSets[0]);
	profiler_log_file->WriteLine("qUPC: cluster B=({0}, {1}, {2})",AxisInCluster[1],NumberOfDataSets[1],LengthOfDataSets[1]);

// query the block configuration
	long BlockIndex[1];
	BlockIndex[0]=0;
	long iPararray[1];
	long dValarray0[1];
// Z axis
	for (int i=1;i<4;i++){
		iPararray[0]=i;
		HandleError(C843_qUPB(ID, "A",BlockIndex,iPararray,dValarray0),"C843_qUPB ");
		profiler_log_file->WriteLine("qUPB: cluster A (Z), block {0}, value{1}={2}",BlockIndex[0],iPararray[0],dValarray0[0]);
	}
// X axis
	for (int i=1;i<4;i++){
		iPararray[0]=i;
		HandleError(C843_qUPB(ID, "B",BlockIndex,iPararray,dValarray0),"C843_qUPB ");
		profiler_log_file->WriteLine("qUPB: cluster B (X), block {0}, value{1}={2}",BlockIndex[0],iPararray[0],dValarray0[0]);
	}

/*
	long iPararray[1];
	long iCmdarray[1];
	for (int i=0;i<2;i++){
		iCmdarray[0]=i;
		HandleError(C843_qUPA(ID, "A",iCmdarray, iPararray),"C843_qUPA ");
		profiler_log_file->WriteLine("qUPA: cluster A, {0}={1}",iCmdarray[0],iPararray[0]);
	}
*/

// query the data set configuration
	long iCmdarray[1];
	iCmdarray[0]=0;
	iPararray[0]=0;	
	double dValarray[4];
// Z axis
	for (long i=0;i<(NumberOfDataSets[0]);i++){
		iPararray[0]=i;	
		HandleError(C843_qUPD(ID, "A",iCmdarray, iPararray,dValarray),"C843_qUPD ");
		profiler_log_file->WriteLine("qUPD cA b{0} d{1} = {2},{3},{4},{5}",iCmdarray[0],iPararray[0],dValarray[0],dValarray[1],dValarray[2],dValarray[3]);
	}
// X axis
	for (long i=0;i<(NumberOfDataSets[1]);i++){
		iPararray[0]=i;	
		HandleError(C843_qUPD(ID, "B",iCmdarray, iPararray,dValarray),"C843_qUPD ");
		profiler_log_file->WriteLine("qUPD cB b{0} d{1} = {2},{3},{4},{5}",iCmdarray[0],iPararray[0],dValarray[0],dValarray[1],dValarray[2],dValarray[3]);
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
	HandleError(C843_FNL(ID,"3"),"initialisation C843_FPL");
	bFlag = FALSE;
	while(bFlag != TRUE){
		 HandleError(C843_IsControllerReady(ID, (long*)&bFlag),"initialisation C843_IsControllerReady");
	}

/*
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
*/	

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
//	double PreviousPosition=100;
	bIsMoving=IsMoving(Axis);
	while(bIsMoving == true) {
		Sleep(100);
		bIsMoving=IsMoving(Axis);		
/*		double Position=GetPosition(Axis);
		bool OnTarget=IsOnTarget(Axis);
		double Velocity;
		HandleError(C843_qVEL(ID, Axis, &Velocity),"C843_qVEL");
		double Acceleration;
		HandleError(C843_qACC(ID, Axis, &Acceleration),"C843_qACC");
		if (bIsMoving & (PreviousPosition==Position)){			
			Sleep(100);
			bIsMoving=IsMoving(Axis);		
			profiler_log_file->WriteLine("ERROR: WaitStageToStopMoving: IsMoving={0}, OnTarget={1}, Velocity={2}, Acceleration={3}",bIsMoving,OnTarget,Velocity,Acceleration);
			bIsMoving=false;
		}
		PreviousPosition=Position;*/
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

void Stage::GenerateProfile()
{
// create cluster A
	char *AxisZX = "12";
	const char* ClusterAB = "AB";
	long DatasetPerblock[2];
	DatasetPerblock[0]=numElementsInProfileZ;
	DatasetPerblock[1]=numElementsInProfileX;
	long Datasetlength[2] ={4, 4}; //time, position, velocity, acceleration
	HandleError(C843_UPC(ID, AxisZX, ClusterAB, DatasetPerblock, Datasetlength),"create profile C843_UPC");

// clear blocks from the clusters A (Z)	and B (X)
	long DatasetToClear[2] = {-1 -1}; // use to clear blocks from a cluster
	HandleError(C843_UPB(ID, ClusterAB, DatasetToClear, DatasetToClear, DatasetToClear),"create profile C843_UPB clear");

// create blocks into the clusters A (Z) and B (X)
	long BlocksToconsiderIndex[2] = {0, 0};	// block index to be used
	long ParameterID[2] = {1, 1};	//UPB used to for UPB
	HandleError(C843_UPB(ID, ClusterAB, BlocksToconsiderIndex, ParameterID, DatasetPerblock),"create profile C843_UPB create");

// create X axis data sets (cluster B)
	char *AxisX = "2";
	const char* ClusterB = "B";

	for(long DataSetIndex=0;DataSetIndex<numElementsInProfileX;DataSetIndex++){
		long DataSetsOffset[1];	//UPD
		DataSetsOffset[0]=DataSetIndex;

		double ValuesToInput[4];	//UPD, Values to input: travel time, abs position, velocity.
		ValuesToInput[0]=ProfileIntervalTimesX[DataSetIndex];
		ValuesToInput[1]=XPOStoP[DataSetIndex];
		ValuesToInput[2]=XVELtoP[DataSetIndex];
		ValuesToInput[3]=XACCtoP[DataSetIndex];
		HandleError(C843_UPD(ID, ClusterB, &(BlocksToconsiderIndex[1]), DataSetsOffset, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	}

// create Z axis data sets (cluster A)
	char *AxisZ = "1";
	const char* ClusterA = "A";

	for(long DataSetIndex=0;DataSetIndex<numElementsInProfileZ;DataSetIndex++){
		long DataSetsOffset[1];	//UPD
		DataSetsOffset[0]=DataSetIndex;

		double ValuesToInput[4];	//UPD, Values to input: travel time, abs position, velocity.
		ValuesToInput[0]=ProfileIntervalTimesZ[DataSetIndex];
		ValuesToInput[1]=ZPOStoP[DataSetIndex];
		ValuesToInput[2]=ZVELtoP[DataSetIndex];
		ValuesToInput[3]=ZACCtoP[DataSetIndex];
		HandleError(C843_UPD(ID, ClusterA, &(BlocksToconsiderIndex[0]), DataSetsOffset, ValuesToInput),"create profile C843_UPD");	//For cluster A, Block 0, Dataset 0.
	}
}

void Stage::RunProfile(){
	
	const char* Cluster = "AB";	// Z and X axes
	long BlocksToconsiderIndex[2] = {0,0};	//UPB, UPD block index to be used		
	long DataSetsPerBlocksIndex[2] = {0,0};	

	HandleError(C843_UPA(ID, Cluster, BlocksToconsiderIndex),"create profile C843_UPA");	
	Sleep(1000);
	char *AxisZX = "12";
	HandleError(C843_UPR(ID, AxisZX, Cluster, DataSetsPerBlocksIndex),"create profile C843_UPR");	
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
		profiler_log_file->WriteLine("ERROR: "+message+": "+errorString);		
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