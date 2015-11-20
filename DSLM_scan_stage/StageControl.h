#ifndef _STAGECONTROL_H
#define _STAGECONTROL_H

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;

//Axis annotation Z="1"; X="2"; Y="3"
//coordinate system: Z(Up, Down); X(Front, Back); Y(Left, Right)

namespace stageNameSpace
{
ref class Stage{
public:
	Stage();
	~Stage();

	static void Initialize();
	static int PerformProfilerTest();
	static double MoveStage(const char *Axis, double Position);
	static void MoveStageBlocking(const char *Axis, double Position);
	static void WaitStageToStopMoving(const char *Axis);

	static bool Stage::IsOnTarget(const char *Axis);

	static double GetPosition(const char *Axis);
	static bool Stage::IsMoving(const char *Axis);
	static bool Stage::IsUserProfileActive(const char *Axis);	
	static void WaitUserProfileModeToFinish(const char *Axis);		   

//	static void Stage::GenerateAndRunProfile(const char *Axis);
	static void Stage::GenerateProfile(const char *Axis);
	static void Stage::RunProfile(const char *Axis);
	static void Stage::ReadProfileConfiguration(const char *Axis);

	static void Stage::ClearOldProfile();

	static String^ Stage::ReadError();
	static bool Stage::DidErrorOccur(BOOL error, String^ errorString);
	static void Stage::HandleErrorAndWriteMessage(BOOL error,String^ message);
	static void Stage::HandleError(BOOL error,String^ message);

	static void Stage::WaitControllerToGetReady();
	static void Stage::RunProfilerFor2Axis(const char *Axis2);

	static StreamWriter^ profiler_log_file;

	static void Stage::EvaluateProfile();
	static void Stage::AllocateProfileArrays();


private:
	static int ID;

	static int numElementsInPath;
	static array< double>^ PathPointsX;
	static array< double>^ PathPointsZ;

	static int numElementsInProfileX;
	static array< double>^ ProfileIntervalTimesX;
	static array< double>^ XPOStoP;
	static array< double>^ XVELtoP;
	static array< double>^ XACCtoP;

	static int numElementsInProfileZ;
	static array< double>^ ProfileIntervalTimesZ;
	static array< double>^ ZPOStoP;
	static array< double>^ ZACCtoP;

	static double ScannerFrameRate; // [steps per second]
	static double StepSize; // [mm per step]
	static double MaxAcceleration; // [mm per s^2]


};

}
#endif