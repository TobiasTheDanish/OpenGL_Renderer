#include "DoubleMario.h"
#include "VertexBufferLayout.h"

DoubleMario::DoubleMario() : m_Shader("../res/shaders/basic.shader"), m_Texture("../res/textures/mario.png") {
	float positions[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};

	m_vb.SetBuffer(positions, 4 * 4 *sizeof(float));

	unsigned int indecies[] = {
		0, 1, 2,
		2, 3, 0,
	};

	m_ib.SetCount(6);
	m_ib.SetData(indecies);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_va.AddBuffer(m_vb, layout);

	m_Shader.SetUniform4f("u_Color", 0.3, 0.2, 0.8, 1.0);

	m_Texture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);
}

DoubleMario::~DoubleMario() {}

void DoubleMario::Run(Renderer& renderer) const
{
    while (!glfwWindowShouldClose(renderer.GetWindow()))
	{
		if (renderer.ShouldRender())
		{
			renderer.Clear();

			renderer.Draw(m_va, m_ib, m_Shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(renderer.GetWindow());

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
}
