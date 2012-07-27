cmake_minimum_required(VERSION 2.8)

string(TOLOWER "${PROJECT_NAME}-demo" DEMO_PROJECT_NAME)

find_package(dglw)
include_directories(${DGLW_INCLUDE_DIRS})

# GLFW target
find_package(GLFW REQUIRED)
if(GLFW_FOUND)
    add_executable(${DEMO_PROJECT_NAME} ${GLFW_SOURCES} demo.cpp)
    target_link_libraries(${DEMO_PROJECT_NAME} dglw)
    target_link_libraries(${DEMO_PROJECT_NAME} ${COMMON_LIBS} ${GLFW_LIBRARIES})
    set_target_properties(${DEMO_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_GLFW")
else()
    message(FATAL_ERROR "GLFW not found!")
    return()
endif()
