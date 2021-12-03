/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>

#include "DriveTrain.h"

namespace ohs2021 {

class Robot : public frc::TimedRobot {
public:
	Robot();

	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	inline static Robot& Get() { return *s_Instance; } 


private:
	static Robot* s_Instance;

	frc::Compressor c{0};
	frc::Solenoid solenoid1{0};
	frc::Solenoid solenoid2{1};
	frc::Solenoid solenoid3{2};
	frc::Solenoid solenoid4{3};

	ohs2021::DriveTrain m_DriveTrain;
};

}//namespace
