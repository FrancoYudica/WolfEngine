#pragma once
#ifndef OPENGL_LAYER_H
#define OPENGL_LAYER_H

#include "../WEngine.h"

namespace Wolf
{
	namespace SandboxLayers
	{

		class OpenGLLayer : public Wolf::Layer
		{
			public:
				OpenGLLayer() = default;
				Wolf::Rendering::ShaderLibrary Shaders;
				std::shared_ptr<Wolf::Rendering::VertexArray> VAO;
				virtual void on_start() override;
				virtual void on_update(const Time& delta) override;
				virtual void on_event(Event* event) override;
				virtual void on_ui_render_start() override;
				virtual void on_ui_render_finish() override;
				virtual void on_end();
				virtual void on_render();
		};
	}
}

#endif