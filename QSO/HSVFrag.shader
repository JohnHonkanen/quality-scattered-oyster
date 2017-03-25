#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform Material material;

uniform float hueShift;
uniform float satBoost;

// Function prototypes
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 rgb2hsv(vec3 rgbColor);
vec3 hsv2rgb(vec3 hsvColor);

void main() {

	// Properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Phase 1: Directional Lighting
	vec3 result = calcDirLight(dirLight, norm, viewDir);

	// Phase 2: Point lights
	result += calcPointLight(pointLight, norm, FragPos, viewDir);

	// Phase 3: Spot light

	result += calcSpotLight(spotLight, norm, FragPos, viewDir);

	// Phase 4: Emission + HSV

	// Sample the image
	vec3 rgb = vec3(texture(material.emission, UV));

	// Look up the corresponding HSV value
	vec3 hsv = rgb2hsv(rgb);

	// Manipulate hue and saturation
	hsv.x = fract(hsv.x + hueShift);
	hsv.y *= satBoost;

	// Look up the corresponding RGB value
	vec3 finalEmission = vec3(hsv2rgb(hsv));

	vec3 emission = finalEmission;

	result += emission;

	// Each light type adds it's contribution to the resulting output color until all light sources are processed.
	// The resulting color contains the color impact of all the light sources in the scene combined. 
	color = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {

	vec3 lightDir = normalize(-light.direction); // Normalize the resulting direction vector

												 // Diffuse
	float diff = max(dot(normal, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.

												  // Specular 
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	return (ambient + diffuse + specular);

}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	vec3 lightDir = normalize(light.position - fragPos); // Normalize the resulting direction vector

														 // Diffuse
	float diff = max(dot(normal, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.

												  // Specular 
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	vec3 lightDir = normalize(light.position - fragPos); // Normalize the resulting direction vector

														 // Diffuse
	float diff = max(dot(normal, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.

												  // Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// Spotlight Intensity (and to apply soft edges) <- We use : Intesity = (theta(in degrees) -  outerCutoff(in degrees)) / epsilon. Where epsilon is the difference between the inner cutOff and the outerCutOff in degrees: epsion = innerCutOff - outerCutOff.  
	// Basically interpolating between the outer cosine and the inner cosine based on the ? value
	float theta = dot(lightDir, normalize(-light.direction)); // We negative light so that the vector is pointing towards the light direction, not from.
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // We clamp the first argument between the values 0.0 and 1.0 to make sure that the intensity values don't end up outside the [0, 1] interval.

																			  // Combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	ambient *= attenuation * intensity; // If prefered. Remove ambient attenuation to ensure that light in spotlight isn't too dark when we move too far away.
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}

vec3 rgb2hsv(vec3 rgbColor)
{
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(rgbColor.bg, K.wz), vec4(rgbColor.gb, K.xy), step(rgbColor.b, rgbColor.g));
	vec4 q = mix(vec4(p.xyw, rgbColor.r), vec4(rgbColor.r, p.yzx), step(p.x, rgbColor.r));

	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;
	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 hsvColor)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(hsvColor.xxx + K.xyz) * 6.0 - K.www);
	return hsvColor.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hsvColor.y);
}

