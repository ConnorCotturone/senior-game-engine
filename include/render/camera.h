// Copyright © 2024 Jacob Curlin
// source: (LearnOpenGL) https://learnopengl.com/Getting-started/Camera

#pragma once

#include "core/common.h"
#include "core/time.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace cgx::render
{

    enum Camera_Movement {
        kForward,
        kBackward,
        kLeft,
        kRight,
        kUp,
        kDown
    };

    constexpr float kYaw                = -90.0f;
    constexpr float kPitch              =   0.0f;
    constexpr float kMovementSpeed      =   2.5f;
    constexpr float kMouseSensitivity   =   0.1f;
    constexpr float kZoom               =  45.0f;

    class Camera 
    {
    public:
        
        explicit Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = kYaw,
            float pitch = kPitch
        );
        ~Camera() = default ;

        glm::mat4 GetViewMatrix();

        // nodiscard attribute encourages caller not to ignore return value
        [[nodiscard]] float getZoom() const { return m_zoom; }

        void KeyboardUpdate(Camera_Movement direction, double time_step);
        void MouseUpdate(double x_offset, double y_offset, GLboolean constrain_pitch);

    private:
        void updateCameraVectors();

        glm::vec3 m_position        = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_front           = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_up              = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_right           = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_world_up        = glm::vec3(0.0f, 1.0f, 0.0f);

        float m_yaw                 = kYaw;
        float m_pitch               = kPitch;
        float m_movement_speed      = kMovementSpeed;
        float m_mouse_sensitivity   = kMouseSensitivity;
        float m_zoom                = kZoom;
    };

}

