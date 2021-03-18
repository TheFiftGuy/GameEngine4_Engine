#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

using namespace glm;

class LightSource	{
public:

	LightSource(vec3 position_, float ambient_, float diffuse_, float specular_, vec3 lightColour_);
	~LightSource();

	vec3 GetPosition() const;
	void SetPosition(vec3 position_);

	float GetAmbient() const;
	void SetAmbient(float ambient_);

	float GetDiffuse() const;
	void SetDiffuse(float diffuse_);
	
	float GetSpecular() const;
	void SetSpecular(float specular_);

	vec3 GetLightColour() const;
	void SetLightColour(vec3 lightColour_);

private:
	vec3 position;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColour;
	
	
};

#endif
