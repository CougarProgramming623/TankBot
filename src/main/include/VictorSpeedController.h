#pragma once

#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/SpeedController.h>
#include <ctre/phoenix/motorcontrol/ControlMode.h>


namespace ohs2021{
class VictorSpeedController : public frc::SpeedController {
public:
    VictorSpeedController(ctre::phoenix::motorcontrol::can::VictorSPX*);

    double Get() const override;
    bool GetInverted() const override;
    void Set(double speed) override;
    void SetInverted(bool isInverted) override;
    void SetVoltage(units::volt_t output) override;
    void Disable (){};
    void StopMotor (){};
    void PIDWrite (double output){};

private:

ctre::phoenix::motorcontrol::can::VictorSPX* m_Victor;
};
}