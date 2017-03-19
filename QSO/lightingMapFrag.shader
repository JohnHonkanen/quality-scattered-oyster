#version 330 core

struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	// Ambient 
	float ambientStrength = 0.1f;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));

	// Diffuse
	vec3 norm = normalize(Normal); // Normalize the normal
	vec3 lightDir = normalize(lightPos - FragPos); // Normalize the resulting direction vector
	float diff = max(dot(norm, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // last signature of float spec is the shininess value of the highlight which is a raise to the power of #. 
																			  // The higher the shininess value of an object, the more it properly reflects the light instead of scattering it around. 
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular);

	color = vec4(result, 1.0f);


}