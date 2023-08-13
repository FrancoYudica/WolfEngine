#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "assets.h"
#include "stb_image.h"
#include "stb_image_write.h"


namespace Wolf
{
    namespace Assets
    {
        Shared<Rendering::BitMap<RGBA8_UI>> Loader::load_bitmap(
            const Wolf::Path& path,
            bool& success
        )
        {
            stbi_set_flip_vertically_on_load(true);

            int32_t width, height, num_components;
            uint8_t* buffer = stbi_load(path.c_str(), &width, &height, &num_components, 4);
            success = buffer != nullptr;
            if (!success)
            {
                const char* failure = stbi_failure_reason();
                std::cout << "Unable to load bitmap: <" << path.c_str() << "> Failure: "<< failure << std::endl;
                success = false;
            }

            auto bitmap = std::make_shared<Rendering::BitMap<RGBA8_UI>>(width, height);
            bitmap->copy_buffer((RGBA8_UI*)buffer);
            return bitmap;
        }

        bool Writer::write_bitmap_png(
            const Wolf::Path& path,
            const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap
        )
        {
            int success = stbi_write_png(
                path.c_str(),
                bitmap->width,
                bitmap->height,
                4, 
                bitmap->buffer_raw_ptr(),
                bitmap->width * sizeof(RGBA8_UI) // Stride is the length of each "row" in bytes
                );

            if (!success)
            {
                const char* failure = stbi_failure_reason();
                std::cout << "Unable to write png bitmap: <" << path.c_str() << "> Failure: "<< failure << std::endl;
            }

            return success;            
        }
        bool Writer::write_bitmap_jpg(
            const Wolf::Path& path,
            const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap,
            uint32_t quality
        )
        {

            int success = stbi_write_jpg(
                path.c_str(),
                bitmap->width,
                bitmap->height,
                4, 
                bitmap->buffer_raw_ptr(),
                quality
                );

            if (!success)
            {
                const char* failure = stbi_failure_reason();
                std::cout << "Unable to write jpg bitmap: <" << path.c_str() << "> Failure: "<< failure << std::endl;
            }

            return success;            

        }
    }
}