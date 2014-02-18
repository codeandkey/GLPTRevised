#include "GLPT.h"

using namespace Neptune;

int main(void) {

	OS::WindowDescription glpt_window_desc;

	new Logging::GeneralLogger(true);
	Logging::GeneralLogger::Handle()->SetWarningsEnabled(true);
	Logging::GeneralLogger::Handle()->Log(Logging::LOG_USER,"Starting GLPT game..");

	// Configuration settings.

	new File::Config("Config/GLPT_graphics.cfg");

	if (File::Config::Handle()->GetConfigValue<std::string>("WindowFullscreen") == "True") {
		glpt_window_desc.fullscreen=true;
	} else {
		glpt_window_desc.fullscreen=false;
	}

	int rec_window_width,rec_window_height;

	File::Config::Handle()->GetConfigValue<int>("WindowWidth",&rec_window_width);
	File::Config::Handle()->GetConfigValue<int>("WindowHeight",&rec_window_height);

	if (rec_window_width) glpt_window_desc.width = rec_window_width;
	if (rec_window_height) glpt_window_desc.height = rec_window_height;

	if (File::Config::Handle()->GetConfigValue<std::string>("[OverrideNativeResolution]") == "True") {
		glpt_window_desc.NativeResolution();
	}

	if (File::Config::Handle()->GetConfigValue<std::string>("WindowVerticalSync") == "True") {
		glpt_window_desc.vertical_sync=true;
	} else {
		glpt_window_desc.vertical_sync=false;
	}

	if (File::Config::Handle()->GetConfigValue<std::string>("WindowedHasBorder") == "True") {
		glpt_window_desc.border=true;
	} else {
		glpt_window_desc.border=false;
	}

	File::Config::Release();

	// End GLPT configuration.

	new ECS::Manager;

	new Kernel::Processor;

	new OS::Window(glpt_window_desc, "GLPTRevised");
	new OS::Input;
	new OS::Timer;

	new Audio::AudioManager;

	new Graphics::Device(false);
	new Graphics::Screen;

	new Graphics::Camera;
	new Graphics::Camera2D;
	new Graphics::Text;

	new Tasks::GameController;
	new Tasks::RenderController;
	new Tasks::PhysicsController;
	new Tasks::LogicController;
	new Tasks::ViewController;

	Misc::ControlBind::LoadKeybinds();
	Misc::ControlBind::ReloadControlsFromFile();

	Tasks::GameController::Handle()->BindEntity<Entities::Player>("ent_player");
	Tasks::GameController::Handle()->BindEntity<Entities::Brush>("ent_brush");

	Tasks::GameController::Handle()->LoadDefaultMap();

	ECS::Manager::Handle()->Push(new Entities::Scene(Entities::Scene::SceneDarkCloudy));

	Kernel::Processor::Handle()->StartTaskLoop();

	Kernel::Processor::Release();
	OS::Window::Release();
	OS::Timer::Release();
	OS::Input::Release();
	Audio::AudioManager::Release();
	Graphics::Screen::Release();
	Graphics::Device::Release();
	Graphics::Text::Release();
	Graphics::Camera::Release();
	Graphics::Camera2D::Release();
	Tasks::RenderController::Release();
	Tasks::GameController::Release();
	ECS::Manager::Release();
	Logging::GeneralLogger::Release();

	return 0;
}