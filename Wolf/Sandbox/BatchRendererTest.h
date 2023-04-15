#pragma once
#ifndef BATCH_LAYER_H
#define BATCH_LAYER_H

#include "../WEngine.h"

namespace Wolf
{
	namespace SandboxLayers
	{

		class BatchLayer : public Wolf::Layer
		{
			public:
				BatchLayer() = default;
				virtual void on_start() override;
				virtual void on_update(const Time& delta) override;
				virtual void on_event(Event* event) override;
				virtual void on_ui_render_start() override;
				virtual void on_ui_render_finish() override;
				virtual void on_end() override;
				virtual void on_render() override;
		};
	}
}

#endif