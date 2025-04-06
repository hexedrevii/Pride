cmake_minimum_required(VERSION 3.15)
project(Pride VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

option(COMPILE_EXAMPLE "Build example executable" OFF)

# Enable FetchContent
include(FetchContent)

find_package(SDL3 QUIET)
find_package(SDL3_image QUIET)

# If not found, fetch and build them
if(NOT SDL3_FOUND OR NOT SDL3_image_FOUND)
    message(STATUS "SDL3 or SDL3_image not found - using embedded versions.")
    
    include(FetchContent)
    
    # SDL3
    if(NOT SDL3_FOUND)
        message(STATUS "Using embedded SDL3.")

        FetchContent_Declare(
            sdl3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG main
        )
    endif()
    
    # SDL3_image (depends on SDL3)
    if(NOT SDL3_image_FOUND)
        message(STATUS "Using embedded SDL3_image.")

        FetchContent_Declare(
            sdl3_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG main

            OVERRIDE_FIND_PACKAGE  # Ensure we use our SDL3
        )
    endif()
    
    # Fetch both with dependency awareness
    FetchContent_MakeAvailable(sdl3 sdl3_image)
endif()

# Handle sources
file(GLOB PRIDE_SOURCES CONFIGURE_DEPENDS "Pride/Source/**.cpp")
file(GLOB PRIDE_HEADERS CONFIGURE_DEPENDS "Pride/Headers/**.h")
add_library(Pride STATIC
    ${PRIDE_SOURCES}
    ${PRIDE_HEADERS}
)

target_include_directories(Pride PUBLIC 
    Pride/Headers
)

target_link_libraries(Pride PRIVATE
    SDL3::SDL3 SDL3_image::SDL3_image
)

# Example window with renderer.
if(COMPILE_EXAMPLE)
    add_executable(WindowExample
        Examples/window.cpp
    )

    target_include_directories(WindowExample PRIVATE
        Pride/Headers

        External/SDL/include
        External/SDL_image/include
    )

    target_link_libraries(WindowExample PRIVATE
        Pride
        SDL3::SDL3
        SDL3_image::SDL3_image
    )
endif()