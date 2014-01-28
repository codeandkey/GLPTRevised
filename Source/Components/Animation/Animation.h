#pragma once

#include <neptune/Neptune.h>

namespace Components {
	class Animation : public Neptune::ECS::Component {
	public:
		Animation(std::string filename);
		Animation(void);

		void CreateFromFile(std::string filename);
		void SetAnimationState(std::string state_name);

		void UpdateAnimation(void);

		Neptune::Resource::Texture* GetAnimationTexture(void);
	private:
		
		std::map<std::string,std::vector<Neptune::Resource::Texture*>> animation_texture_map;
		std::map<std::string,std::vector<unsigned int>> animation_timer_map;
		unsigned int animation_step_counter;

		std::string current_animation_event;
		Neptune::OS::Timer::Stamp current_timer_stamp;
	};
}