#version 330 core
//in vec3 ourColor;
in vec2 UV;

out vec4 color;

uniform sampler2D ourImage;

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

	// Sample the image
	vec3 rgb = vec3(1.0f, 0.5f, 0.5f);//texture2D(ourImage, UV).rgb; 
	
	// Look up the corresponding HSV value
	vec3 hsv = rgb2hsv(rgb);


	// Manipulate hue and saturation
	hsv.x = fract(hsv.x + hueShift);
	hsv.y *= satBoost;

	// Look up the corresponding RGB value
	color = vec4(hsv2rgb(hsv), 1.0f);
}