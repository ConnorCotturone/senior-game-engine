// Copyright © 2024 Jacob Curlin

#include "render/camera.h"

namespace cgx::render
{

    Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : m_position(position)
        , m_up(up)
        , m_yaw(yaw)
        , m_pitch(pitch)
    {
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void Camera::KeyboardUpdate(Camera_Movement direction, double deltaTime)
    {
        float velocity = m_movement_speed * static_cast<float>(deltaTime);
        if (direction == kForward)
            m_position += m_front * velocity;
        if (direction == kBackward)
            m_position -= m_front * velocity;
        if (direction == kLeft)
            m_position -= m_right * velocity;
        if (direction == kRight)
            m_position += m_right * velocity;
    }

    void Camera::MouseUpdate(double x_offset, double y_offset, GLboolean constrain_pitch = true)
    {
        m_yaw     += static_cast<float>(x_offset * m_mouse_sensitivity);
        m_pitch   += static_cast<float>(y_offset * m_mouse_sensitivity);

        if (constrain_pitch)
        {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }

        updateCameraVectors();
    }
        
    void Camera::updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_world_up));
        m_up    = glm::normalize(glm::cross(m_right, m_front));
    }

}