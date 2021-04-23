#ifndef RAY_H
#define RAY_H

#include "BoundingBox.h"
#include "CollisionDetection.h"
using namespace  glm;

struct Ray {
	vec3 origin;
	vec3 direction;
	float intersectionDist;

	inline  Ray() {
		origin = vec3();
		direction = vec3();
		intersectionDist = 0.0f;
	}

	inline Ray(vec3 origin_, vec3 direction_) {
		origin = origin_;
		direction = direction_;
		intersectionDist = 0.0f;
	}

	inline Ray& operator =(const Ray& ray_) {
		origin = ray_.origin;
		direction = ray_.direction;
		intersectionDist = 0.0f;
	}

	inline bool isColliding(BoundingBox* box_) {
		intersectionDist = -1.0f;
		return CollisionDetection::RayObbIntersection(this, box_);
	}
	
};



#endif