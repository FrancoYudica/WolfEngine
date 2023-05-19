<div id="header" align="center">
	INSTALLATION
</div>

Also, it's requiered the following CMakeLists.txt file

//set(WOLF_ENGINE_RELATIVE_TO_ROOT_PATH "Dependencies/WolfEngine")

add_subdirectory(WolfEngine/Wolf)
add_library(dependencies INTERFACE)
target_link_libraries(dependencies INTERFACE engine_lib)

include_directories(dependencies "WolfEngine/Wolf")

USAGE
Requiered main code

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

	// IMGUI REQUIERED
	Layers::ImGuiLayer imguiLayer = Layers::ImGuiLayer();
	app->set_imgui_layer(&imguiLayer);

	// Add the client layer to the app like this
	/*
	SandboxLayers::BatchLayer openglLayer = SandboxLayers::BatchLayer();
	app->add_layer(&openglLayer);
	*/
	app->run();
	return 0;
}


