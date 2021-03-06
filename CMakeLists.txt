cmake_minimum_required(VERSION 3.15.5)
project(math_bubbles)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo") 

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Tell CMake to create the executable
add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_sources(${PROJECT_NAME} PRIVATE 
	src/main.cpp
	src/Game.cpp
	src/Window.cpp
	src/MainWindow.cpp
	)
	
target_sources(${PROJECT_NAME} PRIVATE 
	include/Game.hpp
	include/Window.hpp
	include/MainWindow.hpp
	)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

if (UNIX)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif (UNIX)
