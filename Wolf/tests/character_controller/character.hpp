
/**
 * @brief State character controller.
 * The idea is to separate character behaviour into states
 * and each state can go to a fixed amount of states.
 * This way,
 * + implementing attack specific logic is easier
 * + no need to track for all animations and current animation
 * + no need to setup individual state
 * + no need to store multiple states, just one
 * - extensive code
 */

#ifndef __CHARACTER_TEST__
#define __CHARACTER_TEST__
#include "WEngine.h"
using namespace Wolf;
using namespace Wolf::Rendering;

class Character;

class CharacterState {
public:
    CharacterState(Character& character)
        : _character(character)
    {
    }

    virtual void on_enter() { }
    virtual void on_exit() { }
    virtual void on_update(const Time& dt) { }

protected:
    Character& _character;
};

class Character {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    float horizontal_speed;
    Shared<Animation::SpriteAnimation> animation;

public:
    Character()
        : position(0.0f)
        , velocity(0.0f)
        , horizontal_speed(0.5f)
    {
    }

    void set_animation(Shared<Animation::SpriteAnimation> new_anim)
    {
        animation = new_anim;
    }

    template <class T>
    void change_state()
    {
        if (_current_state)
            _current_state->on_exit();
        _current_state = std::make_unique<T>(*this);
        _current_state->on_enter();
    }

    void on_update(const Time& dt)
    {
        _current_state->on_update(dt);
    }

private:
    std::unique_ptr<CharacterState> _current_state;
};

class CharacterIdleState;
class CharacterWalkState;
class CharacterRunState;
class CharacterAttackState;
class CharacterPunchState;

class CharacterIdleState : public CharacterState {

public:
    CharacterIdleState(Character& character)
        : CharacterState(character)
    {
    }
    void on_enter() override
    {
        Path::FilePath anim_path = Path::get_engine_assets_folder();
        anim_path /= "tests/animated_character/Player Sword Idle 48x48.png";

        bool load_success = true;
        auto bitmap = Wolf::Assets::load_bitmap(anim_path, load_success);
        TextureConfig texture_config;
        texture_config.mag_filter = TextureTypes::Filter::NEAREST;
        Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
        // Animation setup
        _animation = std::make_shared<Animation::SpriteSheetAnimation>();
        _animation->set_sheet(sheet);
        _animation->set_frame_duration(0.1f);
        _animation->set_frames_count(bitmap->width / 48);

        _character.set_animation(_animation);
    }

    void on_exit() override
    {
    }
    void on_update(const Time& dt) override
    {
        _animation->on_update(dt);

        bool attacking = Wolf::Input::is_button_down(MouseButton::LEFT);
        if (attacking) {
            _character.change_state<CharacterAttackState>();
            return;
        }

        bool punching = Wolf::Input::is_button_down(MouseButton::RIGHT);
        if (punching) {
            _character.change_state<CharacterPunchState>();
            return;
        }

        bool moving = Wolf::Input::is_key_down(KeyCode::KEY_D) || Wolf::Input::is_key_down(KeyCode::KEY_A);
        if (moving) {
            _character.change_state<CharacterWalkState>();
        }
    }

private:
    Shared<Animation::SpriteSheetAnimation> _animation;
};

class CharacterWalkState : public CharacterState {

public:
    CharacterWalkState(Character& character)
        : CharacterState(character)
    {
    }
    void on_enter() override
    {
        Path::FilePath anim_path = Path::get_engine_assets_folder();
        anim_path /= "tests/animated_character/PlayerWalk 48x48.png";

        bool load_success = true;
        auto bitmap = Wolf::Assets::load_bitmap(anim_path, load_success);
        TextureConfig texture_config;
        texture_config.mag_filter = TextureTypes::Filter::NEAREST;
        Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
        // Animation setup
        _animation = std::make_shared<Animation::SpriteSheetAnimation>();
        _animation->set_sheet(sheet);
        _animation->set_frame_duration(0.1f);
        _animation->set_frames_count(bitmap->width / 48);

        _character.set_animation(_animation);
    }

    void on_exit() override
    {
    }
    void on_update(const Time& dt) override
    {
        _animation->on_update(dt);

        bool attacking = Wolf::Input::is_button_down(MouseButton::LEFT);
        if (attacking) {
            _character.change_state<CharacterAttackState>();
            return;
        }

        bool punching = Wolf::Input::is_button_down(MouseButton::RIGHT);
        if (punching) {
            _character.change_state<CharacterPunchState>();
            return;
        }

        bool moving = false;
        if (Input::is_key_down(KeyCode::KEY_D)) {
            _character.velocity.x = _character.horizontal_speed;
            moving = true;
        }
        if (Input::is_key_down(KeyCode::KEY_A)) {
            _character.velocity.x = -_character.horizontal_speed;
            moving = true;
        }

        _character.position += _character.velocity * static_cast<float>(dt.seconds());

        if (!moving) {
            _character.change_state<CharacterIdleState>();
            return;
        }

        if (moving && Input::is_key_down(KeyCode::KEY_LEFT_SHIFT))
            _character.change_state<CharacterRunState>();
    }

private:
    Shared<Animation::SpriteSheetAnimation> _animation;
};

