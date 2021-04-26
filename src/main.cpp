#include <string>

#include <spdlog/spdlog.h>

#include "renderer.h"
#include "program.h"

constexpr const char *shader_folder = NJIN_SHADER_FOLDER;

auto main() -> int {
	spdlog::info(std::string(NJIN_NAME) + " v" + std::string(NJIN_VERSION));

	njin::renderer renderer;
	renderer.set_cursor(GLFW_CROSSHAIR_CURSOR);
	renderer.set_clear_color({.87f, .23f, .16f, 1.f});
	renderer.set_polygon_mode(GL_FRONT_AND_BACK, GL_FILL);

	std::string shader_path_prefix{shader_folder};
	njin::program default_program{shader_path_prefix + "default.vs",
								  shader_path_prefix + "default.fs"};
	spdlog::info(default_program);

	while(renderer.is_running()) {
		renderer.handle_events();
		renderer.clear();

		renderer.swap();
	}
}
