
#include "BatchRendererTest.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>

namespace Wolf
{
	namespace SandboxLayers
	{


		void BatchLayer::on_start()
		{
			Rendering::Renderer2D::init();

			Window* window = Application::get()->get_main_window();
			_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
			_key_states[KeyCode::KEY_W] = false;
			_key_states[KeyCode::KEY_D] = false;
			_key_states[KeyCode::KEY_S] = false;
			_key_states[KeyCode::KEY_A] = false;
			_points.reserve(10000);

			for (uint32_t i = 0; i < 10000; i++)
			{
				float x = Wolf::Numerical::Random::range_f(-2, 2);
				float y = Wolf::Numerical::Random::range_f(-2, 2);
				_points.emplace_back(glm::vec3(x, y, 0));
			}
			std::cout << "Layer started" << std::endl;
		}

		void BatchLayer::on_event(Event* event)
		{
			EventDispatcher dispatcher(event);
			dispatcher.dispatch<WindowResizeEvent>(
				EventType::WindowResize,
				[this](WindowResizeEvent* resize_event){
					_camera.on_viewport_resize(resize_event->width, resize_event->height);
					std::cout << "Window resized: " << resize_event->width << ", " << resize_event->height << std::endl;
					return false;
				}
			);

			dispatcher.dispatch<KeyDownEvent>(
				EventType::KeyDown,
				[this](KeyDownEvent* key_event){
					_key_states[key_event->key] = true;
					std::cout << "Key: " << key_event->key << std::endl;
					return false;
				}
			);
			dispatcher.dispatch<KeyUpEvent>(
				EventType::KeyUp,
				[this](KeyUpEvent* key_event){
					_key_states[key_event->key] = false;
					return false;
				}
			);

			dispatcher.dispatch<MouseScrollEvent>(
				EventType::MouseScroll,
				[this](MouseScrollEvent* scroll)
				{
					float zoom_ratio = 0.25f;

					float zoom = _camera.get_zoom();
					float offset = _camera.get_zoom() * zoom_ratio * scroll->y_offset;
					_camera.set_zoom(zoom + offset);
					return false;
				}
			);
		}

		void BatchLayer::on_update(const Time& delta)
		{
			
			// Updates camera translation
			float speed = 2.0f * delta.seconds() / _camera.get_zoom();
			glm::vec3 direction(0);
			if (_key_states[KeyCode::KEY_W])
				direction += glm::vec3(0, 1, 0);

			if (_key_states[KeyCode::KEY_S])
				direction += glm::vec3(0, -1, 0);

			if (_key_states[KeyCode::KEY_D])
				direction += glm::vec3(1, 0, 0);

			if (_key_states[KeyCode::KEY_A])
				direction += glm::vec3(-1, 0, 0);

			_camera.set_position(_camera.get_position() + direction * speed);
		}

		void BatchLayer::on_ui_render_start()
		{
			ImGui::Begin("Status");
			float render_time = Application::get()->get_render_time().seconds();
			float update_time = Application::get()->get_update_time().seconds();
			ImGui::Text(("Render time: " + std::to_string(render_time)).c_str());
			ImGui::Text(("Update time: " + std::to_string(update_time)).c_str());
			ImGui::End();
		}
		void BatchLayer::on_ui_render_finish()
		{
		}
		void BatchLayer::on_end()
		{
		}
		void BatchLayer::on_render()
		{
			Rendering::Renderer2D::begin_scene(_camera);
			Rendering::Renderer2D::new_frame();

			auto size = glm::vec3(0.01f);
			auto color = glm::vec4(1.0f);

			for (glm::vec3& point : _points)
			{
				Rendering::Renderer2D::submit_quad(point, size, color);
			}

			Rendering::Renderer2D::end_frame();
		}
	}
}

