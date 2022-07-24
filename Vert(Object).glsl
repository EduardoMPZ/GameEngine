#version 460 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aTex;

layout (std430, binding = 2) buffer Textures
{
	vec2 Coord[];
};

layout (std430, binding = 3) buffer Matrices
{
	mat4 model[];
};


uniform mat4 CamM;
uniform int ObjectNum;

out vec2 TextCoord;
out vec2 TextNum;

void main()
{
	gl_Position = CamM * model[int(aTex.w)] * aPos;
	TextNum = Coord[int(aTex.w)];
	TextCoord = aTex.xy;
}