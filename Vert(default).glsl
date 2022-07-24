#version 460 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aTex;

uniform mat4 CamM;

out vec2 TextCoord;

void main()
{
	gl_Position = CamM * aPos;
	TextCoord = aTex.xy;
}