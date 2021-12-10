#include "ohs/RobotID.h"

#include <algorithm>
#include <sys/ioctl.h>
#include <net/if.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdint.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

#include <stdint.h>


namespace ohs623 {

	BotType RobotID::s_CurrentBot = BotType::BOT_TYPE_COUNT;
	MotorData MotorIDs [BotType::BOT_TYPE_COUNT][Motor::MOTOR_COUNT];
	ButtonData ButtonIDs [BotType::BOT_TYPE_COUNT][Button::BUTTON_COUNT];

	const uint8_t HENRY_MAC_ADDRESS [6] = {0x00, 0x80, 0x2F, 0x27, 0x20, 0x48  };
	const uint8_t NEWBOT_MAC_ADDRESS [6] = {0x00, 0x80, 0x2F, 0x17, 0xEE, 0xE9  };

	bool AreMacAddressEqual(const uint8_t (&a)[6], const uint8_t (&b)[6]) {
		static_assert(sizeof(a) == sizeof(b));
		for (unsigned int i = 0; i < sizeof(a); i++) {
			if (a[i] != b[i]) return false;
		}
		return true;
	}

	int RobotID::GetMotorID(Motor id) {
		const MotorData& data = Get(id);
		return data.ID;
	}

	int RobotID::GetButtonID(Button id) {
		const ButtonData& data = Get(id);
		return data.ID;
	}

	VictorSPX* RobotID::InitMotor(Motor motor) {
		const MotorData& data = Get(motor);
		
		return new VictorSPX(data.ID);

		// switch (data.Controller)
		// {
		// 	case MotorControllerType::TALON_SRX: 
		// 	{
		// 		OHS_DEBUG([motor](auto& f) { f << "Initalizing Talon SRX id " << motor; });
		// 		return new WPI_TalonSRX(data.ID);
		// 	}
		// 	case MotorControllerType::TALON_FX:
		// 	{
		// 		OHS_DEBUG([motor](auto& f) { f << "Initalizing Talon FX id " << motor; });
		// 		return new WPI_TalonFX(data.ID);
		// 	}
		// 	//default: OHS_ASSERT(false, "Motor controller type not recognised!!");
		// }
		// return nullptr;
	}

	const ButtonData& RobotID::Get(Button buttonID) {
		if (s_CurrentBot == BotType::BOT_TYPE_COUNT) {
			std::fill(ButtonIDs[0], ButtonIDs[0] + sizeof(ButtonIDs) / sizeof(ButtonIDs[0]), -1);

			//list buttons here
			ButtonIDs[BotType::HENRY][Button::ENDGAME_OVERRIDE] = {18};
			
		}

		return ButtonIDs[s_CurrentBot][buttonID];
	}

	const MotorData& RobotID::Get(Motor motorID) {
		if (s_CurrentBot == BotType::BOT_TYPE_COUNT) {
			MotorData defaultData = { -1, MotorControllerType::VICTOR_SPX};
			std::fill(MotorIDs[0], MotorIDs[0] + sizeof(MotorIDs) / sizeof(MotorIDs[0]), defaultData);

			//list motors here
			MotorIDs[BotType::HENRY][Motor::LEFT_TOP] = { 2, MotorControllerType::VICTOR_SPX};
			MotorIDs[BotType::HENRY][Motor::LEFT_BOTTOM] = { 1, MotorControllerType::VICTOR_SPX};
			MotorIDs[BotType::HENRY][Motor::RIGHT_TOP] = { 4, MotorControllerType::VICTOR_SPX};
			MotorIDs[BotType::HENRY][Motor::RIGHT_BOTTOM] = { 3, MotorControllerType::VICTOR_SPX};      

			//Default to saber if the bot type cant be found
			s_CurrentBot = BotType::HENRY;

			// MAC address detection

			struct ifreq ifr;
			struct ifconf ifc;
			char buf[1024];
			int success = 0;

			int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
			//OHS_ASSERT(sock != -1, "socket(AF_INET, SOCK_DGRAM, IPPROTO_IP) FAILED!");

			ifc.ifc_len = sizeof(buf);
			ifc.ifc_buf = buf;
			//if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { frc::DriverStation::ReportError("ioctl(sock, SIOCGIFCONF, &ifc) FAILED!"); }

			struct ifreq* it = ifc.ifc_req;
			const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

			for (; it != end; ++it) {
				strcpy(ifr.ifr_name, it->ifr_name);
				if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
					if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
						if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
							success = 1;
							break;
						}
					}
				}
				else { /* handle error */ }
			}
			unsigned char mac_address[6];

			if (success) memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
			//else frc::DriverStation::ReportError("Unable to find mac address for roborio!");

			if (AreMacAddressEqual(mac_address, HENRY_MAC_ADDRESS)) s_CurrentBot = BotType::HENRY;
			else if (AreMacAddressEqual(mac_address, NEWBOT_MAC_ADDRESS)) s_CurrentBot = BotType::NEWBOT;
			// else {
			// 	ohs623::DefaultFormatter formatter;
			// 	formatter.Write("Failed to match MAC address: ");
			// 	for (unsigned int i = 0; i < sizeof(mac_address); i++) {
			// 		formatter.Write("0x").Base(mac_address[i], 16).Write(' ');
			// 	}
			// 	frc::DriverStation::ReportError(formatter.c_str());
			// }
		}

		if (MotorIDs[s_CurrentBot][motorID].ID == -1) {
			// frc::DriverStation::ReportError("Invalid ID Number: " + std::to_string(motorID) + " For bot " + std::to_string(s_CurrentBot));
		}

		return MotorIDs[s_CurrentBot][motorID];
	}

} // namespace