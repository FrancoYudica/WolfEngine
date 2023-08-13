#ifndef __IMAGE_WRITE_TEST_H__
#define __IMAGE_WRITE_TEST_H__

#include "WEngine.h"
#include <imgui/imgui.h>


namespace Tests
{	
	namespace Assets
	{
		using namespace Wolf;
		class ImageWriteTest : public Layer
		{
			private:
				Wolf::Rendering::Camera _camera;
				Shared<Rendering::BitMap<RGBA8_UI>> bitmap;
			public:
				void on_start()
				{
					/*
					bitmap = std::make_shared<Rendering::BitMap<RGBA8_UI>>(4, 4);
					bitmap->set_pixel({0, 0}, {1, 1, 1, 1});
					bitmap->set_pixel({1, 0}, {0, 1, 0, 1});
					bitmap->set_pixel({2, 0}, {0, 0, 1, 1});
					bitmap->set_pixel({3, 0}, {0, 1, 1, 1});
					bitmap->set_pixel({0, 1}, {1, 1, 1, 1});
					*/
					bitmap = std::make_shared<Rendering::BitMap<RGBA8_UI>>(1, 1);
					bitmap->set_pixel({0, 0}, {1, 0, 1, 1});
					//bool success = Wolf::Assets::Writer::write_bitmap_jpg("write_test.jpg", bitmap, 10);
					bool success = Wolf::Assets::Writer::write_bitmap_png("write_test.png", bitmap);
					std::cout << "Write success: " << success << std::endl;
				}

				void on_ui_render_start()
				{
					ImGui::Begin("Test");
					ImGui::End();
				}
		};
	}
}
#endif