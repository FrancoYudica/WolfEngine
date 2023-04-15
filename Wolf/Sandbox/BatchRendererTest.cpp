
#include "BatchRendererTest.h"
#include <glm/glm.hpp>

namespace Wolf
{
	namespace SandboxLayers
	{


		void BatchLayer::on_start()
		{
			Rendering::Renderer2D::init();
		}
		void BatchLayer::on_update(const Time& delta)
		{
		}
		void BatchLayer::on_event(const Event& event)
		{
		}
		void BatchLayer::on_ui_render_start()
		{
		}
		void BatchLayer::on_ui_render_finish()
		{
		}
		void BatchLayer::on_end()
		{
		}
		void BatchLayer::on_render()
		{

			Rendering::Renderer2D::new_frame();
			Rendering::Renderer2D::submit_quad(glm::vec3(0), glm::vec3(1), glm::vec4(1.0f, 0.6f, 0.3f, 1.0f));
			Rendering::Renderer2D::end_frame();


		}
	}
}

