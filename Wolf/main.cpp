
#include <iostream>

#include "WEngine.h"
#include "Sandbox/OpenGLLayer.h"
#include "Sandbox/BatchRendererTest.h"

using namespace Wolf;

int main()
{

	auto app = Application();
	app.initialize(Window::Configuration());
	Layers::ImGuiLayer imguiLayer = Layers::ImGuiLayer();
	app.add_layer(&imguiLayer);

	SandboxLayers::BatchLayer openglLayer = SandboxLayers::BatchLayer();
	app.add_layer(&openglLayer);

	app.run();
	return 0;
}
