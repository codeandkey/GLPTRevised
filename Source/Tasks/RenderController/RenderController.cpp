#include "RenderController.h"

using namespace Neptune;
using namespace Tasks;

RenderController::RenderController(bool debug_enabled) : Kernel::Task("_RenderController") , debug_overlay(debug_enabled) {

	shader_map["WorldShaderDefault"] = new Graphics::Shader<>("Assets/Shaders/world_shader.hlsl","neptune_transform","neptune_texture");

	if (OS::Timer::Exists()) {
		fps_timestamp = OS::Timer::Handle()->GetStamp();
	}

	fps_value=0;
	fps_counter = 0;
}

void RenderController::TaskStep(void) {
	// Use overlay toggle control.

	if (OS::ActionMap::GetBooleanPressed("ToggleDebugOverlay")) {
		debug_overlay = !debug_overlay;
	}

	// Calculate FPS.

	if (!OS::Timer::Exists()) {
		fps_value=0;
	} else {
		fps_counter++;

		if (OS::Timer::Handle()->GetMS(fps_timestamp) >= 1000.0f) {
			fps_value=fps_counter;
			fps_timestamp = OS::Timer::Handle()->GetStamp();
			fps_counter=0;
		}
	}

	if (Graphics::Device::Exists() && Graphics::Screen::Exists()) {
		Graphics::Screen::Handle()->ClearScreen(0.0f,0.3f,0.8f,0.0f);
	} else {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_USER | Logging::LOG_APP,"[Tasks::RenderController] Detected that graphics device or screen is missing. Cannot proceed.");
		return;
	}

	if (ECS::Manager::Exists()) {
		ECS::Manager::Handle()->CallVirtualEvent(&Neptune::ECS::Entity::EDraw);
	} else {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_USER | Logging::LOG_APP | Logging::LOG_WARNING,"[Tasks::RenderController] No Object::Manager exists! No entities will draw.");
	}

	if (debug_overlay) {
		Graphics::Text::Handle()->SetTextFormat(0.0f,0.0f,0.0f,0.7f,"Small Fonts",20.0f,true);

		Graphics::Text::Handle()->DrawString("[GLPT debug overlay]",10.0f,10.0f);
		Graphics::Text::Handle()->DrawString(Conversion::String::Format("FPS : {}",GetFPS()),10.0f,30.0f);
	}

	Graphics::Screen::Handle()->PresentScreen();
}

void RenderController::TaskEnd(void) {

	if (Graphics::Device::Exists()) {
		Graphics::Device::Release();
	}

	if (Graphics::Screen::Exists()) {
		Graphics::Screen::Release();
	}

	if (Graphics::Camera::Exists()) {
		Graphics::Camera::Release();
	}

	if (Graphics::Camera2D::Exists()) {
		Graphics::Camera2D::Release();
	}

}

Graphics::Shader<>* RenderController::GetShader(std::string name) {
	Graphics::Shader<>* target_shader=NULL;

	try {
		target_shader=shader_map.at(name);
	} catch(std::out_of_range) {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_APP | Logging::LOG_USER,"[RenderController] Shader index of unknown name attempted. [" + name + "]");
	}

	return target_shader;
}

int RenderController::GetFPS(void) {
	return fps_value;
}