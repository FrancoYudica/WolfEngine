
#include <iostream>

#include "WEngine.h"
#include "batch_renderer_test.hpp"

using namespace Wolf;

int main()
{
	bool success = Wolf::init();
    if (!success)
        return -1;

	// CLient layer	
	auto& app = Wolf::Application::get();
	std::shared_ptr<Layer> test_Layer = std::make_shared<SandboxLayers::BatchLayer>();
	app->add_layer(test_Layer);
	app->run();
	return 0;
}