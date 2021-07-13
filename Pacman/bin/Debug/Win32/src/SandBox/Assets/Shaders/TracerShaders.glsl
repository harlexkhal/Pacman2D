#Shader Vertex
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texture;

out vec2 FragTexture;

uniform vec2 OffsetPosition;
uniform mat4 CamView;

void main()
{
    float Scale = 0.01f;
	gl_Position = CamView * vec4((Position.x * Scale) + OffsetPosition.x, (Position.y * Scale) + OffsetPosition.y, Position.z, 1.0f);
	FragTexture = Texture;
}

#Shader Fragment
#version 330 core

in vec2 FragTexture;
out vec4 FragColor;

uniform sampler2D Image;
uniform vec4 ParticleColor;
void main()
{
     vec4 TextureColor = texture(Image, FragTexture);
	 FragColor =  TextureColor;	
}