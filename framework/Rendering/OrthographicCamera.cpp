#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

OrthographicCamera::OrthographicCamera(
    const Frustrum& frustrum,
    const glm::vec3& position, 
    float rotation
) : CameraFrustrum(frustrum), Rotation(rotation) 
{
    RecalculateMatrix();
}

void OrthographicCamera::RecalculateMatrix()
{
    // update projection matrix
    ProjectionMatrix = glm::ortho(
        CameraFrustrum.left,
        CameraFrustrum.right,
        CameraFrustrum.bottom,
        CameraFrustrum.top,
        CameraFrustrum.near,
        CameraFrustrum.far
    );

    // update view matrix
    ViewMatrix = glm::mat4(1.f);
    ViewMatrix = glm::translate(ViewMatrix, Position);
    ViewMatrix = glm::rotate(
        ViewMatrix, 
        glm::radians(Rotation), 
        glm::vec3(0.f, 0.f, 1.f)
    );
}