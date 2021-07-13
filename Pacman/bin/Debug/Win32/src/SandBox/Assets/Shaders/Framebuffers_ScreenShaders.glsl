#Shader Vertex
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texture;

out vec2 FragTexture;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	FragTexture = Texture;
}

#Shader Fragment
#version 330 core

in vec2 FragTexture;
out vec4 FragColor;

uniform sampler2D ScreenTexture;
void main()
{
	 FragColor = texture(ScreenTexture, FragTexture);
}
