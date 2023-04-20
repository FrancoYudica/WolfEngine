#pragma once
#ifndef WOLF_LAYER_H
#define WOLF_LAYER_H
#include "Event.h"
#include <vector>
#include <iostream>
#include "Time.h"


namespace Wolf
{

	class Layer
	{
		public:
		Layer() = default;
		~Layer() = default;
		virtual void on_start() = 0;					// Added to the stack
		virtual void on_end() = 0;						// Removed from the stack 
		virtual void on_update(const Time& delta) = 0;	// Once per frame
		virtual void on_render() = 0;					// Once per frame
		virtual void on_ui_render_start() = 0;
		virtual void on_ui_render_finish() = 0;
		virtual void on_event(Event* event) = 0;	// Once per frame at event poll
	};


	class LayerStack
	{
		// Data structure for containing and adding the layers
		// Follows the LIFO (Lirst in -> First out)
	public:

		LayerStack() = default;
		~LayerStack() { clear(); }

		void clear()
		{
			for (Layer* layer : _layers)
			{
				layer->on_end();
			}
			_layers.clear();
		}

		void add(Layer* layer)
		{
			_layers.insert(_layers.end() - _overlay_count, layer);
			layer->on_start();

		}
		bool remove(Layer* layer)
		{
			for (uint32_t i = 0; i < _layers.size(); i++)
			{
				if (_layers[i] == layer)
				{
					// Element found
					uint32_t first_overlay_index = _layers.size() - 1 - _overlay_count;
					if (first_overlay_index <= i)
					{
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
		void add_overlay(Layer* layer)
		{
			_layers.emplace_back(layer);
			_overlay_count++;
			layer->on_start();
		}
		const std::vector<Layer*>& get_layers() const { return _layers; }

	private:
		uint32_t _overlay_count = 0;
		std::vector<Layer*> _layers;
	};
}
#endif