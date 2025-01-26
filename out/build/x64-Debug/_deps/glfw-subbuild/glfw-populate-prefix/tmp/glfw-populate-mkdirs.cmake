# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-src"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-build"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix/tmp"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix/src"
  "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Projekty/Vulkan/OpenGL Projekt/out/build/x64-Debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/${subDir}")
endforeach()
