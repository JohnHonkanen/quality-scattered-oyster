#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	//vec3 position;
	vec3 direction;

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

uniform float hueShift;
uniform float satBoost;

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

void main()
{
	
	// Ambient 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));

	// Diffuse
	vec3 norm = normalize(Normal); // Normalize the normal
	vec3 lightDir = normalize(light.direction - FragPos); // Normalize the resulting direction vector
	float diff = max(dot(norm, lightDir), 0.0); // Use Max to avoid dot product going negative when vector is greater than 90 degrees.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // last signature of float spec is the shininess value of the highlight which is a raise to the power of #. 
																			  // The higher the shininess value of an object, the more it properly reflects the light instead of scattering it around. 
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	//Emission

	// Sample the image
	vec3 rgb = vec3(texture(material.emission, UV));//texture2D(ourImage, UV).rgb; 

	// Look up the corresponding HSV value
	vec3 hsv = rgb2hsv(rgb);


	// Manipulate hue and saturation
	hsv.x = fract(hsv.x + hueShift);
	hsv.y *= satBoost;

	// Look up the corresponding RGB value
	vec3 finalEmission = vec3(hsv2rgb(hsv));

	vec3 emission = finalEmission;

	vec3 result = (ambient + diffuse + specular + emission);

	color = vec4(result, 1.0f);


}