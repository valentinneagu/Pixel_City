#version 330
 
 // TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int spotlight;
uniform int angle_spotlight;

uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int textures;


in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color1 = texture2D(texture_1, texcoord);  
	vec4 color2 = texture2D(texture_2, texcoord);         

	vec3 N = normalize( world_normal );
	vec3 L = vec3(0, 1, 0);
	vec3 V = normalize( eye_position - world_position );
	vec3 H = normalize( L + V );

	float d = distance(world_position, world_normal);
	float atten;
	float ambient_light;

	ambient_light = 0.25;
	atten = 1 / (0.01*d*d + 0.02*d + 1);
	
	float diffuse_light = material_kd * (max (dot(N, L), 0) + ambient_light);

	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	float light = specular_light + diffuse_light;

	out_color = color1 * light;// * atten;
}