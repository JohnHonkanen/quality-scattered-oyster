#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{	
	// Ambient 
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse
	vec3 norm = normalize(Normal); // Normalize the normal
	vec3 lightDir = normalize(lightPos - FragPos); // Normalize the resulting direction vector
	float diff = max(dot(norm, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	color = vec4(result, 1.0f);


}