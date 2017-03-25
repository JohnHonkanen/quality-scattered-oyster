#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(position, 1.0f));
	// the transpose of the inverse of the upper-left corner of the model matrix : 
	// see http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/ // <- try to do in CPU instead. Less expensive
	Normal = normalize(normalMatrix * normal);
	UV = uv;

}