cmake_minimum_required(VERSION 3.10)
project(KuboomCheat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED src/main.cpp src/offsets.h)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    PREFIX "" 
    SUFFIX ".dll"
)

# If you use MinHook, you can add it here
# find_package(MinHook REQUIRED)
# target_link_libraries(${PROJECT_NAME} MinHook::MinHook)
