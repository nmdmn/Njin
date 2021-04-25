#include <spdlog/spdlog.h>

#include "config.h"
#include "renderer.h"

auto main() -> int {
	spdlog::info(std::string(NJIN_NAME) + " v" + std::string(NJIN_VERSION));

	njin::renderer renderer;
	renderer.set_cursor(GLFW_CROSSHAIR_CURSOR);
	renderer.set_clear_color({.87f, .23f, .16f, 1.f});
	renderer.set_polygon_mode(GL_FILL);

	while(renderer.is_running()) {
		renderer.handle_events();
		renderer.clear();

		renderer.swap();
	}
}
