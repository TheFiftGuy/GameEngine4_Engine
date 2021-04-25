#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include  <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

struct BoundingBox {
	vec3 maxVert, minVert;
	mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = vec3();
		transform = mat4();
	}

	inline BoundingBox(vec3 maxVert_, vec3 minVert_, mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		vec3 minCorner = GetTransformedPoint(minVert, transform);
		vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		//add collision detection
		
		return true;
	}


private:
	inline vec3 GetTransformedPoint(vec3 point_, mat4 transform_) {
		return vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};




#endif
