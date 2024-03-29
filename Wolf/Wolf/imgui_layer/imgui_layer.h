#pragma once
#ifndef __WOLF_IMGUI_LAYER__
#define __WOLF_IMGUI_LAYER__

#include "../core/Layer.h"

namespace Wolf {
namespace Layers {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() = default;
        virtual void on_start() override;
        virtual void on_update(const Time& delta) override;
        virtual void on_event(const Unique<Event>& event) override;
        virtual void on_ui_render_start() override;
        virtual void on_ui_render_finish() override;
        virtual void on_end() override;
        virtual void on_render() override;

    public:
        bool capture_events;
    };
}
}

#endif
