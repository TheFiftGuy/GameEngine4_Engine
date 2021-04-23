#include "CollisionDetection.h"


#include <glm/detail/_vectorize.hpp>
#include <glm/detail/_vectorize.hpp>

#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()	{
	
}

Ray CollisionDetection::MousePosToWorldRay(vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_)	{
	vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f, -1.0f, 1.0f);
	vec4 rayEndNDC	((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f, 0.0f, 1.0f);

	mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)	{
	mat4 modelMatrix = box_->transform;
	vec3 rayOrigin = ray_->origin;
	vec3 rayDirection = ray_->direction;
	vec3 boxMin = box_->minVert;
	vec3 boxMax = box_->maxVert;
	
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();
	
	vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	vec3 delta = worldPos - rayOrigin;

	//X axis
	vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = dot(delta, xAxis);
	float dotDir = dot(rayDirection, xAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		if (t1 > t2) { //makes sure that t1 is the min and t2 is max, if they aren't then swap them
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else { //teacher question
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}

	//Y axis
	vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	dotDelta = dot(delta, yAxis);
	dotDir = dot(rayDirection, yAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.y) / dotDir;
		float t2 = (dotDelta + boxMax.y) / dotDir;

		if (t1 > t2) { //makes sure that t1 is the min and t2 is max, if they aren't then swap them
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else { //teacher question
		if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f) {
			return false;
		}
	}

	//Z axis
	vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	dotDelta = dot(delta, zAxis);
	dotDir = dot(rayDirection, zAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.z) / dotDir;
		float t2 = (dotDelta + boxMax.z) / dotDir;

		if (t1 > t2) { //makes sure that t1 is the min and t2 is max, if they aren't then swap them
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else { //teacher question
		if (-dotDelta + boxMin.z > 0.0f || -dotDelta + boxMax.z < 0.0f) {
			return false;
		}
	}

	ray_->intersectionDist = tMin;
	return true;
}
