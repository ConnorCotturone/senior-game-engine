// Copyright © 2024 Jacob Curlin

#include "render/camera.h"
#include "ecs/events/engine_events.h"

namespace cgx::render
{

    Camera::Camera(std::shared_ptr<cgx::input::InputManager> input_manager, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : m_input_manager(input_manager)
        , m_position(position)
        , m_up(up)
        , m_yaw(yaw)
        , m_pitch(pitch)
    {
        updateCameraVectors();
    }

    void Camera::Update(double dt)
    {
        if (m_manual_control_enabled)
        {
            double x_offset, y_offset;
            m_input_manager->getMouseOffset(x_offset, y_offset);
            Look(x_offset, y_offset, true);
            
            if (m_input_manager->isKeyPressed(cgx::input::Key::key_w)) { Translate(kForward, dt);  }
            if (m_input_manager->isKeyPressed(cgx::input::Key::key_s)) { Translate(kBackward, dt); }
            if (m_input_manager->isKeyPressed(cgx::input::Key::key_a)) { Translate(kLeft, dt);     }
            if (m_input_manager->isKeyPressed(cgx::input::Key::key_d)) { Translate(kRight, dt);    }
        }
        updateCameraVectors();
    }

    void Camera::Translate(TranslateDirection dir, double dt)
    {
        // CGX_TRACE("Camera::Translate [dir={}] [dt={}]", dir, dt);
        float velocity = m_movement_speed * static_cast<float>(dt);
        switch (dir) 
        {
            case kForward:
                m_position += m_front * velocity;
                break;
            case kBackward:
                m_position -= m_front * velocity;
                break;
            case kLeft:
                m_position -= m_right * velocity;
                break;
            case kRight:
                m_position += m_right * velocity;
                break;
            default:
                break;
        };
    }

    void Camera::Look(double x_offset, double y_offset, GLboolean constrain_pitch = true)
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

    void Camera::EnableManualControl()
    {
        m_manual_control_enabled = true;

        // extra pre-call to getMouseOffset to 'reset' the current offset created by mouse movements
        // while camera control disabled
        double x_offset, y_offset;
        m_input_manager->getMouseOffset(x_offset, y_offset); 
    }

    void Camera::DisableManualControl()
    {
        m_manual_control_enabled = false;
    }

}