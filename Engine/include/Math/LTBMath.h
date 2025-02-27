#pragma once

#include <glm/glm.hpp>

namespace LTB::Math {

	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	Matrix GetTransformMatrix(Vector3 position, Quaternion rotation, Vector3 scale);
	void MatrixDecompose(Matrix mat, Vector3 *outTranslation, Quaternion *outRotation, Vector3 *outScale);

}