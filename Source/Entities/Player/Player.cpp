#include "Player.h"

#include "../../Tasks/RenderController/RenderController.h"

using namespace Neptune;
using namespace Entities;

void Player::InitEvent(void) {
	animation_sprite_handle = new Actions::AnimatedSprite(Tasks::RenderController::Handle()->GetShader("WorldShader"));

	physbox_handle = new Actions::PhysBox();

	lower_sensor = new Actions::PhysSensor(0.5f,2.1f);

	AppendActionEvents(physbox_handle);
	AppendActionEvents(lower_sensor);
	AppendActionEvents(animation_sprite_handle);

	Identity("Player");
}

void Player::StepEvent(void) {
	
	// physbox_handle->Angle(0.0f);

	if (IsGrounded()) {
		if (OS::ActionMap::GetBooleanPressed("PlayerJump")) {
			physbox_handle->YSpeed(20.0f);
		}

		physbox_handle->XSpeed((OS::ActionMap::GetRangedValue("PlayerMovement") - 0.5f)*20.0f);
	}
}

void Player::DrawEvent(void) {
	// Synchronize the animation with the physbox.

	animation_sprite_handle->x = physbox_handle->X();
	animation_sprite_handle->y = physbox_handle->Y();
	animation_sprite_handle->z=0.0f;
	animation_sprite_handle->rotation=physbox_handle->Angle();

	// Graphics::Text::Handle()->SetTextFormat(0.0f, 0.0f, 0.0f, 1.0f, "Small Fonts", 15.0f, false);

	// Graphics::Text::Handle()->DrawString(Conversion::String::Format("player X : {}", physbox_handle->X()), 10, 100);
	// Graphics::Text::Handle()->DrawString(Conversion::String::Format("player Y : {}", physbox_handle->Y()), 10, 130);
	// Graphics::Text::Handle()->DrawString(Conversion::String::Format("player grounded : {}", IsGrounded()), 10, 160);

	// Done synchronizing.
}

bool Player::IsGrounded(void) {

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

float Player::Width(void) {
	return 1.0f; // These should never change.
}

float Player::Height(void) {
	return 1.0f;
}

void Player::SetGrounded(bool grounded) {
	this->is_grounded = grounded;
}