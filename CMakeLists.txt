cmake_minimum_required(VERSION 3.1)
project(openGL_project)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
 
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

set( GLEW_USE_STATIC_LIBS ON)
add_definitions( -DGLEW_NO_GLU )

add_subdirectory(./libs/glfw-3.3.8/)
add_library(utils ./src/utils/glErrorUtils.cpp ./src/utils/shaderUtils.cpp)
add_library(renderer ./src/VertexBuffer.cpp ./src/IndexBuffer.cpp ./src/Renderer.cpp ./src/Shader.cpp ./src/VertexArray.cpp ./src/VertexBufferLayout.cpp)

target_link_libraries(renderer utils)

find_library(STB_LIB stb_image.h PATHS "./src/vendor/stb_image/stb_image.h")
message("${STB_LIB}")
find_package(GLEW REQUIRED)

include_directories(
	./src/INCLUDES/
	./src/vendor/stb_image/
	${GLEW_INCLUDE_DIRS} 
	./libs/glfw-3.3.8/include/) 

add_executable(app src/main.cpp)
target_link_libraries(
	app 
	GLEW::glew_s 
	glfw 
	${GLFW_LIBRARIES} 
	renderer)
