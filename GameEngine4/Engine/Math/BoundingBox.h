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
};




#endif
