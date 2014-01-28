#include "Animation.h"

#include <fstream>

using namespace Neptune;
using namespace Components;

Animation::Animation(void) {
	animation_step_counter=0;
}

Animation::Animation(std::string filename) {
	animation_step_counter=0;

	CreateFromFile(filename);
}

void Animation::CreateFromFile(std::string filename) {

	std::ifstream file(filename);

	if (!file) {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_APP | Logging::LOG_USER,"[Animation] Failed to locate animation file. [" + filename + "]");
		return;
	}

	std::string file_input;

	while(!file.eof()) {
		file >> file_input;
		if (file_input[0]=='#') {
			std::getline(file,file_input);
			continue;
		}

		if (file_input=="animation") {
			std::string event_name="",texture_name="";
			unsigned int duration=0;

			file >> file_input;

			event_name=file_input;
			current_animation_event=event_name;

			while(true) {

				file >> texture_name;

				if (texture_name=="end") break;

				file >> duration;
				animation_texture_map[event_name].push_back(new Neptune::Resource::Texture(texture_name));
				animation_timer_map[event_name].push_back(duration);
			}
		}
	}
}

void Animation::SetAnimationState(std::string state) {
	if (current_animation_event==state) return;

	try {
		animation_texture_map.at(state);
	} catch(std::out_of_range) {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_USER | Logging::LOG_APP,"[Animation] Could not find animation state. [" + state + "]");
		return;
	}

	current_animation_event=state;
	animation_step_counter=0;

	if (!animation_texture_map[current_animation_event].size()) return;
	if (!animation_timer_map[current_animation_event][0]) return;

	current_timer_stamp=OS::Timer::Handle()->GetStamp();
}

void Animation::UpdateAnimation(void) {
	try {
		animation_texture_map.at(current_animation_event);
	} catch(std::out_of_range) {
		return;
	}

	static unsigned int next_anim_index=0;

	if (Neptune::OS::Timer::Handle()->GetMS(current_timer_stamp) > animation_timer_map[current_animation_event][animation_step_counter]) {
		next_anim_index++;
		if (next_anim_index>=animation_texture_map[current_animation_event].size()) next_anim_index=0;
		animation_step_counter=next_anim_index;
		
		if (!animation_timer_map[current_animation_event][animation_step_counter]) return;

		current_timer_stamp=OS::Timer::Handle()->GetStamp();
	}
}

Neptune::Resource::Texture* Animation::GetAnimationTexture(void) {
	if (animation_step_counter < 0 || animation_step_counter >= animation_timer_map[current_animation_event].size()) {
		return NULL;
	}

	return animation_texture_map[current_animation_event][animation_step_counter];
}