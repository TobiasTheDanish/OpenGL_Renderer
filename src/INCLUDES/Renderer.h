#include "GLFW/glfw3.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

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
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;

private:
	GLFWwindow* SetupWindow();	
};
