#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "PerspectiveCamera.h"
#include "logger.h"

PerspectiveCamera::PerspectiveCamera(
	const Frustrum& frustrum,
	const glm::vec3& position,
	const glm::vec3& lookAt,
	const glm::vec3& upVector
) : CameraFrustrum(frustrum), LookAt(lookAt), UpVector(upVector)
{
	SetPosition(position);
}

void PerspectiveCamera::RecalculateMatrix()
{
	ProjectionMatrix = glm::perspective(
		glm::radians(CameraFrustrum.angle),
		CameraFrustrum.width / CameraFrustrum.height,
		CameraFrustrum.near,
		CameraFrustrum.far
	);

	ViewMatrix = glm::lookAt(
		Position,
		LookAt, 
		UpVector
	);
	
	// Uncomment to change to left handed coordinates
	// ViewMatrix = glm::scale(ViewMatrix, glm::vec3(-1.0f, 1.0f, -1.0f));

	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}