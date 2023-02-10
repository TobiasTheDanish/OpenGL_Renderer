#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "utils/glErrorUtils.h"

int main(void)
{
	Renderer renderer(30);

	GLenum err = glewInit();
	
	if (err != GLEW_OK) {
		//GLEW was not initialized stop the program!
		return 0;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indecies[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	IndexBuffer ib(indecies, 6);
	
	Shader shader("../res/shaders/basic.shader");
	shader.SetUniform("u_Color", 0.3, 0.2, 0.8, 1.0);

	va.UnBind();
	ib.UnBind();
	shader.UnBind();

	float r = 0.3;
	float g = 0.2;
	float b = 0.8;
	float a = 1.0;
	float rOffset, gOffset, bOffset = 0.1;

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(renderer.GetWindow()))
	{
		if (renderer.ShouldRender())
		{
			renderer.Clear();

			if (r >= 1.0) 
			{
				rOffset = -0.04;
			}
			else if (r <= 0.0)
			{
				rOffset = 0.08;
			}

			r += rOffset;

			if (g >= 1.0) 
			{
				gOffset = -0.01;
			}
			else if (g <= 0.0)
			{
				gOffset = 0.05;
			}

			g += gOffset;

			if (b >= 1.0) 
			{
				bOffset = -0.03;
			}
			else if (b <= 0.0)
			{
				bOffset = 0.02;
			}

			b += bOffset;

			shader.Bind();
			shader.SetUniform("u_Color", r, g, b, a);

			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(renderer.GetWindow());

			/* Poll for and process events */
			glfwPollEvents();
		}
	}


    return 0;
}

