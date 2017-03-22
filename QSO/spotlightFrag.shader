#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 spotPosition;
	vec3 spotDirection;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(light.spotPosition - FragPos); // Normalize the resulting direction vector
		
	// Ambient 
	float ambientStrength = 0.1f;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));

	// Diffuse
	vec3 norm = normalize(Normal); // Normalize the normal
	
	float diff = max(dot(norm, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // last signature of float spec is the shininess value of the highlight which is a raise to the power of #. 
																			  // The higher the shininess value of an object, the more it properly reflects the light instead of scattering it around. 
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	// Spotlight (and to apply soft edges) <- We use : Intesity = (theta(in degrees) -  outerCutoff(in degrees)) / epsilon. Where epsilon is the difference between the inner cutOff and the outerCutOff in degrees: epsion = innerCutOff - outerCutOff.  
	// Basically interpolating between the outer cosine and the inner cosine based on the ? value
	float theta = dot(lightDir, normalize(-light.spotDirection)); // We negative light so that the vector is pointing towards the light direction, not from.
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // We clamp the first argument between the values 0.0 and 1.0 to make sure that the intensity values don't end up outside the [0, 1] interval.
	diffuse *= intensity;
	specular *= intensity;

	// Attenuation

	float distance = length(light.spotPosition - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;  // If prefered. Remove ambient attenuation to ensure that light in spotlight isn't too dark when we move too far away.
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);

	color = vec4(result, 1.0f);
}