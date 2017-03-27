#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bittangent;

out vec3 FragPos;
//out vec3 Normal;
out vec2 UV;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(position, 1.0f));
	//// the transpose of the inverse of the upper-left corner of the model matrix : 
	//// see http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/ // <- try to do in CPU instead. Less expensive
	//Normal = normalize(normalMatrix * normal);
	UV = uv;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	// TBN matrix = tangent, bitangent, and normal vector 

	// Trick : Gram/Schmidt process we can orthogolize the TBN vectors so that each vector is again perpendicular to the other vectors. 
	// See : https://www.youtube.com/watch?v=4FaWLgsctqY
	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(model *vec4(normal, 0.0)));
	// re-orthogonalize T with respect to N
	T = normalize(T - dot(T, N) * N);
	// then retrieve perpendicular vector B with the cross product of T and N
	vec3 B = cross(N, T);

	mat3 TBN = mat3(T, B, N);

	TangentLightPos = TBN;
	TangentViewPos = TBN;
	TangentFragPos = TBN * FragPos;
}