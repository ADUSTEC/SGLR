#version 430 core

out vec4 o_fragout;
in DATA 
{

	vec3 pos;
   	vec2 uv;
   	vec3 normal;

   	mat4 projection;
   	mat4 view;
   	mat4 model;

   	vec3 fpos;

} i_data;

uniform vec3 u_camerapos;

struct material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	float shininess;
};

uniform vec3 u_globalambient = vec3(0.08);

// point light
struct pointlight 
{
	vec3 position;
  
    vec3 diffuse;

	float constant;
    float quadratic;
    float linear;

	float intensity;
};

// spotlight
struct spotlight 
{
	vec3 position;
  
    vec3 diffuse;

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
	vec3 diffuse;

	vec3 angle;
};

// lighting type functions
vec3 point(pointlight plight, material mat, vec3 camerapos, vec3 fnormal, vec3 fpos, vec2 uv)
{

	vec3 lightvec = plight.position - fpos;


    // ambient light prevents the object from being completely dark when in shadow
	vec3 ambient = u_globalambient * vec3(texture(mat.diffuse, uv));


	// normalize the given texture normal data
	// normalize forces the data to be between a value of 0 and 1
	vec3 normal = normalize(texture2D(mat.normal, uv).rgb)*2.0 - 1.0;
	// compute tangent & bitangent
	vec3 Q1 = dFdx(fpos);
	vec3 Q2 = dFdy(fpos);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);
	
	vec3 T = normalize(Q1*st2.t - Q2*st1.t);
	vec3 B = normalize(-Q1*st2.s + Q2*st1.s);
	mat3 TBN = mat3(T, B, normalize(fnormal));
	normal = TBN*normal;

	// normalize the different between the light position and the current object position
	vec3 lightdir = normalize(lightvec);

	// calculate the diffuse - the dot product between the light direction and the normal
	// dot product defines how much the normal faces the direction of the light
	// if the dot product is greater than 0, then the light is on the object
	float diff = max(dot(normal, lightdir), 0.0f);

	vec3 diffuse = plight.diffuse * diff * vec3(texture(mat.diffuse, uv));


	vec3 specular = vec3(0);
	if (diff != 0) // prevent specular lighting under surfaces
	{
		// normalize the difference betweens the camera position and the current object position
		vec3 viewdir = normalize(camerapos - fpos);
		
		// halfway vector from the view direction and light direction
		vec3 halfway = normalize(viewdir + lightdir);

		// specular = the dot product to the power of shininess
		float spec = 
		  pow
		( max // return the dot product if it is greater than 0
		( dot(normal, halfway),						  0.0f), mat.shininess // <-- pow(dotproduct, shininess)
		  // dot product of the view & reflection direction   ^ max(dotproduct, 0.0f)
		);

		// multiply the color of the light with the specular data
		specular = plight.diffuse * (spec * vec3(texture(mat.specular, uv)));
	}
	
	// do attenuation
	float dist = length(lightvec); // get length of light position & object position
	float attenuation = 1.0 / (plight.constant + plight.linear * dist + plight.quadratic * (dist * dist)); 
	diffuse  *= attenuation;
	specular *= attenuation;

	diffuse  *= plight.intensity;
	specular *= plight.intensity;

	// add everything together
	vec3 pointlight = ambient + diffuse + specular;

	return pointlight;
}

