#include "LogicController.h"

using namespace Neptune;
using namespace Tasks;

LogicController::LogicController(void) : Kernel::Task("_LogicController") {}

void LogicController::TaskStep(void) {
	// The logic controller does not do much yet..
	// It is still very necessary though.

	ECS::Manager::Handle()->CallVirtualEvent(&ECS::Entity::EStep);
}