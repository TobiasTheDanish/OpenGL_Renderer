#include <exception>
//
//glew.h needs to be included before Renderer.h since Renderer.h includes GLFW
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "utils/glErrorUtils.h"

static void FbSizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

Renderer::Renderer(int framerate)
	: m_Framerate(framerate),
	  m_PreviousRenderTime(0.0)
{
	m_Window = SetupWindow();

    glfwMakeContextCurrent(m_Window);

	glfwSwapInterval(1);

	GLenum err = glewInit();
	
	if (err != GLEW_OK) {
		//GLEW was not initialized stop the program!
		std::terminate();
	}

}

Renderer::~Renderer()
{
    glfwTerminate();
}

GLFWwindow* Renderer::GetWindow() const
{
	return m_Window;
}

int Renderer::GetFramerate() const
{
	return m_Framerate;
}

bool Renderer::ShouldRender()
{
	if (m_PreviousRenderTime + 1.0/m_Framerate < glfwGetTime())
	{
		m_PreviousRenderTime = glfwGetTime();
		return true;
	}

	return false;
}

void Renderer::Render(void(*render)()) const
{
    if (!glfwWindowShouldClose(m_Window))
	{
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
		render();
		GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
	}
}

GLFWwindow* Renderer::SetupWindow() 
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	window = glfwCreateWindow(1080, 1080, "MY WINDOW!", NULL, NULL);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	glfwSetFramebufferSizeCallback(window, FbSizeCallback);

	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	return window;
}
