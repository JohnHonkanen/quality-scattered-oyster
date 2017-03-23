#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec2 UV;

out vec4 color;

uniform Material material;

void main()
{
	color = vec4(texture(material.diffuse, UV).rgb, 1.0f);
}