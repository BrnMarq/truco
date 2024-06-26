cmake_minimum_required(VERSION 3.12)
project(truco_venezolano)
set(CMAKE_CXX_STANDARD 17)

if (NOT TARGET hello_imgui)
    message(STATUS "Fetching hello_imgui")
    include(FetchContent)
    FetchContent_Declare(hello_imgui GIT_REPOSITORY https://github.com/pthom/hello_imgui.git GIT_TAG master)
    FetchContent_MakeAvailable(hello_imgui)
endif()

include_directories("${CMAKE_SOURCE_DIR}/src/lib/include")
FILE(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/lib/src/*.cpp")

# Build your app
# ==============
hello_imgui_add_app(TrucoVenezolano main.cpp ${SOURCES})


# hello_imgui_add_app is a helper function, similar to cmake's "add_executable"
# Usage:
# hello_imgui_add_app(app_name file1.cpp file2.cpp ...)
#
# Features: 
# * It will automatically link the target to the required libraries (hello_imgui, OpenGl, glad, etc)
# * It will embed the assets (for desktop, mobile, and emscripten apps)
# * It will perform additional customization (app icon and name on mobile platforms, etc)

# Now you can build your app with
#     mkdir build && cd build && cmake .. && cmake --build .
