#include "renderer.h"

#include <sstream>
#include <exception>

#include <spdlog/spdlog.h>

namespace njin {
renderer::renderer(std::string_view window_title, const int window_width, const int window_height)
	: window_title_{window_title}
	, window_width_{window_width}
	, window_height_{window_height}
	, glfw_window_{nullptr, glfwDestroyWindow} {
	if(!glfwInit()) { throw std::runtime_error("glfwIni() failed!"); }
	set_window_hints(3, 3);
	get_monitor_attribs();
	create_window_and_make_current();
	set_callbacks();
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

auto renderer::clear() -> void {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto renderer::set_cursor(const int cursor_id) -> void {
	glfwSetCursor(glfw_window_.get(), glfwCreateStandardCursor(cursor_id));
}
auto renderer::set_clear_color(const glm::vec4 &clear_color) -> void {
	clear_color_ = clear_color;
	glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
}

auto renderer::set_polygon_mode(const GLenum face, const GLenum mode) -> void {
	glPolygonMode(face, mode);
}

auto renderer::set_window_hints(const int version_major, const int version_minor) -> void {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
}

auto renderer::on_window_size_changed(GLFWwindow *window, int width, int height) -> void {
	spdlog::info("window size changed: width={0}px, height={1}px", width, height);
	glViewport(0, 0, width, height);
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
	glfw_window_.reset(glfwCreateWindow(window_width_,
										window_height_,
										(window_title_ + " v" + NJIN_VERSION).c_str(),
										nullptr,
										nullptr));
	if(!glfw_window_) {
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow() failed!");
	}
	glfwMakeContextCurrent(glfw_window_.get());
}

auto renderer::set_callbacks() -> void {
	glfwSetWindowSizeCallback(glfw_window_.get(), on_window_size_changed);
}

auto renderer::load_glad() -> void {
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::runtime_error("gladLoadGLLoader() failed");
}

auto renderer::to_string() const -> std::string {
	std::stringstream msg_stream;
	msg_stream << "window: width=" << window_width_ << ", height=" << window_height_ << "; "
			   << "monitor: width=" << monitor_width_ << ", height=" << monitor_height_
			   << ", refresh rate=" << monitor_refresh_rate_;
	return msg_stream.str();
}
} // namespace njin
