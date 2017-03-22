#version 330 core

layout(location = 0) in vec3 position;

out vec3 UV;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww;
	UV = position;
}