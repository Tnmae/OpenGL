cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# Add folders
include_directories(include)

# Add your source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES} lib/glad/glad.c)

# Include dirs for GLFW and ASSIMP via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(ASSIMP REQUIRED assimp)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${GLFW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${ASSIMP_LIBRARIES} dl)
