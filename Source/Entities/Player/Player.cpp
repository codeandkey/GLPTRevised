#include "Player.h"

#include "../../Tasks/RenderController/RenderController.h"

using namespace Neptune;
using namespace Entities;

static void AnimateValue(float* value, float target_value, float factor) {
	*value = (target_value - *value) / factor + *value;
}

void Player::InitEvent(void) {
	Graphics::Shader<>* world_shader = Tasks::RenderController::Handle()->GetShader("WorldShaderNoWrap");

	sprite_core_handle = new Actions::AnimatedSprite(world_shader, "Assets/Animations/player.ani", "Core", 0.25f, 0.25f, 1.0f, 1.0f);
	sprite_hat_handle = new Actions::AnimatedSprite(world_shader, "Assets/Animations/player.ani", "Hat", 0.25f, 0.25f, 1.0f, 1.0f);
	sprite_rings_handle = new Actions::AnimatedSprite(world_shader, "Assets/Animations/player.ani", "Rings", 1.2f, 1.2f, 1.0f, 1.0f);

	physbox_handle = new Actions::PhysBox();

	lower_sensor = new Actions::PhysSensor(0.5f,2.1f);

	AppendActionEvents(physbox_handle);
	AppendActionEvents(lower_sensor);
	AppendActionEvents(sprite_core_handle);
	AppendActionEvents(sprite_hat_handle);
	AppendActionEvents(sprite_rings_handle);

	Identity("Player");
}

void Player::StepEvent(void) {

	physbox_handle->Angle(0.0f);

	if (OS::ActionMap::GetBooleanPressed("PlayerReset")) {
		physbox_handle->X(initial_x);
		physbox_handle->Y(initial_y);
		physbox_handle->Angle(0.0f);
	}

	if (IsGrounded()) {
		if (OS::ActionMap::GetBooleanPressed("PlayerJump")) {
			physbox_handle->YSpeed(20.0f);
		}

		physbox_handle->XSpeed((OS::ActionMap::GetRangedValue("PlayerMovement") - 0.5f)*20.0f);
	}
}

void Player::DrawEvent(void) {

	// Player sprite group animations.

	const float sprite_core_animation_factor = 2.0f;
	const float sprite_rings_animation_factor = 8.0f;
	const float sprite_hat_animation_factor = 2.0f;

	float player_x = X();
	float player_y = Y();
	float player_angle = Angle();

	float target_sprite_core_x = player_x;
	float target_sprite_core_y = player_y;
	float target_sprite_core_angle = rings_angle_speed * 2.0f;

	float target_hat_x = player_x - 0.1f;
	float target_hat_y = player_y + 0.2f;
	float target_hat_angle = rings_angle_speed * 2.0f;

	float target_rings_x = player_x;
	float target_rings_y = player_y;
	float target_rings_angle_speed = -physbox_handle->XSpeed();

	AnimateValue(&rings_angle_speed, target_rings_angle_speed, sprite_rings_animation_factor);

	AnimateValue(&sprite_core_x, target_sprite_core_x, sprite_core_animation_factor);
	AnimateValue(&sprite_core_y, target_sprite_core_y, sprite_core_animation_factor);
	AnimateValue(&sprite_core_angle, target_sprite_core_angle, sprite_core_animation_factor);

	AnimateValue(&sprite_hat_x, target_hat_x, sprite_hat_animation_factor);
	AnimateValue(&sprite_hat_y, target_hat_y, sprite_hat_animation_factor);
	AnimateValue(&sprite_hat_angle, target_hat_angle, sprite_hat_animation_factor);

	AnimateValue(&sprite_rings_x, target_rings_x, sprite_core_animation_factor);
	AnimateValue(&sprite_rings_y, target_rings_y, sprite_core_animation_factor);

	sprite_rings_angle += rings_angle_speed;

	// End player sprite group animations.

	// Now, we change the animated sprites to exhibit our new values.

	sprite_core_handle->x = sprite_core_x;
	sprite_core_handle->y = sprite_core_y;
	sprite_core_handle->rotation = sprite_core_angle;

	sprite_hat_handle->x = sprite_hat_x;
	sprite_hat_handle->y = sprite_hat_y;
	sprite_hat_handle->z = -0.1f;
	sprite_hat_handle->rotation = sprite_hat_angle;

	sprite_rings_handle->x = sprite_rings_x;
	sprite_rings_handle->y = sprite_rings_y;
	sprite_rings_handle->z = 0.1f;
	sprite_rings_handle->rotation = sprite_rings_angle;
}

