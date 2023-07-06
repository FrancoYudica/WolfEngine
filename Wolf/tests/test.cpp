
#include <iostream>

#include "WEngine.h"
#include "performance_display.hpp"
#include "renderer/batch_renderer_test.hpp"
#include "renderer/texture_test.hpp"	
#include "renderer/sprite_rendering_test.hpp"
#include <memory>

using namespace Wolf;

int main()
{
	bool success = Wolf::init();
    if (!success)
        return -1;

	// CLient layer	
	auto& app = Wolf::Application::get();
	Shared<Wolf::Layer> performance_layer = std::make_shared<Tests::PerformanceDisplayLayer>();
	app->add_layer(performance_layer);

	Shared<Wolf::Layer> test_layer = std::make_shared<Tests::Renderer::SpriteRendering>();
	app->add_layer(test_layer);
	app->run();
	return 0;
}