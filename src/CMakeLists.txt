file(GLOB_RECURSE NJIN_HEADERS *.h)
file(GLOB_RECURSE NJIN_SOURCES *.cpp)

set(NJIN_NAME ${PROJECT_NAME})
set(NJIN_VERSION ${PROJECT_VERSION})
set(NJIN_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(NJIN_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(NJIN_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(NJIN_SHADER_FOLDER ${CMAKE_SOURCE_DIR}/shader)
configure_file(config.h.in config.h)

add_executable(njin "${NJIN_HEADERS}" "${NJIN_SOURCES}")
target_include_directories(njin PRIVATE ${CMAKE_SOURCE_DIR}/src
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(
  njin PRIVATE njin_options CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw
               CONAN_PKG::glm)
