#ifndef __WOLF_TEST_IMAGE_WRITE__
#define __WOLF_TEST_IMAGE_WRITE__

#include "WEngine.h"
#include <imgui/imgui.h>

namespace Tests {
namespace Assets {
    using namespace Wolf;
    class BitmapSaveTest : public Layer {
    private:
        Wolf::Rendering::Camera _camera;
        Shared<Rendering::BitMap<RGBA8_UI>> bitmap;

    public:
        void on_start()
        {
            uint32_t size = 100;
            bitmap = std::make_shared<Rendering::BitMap<RGBA8_UI>>(size, size);

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    bitmap->set_pixel({ i, j }, { i, j, std::abs(i - j) % 256, 255 });
                }
            }
        }

        void on_ui_render_start()
        {
            static bool success = false;
            static bool written = false;
            ImGui::Begin("Test");

            if (ImGui::Button("Save images")) {
                written = true;
                bool success_jpg = Wolf::Assets::save_bitmap_jpg("./write_test.jpg", bitmap, 100);
                bool success_png = Wolf::Assets::save_bitmap_png("./write_test.png", bitmap);
                success = success_jpg & success_png;
            }
            if (written) {
                if (success) {
                    ImGui::Text("Write success");
                } else {
                    ImGui::Text("Write failure");
                }
            }
            ImGui::End();
        }
    };
}
}
#endif