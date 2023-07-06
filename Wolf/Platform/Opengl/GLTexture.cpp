#include "GLTexture.h"
#include <glad/glad.h>


namespace Wolf
{
    namespace Rendering
    {

        namespace GL
        {
            static int32_t parse_gl(TextureTypes::WrapMode mode)
            {
                switch (mode)
                {
                    case TextureTypes::WrapMode::REPEAT:
                        return GL_REPEAT;
                        break;
                    case TextureTypes::WrapMode::MIRRORED_REPEAT:
                        return GL_MIRRORED_REPEAT;
                        break;
                    case TextureTypes::WrapMode::CLAMP_TO_EDGE:
                        return GL_CLAMP_TO_EDGE;
                        break;
                    case TextureTypes::WrapMode::CLAMP_TO_BORDER:
                        return GL_CLAMP_TO_BORDER;
                        break;
                    default:
                        throw "Unimplemented 'WrapMode' GLTextureConfig type in parse_gl()";
                        break;
                }     
            }

            static int32_t parse_gl(TextureTypes::Filter filter)
            {
                switch (filter)
                {
                    case TextureTypes::Filter::LINEAR:
                        return GL_LINEAR;
                        break;

                    case TextureTypes::Filter::NEAREST:
                        return GL_NEAREST;
                        break;

                    default:
                        throw "Unimplemented 'Filter' GLTextureConfig type in parse_gl()";
                        break;                
                }        

            }

            static int32_t parse_gl(TextureTypes::PixelFormat format)
            {
                switch (format)
                {
                    case TextureTypes::PixelFormat::R:
                        return GL_RED;
                        break;

                    case TextureTypes::PixelFormat::RGB:
                        return GL_RGB;
                        break;

                    case TextureTypes::PixelFormat::RGBA:
                        return GL_RGBA;
                        break;

                    default:
                        throw "Unimplemented 'Pixel Format' GLTextureConfig type in parse_gl()";
                        break;                
                }        
            }

            static int32_t parse_gl(TextureTypes::PixelInternalFormat format)
            {
                switch (format)
                {
                    case TextureTypes::PixelInternalFormat::R_8:
                        return GL_RED;
                        break;
                    case TextureTypes::PixelInternalFormat::RGB_8:
                        return GL_RGB8;
                        break;

                    case TextureTypes::PixelInternalFormat::RGBA_8:
                        return GL_RGBA8;
                        break;

                    default:
                        throw "Unimplemented 'Pixel Format' GLTextureConfig type in parse_gl()";
                        break;                
                }        
            }

            static uint32_t parse_gl(TextureTypes::PixelType pixel_type)
            {
                switch (pixel_type)
                {
                    case TextureTypes::PixelType::UNSIGNED_BYTE:
                        return GL_UNSIGNED_BYTE;
                        break;

                    case TextureTypes::PixelType::BYTE:
                        return GL_BYTE;
                        break;

                    case TextureTypes::PixelType::FLOAT:
                        return GL_FLOAT;
                        break;
                    default:
                        throw "Unimplemented 'Pixel Type' GLTextureConfig type in parse_gl()";
                        break;                
                }        
            }

            static GLTextureConfig parse_gl(const TextureConfig& config)
            {
                GLTextureConfig gl_config;
                gl_config.wrap_mode =               parse_gl(config.wrap_mode);
                gl_config.mag_filter =              parse_gl(config.mag_filter);
                gl_config.min_filter =              parse_gl(config.min_filter);
                gl_config.pixel_format =            parse_gl(config.pixel_format);
                gl_config.internal_pixel_format =   parse_gl(config.internal_pixel_format);
                gl_config.pixel_type =              parse_gl(config.pixel_type);
                gl_config.samples = config.samples;
                return gl_config;
            }
        }

        GL::GLTexture::~GLTexture()
        {
            glDeleteTextures(1, &_renderer_id);
        }

        void GL::GLTexture::bind()
        {
            glBindTexture(target, _renderer_id);
        }

        void Texture::activate_texture(const Shared<Texture>& texture, uint8_t slot)
        {
#ifdef WOLF_DEBUG_MODE
            if (slot > GL_TEXTURE31)
            {
                throw "Texture::activate_texture OpenGL implementation. Slot greater than 31";
            }
#endif
            glActiveTexture(GL_TEXTURE0 + slot);
            texture->bind();
        }

        template<typename T>
        Shared<Texture> _initialize_from_bitmap_impl(const Shared<BitMap<T>>& bitmap, const TextureConfig& config)
        {
            
            uint32_t texture_renderer_id;
            glGenTextures(1, &texture_renderer_id);

            Shared<GL::GLTexture> texture = std::make_shared<GL::GLTexture>(texture_renderer_id);

            GL::GLTextureConfig gl_config = GL::parse_gl(config);

            // Changes target if multi sampled
            bool multi_sampled = gl_config.samples > 1;
            texture->target = multi_sampled ? GL_TEXTURE_2D_MULTISAMPLE_ARRAY : GL_TEXTURE_2D;
            // Texture setup
            glBindTexture(texture->target, texture->get_id());

            glTexParameteri(texture->target, GL_TEXTURE_WRAP_S, gl_config.wrap_mode);
            glTexParameteri(texture->target, GL_TEXTURE_WRAP_T, gl_config.wrap_mode);
            glTexParameteri(texture->target, GL_TEXTURE_WRAP_R, gl_config.wrap_mode);
            glTexParameteri(texture->target, GL_TEXTURE_MAG_FILTER, gl_config.mag_filter);
            glTexParameteri(texture->target, GL_TEXTURE_MIN_FILTER, gl_config.min_filter);

            // Set the unpack alignment parameter to 1
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            if (multi_sampled)
            {
                glTexImage2DMultisample(
                    texture->target,
                    gl_config.samples,
                    gl_config.internal_pixel_format,
                    bitmap->width,
                    bitmap->height,
                    GL_TRUE
                );
            }
            else
            {
                glTexImage2D(
                    texture->target,
                    0,
                    gl_config.internal_pixel_format,
                    bitmap->width,
                    bitmap->height,
                    0,
                    gl_config.pixel_format,
                    gl_config.pixel_type,
                    bitmap->buffer_raw_ptr()
                );
            }

            return texture;
        }

        Shared<Texture> Texture::from_bitmap(const Shared<BitMap<glm::u8vec3>>& bitmap, const TextureConfig& config)
        {
            return _initialize_from_bitmap_impl(bitmap, config);
        }

        Shared<Texture> Texture::from_bitmap(const Shared<BitMap<glm::u8vec4>>& bitmap, const TextureConfig& config)
        {
            return _initialize_from_bitmap_impl(bitmap, config);
        }

        Shared<Texture> Texture::from_bitmap(const Shared<BitMap<glm::vec4>>& bitmap, const TextureConfig& config)
        {
            return _initialize_from_bitmap_impl(bitmap, config);
        }
        Shared<Texture> Texture::from_bitmap(const Shared<BitMap<glm::vec3>>& bitmap, const TextureConfig& config)
        {
            return _initialize_from_bitmap_impl(bitmap, config);
        }

        Shared<Texture> Texture::from_bitmap(const Shared<BitMap<float>>& bitmap, const TextureConfig& config)
        {
            return _initialize_from_bitmap_impl(bitmap, config);
        }
    }
}