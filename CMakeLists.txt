cmake_minimum_required(VERSION 3.10)

project(massif2img CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the tests" OFF)

include(FetchContent)

if(BUILD_TESTS)
	find_package(Catch2 3 QUIET)
	if(NOT Catch2_FOUND)
		FetchContent_Declare(
			Catch2
			GIT_REPOSITORY https://github.com/catchorg/Catch2.git
			GIT_TAG        v3.9.0
		)

		FetchContent_MakeAvailable(Catch2)
	endif()
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL Release)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
include(CTest)
add_subdirectory(tests)
endif()
