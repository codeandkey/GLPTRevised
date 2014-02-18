#include "GameController.h"
#include "../LogicController/LogicController.h"
#include "../RenderController/RenderController.h"
#include "../../Misc/ParamFetch.h"

#include <fstream>

using namespace Neptune;
using namespace Tasks;

GameController::GameController(void) : Kernel::Task("_GameController") {

	new File::Config("Config/GLPT_game.cfg");

	default_map_name = File::Config::Handle()->GetConfigValue<std::string>("DefaultMap");

	default_map_name = "Assets/Maps/" + default_map_name + ".cdm";

	File::Config::Release();

}

void GameController::TaskStep(void) {

	if (OS::Window::Handle()->CloseRequested() || OS::ActionMap::GetBooleanDown("QuitGame")) {
		Kernel::Processor::Handle()->StopTaskLoop();
	}

}

void GameController::LoadDefaultMap(void) {
	if (default_map_name.size()) {
		LoadMap(default_map_name);
	} else {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_USER | Logging::LOG_APP, "[GameController] Default map is not set!");
	}
}

void GameController::LoadMap(std::string filename) {

	ECS::Manager::Handle()->Flush();

	std::ifstream file;
	file.open(filename.c_str(),std::ios::in | std::ios::binary);

	if (!file) {
		Logging::GeneralLogger::Handle()->Log(Logging::LOG_APP | Logging::LOG_USER,"[GameController] Could not find map file. [" + filename + "]");
		return;
	}

	unsigned int entity_count;
	
	file.read(reinterpret_cast<char*>(&entity_count),sizeof(unsigned int));

	for(unsigned int i=0;i<entity_count;i++) {

		std::string type,identity;
		unsigned int type_size,identity_size,key_count,key_size,value_size;
		std::string key,value;
		std::map<std::string,std::string> pass_data;
		ECS::Entity* new_entity;

		file.read(reinterpret_cast<char*>(&type_size),sizeof(unsigned int));
		type.resize(type_size);
		file.read(&type[0],type_size);
		file.read(reinterpret_cast<char*>(&identity_size),sizeof(unsigned int));
		identity.resize(identity_size);
		file.read(&identity[0],identity_size);
		
		file.read(reinterpret_cast<char*>(&key_count),sizeof(unsigned int));

		for(unsigned int f=0;f<key_count;f++) {

			file.read(reinterpret_cast<char*>(&key_size),sizeof(unsigned int));
			key.resize(key_size);
			file.read(&key[0],key_size);
			file.read(reinterpret_cast<char*>(&value_size),sizeof(unsigned int));
			value.resize(value_size);
			file.read(&value[0],value_size);

			pass_data[key]=value;
		}

		try {
			entity_register_map.at(type);
		} catch(std::out_of_range) {
			Logging::GeneralLogger::Handle()->Log(Logging::LOG_APP | Logging::LOG_USER,"[GameController] Map contained unknown entity type. [" + type + "]");
			continue;
		}


		new_entity=entity_register_map[type]();

		ECS::Manager::Handle()->Push(new_entity);

		new_entity->ESpecial((void*) &pass_data);
	}

	file.close();
}