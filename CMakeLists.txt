cmake_minimum_required(VERSION 3.20)
project(BudgieOS_Engine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(budgie_engine_core
    src/core/Engine.cpp
    src/core/Scene.cpp
)
target_include_directories(budgie_engine_core PUBLIC include)

if(WIN32)
    add_executable(BudgieOS-Engine WIN32
        src/platform/windows/EditorApp.cpp
    )
    target_link_libraries(BudgieOS-Engine PRIVATE budgie_engine_core user32 gdi32)
    target_compile_definitions(BudgieOS-Engine PRIVATE UNICODE _UNICODE)
else()
    add_executable(budgie-engine-core-check src/main.cpp)
    target_link_libraries(budgie-engine-core-check PRIVATE budgie_engine_core)
endif()