bool Player::IsGrounded(void) {

	// Player grounding check algorithm.
	// Uses contact point checking against bottom line of player.

	SetGrounded(false);

	physbox_handle->GetPhysObject()->GetAllCollisions([=](std::vector <std::pair<float, float>> contact_points) -> bool {

		// Called for every contact.

		// We check to see that the contact would be a plausible jumping surface.

		if (contact_points.size() >= 2) {
			if (contact_points[0].first = contact_points[1].first && contact_points[0].second != contact_points[1].second) {
				// Vertical surfaces.
				return true;
			}

			if (abs((contact_points[0].second - contact_points[1].second) / (contact_points[0].second - contact_points[1].second)) > 2.0f) {
				// Heavily angled surfaces.
				return true;
			}
		}

		for (auto i : contact_points) {
			float contact_x = i.first;
			float contact_y = i.second;

			// We now determine whether the point is on the lower player line.

			float player_bottom_left_x = cos(this->Angle() * (D3DX_PI / 180.0f) - (3.0f * D3DX_PI) / 4.0f) * sqrt(2.0f) + this->X();
			float player_bottom_right_x = cos(this->Angle() * (D3DX_PI / 180.0f) - D3DX_PI / 4.0f) * sqrt(2.0f) + this->X();
			float player_bottom_left_y = sin(this->Angle() * (D3DX_PI / 180.0f) - (3.0f * D3DX_PI) / 4.0f) * sqrt(2.0f) + this->Y();
			float player_bottom_right_y = sin(this->Angle() * (D3DX_PI / 180.0f) - D3DX_PI / 4.0f) * sqrt(2.0f) + this->Y();

			bool right_is_larger = player_bottom_right_x > player_bottom_left_x;

			float point_slope, line_slope;

			if (player_bottom_right_x == player_bottom_left_x) {
				// To avoid dividing by zero, we take a detour.

				if (contact_x == player_bottom_right_x) {
					this->SetGrounded(true);
					return false;
				}
			}

			if (right_is_larger) {
				line_slope = (player_bottom_right_y - player_bottom_left_y) / (player_bottom_left_x - player_bottom_right_x);
				point_slope = (player_bottom_right_y - contact_y) / (player_bottom_right_x - contact_x);
			
			} else {
				line_slope = (player_bottom_left_y - player_bottom_right_y) / (player_bottom_right_x - player_bottom_left_x);
				point_slope = (player_bottom_left_y - contact_y) / (player_bottom_left_x - contact_x);
			}

			if (abs(round(line_slope * 10.0f) / 10.0f - round(point_slope * 10.0f) / 10.0f) < 1.0f && contact_y < this->Y()) {
				this->SetGrounded(true);
				return false;
			}
		}

	});

	return is_grounded;
}

void Player::DestroyEvent(void) {
	if (sprite_core_handle) delete sprite_core_handle;
	if (sprite_hat_handle) delete sprite_core_handle;
	if (sprite_rings_handle) delete sprite_core_handle;
	if (physbox_handle) delete physbox_handle;
}

void Player::SpecialEvent(void*) {
	
	initial_x = X();
	initial_y = Y();

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

float Player::Width(void) {
	return 1.0f; // These should never change.
}

float Player::Height(void) {
	return 1.0f;
}

void Player::SetGrounded(bool grounded) {
	this->is_grounded = grounded;
}