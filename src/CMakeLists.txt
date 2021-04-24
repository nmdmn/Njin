project(njin)

file(GLOB_RECURSE NJIN_HEADERS *.h)
file(GLOB_RECURSE NJIN_SOURCES *.cpp)

add_executable(njin "${NJIN_HEADERS}" "${NJIN_SOURCES}")

target_include_directories(njin PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(
  njin PRIVATE njin_options CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw
               CONAN_PKG::glm)
