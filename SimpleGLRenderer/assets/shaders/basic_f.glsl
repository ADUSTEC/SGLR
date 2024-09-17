#version 420 core
// #extension GL_ARB_shading_language_include : require <-- use later, will divide up into multiple files to make it easier to read

out vec4 o_fragout;
in DATA 
{
	vec3 rgb;
   	vec2 uv;
   	vec3 normal;

   	mat4 projection;
   	mat4 view;
   	mat4 model;

   	vec3 cpos;

} i_data;

uniform vec3 u_campos;

// Material struct
struct material
{
	// neccesary values
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform material u_material; // mat uniform

// same for light
struct light 
{
    vec3 position;
  
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

	int lightmode; // value 1 to 3
};

uniform light u_light;


// STRUCTS FOR LIGHTING TYPE DATA
// point light
struct pointlight 
{
	float constant;
    float quadratic;
    float linear;

	float intensity;
};

// spotlight
struct spotlight 
{
	float constant;
    float quadratic;
    float linear;

	vec3 angle;
	float innercone;
	float outercone;
	float intensity;
};

// sunlight
struct sunlight 
{
	vec3 angle;
};

// uniforms
uniform pointlight u_pointlight;
uniform spotlight u_spotlight;
uniform sunlight u_sunlight;

// lighting type functions
vec3 point()
{
	vec3 lightvec = u_light.position - i_data.cpos;


    // ambient light prevents the object from being completely dark when in shadow
	vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, i_data.uv));


	// normalize the given vertex normal data
	// normalize forces the data to be between a value of 0 and 1
	vec3 normal = normalize(i_data.normal);

	// normalize the different between the light position and the current object position
	vec3 lightdir = normalize(lightvec);

	// calculate the diffuse - the dot product between the light direction and the normal
	// dot product defines how much the normal faces the direction of the light
	// if the dot product is greater than 0, then the light is on the object
	float diff = max(dot(normal, lightdir), 0.0f);

	vec3 diffuse = u_light.diffuse * diff * vec3(texture(u_material.diffuse, i_data.uv));

	// normalize the difference betweens the camera position and the current object position
	vec3 viewdir = normalize(u_campos - i_data.cpos);

	// find the direction of the reflection
	// reflect() requires the direction of the light and the normal of the object

	// first "flip" the light direction by negating it
	// this is because the light direction is in the opposite direction of the normal
	// doing this makes the light point towards the normal

	vec3 reflectiondir = reflect(-lightdir, normal);

	// specular = the dot product to the power of shininess
	float spec = 
	  pow
	( max // return the dot product if it is greater than 0
	( dot(viewdir, reflectiondir),						  0.0f), u_material.shininess // <-- pow(dotproduct, shininess)
	  // dot product of the view & reflection direction   ^ max(dotproduct, 0.0f)
	);

	// multiply the color of the light with the specular data
	vec3 specular = u_light.specular * (spec * vec3(texture(u_material.specular, i_data.uv)));
	
	// do intensity
	diffuse  *= u_pointlight.intensity;
	specular *= u_pointlight.intensity;

	// do attenuation
	float dist = length(lightvec); // get length of light position & object position
	float attenuation = 1.0 / (u_pointlight.constant + u_pointlight.linear * dist + u_pointlight.quadratic * (dist * dist)); 
	diffuse  *= attenuation;
	specular *= attenuation;   


	// add everything together
	vec3 pointlight = ambient + diffuse + specular;

	return pointlight;
}

vec3 spot()
{
	// reduced comments as it uses most the same concepts

	// diffuse
	vec3 lightvec = u_light.position - i_data.cpos;

	vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, i_data.uv));

	vec3 normal = normalize(i_data.normal);
	vec3 lightdir = normalize(lightvec);
	float diff = max(dot(normal, lightdir), 0.0f);
	vec3 diffuse = u_light.diffuse * diff * vec3(texture(u_material.diffuse, i_data.uv));

	// specular
	vec3 viewdir = normalize(u_campos - i_data.cpos);
	vec3 reflectiondir = reflect(-lightdir, normal);
	float spec = pow(max(dot(viewdir, reflectiondir), 0.0f), u_material.shininess);
	vec3 specular = u_light.specular * (spec * vec3(texture(u_material.specular, i_data.uv)));

	// spotlight specific calculations
	float theta = dot(lightdir, normalize(-u_spotlight.angle));
	float epsilon = u_spotlight.innercone - u_spotlight.outercone;
	float intensity = clamp((theta - u_spotlight.outercone) / epsilon, 0.0, u_spotlight.intensity); 
	diffuse  *= intensity;
	specular *= intensity;

	// attenuation
	float dist = length(lightvec);
	float attenuation = 1.0 / (u_spotlight.constant + u_spotlight.linear * dist + u_spotlight.quadratic * (dist * dist)); 
	diffuse  *= attenuation;
	specular *= attenuation;  

	// add everything together
	vec3 spotlight = ambient + diffuse + specular;

	return spotlight;
}

vec3 sun()
{
	// diffuse
	vec3 lightvec = u_light.position - i_data.cpos;

	vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, i_data.uv));

	vec3 normal = normalize(i_data.normal);
	vec3 lightdir = normalize(-u_sunlight.angle);
	float diff = max(dot(normal, lightdir), 0.0f);
	vec3 diffuse = u_light.diffuse * diff * vec3(texture(u_material.diffuse, i_data.uv));

	// specular
	vec3 viewdir = normalize(u_campos - i_data.cpos);
	vec3 reflectiondir = reflect(-lightdir, normal);
	float spec = pow(max(dot(viewdir, reflectiondir), 0.0f), u_material.shininess);
	vec3 specular = u_light.specular * (spec * vec3(texture(u_material.specular, i_data.uv)));

	// add everything together
	vec3 sunlight = ambient + diffuse + specular;

	return sunlight;
}

void main()
{	
	// output

	switch (u_light.lightmode)
	{
		case 1:
			o_fragout = vec4(point(), 1.0f);
			break;
		case 2:
			o_fragout = vec4(spot(), 1.0f);
			break;
		case 3:
			o_fragout = vec4(sun(), 1.0f);
			break;
		
		// use point light by default
		default:
			o_fragout = vec4(point(), 1.0f);
			break;
	}
}