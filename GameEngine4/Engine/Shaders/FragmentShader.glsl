#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

uniform vec3 viewPosition;


out vec4 fColour;

struct Light	{
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColour;
};
uniform Light light;

struct Material	{
	sampler2D diffuseMap;
	float shininess; //Ns
	float transparency; //d
	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
};
uniform Material material;


void main(){
	//Ambient
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Specular
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);
}