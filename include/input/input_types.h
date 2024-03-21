// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"

namespace cgx::input
{
    enum class Key
    {
        key_0,
        key_1,
        key_2,
        key_3,
        key_4,
        key_5,
        key_6,
        key_7,
        key_8,
        key_9,
        key_a,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,
        key_enter,
        key_escape,
        key_right,
        key_left,
        key_down,
        key_up,
        mouse_button_1,
        mouse_button_2,
        mouse_button_3,
        mouse_button_4,
        mouse_button_5,
        mouse_button_6,
        mouse_button_7,
        mouse_button_8,
        undefined_key
    };

    enum class KeyAction
    {
        press,
        release,
        undefined_key_action
    };

    struct KeyInput
    {
        Key key;
        KeyAction action;

        
    };
    
    enum class MouseAction
    {
        cursor,
        scroll,
        undefined_mouse_action
    };

    struct MouseInput
    {
        double x;
        double y;
        MouseAction action;
    };

    inline bool operator==(const KeyInput& lhs, const KeyInput& rhs)
    {
        return (lhs.key == rhs.key) && (lhs.action == rhs.action);
    }

    struct KeyInputHash
    {
        std::size_t operator()(const KeyInput& key_input) const
        {
            std::size_t h1 = std::hash<int>{}(static_cast<int>(key_input.key));
            std::size_t h2 = std::hash<int>{}(static_cast<int>(key_input.action));
            return h1 ^ (h2 << 1);
        }
    };

} // namespace cgx::input