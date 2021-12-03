/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"



namespace ohs2021 {

	Robot* Robot::s_Instance = nullptr;

Robot::Robot() {

	s_Instance = this;

}


void Robot::RobotInit() {
	wpi::outs() << "Robot Init Started\n";
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */

void Robot::DisabledInit() {
	wpi::outs() << "Disabled\n";
}

void Robot::DisabledPeriodic() {

}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
	wpi::outs() << "Auto Init Started\n";
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
	wpi::outs() << "Teleop Init Started\n";
	solenoid1.Set(false);
	solenoid2.Set(true);
	solenoid3.Set(true);
	solenoid4.Set(true);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {

}


}//namespace


int main() {
	return frc::StartRobot<ohs2021::Robot>();
}



bool CanAssertionsQuit() {
	return true;//Maybe disable during competitions
}