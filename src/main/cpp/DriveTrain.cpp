#include "DriveTrain.h"

namespace ohs2021{

DriveTrain::DriveTrain() :
    m_LeftBottom (1),
    m_LeftTop (2),
    m_RightBottom (3),
    m_RightTop (4)
{};

void DriveTrain::Init(){
    m_LeftTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
    m_RightTop.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 3);

}

void DriveTrain::Drive(double x, double y){
    m_LeftBottom.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, .1);
    m_RightBottom.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -.1);
}

} //namespace