#pragma once

#include <string_view>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "config.h"

namespace njin {
class renderer {
public:
	renderer(std::string_view window_title = "njin",
			 const int window_width = 800,
			 const int window_height = 600);
	auto is_running() -> bool;
	auto handle_events() -> void;
	auto swap() -> void;
	auto clear() -> void;

	auto set_cursor(const int cursor_id) -> void;
	auto set_clear_color(const glm::vec4 &cclear_olor) -> void;
	auto set_polygon_mode(const GLenum face, const GLenum mode) -> void;

	static auto on_window_size_changed(GLFWwindow *window, int width, int height) -> void;

private:
	using glfw_window_type = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

	auto set_window_hints(const int version_major, const int version_minor) -> void;
	auto get_monitor_attribs() -> void;
	auto create_window_and_make_current() -> void;
	auto set_callbacks() -> void;
	auto load_glad() -> void;

	std::string window_title_;
	int window_width_;
	int window_height_;
	glfw_window_type glfw_window_;
	int monitor_width_;
	int monitor_height_;
	int monitor_refresh_rate_;
	glm::vec4 clear_color_;
};
} // namespace njin
