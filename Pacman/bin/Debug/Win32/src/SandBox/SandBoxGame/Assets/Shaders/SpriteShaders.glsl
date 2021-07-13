#Shader Vertex
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texture;

out vec2 FragTexture;

uniform mat4 CamView;
uniform mat4 Model;

void main()
{
	gl_Position = CamView * Model * vec4(Position.x, Position.y, Position.z, 1.0f);
	FragTexture = Texture;
}

#Shader Fragment
#version 330 core

in vec2 FragTexture;
out vec4 FragColor;

uniform sampler2D Image;
uniform vec3 Color;
void main()
{
	 FragColor = texture(Image, FragTexture);
}
