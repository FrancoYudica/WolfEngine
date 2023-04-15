#pragma once
#ifndef WOLF_BATCH_RENDERER_H
#define WOLF_BATCH_RENDERER_H

#include <glm/glm.hpp>

namespace Wolf
{
	namespace Rendering
	{

		class Renderer2D
		{
			/*
			* 2D Quad batch renderer
			*/

		public:
			static void init();
			static void shutdown();
			static void new_frame();
			static void end_frame();
			static void submit_quad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color);
		private:
			static void _flush();

		};

	}
}

#endif
