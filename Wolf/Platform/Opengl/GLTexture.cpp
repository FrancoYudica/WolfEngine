#include "GLTexture.h"
#include <glad/glad.h>


namespace Wolf
{
    namespace Rendering
    {

        namespace GL
        {
            struct GLTextureConfig
            {
                // OpenGL types equivalent to Wolf::Rendering::TextureConfig
                GLenum target;
                GLint pixel_format, internal_pixel_format;
                GLenum pixel_type;

                // Texture parameters
                GLint wrap_mode;
                GLint mag_filter, min_filter;
                GLuint samples;
            };

            static GLint parse_gl(TextureTypes::WrapMode mode)
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

            static GLint parse_gl(TextureTypes::Filter filter)
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

            static GLint parse_gl(TextureTypes::PixelFormat format)
            {
                switch (format)
                {
                    case TextureTypes::PixelFormat::R:
                        return GL_RED;
                        break;

                    case TextureTypes::PixelFormat::RG:
                        return GL_RG;
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

            static GLint parse_gl(TextureTypes::PixelType pixel_type)
            {
                switch (pixel_type)
                {
                    case TextureTypes::PixelType::UnsignedByte:
                        return GL_UNSIGNED_BYTE;
                        break;

                    case TextureTypes::PixelType::Byte:
                        return GL_BYTE;
                        break;

                    case TextureTypes::PixelType::Float:
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
                gl_config.wrap_mode = parse_gl(config.wrap_mode);
                gl_config.mag_filter = parse_gl(config.mag_filter);
                gl_config.min_filter = parse_gl(config.min_filter);
                gl_config.pixel_format = parse_gl(config.pixel_format);
                gl_config.internal_pixel_format = parse_gl(config.internal_pixel_format);
                gl_config.pixel_type = parse_gl(config.pixel_type);
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
            glBindTexture(_target, _renderer_id);
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


        Shared<Texture> Texture::initialize_from_bitmap(const Shared<BitMap>& bitmap, const TextureConfig& config)
        {

            Shared<GL::GLTexture> texture = std::make_shared<GL::GLTexture>();
            glGenTextures(1, &texture->_renderer_id);

            GL::GLTextureConfig gl_config = GL::parse_gl(config);

            // Changes target if multi sampled
            bool multi_sampled = gl_config.samples > 1;
            texture->_target = multi_sampled ? GL_TEXTURE_2D_MULTISAMPLE_ARRAY : GL_TEXTURE_2D;
            // Texture setup
            glBindTexture(texture->_target, texture->_renderer_id);

            glTexParameteri(texture->_target, GL_TEXTURE_WRAP_S, gl_config.wrap_mode);
            glTexParameteri(texture->_target, GL_TEXTURE_WRAP_T, gl_config.wrap_mode);
            glTexParameteri(texture->_target, GL_TEXTURE_WRAP_R, gl_config.wrap_mode);
            glTexParameteri(texture->_target, GL_TEXTURE_MAG_FILTER, gl_config.mag_filter);
            glTexParameteri(texture->_target, GL_TEXTURE_MIN_FILTER, gl_config.min_filter);

            if (multi_sampled)
            {
                glTexImage2DMultisample(
                    texture->_target,
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
                    texture->_target,
                    0,
                    gl_config.internal_pixel_format,
                    bitmap->width,
                    bitmap->height,
                    0,
                    gl_config.pixel_format,
                    gl_config.pixel_type,
                    bitmap->get_buffer().data()
                );
            }

            return texture;
        }
    }
}