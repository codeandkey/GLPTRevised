#pragma once

#include <neptune/Neptune.h>

#include "../../Components/Animation/Animation.h"

namespace Actions {
	class AnimatedSprite : public Neptune::ECS::Action {
	public:
		AnimatedSprite(std::string animation_filename,float width, float height,float wrap_amt_x=0.0f,float wrap_amt_y=0.0f);

		void CreateHook(void);
		void DrawHook(void);
		void DestroyHook(void);
		void SpecialHook(void*);

		void SetState(std::string state);

		void SetShader(Neptune::Graphics::Shader<>* shader_handle);

		float x,y,z;
		float rotation;
		float width, height;
	private:
		Components::Animation* animation_handle;
		Neptune::Graphics::Shader<>* shader_handle;
		Neptune::Resource::Primitive<>* primitive_handle;
	};
}