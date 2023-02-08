#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
	Renderer renderer;
	
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

	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	GlCall(glEnableVertexAttribArray(0));
	GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	IndexBuffer ib(indecies, 6);
	
	Shader shader("../res/shaders/basic.shader");
	shader.Bind();
	shader.SetUniform("u_Color", 0.3, 0.2, 0.8, 1.0);

	vb.UnBind();
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
			GlCall(glClear(GL_COLOR_BUFFER_BIT));

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

			vb.Bind();
			ib.Bind();
			shader.Bind();
			shader.SetUniform("u_Color", r, g, b, a);

			GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			/* Swap front and back buffers */
			glfwSwapBuffers(renderer.GetWindow());

			/* Poll for and process events */
			glfwPollEvents();
		}
	}


    return 0;
}

