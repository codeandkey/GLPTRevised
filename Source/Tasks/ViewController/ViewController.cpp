#include "ViewController.h"

#include "../../Entities/Player/Player.h"

using namespace Tasks;
using namespace Neptune;

ViewController::ViewController(void) : Kernel::Task("_ViewController") {
	
	camera_x = 0.0f;
	camera_y = 0.0f;
	camera_z = -10.0f;
	camera_look_x = 0.0f;
	camera_look_y = 0.0f;
	camera_look_z = 0.0f;

	target_camera_x = 0.0f;
	target_camera_y = 0.0f;
	target_camera_z = -12.0f;
	target_camera_look_x = 0.0f;
	target_camera_look_y = 0.0f;
	target_camera_look_z = 0.0f;

	camera_look_animation_factor = 5.0f;
	camera_position_animation_factor = 16.0f;

	Graphics::Camera::Handle()->SetFOV(60.0f * D3DX_PI / 180.0f);
	Graphics::Camera::Handle()->SetPosition(camera_x, camera_y, camera_z);
	Graphics::Camera::Handle()->SetTarget(camera_look_x, camera_look_y, camera_look_z);
}

void ViewController::TaskStep(void) {

	Entities::Player* target_player_object = (Entities::Player*) ECS::Manager::Handle()->GetEntityFromIdentity("Player");

	// Camera animation target assignments.

	if (target_player_object) {

		target_camera_x = target_player_object->X();
		target_camera_y = target_player_object->Y();
		target_camera_z = -12.0f;

		target_camera_look_x = target_player_object->X();
		target_camera_look_y = target_player_object->Y();
		target_camera_look_z = 0.0f;
	}

	// Camera animation calculations.

	camera_x = (target_camera_x - camera_x) / camera_position_animation_factor + camera_x;
	camera_y = (target_camera_y - camera_y) / camera_position_animation_factor + camera_y;
	camera_z = (target_camera_z - camera_z) / camera_position_animation_factor + camera_z;
	camera_look_x = (target_camera_look_x - camera_look_x) / camera_look_animation_factor + camera_look_x;
	camera_look_y = (target_camera_look_y - camera_look_y) / camera_look_animation_factor + camera_look_y;
	camera_look_z = (target_camera_look_z - camera_look_z) / camera_look_animation_factor + camera_look_z;

	Graphics::Camera::Handle()->SetPosition(camera_x, camera_y, camera_z);
	Graphics::Camera::Handle()->SetTarget(camera_look_x, camera_look_y, camera_look_z);
}