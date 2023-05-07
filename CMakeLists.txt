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
add_library(vendor ./src/vendor/stb_image/stb_image.cpp)
add_library(utils ./src/utils/glErrorUtils.cpp ./src/utils/shaderUtils.cpp)
add_library(renderer ./src/VertexBuffer.cpp ./src/IndexBuffer.cpp ./src/Renderer.cpp ./src/Shader.cpp ./src/VertexArray.cpp ./src/VertexBufferLayout.cpp ./src/Texture.cpp)
add_library(examples ./src/DoubleMario.cpp ./src/RenderExample2D.cpp)

target_link_libraries(renderer utils vendor)

find_package(GLEW REQUIRED)

include_directories(
	./src/INCLUDES/
	./src/vendor/stb_image/
	${GLEW_INCLUDE_DIRS} 
	./libs/glfw-3.3.8/include/) 

add_executable(app src/main.cpp)
target_link_libraries(
	app 
	examples
	renderer
	GLEW::glew_s 
	glfw 
	${GLFW_LIBRARIES})
