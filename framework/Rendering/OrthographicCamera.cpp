#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(
    const Frustrum& frustrum = { -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f },
    const glm::vec3& position = glm::vec3(0.0f), 
    float rotation = 0.0f
)
    : CameraFrustrum(frustrum), Rotation(rotation) 
{

}

void OrthographicCamera::RecalculateMatrix()
{

}