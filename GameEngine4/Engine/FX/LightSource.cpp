#include "LightSource.h"

LightSource::LightSource(vec3 position_, float ambient_, float diffuse_, float specular_, vec3 lightColour_)    {
    position = position_;
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    lightColour = lightColour_;
}

LightSource::~LightSource(){
}

vec3 LightSource::GetPosition() const   {
    return position;
}

void LightSource::SetPosition(vec3 position_)   {
    position = position_;
}

float LightSource::GetAmbient() const   {
    return ambient;
}

void LightSource::SetAmbient(float ambient_)    {
    ambient = ambient_;
}

float LightSource::GetDiffuse() const   {
    return diffuse;
}

void LightSource::SetDiffuse(float diffuse_)    {
    diffuse = diffuse_;
}

float LightSource::GetSpecular() const  {
    return specular;
}

void LightSource::SetSpecular(float specular_)  {
    specular = specular_;
}

vec3 LightSource::GetLightColour() const    {
    return lightColour;
}

void LightSource::SetLightColour(vec3 lightColour_) {
    lightColour = lightColour_;
}
