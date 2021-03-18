#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

uniform sampler2D inputTexture;

out vec4 fColour;

struct Light	{
vec3 lightPos;
float ambient;
float diffuse;
float specular;
vec3 lightColour;
};

void main(){
	fColour = texture(inputTexture, TexCoords);
}