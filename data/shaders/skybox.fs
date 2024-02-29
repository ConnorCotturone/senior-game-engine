// Copyright © 2024 Jacob Curlin
// source: (learnOpenGL:Cubemaps) https://learnopengl.com/Advanced-OpenGL/Cubemaps

#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
}