# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-src"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-build"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/tmp"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/src/hello_imgui-populate-stamp"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/src"
  "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/src/hello_imgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/src/hello_imgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/brnmarq/Documents/BrnCode/Cpp/hello_imgui_template/_deps/hello_imgui-subbuild/hello_imgui-populate-prefix/src/hello_imgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
