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

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GlCall(glClear(GL_COLOR_BUFFER_BIT));
}

GLFWwindow* Renderer::SetupWindow() 
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1080, 1080, "MY WINDOW!", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, FbSizeCallback);
	
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	return window;
}
