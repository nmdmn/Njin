#include "spdlog/spdlog.h"

#include "renderer.h"

auto main() -> int {
	spdlog::info("hello njin!");
	njin::renderer renderer;

	while(renderer.is_running()) {
		renderer.handle_events();

		renderer.swap();
	}
}
