#include "VictorSpeedController.h"

namespace ohs2021{

    VictorSpeedController::VictorSpeedController(ctre::phoenix::motorcontrol::can::VictorSPX *victor){
        m_Victor = victor;
    }

    double VictorSpeedController::Get() const {
        return 0;
    };
    bool VictorSpeedController::GetInverted() const {
        return m_Victor->GetInverted();
    };
    void VictorSpeedController::Set(double speed) {
        m_Victor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    };
    void VictorSpeedController::SetInverted(bool isInverted) {};
    void VictorSpeedController::SetVoltage(units::volt_t output) {};
}