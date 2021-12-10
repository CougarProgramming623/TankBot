#pragma once

#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/ControlMode.h>
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/RobotDrive.h>



namespace ohs2021{

class DriveTrain {
public: 
    DriveTrain();

    void Init();

    void Drive(double x, double y);

    void Driving();

private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_LeftTop;
    ctre::phoenix::motorcontrol::can::VictorSPX m_LeftBottom;
    ctre::phoenix::motorcontrol::can::VictorSPX m_RightTop;
    ctre::phoenix::motorcontrol::can::VictorSPX m_RightBottom;

    frc2::Button m_GearboxToggle;
	frc::Joystick m_DriverJoystick{0};

    frc::RobotDrive m_RobotDrive;
 
}; //class
} //namespace