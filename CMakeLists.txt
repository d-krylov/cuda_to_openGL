cmake_minimum_required(VERSION 3.18)

project(CUDA_to_OpenGL LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")

set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CUDA REQUIRED)

set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)

set(COMMON_SOURCES
  ${PROJECT_SOURCE_DIR}/common/texture.cpp
  ${PROJECT_SOURCE_DIR}/common/buffer.cpp
  ${PROJECT_SOURCE_DIR}/common/vertex_array.cpp
  ${PROJECT_SOURCE_DIR}/common/window.cpp
  ${PROJECT_SOURCE_DIR}/common/shader_pipeline.cpp
  ${PROJECT_SOURCE_DIR}/common/cuda_graphics_resource.cu
  ${PROJECT_SOURCE_DIR}/glad/glad.c
)

set(COMMON_HEADERS
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/common/include
  ${OPENGL_INCLUDE_DIR} 
  ${CUDA_INCLUDE_DIRS}
)

add_executable(cuda_to_vbo
  ${PROJECT_SOURCE_DIR}/cuda_to_vbo/main.cpp
  ${PROJECT_SOURCE_DIR}/cuda_to_vbo/renderer.cu
  ${COMMON_SOURCES}
)

target_include_directories(cuda_to_vbo PUBLIC 
  ${COMMON_HEADERS}
  ${PROJECT_SOURCE_DIR}/cuda_to_vbo/include
)

target_link_libraries(cuda_to_vbo glfw OpenGL::GL ${CUDA_LIBRARIES})

add_executable(cuda_to_texture
  ${PROJECT_SOURCE_DIR}/cuda_to_texture/main.cpp
  ${PROJECT_SOURCE_DIR}/cuda_to_texture/renderer.cu
  ${COMMON_SOURCES}
)

target_include_directories(cuda_to_texture PUBLIC 
  ${COMMON_HEADERS}
  ${PROJECT_SOURCE_DIR}/cuda_to_texture/include
)

target_link_libraries(cuda_to_texture glfw OpenGL::GL ${CUDA_LIBRARIES})