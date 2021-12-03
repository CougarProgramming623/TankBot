#pragma once

#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

namespace ohs2021{

class DriveTrain {
public: 
    DriveTrain();

    void Init();

    void Drive(double x, double y);

private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_LeftTop;
    ctre::phoenix::motorcontrol::can::VictorSPX m_LeftBottom;
    ctre::phoenix::motorcontrol::can::VictorSPX m_RightTop;
    ctre::phoenix::motorcontrol::can::VictorSPX m_RightBottom;
 
}; //class
} //namespace