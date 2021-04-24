#include "renderer.h"

namespace njin {
renderer::renderer(std::string_view window_title, const int window_width, const int window_height)
	: window_title_{window_title}
	, window_width_{window_width}
	, window_height_{window_height}
	, glfw_window_{nullptr, glfwDestroyWindow} {
	if(!glfwInit()) { throw std::logic_error("glfwIni() failed!"); }
	set_window_hints(3, 3);
	get_monitor_attribs();
	create_window_and_make_current();
	set_cursor(GLFW_CROSSHAIR_CURSOR);
	load_glad();
}

auto renderer::is_running() -> bool {
	return !glfwWindowShouldClose(glfw_window_.get());
}

auto renderer::handle_events() -> void {
	glfwPollEvents();
	if(glfwGetKey(glfw_window_.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfw_window_.get(), true);
}

auto renderer::swap() -> void {
	glfwSwapBuffers(glfw_window_.get());
}

auto renderer::clear(const glm::vec4 &color) -> void { }

auto renderer::set_window_hints(const int version_major, const int version_minor) -> void {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
}

auto renderer::get_monitor_attribs() -> void {
	auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	monitor_width_ = mode->width;
	monitor_height_ = mode->height;
	monitor_refresh_rate_ = mode->refreshRate;
}

auto renderer::create_window_and_make_current() -> void {
	glfw_window_.reset(
		glfwCreateWindow(window_width_, window_height_, window_title_.c_str(), nullptr, nullptr));
	if(!glfw_window_) {
		glfwTerminate();
		throw std::logic_error("glfwCreateWindow() failed!");
	}
	glfwMakeContextCurrent(glfw_window_.get());
}

auto renderer::set_cursor(const int cursor_id) -> void {
	glfwSetCursor(glfw_window_.get(), glfwCreateStandardCursor(cursor_id));
}

auto renderer::load_glad() -> void {
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::logic_error("gladLoadGLLoader() failed");
}
} // namespace njin
