
#include <iostream>

#include "Wolf/WEngine.h"
#include "Sandbox/OpenGLLayer.h"
#include "Sandbox/BatchRendererTest.h"

using namespace Wolf;

int main()
{
	Wolf::init();
	auto app = Wolf::Application::get();
	bool sucess = app->initialize(Window::Configuration());
	if (!sucess)
	{
		std::cout << "Appication init fail" << std::endl;
		return -1;
	}

	// If imgui is used
	Layers::ImGuiLayer imguiLayer = Layers::ImGuiLayer();
	app->add_layer(&imguiLayer);

	// CLient layer	
	SandboxLayers::BatchLayer openglLayer = SandboxLayers::BatchLayer();
	app->add_layer(&openglLayer);

	app->run();
	return 0;
}
