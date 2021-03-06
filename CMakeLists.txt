cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(
  njin
  VERSION 1.1.1
  LANGUAGES CXX)

include(cmake/njin-setup.cmake)
setup_build_type()
prevent_in_src_builds()

add_library(njin_options INTERFACE)
target_compile_features(njin_options INTERFACE cxx_std_20)
include(cmake/compiler_warinings_setup.cmake)
setup_warnings(njin_options)

include(cmake/conan-setup.cmake)
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} spdlog/1.8.5)
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} glfw/3.3.4)
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} glad/0.1.34)
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} glm/0.9.9.8)
# set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} tinyobjloader/1.0.6)
# set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} imgui/1.82)
setup_conan()

add_subdirectory(src)
