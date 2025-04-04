cmake_minimum_required(VERSION 3.15)
project(Pride VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)

option(COMPILE_EXAMPLE "Build example executable" OFF)

add_subdirectory(Pride/External/SDL)
add_subdirectory(Pride/External/SDL_image)

# Handle sources
file(GLOB PRIDE_SOURCES CONFIGURE_DEPENDS "Pride/Source/**.cpp")
file(GLOB PRIDE_HEADERS CONFIGURE_DEPENDS "Pride/Headers/**.h")
add_library(Pride STATIC
    ${PRIDE_SOURCES}
    ${PRIDE_HEADERS}
)

target_include_directories(Pride 
    PUBLIC 
        Pride/Headers
    
    PRIVATE
        Pride/External/SDL/include
        Pride/External/SDL_image/include
)

target_link_libraries(Pride PRIVATE
    SDL3
    SDL3_image
)

# Example window with renderer.
if(COMPILE_EXAMPLE)
    add_executable(WindowExample
        Examples/window.cpp
    )

    target_include_directories(WindowExample PRIVATE
        Pride/Headers

        Pride/External/SDL/include
        Pride/External/SDL_image/include
    )

    target_link_libraries(WindowExample PRIVATE
        Pride
        SDL3
        SDL3_image
    )
endif()