vec3 spot(spotlight splight, material mat, vec3 camerapos, vec3 fnormal, vec3 fpos, vec2 uv)
{
	// reduced comments as it uses most the same concepts

	// diffuse
	vec3 lightvec = splight.position - fpos;

	vec3 ambient = u_globalambient * vec3(texture(mat.diffuse, uv));

	vec3 normal = normalize(texture2D(mat.normal, uv).rgb)*2.0 - 1.0;
	vec3 Q1 = dFdx(fpos);
	vec3 Q2 = dFdy(fpos);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);
	
	vec3 T = normalize(Q1*st2.t - Q2*st1.t);
	vec3 B = normalize(-Q1*st2.s + Q2*st1.s);
	mat3 TBN = mat3(T, B, normalize(fnormal));
	normal = TBN*normal;

	vec3 lightdir = normalize(lightvec);
	float diff = max(dot(normal, lightdir), 0.0f);
	vec3 diffuse = splight.diffuse * diff * vec3(texture(mat.diffuse, uv));

	// specular
	vec3 specular = vec3(0);
	if (diff != 0)
	{
		vec3 viewdir = normalize(camerapos - fpos);
		vec3 halfway = normalize(viewdir + lightdir);
		float spec = pow(max(dot(normal, halfway), 0.0f), mat.shininess);
		specular = splight.diffuse * (spec * vec3(texture(mat.specular, uv)));
	}

	// spotlight specific calculations
	float theta = dot(lightdir, normalize(-splight.angle));
	float epsilon = splight.innercone - splight.outercone;
	float cintensity = clamp((theta - splight.outercone) / epsilon, 0.0, 1.0f); 
	diffuse  *= cintensity;
	specular *= cintensity;

	// attenuation
	float dist = length(lightvec);
	float attenuation = 1.0 / (splight.constant + splight.linear * dist + splight.quadratic * (dist * dist)); 
	diffuse  *= attenuation;
	specular *= attenuation;

	diffuse  *= splight.intensity;
	specular *= splight.intensity;

	// add everything together
	vec3 spotlight = ambient + diffuse + specular;

	return spotlight;
}

vec3 sun(sunlight slight, material mat, vec3 camerapos, vec3 fnormal, vec3 fpos, vec2 uv)
{
	// diffuse
	vec3 ambient = u_globalambient * vec3(texture(mat.diffuse, uv));

	vec3 normal = normalize(texture2D(mat.normal, uv).rgb)*2.0 - 1.0;
	vec3 Q1 = dFdx(fpos);
	vec3 Q2 = dFdy(fpos);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);
	
	vec3 T = normalize(Q1*st2.t - Q2*st1.t);
	vec3 B = normalize(-Q1*st2.s + Q2*st1.s);
	mat3 TBN = mat3(T, B, normalize(fnormal));
	normal = TBN*normal;

	vec3 lightdir = normalize(-slight.angle);
	float diff = max(dot(normal, lightdir), 0.0f);
	vec3 diffuse = slight.diffuse * diff * vec3(texture(mat.diffuse, uv));

	vec3 specular = vec3(0);
	if (diff != 0)
	{
		// specular
		vec3 viewdir = normalize(camerapos - fpos);
		vec3 halfway = normalize(viewdir + lightdir);
		float spec = pow(max(dot(normal, halfway), 0.0f), mat.shininess);
		specular = slight.diffuse * (spec * vec3(texture(mat.specular, uv)));
	}

	// add everything together
	vec3 sunlight = ambient + diffuse + specular;

	return sunlight;
}

#define MAXLIGHTS 50

// uniforms
uniform material u_material;
uniform pointlight u_pointlight[MAXLIGHTS];
uniform spotlight u_spotlight[MAXLIGHTS];
uniform sunlight u_sunlight[1];

uniform int pointlightnum = 0;
uniform int spotlightnum = 0;
uniform int sunlightnum = 0;


void main()
{	
	// output
    vec3 outp = vec3(0);

	if (pointlightnum > 0)
	{
		for(int i = 0; i < pointlightnum; i++)
		{
			outp += point(u_pointlight[i], u_material, u_camerapos, i_data.normal, i_data.fpos, i_data.uv);
		}
	}
	else if (spotlightnum > 0)
	{
		for(int i = 0; i < spotlightnum; i++) 
		{
			outp += spot(u_spotlight[i], u_material, u_camerapos, i_data.normal, i_data.fpos, i_data.uv);
		}
	}
	else if (sunlightnum > 0)
	{
		for(int i = 0; i < sunlightnum; i++)
		{
		    outp += sun(u_sunlight[i], u_material, u_camerapos, i_data.normal, i_data.fpos, i_data.uv);
		}
	}
	else 
	{
		outp = u_globalambient * vec3(texture(u_material.diffuse, i_data.uv));
	}

	o_fragout = vec4(outp, 1.0f);

}