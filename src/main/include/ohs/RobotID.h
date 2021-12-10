#pragma once

#include <ctre/Phoenix.h>

namespace ohs623 {

enum BotType {
	HENRY, NEWBOT,
	BOT_TYPE_COUNT
};

enum Button {
	ENDGAME_OVERRIDE,
	BUTTON_COUNT
};

struct ButtonData {
	int ID;
};

enum Motor { 
	LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM,
	MOTOR_COUNT
};

enum class MotorControllerType {
	VICTOR_SPX
};

struct MotorData {
	int ID;
	MotorControllerType Controller;
};

class RobotID {    

public:
	RobotID() = delete;

	static const MotorData& Get(Motor);
	static const ButtonData& Get(Button);
	int GetMotorID(Motor);
	int GetButtonID(Button);
	static VictorSPX* InitMotor(Motor);

	inline static BotType GetCurrentBot() { return s_CurrentBot; }

private:
	static BotType s_CurrentBot;

};

} // namepsace