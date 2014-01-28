#include "Player.h"

#include "../../Tasks/RenderController/RenderController.h"

using namespace Neptune;
using namespace Entities;

void Player::InitEvent(void) {
	animation_sprite_handle = new Actions::AnimatedSprite("Assets/Animations/player.ani",1.0f,1.0f);

	animation_sprite_handle->SetState("Idle");
	animation_sprite_handle->SetShader(Tasks::RenderController::Handle()->GetShader("WorldShaderDefault"));

	physbox_handle = new Actions::PhysBox(Actions::PhysBox::PhysBoxDesc(0.42f,1.0f));

	AppendActionEvents(physbox_handle);
	AppendActionEvents(animation_sprite_handle);

	Identity("Player");
}

void Player::StepEvent(void) {
	physbox_handle->XSpeed((OS::ActionMap::GetRangedValue("PlayerMovement") - 0.5f)*20.0f);

	if (OS::ActionMap::GetBooleanPressed("PlayerJump")) {
		physbox_handle->YSpeed(20.0f);
	}

	physbox_handle->Angle(0.0f);
}

void Player::DrawEvent(void) {
	// Synchronize the animation with the physbox.

	animation_sprite_handle->x=physbox_handle->X();
	animation_sprite_handle->y=physbox_handle->Y();
	animation_sprite_handle->z=0.0f;
	animation_sprite_handle->rotation=physbox_handle->Angle();

	// Done synchronizing.
}

void Player::DestroyEvent(void) {
	if (animation_sprite_handle) delete animation_sprite_handle;
	if (physbox_handle) delete physbox_handle;
}

float Player::X(void) {
	return physbox_handle->X();
}

float Player::Y(void) {
	return physbox_handle->Y();
}

float Player::Angle(void) {
	return physbox_handle->Angle();
}