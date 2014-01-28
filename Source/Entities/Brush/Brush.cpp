#include "Brush.h"
#include "../../Tasks/RenderController/RenderController.h"

using namespace Neptune;
using namespace Entities;

void Brush::InitEvent(void) {
	animation_handle = new Actions::AnimatedSprite("Assets/Animations/brush.ani",10.0f,1.0f);
	animation_handle->SetShader(Tasks::RenderController::Handle()->GetShader("WorldShaderDefault"));

	physbox_handle = new Actions::PhysBox(Actions::PhysBox::PhysBoxDesc(10.0f,1.0f,true));

	physbox_handle->Y(-3.0f);

	AppendActionEvents(animation_handle);
	AppendActionEvents(physbox_handle);
}

Brush::~Brush(void) {
	if (physbox_handle) delete physbox_handle;
	if (animation_handle) delete animation_handle;
}

void Brush::StepEvent(void) {
	animation_handle->x=physbox_handle->X();
	animation_handle->y=physbox_handle->Y();
	animation_handle->z=0.0f;
	animation_handle->rotation=physbox_handle->Angle();
}

void Brush::DrawEvent(void) {}