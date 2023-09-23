#ifndef __WOLF_SPRITE_ANIMATION__
#define __WOLF_SPRITE_ANIMATION__
#include "../core/Time.h"
#include "../core/wolf_types.h"
#include "../rendering/Texture.h"
#include "../numerical/Bounds.h"

namespace Wolf {
namespace Animation {

    enum class AnimationMode {
        Repeat,
        Once,
    };

    class SpriteAnimation {

    public:
        SpriteAnimation()
            : _elapsed(0.0f)
            , _frame_duration(0.25f)
            , _frames_count(0)
            , _current_frame_index(0)
            , _mode(AnimationMode::Repeat)
        {
        }

        void on_update(const Time& dt)
        {
            _elapsed += dt.seconds();

            uint32_t index = static_cast<int>(_elapsed / _frame_duration);
            switch (_mode) {
            case AnimationMode::Repeat:

                _current_frame_index = index % _frames_count;
                break;

            case AnimationMode::Once:

                if (ended())
                    _current_frame_index = _frames_count - 1;
                else
                    _current_frame_index = index % _frames_count;
                break;

            default:
                break;
            }
        }

        void restart()
        {
            _elapsed = 0.0f;
            _current_frame_index = 0;
        }

        /// @brief Tells if animation ended, only if AnimationMode is set to Once
        bool ended() { return _mode == AnimationMode::Once && static_cast<int>(_elapsed / _frame_duration) >= _frames_count; }

        inline void set_frame_duration(float duration) { _frame_duration = duration; }
        inline void set_frames_count(float count) { _frames_count = count; }
        inline void set_animation_mode(AnimationMode mode) { _mode = mode; }
        inline uint32_t get_frame_index() const { return _current_frame_index; }
        /// @return current frame texture
        virtual Shared<Rendering::Texture> get_texture() const = 0;

        /// @return texture coordinate bounds of current frame
        virtual Numerical::Bounds<glm::vec2> get_bounds() const = 0;

    protected:
        float _elapsed;
        float _frame_duration;
        uint32_t _frames_count;
        uint32_t _current_frame_index;
        AnimationMode _mode;
    };

    /// @brief Linear sprite sheet animator.
    class SpriteSheetAnimation : public SpriteAnimation {
    public:
        SpriteSheetAnimation()
            : _sheet(nullptr)
            , SpriteAnimation()

        {
        }

        SpriteSheetAnimation(Shared<Rendering::Texture>& sheet)
            : _sheet(sheet)
        {
        }

        inline void set_sheet(Shared<Rendering::Texture>& sheet) { _sheet = sheet; }

        /// @return current frame texture
        virtual Shared<Rendering::Texture> get_texture() const override
        {
            return _sheet;
        }
        /// @return texture coordinate bounds of current frame
        virtual Numerical::Bounds<glm::vec2> get_bounds() const override
        {
            float dx = 1.0f / static_cast<float>(_frames_count);

            Numerical::Bounds<glm::vec2> bounds;

            bounds.max.y = 1.0f;
            bounds.min.y = 0.0f;

            bounds.min.x = _current_frame_index * dx;
            bounds.max.x = (_current_frame_index + 1.0f) * dx;

            return bounds;
        }

    private:
        Shared<Rendering::Texture> _sheet;
    };

}
}

#endif