#include "AnimatedSprite.h"

#include "../../Misc/ParamFetch.h"

using namespace Neptune;
using namespace Actions;

AnimatedSprite::AnimatedSprite(Graphics::Shader<>* shader_handle) {
	animation_handle = NULL;
	this->shader_handle = shader_handle;
}

void AnimatedSprite::CreateHook(void) {

}

void AnimatedSprite::SetState(std::string state) {
	animation_handle->SetAnimationState(state);
}

void AnimatedSprite::DestroyHook(void) {
	if (primitive_handle) delete primitive_handle;
	if (animation_handle) delete animation_handle;
}

void AnimatedSprite::DrawHook(void) {
	if (primitive_handle) {
		primitive_handle->GetDrawable()->SetPosition(x,y,z);
		primitive_handle->GetDrawable()->SetRotation(rotation * (float)  D3DX_PI / 180.0f,0,0,1);
		
		animation_handle->UpdateAnimation();
		primitive_handle->GetDrawable()->Texturize(animation_handle->GetAnimationTexture());

		primitive_handle->GetDrawable()->Draw();
	}
}

void AnimatedSprite::SpecialHook(void* parameter) {

	std::map<std::string, std::string> map_object = *((std::map<std::string, std::string>*) parameter);

	std::string animation_filename = Misc::ParamFetch::Fetch<std::string, AnimatedSprite>(map_object, "animation_filename");

	x = Misc::ParamFetch::Fetch<float,AnimatedSprite>(map_object, "position_x");
	y = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "position_y");
	z = 0.0f;

	float wrap_amt_x = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "sprite_wrap_x");
	float wrap_amt_y = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "sprite_wrap_y");
	
	width = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "dim_width");
	height = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "dim_height");

	if (!wrap_amt_x) wrap_amt_x = width;
	if (!wrap_amt_y) wrap_amt_y = height;

	animation_handle = new Components::Animation(animation_filename);

	primitive_handle = Resource::Primitive<>::CreateXYRect(width, height, wrap_amt_x, wrap_amt_y);

	primitive_handle->GetDrawable()->SetPosition(x, y, z);
	primitive_handle->GetDrawable()->SetShader(shader_handle);

	float player_angle = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "position_angle");

	animation_handle->SetAnimationState(Misc::ParamFetch::Fetch<std::string, AnimatedSprite>(map_object, "animation_state"));

	primitive_handle->GetDrawable()->SetRotation(player_angle * D3DX_PI / 180.0f, 0.0f, 0.0f, -1.0f);
}

void AnimatedSprite::SetShader(Neptune::Graphics::Shader<>* target_shader) {
	this->shader_handle = target_shader;
	primitive_handle->GetDrawable()->SetShader(target_shader);
}