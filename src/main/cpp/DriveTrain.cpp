#include "DriveTrain.h"
#include "Robot.h"
#include "frc2/command/InstantCommand.h"
#include "VictorSpeedController.h"

namespace ohs2021{

DriveTrain::DriveTrain() :
    m_LeftBottom (1),
    m_LeftTop (2),
    m_RightBottom (3),
    m_RightTop (4),

    m_RobotDrive (new VictorSpeedController(&m_LeftBottom), new VictorSpeedController(&m_RightBottom)),

    m_GearboxToggle([&]{ return m_DriverJoystick.GetRawButton(1);})
{};

void DriveTrain::Init(){

    m_LeftTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
    m_RightTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 3);
    m_GearboxToggle.WhenPressed(frc2::InstantCommand([&]{

		Robot::Get().getGearSolenoid().Toggle();
		wpi::outs() << "Gear Change\n";
    
	}));
}

void DriveTrain::Drive(double x, double y){
    m_RobotDrive.ArcadeDrive(x, y, false);
}

void DriveTrain::Driving() {
    Drive(m_DriverJoystick.GetRawAxis(1), m_DriverJoystick.GetRawAxis(0));
}



} //namespace