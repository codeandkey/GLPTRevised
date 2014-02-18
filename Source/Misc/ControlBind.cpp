#include "ControlBind.h"

using namespace Misc;
using namespace Neptune::OS;

std::vector<std::pair<std::string, int>> ControlBind::control_map;

void ControlBind::LoadKeybinds(void) {
	if (ControlBind::control_map.size()) return;

	control_map.push_back(std::make_pair("Space",DIK_SPACE));
	control_map.push_back(std::make_pair("Escape", DIK_ESCAPE));
	control_map.push_back(std::make_pair("Left", DIK_LEFT));
	control_map.push_back(std::make_pair("Right", DIK_RIGHT));
	control_map.push_back(std::make_pair("Up", DIK_UP));
	control_map.push_back(std::make_pair("Down", DIK_DOWN));
	control_map.push_back(std::make_pair("A", DIK_A));
	control_map.push_back(std::make_pair("B", DIK_B));
	control_map.push_back(std::make_pair("C", DIK_C));
	control_map.push_back(std::make_pair("D", DIK_D));
	control_map.push_back(std::make_pair("E", DIK_E));
	control_map.push_back(std::make_pair("F", DIK_F));
	control_map.push_back(std::make_pair("G", DIK_G));
	control_map.push_back(std::make_pair("H", DIK_H));
	control_map.push_back(std::make_pair("I", DIK_I));
	control_map.push_back(std::make_pair("J", DIK_J));
	control_map.push_back(std::make_pair("K", DIK_K));
	control_map.push_back(std::make_pair("L", DIK_L));
	control_map.push_back(std::make_pair("M", DIK_M));
	control_map.push_back(std::make_pair("N", DIK_N));
	control_map.push_back(std::make_pair("O", DIK_O));
	control_map.push_back(std::make_pair("P", DIK_P));
	control_map.push_back(std::make_pair("Q", DIK_Q));
	control_map.push_back(std::make_pair("R", DIK_R));
	control_map.push_back(std::make_pair("S", DIK_S));
	control_map.push_back(std::make_pair("T", DIK_T));
	control_map.push_back(std::make_pair("U", DIK_U));
	control_map.push_back(std::make_pair("V", DIK_V));
	control_map.push_back(std::make_pair("W", DIK_W));
	control_map.push_back(std::make_pair("X", DIK_X));
	control_map.push_back(std::make_pair("Y", DIK_Y));
	control_map.push_back(std::make_pair("Z", DIK_Z));
	control_map.push_back(std::make_pair("Tilde",DIK_GRAVE));

	control_map.push_back(std::make_pair("C_A", 1));
	control_map.push_back(std::make_pair("C_B", 2));
	control_map.push_back(std::make_pair("C_X", 3));
	control_map.push_back(std::make_pair("C_Y", 4));
	control_map.push_back(std::make_pair("C_LB", 5));
	control_map.push_back(std::make_pair("C_RB", 6));
	control_map.push_back(std::make_pair("C_LS", 9));
	control_map.push_back(std::make_pair("C_RS", 10));
	control_map.push_back(std::make_pair("C_BACK", 7));
	control_map.push_back(std::make_pair("C_START", 8));
}

void ControlBind::ReloadControlsFromFile(void) {
	if (!Neptune::File::Config::Exists()) {
		new Neptune::File::Config("Config/GLPT_controls.cfg");
	} 
	else {
		Neptune::File::Config::Handle()->Switch("GLPT_controls.cfg");
	}

	// We enumerate all of the actions we will be using in the game here.

	std::string config_string_value,config_string_value_2;

	config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("ImmediateQuit");
	ActionMap::BindBooleanControl("QuitGame", ActionMap::BinaryActionType::KeyboardButton, GetKey(config_string_value));

	config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("ToggleDebugOverlay");
	ActionMap::BindBooleanControl("ToggleDebugOverlay", ActionMap::BinaryActionType::KeyboardButton, GetKey(config_string_value));

	if (Neptune::File::Config::Handle()->GetConfigValue<std::string>("[PlayerControllerOverride]") == "True") {
		ActionMap::BindRangedAxisControl("PlayerMovement", Input::AxisInput::Left, Input::Axis::X);

		config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("PlayerControllerJump");
		ActionMap::BindBooleanControl("PlayerJump", ActionMap::BinaryActionType::ControllerButton, GetKey(config_string_value));
	}
	else {
		config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("PlayerKeyboardLeft");
		config_string_value_2 = Neptune::File::Config::Handle()->GetConfigValue<std::string>("PlayerKeyboardRight");
		ActionMap::BindRangedKeyControl("PlayerMovement", GetKey(config_string_value), GetKey(config_string_value_2));

		config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("PlayerKeyboardJump");
		ActionMap::BindBooleanControl("PlayerJump", ActionMap::BinaryActionType::KeyboardButton, GetKey(config_string_value));
	}

	config_string_value = Neptune::File::Config::Handle()->GetConfigValue<std::string>("PlayerReset");

	ActionMap::BindBooleanControl("PlayerReset", ActionMap::BinaryActionType::KeyboardButton, GetKey(config_string_value));

	Neptune::File::Config::Release();
}

int ControlBind::GetKey(std::string key) {
	for (auto i : control_map) {
		if (i.first == key) {
			return i.second;
		}
	}

	return 0;
}