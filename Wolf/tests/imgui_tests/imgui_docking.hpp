#ifndef __IMGUI_DOCKING_TEST__
#define __IMGUI_DOCKING_TEST__

#include "WEngine.h"
#include <unordered_map>
#include <vector>
#include <imgui/imgui.h>


namespace Tests
{	
	namespace ImGuiTests
	{
		using namespace Wolf;
		class DockingTest : public Layer
		{
			private:
				Wolf::Rendering::Camera _camera;
				std::vector<Shared<Wolf::Rendering::Texture>> _textures;
				uint32_t rows_columns;

			public:
				void on_start(){}

				void on_event(const Unique<Event>& event){}

				void on_ui_render_start()
				{
					ImGui::Begin("Test");
                    ImGui::Text("Sample text");
					ImGui::End();

					ImGui::Begin("Test2");
                    ImGui::Text("Sample text2222");
					ImGui::End();

				}
		};
	}
}
#endif