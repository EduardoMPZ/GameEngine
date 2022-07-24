#version 460 core

uniform sampler2D tex0;
uniform int textsize;

in vec2 TextCoord;
in vec2 TextNum;

out vec4 FragColor;

void main()
{
	float factor = 1.0f/float(textsize);
	FragColor = texture(tex0, (factor * TextCoord) + (factor * TextNum));
	FragColor = vec4(0.0f);
}