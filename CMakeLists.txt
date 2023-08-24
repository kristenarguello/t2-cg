cmake_minimum_required(VERSION 3.22)
project(TEST)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

set(EXECUTABLE_NAME main)
set(INCLUDE_DIR include)
set(SOURCE_DIR src)

include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL OpenGL::GLU GLUT::GLUT)
