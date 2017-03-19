#version 330 core
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f); //Set all 4 vector values to 1.0f to ensre that the lamp color stays a constant white.
}