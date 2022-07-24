#version 460 core

uniform sampler2D BackGround;

in vec2 TextCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(BackGround, TextCoord);
}