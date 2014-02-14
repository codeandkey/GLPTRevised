#pragma once

/*

	Shader list [query with RenderController::GetShader("ShaderName");]

	'WorldShaderDefault' : Default world rendering shader. No special effects, has texture wrapping.
	'WorldShaderNoWrap' : Same as world rendering shader, except with no wrapping.
	'PostShaderBloom' : Applies a bloom to the texture it is passed.

*/

#include <neptune/Neptune.h>

namespace Tasks {
	class RenderController : public Neptune::Kernel::Task , public Neptune::Singleton::Singleton<RenderController> {
	public:
		RenderController(bool enable_debug_overlay=false);

		void EnableDebugOverlay(bool enable=true);

		void TaskStep(void);
		void TaskEnd(void);

		int GetFPS(void);

		Neptune::Graphics::Shader<>* GetShader(std::string target_shader_name);

	private:
		void RenderThroughPipeline(void);

		Neptune::Resource::Texture* render_target_texture_01;
		Neptune::Resource::Texture* render_target_texture_02;

		Neptune::Resource::Primitive<>* screen_primitive;

		std::map<std::string,Neptune::Graphics::Shader<>*> shader_map;

		bool debug_overlay;
		int fps_value;
		int fps_counter;
		Neptune::OS::Timer::Stamp fps_timestamp;
	};
}