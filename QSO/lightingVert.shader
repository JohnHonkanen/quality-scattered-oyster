#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(position, 1.0f)); // Transform the vertex position with the model matrix to get the FragPos in world coords.

	Normal = normal; // mat3(transpose(inverse(model))) * normal <- use if you want to scale, but try to do in CPU instead. Less expensive
	UV = uv;

}