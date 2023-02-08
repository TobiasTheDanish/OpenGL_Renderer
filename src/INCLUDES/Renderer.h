#include "GLFW/glfw3.h"

class Renderer
{
private:
	GLFWwindow* m_Window;
	int m_Framerate;
	double m_PreviousRenderTime;

public:
	Renderer(int framerate = 60);
	~Renderer();
	GLFWwindow* GetWindow() const;
	int GetFramerate() const;
	bool ShouldRender();
	void Render(void(*render)()) const;

private:
	GLFWwindow* SetupWindow();	
};
