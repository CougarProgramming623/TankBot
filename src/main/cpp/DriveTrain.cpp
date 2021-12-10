#include "DriveTrain.h"
#include "ohs/RobotID.h"

namespace ohs2021{

using namespace ohs623; 

DriveTrain::DriveTrain() :
    m_LeftBottom (RobotID::GetMotorID(LEFT_BOTTOM)),
    m_LeftTop (RobotID::GetMotorID(LEFT_TOP)),
    m_RightBottom (RobotID::GetMotorID(RIGHT_BOTTOM)),
    m_RightTop (RobotID::GetMotorID(RIGHT_TOP))
{};

void DriveTrain::Init(){
    m_LeftTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RobotID::GetMotorID(LEFT_BOTTOM));
    m_RightTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RobotID::GetMotorID(RIGHT_BOTTOM));

    

}

void DriveTrain::Drive(double x, double y){
    m_LeftBottom.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, .1);
    m_RightBottom.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -.1);
}

} //namespace