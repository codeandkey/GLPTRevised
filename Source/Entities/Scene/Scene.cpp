#include "Scene.h"

#include "../Player/Player.h"

#include "../../Tasks/TaskModule.h"

using namespace Neptune;
using namespace Entities;

Scene::Scene(SceneMode target_mode) {
	current_mode = target_mode;

	cloud_sprite_handle = new Actions::AnimatedSprite(Tasks::RenderController::Handle()->GetShader("WorldShaderScene"), "Assets/Animations/scene.ani", "CloudLarge", 50.0f, 50.0f, 1.0f, 1.0f);
	cloud_2_sprite_handle = new Actions::AnimatedSprite(Tasks::RenderController::Handle()->GetShader("WorldShaderScene"), "Assets/Animations/scene.ani", "CloudLarge", 50.0f, 50.0f, 1.0f, 1.0f);
	background_star_handle = new Actions::AnimatedSprite(Tasks::RenderController::Handle()->GetShader("WorldShader"), "Assets/Animations/scene.ani", "BackgroundStar", 70.0f, 40.0f, 1.0f, 1.0f);

	cloud_sprite_handle->z = 25.0f;
	cloud_2_sprite_handle->z = 20.0f;
	background_star_handle->z = 30.0f;

	Depth(10);

	AppendActionEvents(background_star_handle);
	AppendActionEvents(cloud_sprite_handle);
	AppendActionEvents(cloud_2_sprite_handle);

	switch (target_mode) {
	case SceneDarkCloudy:
		Tasks::RenderController::Handle()->GetShader("WorldShaderScene")->SetBoolVariable("darkness_enabled", true);

		background_sound_handle = new Audio::Sound("Assets/Sound/Music/game_background_01.mp3", true);
		background_sound_handle->Loop(true);
		background_sound_handle->Play();

		break;
	}
}

void Scene::InitEvent(void) {

}

void Scene::StepEvent(void) {

	Entities::Player* player_object = (Entities::Player*) ECS::Manager::Handle()->GetEntityFromIdentity("Player");

	// const float cloud_1_speed = 0.005f;
	// const float cloud_2_speed = 0.01f;

	// cloud_sprite_handle->x += cloud_1_speed;
	// cloud_2_sprite_handle->x += cloud_2_speed;

	background_star_handle->rotation += 0.0001f;
	background_star_handle->x = player_object->X();
	background_star_handle->y = player_object->Y();

	if (cloud_sprite_handle->x >= 50.0f) {
		cloud_sprite_handle->x = 0.0f;
	}

	if (cloud_2_sprite_handle->x >= 50.0f) {
		cloud_2_sprite_handle->x = 0.0f;
	}

}

void Scene::DrawEvent(void) {

	

}

