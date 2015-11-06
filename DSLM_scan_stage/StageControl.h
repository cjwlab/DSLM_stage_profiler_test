#ifndef _STAGECONTROL_H
#define _STAGECONTROL_H

using namespace System;
using namespace System::IO::Ports;

//Axis annotation Z="1"; X="2"; Y="3"
//coordinate system: Z(Up, Down); X(Front, Back); Y(Left, Right)

ref class Stage{
public:
	Stage();
	~Stage();

	static int Initialize();
	static int GetStageID();
	static double MoveStage(const char *Axis, double Position);
	static double MoveStageBlocking(const char *Axis, double Position);
	static double MoveRelative(const char *Axis, double Position);
	static double GetPosition(const char *Axis);
	static bool Stage::IsMoving(const char *Axis);

	static bool Stage::UserProfileIsActive(const char *Axis);
	static bool Stage::Profiler1Axis(const char *Axis, double InitialPos);
	static bool Stage::Profiler2Axis(const char *Axis2, const char *Axis0, const char *Axis1, double InitialPosX[5], double InitialPosZ[5], double XVel[5], double ZVel[5], int Iteration);
	static bool Stage::ProfilerClearer();
	static String^ Stage::ReadError();
	static bool Stage::ControllerIsReady();
	static bool Stage::RunProfilerFor2Axis(const char *Axis2, int Iteration);

	static int setPosX(double position);
	static double getPosX(){return posX;};
	static int setPosY(double position);
	static double getPosY(){return posY;};
	static int setPosZ(double position);
	static double getPosZ(){return posZ;};
	static int setVelX(double velocity);
	static double getVelX(){return velX;};
	static int setVelY(double velocity);
	static double getVelY(){return velY;};
	static int setVelZ(double velocity);
	static double getVelZ(){return velZ;};

private:
	static int ID;
	static double posX;
	static double posY;
	static double posZ;
	static double velX;
	static double velY;
	static double velZ;
	;
};

#endif