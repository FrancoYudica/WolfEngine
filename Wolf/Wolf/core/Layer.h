#pragma once
#ifndef __WOLF_LAYER__
#define __WOLF_LAYER__
#include "Event.h"
#include "Time.h"
#include "wolf_types.h"
#include <iostream>
#include <memory>
#include <vector>

namespace Wolf {

class Layer {
public:
    Layer() = default;
    ~Layer() {};
    virtual void on_start() {}; // Added to the stack
    virtual void on_end() {}; // Removed from the stack
    virtual void on_update(const Time& delta) {}; // Once per frame
    virtual void on_render() {}; // Once per frame
    virtual void on_ui_render_start() {};
    virtual void on_ui_render_finish() {};
    virtual void on_event(const Unique<Event>& event) {}; // Once per frame at event poll

public:
    std::string name = "DefaultLayer";
};

class LayerStack {
    // Data structure for containing and adding the layers
    // Follows the LIFO (First in -> First out)
public:
    LayerStack() = default;
    ~LayerStack() { clear(); }

    void clear()
    {
        for (const Shared<Layer>& layer : _layers) {
            layer->on_end();
        }
        _layers.clear();
    }

    void add(const Shared<Layer>& layer)
    {
        _layers.insert(_layers.end() - _overlay_count, layer);
        layer->on_start();
    }
    bool remove(const Shared<Layer>& layer)
    {
        for (uint32_t i = 0; i < _layers.size(); i++) {
            if (_layers[i] == layer) {
                // Element found
                uint32_t first_overlay_index = _layers.size() - 1 - _overlay_count;
                if (first_overlay_index <= i) {
                    // It's an overlay
                    _overlay_count--;
                }

                _layers.erase(_layers.begin() + i, _layers.begin() + i);
                layer->on_end();
                return true;
            }
        }
        return false;
    }
    void add_overlay(const Shared<Layer>& layer)
    {
        _layers.push_back(layer);
        _overlay_count++;
        layer->on_start();
    }
    const std::vector<Shared<Layer>>& get_layers() const { return _layers; }

private:
    uint32_t _overlay_count = 0;
    std::vector<Shared<Layer>> _layers;
};
}
#endif