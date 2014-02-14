#pragma once

#include <neptune/Neptune.h>

#include "../../Components/Animation/Animation.h"

namespace Actions {
	class AnimatedSprite : public Neptune::ECS::Action {
	public:
		AnimatedSprite(Neptune::Graphics::Shader<>* shader_handle);

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