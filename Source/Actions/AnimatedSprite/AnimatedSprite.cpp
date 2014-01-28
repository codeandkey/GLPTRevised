#include "AnimatedSprite.h"

#include "../../Misc/ParamFetch.h"

using namespace Neptune;
using namespace Actions;

AnimatedSprite::AnimatedSprite(std::string animation_filename,float width, float height,float wrap_amt_x,float wrap_amt_y) : width(width) , height(height) {
	if (!wrap_amt_x) wrap_amt_x = width;
	if (!wrap_amt_y) wrap_amt_y = height;
	
	animation_handle=new Components::Animation(animation_filename);

	primitive_handle=Resource::Primitive<>::CreateXYRect(width,height,wrap_amt_x,wrap_amt_y);

	primitive_handle->GetDrawable()->SetPosition();
	primitive_handle->GetDrawable()->SetRotation();
	primitive_handle->GetDrawable()->SetShader(NULL);

	x=y=rotation=0.0f;
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

	float x_position = Misc::ParamFetch::Fetch<float,AnimatedSprite>(map_object, "position_x");
	float y_position = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "position_y");
	float z_position = 0.0f;
	
	primitive_handle->GetDrawable()->SetPosition(x_position, y_position, z_position);

	float player_angle = Misc::ParamFetch::Fetch<float, AnimatedSprite>(map_object, "position_angle");

	primitive_handle->GetDrawable()->SetRotation(player_angle * D3DX_PI / 180.0f, 0.0f, 0.0f, -1.0f);


}

void AnimatedSprite::SetShader(Neptune::Graphics::Shader<>* target_shader) {
	primitive_handle->GetDrawable()->SetShader(target_shader);
}