class CharacterRunState : public CharacterState {

public:
    CharacterRunState(Character& character)
        : CharacterState(character)
    {
    }
    void on_enter() override
    {
        Path::FilePath anim_path = Path::get_engine_assets_folder();
        anim_path /= "tests/animated_character/Player Sword Run 48x48.png";

        bool load_success = true;
        auto bitmap = Wolf::Assets::load_bitmap(anim_path, load_success);
        TextureConfig texture_config;
        texture_config.mag_filter = TextureTypes::Filter::NEAREST;
        Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
        // Animation setup
        _animation = std::make_shared<Animation::SpriteSheetAnimation>();
        _animation->set_sheet(sheet);
        _animation->set_frame_duration(0.1f);
        _animation->set_frames_count(bitmap->width / 48);

        _character.set_animation(_animation);
    }

    void on_exit() override
    {
    }
    void on_update(const Time& dt) override
    {
        _animation->on_update(dt);

        bool attacking = Wolf::Input::is_button_down(MouseButton::LEFT);
        if (attacking) {
            _character.change_state<CharacterAttackState>();
            return;
        }

        bool punching = Wolf::Input::is_button_down(MouseButton::RIGHT);
        if (punching) {
            _character.change_state<CharacterPunchState>();
            return;
        }

        bool moving = false;
        bool running = Input::is_key_down(KeyCode::KEY_LEFT_SHIFT);
        if (running && Input::is_key_down(KeyCode::KEY_D)) {
            _character.velocity.x = _character.horizontal_speed;
            moving = true;
        }
        if (running && Input::is_key_down(KeyCode::KEY_A)) {
            _character.velocity.x = -_character.horizontal_speed;
            moving = true;
        }

        _character.position += 3.0f * _character.velocity * static_cast<float>(dt.seconds());

        if (!moving) {
            _character.change_state<CharacterIdleState>();
        }
    }

private:
    Shared<Animation::SpriteSheetAnimation> _animation;
};

class CharacterAttackState : public CharacterState {

public:
    CharacterAttackState(Character& character)
        : CharacterState(character)
    {
    }
    void on_enter() override
    {
        Path::FilePath anim_path = Path::get_engine_assets_folder();
        anim_path /= "tests/animated_character/Player sword atk 64x64.png";

        bool load_success = true;
        auto bitmap = Wolf::Assets::load_bitmap(anim_path, load_success);
        TextureConfig texture_config;
        texture_config.mag_filter = TextureTypes::Filter::NEAREST;
        Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
        // Animation setup
        _animation = std::make_shared<Animation::SpriteSheetAnimation>();
        _animation->set_sheet(sheet);
        _animation->set_frame_duration(0.1f);
        _animation->set_frames_count(bitmap->width / 64);
        _animation->set_animation_mode(Animation::AnimationMode::Once);
        _character.set_animation(_animation);
    }

    void on_exit() override
    {
    }
    void on_update(const Time& dt) override
    {
        _animation->on_update(dt);

        if (_animation->ended())
            _character.change_state<CharacterIdleState>();
    }

private:
    Shared<Animation::SpriteSheetAnimation> _animation;
};

class CharacterPunchState : public CharacterState {

public:
    CharacterPunchState(Character& character)
        : CharacterState(character)
    {
    }
    void on_enter() override
    {
        Path::FilePath anim_path = Path::get_engine_assets_folder();
        anim_path /= "tests/animated_character/Player Punch 64x64.png";

        bool load_success = true;
        auto bitmap = Wolf::Assets::load_bitmap(anim_path, load_success);
        TextureConfig texture_config;
        texture_config.mag_filter = TextureTypes::Filter::NEAREST;
        Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
        // Animation setup
        _animation = std::make_shared<Animation::SpriteSheetAnimation>();
        _animation->set_sheet(sheet);
        _animation->set_frame_duration(0.1f);
        _animation->set_frames_count(bitmap->width / 64);
        _animation->set_animation_mode(Animation::AnimationMode::Once);
        _character.set_animation(_animation);
    }

    void on_exit() override
    {
    }
    void on_update(const Time& dt) override
    {
        _animation->on_update(dt);

        if (_animation->ended())
            _character.change_state<CharacterIdleState>();
    }

private:
    Shared<Animation::SpriteSheetAnimation> _animation;
};

#endif