#version 330 core
//in vec3 ourColor;
in vec2 UV;

out vec4 color;

uniform sampler2D ourUV;

void main()
{
	color =texture(ourUV, UV); // * vec4(ourColor, 1.0f);
}