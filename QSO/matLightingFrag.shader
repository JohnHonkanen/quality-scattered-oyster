#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;
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

	// Specular
	float specularStrength = 0.5f; // increase/decrease to change the impact on the color. 1.0f = bright, 0.0f = dark.
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // last signature of float spec is the shininess value of the highlight which is a raise to the power of #. 
															  // The higher the shininess value of an object, the more it properly reflects the light instead of scattering it around. 
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	color = vec4(result, 1.0f);


}