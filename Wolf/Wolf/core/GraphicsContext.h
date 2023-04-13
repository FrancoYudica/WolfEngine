#pragma once
#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H
#include <memory>
#include "Window.h"

namespace Wolf
{
	class  GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual void Init() = 0;
		static std::shared_ptr<GraphicsContext> Create(const Wolf::Window& window);
	};
}
#endif