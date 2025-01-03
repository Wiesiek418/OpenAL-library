cmake_minimum_required(VERSION 3.20)

project(EXAMPLE_OPENGL)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Select another Build Directory!")
endif()

if (CMAKE_SOURCE_DIR MATCHES " ")
	message(WARNING "Source Directory path contains spaces!")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
	message(WARNING "Build Directory path contains spaces!")
endif()

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
	GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(glfw)

add_executable(main
	src/main.cpp
	lib/glad.c
)

include_directories(
	${glfw_SOURCE_DIR}/include    # Headers in ./GLFW
	src/
	.
)

target_link_libraries(main PRIVATE glfw)
