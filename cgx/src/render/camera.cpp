// jacob curlin
// camera.cpp
// 01/06/2023

#include "camera.h"

namespace cgx::graphics
{

    Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
        :   Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
            MovementSpeed(SPEED), 
            MouseSensitivity(SENSITIVITY), 
            Zoom(ZOOM) 
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();                
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Camera::KeyboardUpdate(Camera_Movement direction, double deltaTime)
    {
        float velocity = MovementSpeed * static_cast<float>(deltaTime);
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void Camera::MouseUpdate(double xoffset, double yoffset, GLboolean constrainPitch = true)
    {
        Yaw     += static_cast<float>(xoffset * MouseSensitivity);
        Pitch   += static_cast<float>(yoffset * MouseSensitivity);

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

        
    void Camera::updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }

}