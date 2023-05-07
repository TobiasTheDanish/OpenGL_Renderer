#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_VertCoord;

void main() 
{
	v_VertCoord = position;
	gl_Position = position;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;
in vec4 gl_FragCoord;
in vec4 v_VertCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() 
{
	vec4 texColor = texture(u_Texture, v_TexCoord);

	if (texColor.w > 0.0) {
		color = texColor;
	} else {
		color = mix(u_Color, v_VertCoord + vec4(0.5, 0.5, 0.0, 0.0), 0.5);
	}
}
