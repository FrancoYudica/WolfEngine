#pragma once
#ifndef SPRITE_BATCH_TEST_H
#define SPRITE_BATCH_TEST_H

#include "WEngine.h"
#include <unordered_map>
#include <vector>
#include <imgui/imgui.h>


namespace Tests
{	
	namespace Renderer
	{
		using namespace Wolf;
		class SpriteRendering : public Layer
		{
			private:
				Wolf::Rendering::Camera _camera;
				std::vector<Shared<Wolf::Rendering::Texture>> _textures;
				uint32_t rows_columns;

			public:
				void on_start()
				{
					Rendering::Renderer2D::init();
					Wolf::Unique<Window>& window = Application::get()->get_main_window();
					_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);

					Wolf::Rendering::TextureConfig config;
					config.pixel_type = Wolf::Rendering::TextureTypes::FLOAT;

					// Creates textures
					for (uint32_t i = 0; i < 70; i++)
					{
						Shared<Rendering::BitMap<glm::vec4>> bitmap = std::make_shared<Rendering::BitMap<glm::vec4>>(1, 1);
						bitmap->set_pixel({0, 0}, glm::vec4(
							Wolf::Numerical::Random::unit_f(),
							Wolf::Numerical::Random::unit_f(),
							Wolf::Numerical::Random::unit_f(), 
							1));
						auto texture = Wolf::Rendering::Texture::from_bitmap(bitmap, config);
						_textures.push_back(texture);
					}
					rows_columns = 200;
				}

				void on_event(const Unique<Event>& event)
				{
					EventDispatcher dispatcher(event);
					dispatcher.dispatch<WindowResizeEvent>(
						EventType::WindowResize,
						[this](const Unique<WindowResizeEvent>& resize_event){
							_camera.on_viewport_resize(resize_event->width, resize_event->height);
							return false;
						}
					);

					dispatcher.dispatch<MouseScrollEvent>(
						EventType::MouseScroll,
						[this](const Unique<MouseScrollEvent>& scroll)
						{
							float zoom_ratio = 0.25f;

							float zoom = _camera.get_zoom();
							float offset = _camera.get_zoom() * zoom_ratio * scroll->y_offset;
							_camera.set_zoom(zoom + offset);
							return false;
						}
					);
				}

				void on_ui_render_start()
				{
					ImGui::Begin("Test");
					ImGui::Text((std::string("- Rendering: ") + std::to_string(rows_columns * rows_columns) + std::string(" quads")).c_str());
					ImGui::Text((std::string("There are a total of ") + std::to_string(_textures.size()) + std::string(" textures")).c_str());
					ImGui::End();
				}

				void on_update(const Time& delta)
				{
					
					// Updates camera translation
					float speed = 2.0f * delta.seconds() / _camera.get_zoom();
					glm::vec3 direction(0);
					direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_W) * glm::vec3(0, 1, 0);
					direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_S) * glm::vec3(0, -1, 0);
					direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_D) * glm::vec3(1, 0, 0);
					direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_A) * glm::vec3(-1, 0, 0);

					_camera.set_position(_camera.get_position() + direction * speed);
				}
				void on_render()
				{
					

					// Renders objects
					Rendering::Renderer2D::begin_scene(_camera);
					Rendering::Renderer2D::new_frame();
					
					for (uint32_t x = 0; x < rows_columns; x++)
					{
						for (uint32_t y = 0; y < rows_columns; y++)
						{
							Wolf::Rendering::Renderer2D::submit_quad(
								glm::vec3(x, y, 0) - glm::vec3(rows_columns * 0.5, rows_columns * 0.5, 0.0), 
								glm::vec3(0.5f), 
								glm::vec4(1.0f), 
								_textures[(static_cast<uint8_t>(Wolf::Time::current().seconds() * 10 + x) * y + 3 * y) % _textures.size()]
								);
						}
					}
					Rendering::Renderer2D::end_frame();

				}
		};
	}
}
#endif