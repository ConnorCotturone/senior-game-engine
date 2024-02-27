// Copyright © 2024 Jacob Curlin

#version 330 core
out vec4 FragColor;

#define AMBIENT_MAP_BIT 1
#define DIFFUSE_MAP_BIT 2
#define SPECULAR_MAP_BIT 4
#define NORMAL_MAP_BIT 8

struct Material {
    vec3 ambient_color;         // ambient base color 
    vec3 diffuse_color;         // diffuse base color
    vec3 specular_color;        // specular base color

    float shininess;            // shininess factor

    sampler2D ambient_map;      // ambient lighting map (texture)
    sampler2D diffuse_map;      // diffuse lighting map (texture)
    sampler2D specular_map;     // specular lighting map (texture)
    sampler2D normal_map;       // normal map (texture)

    int map_bitset;             // bitset indicating which maps are available
};

struct Light {
    vec3 position;              // position of light source

    vec3 ambient;               // strength factor of ambient lighting
    vec3 diffuse;               // strength factor of diffuse lighting
    vec3 specular;              // strength factor of specular lighting
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;            
uniform Material material;
uniform Light light;

void main()
{
    // ambient 
    vec3 ambient = light.ambient * ((material.map_bitset & DIFFUSE_MAP_BIT) != 0 ? texture(material.diffuse_map, TexCoords).rgb : material.diffuse_color);

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * ((material.map_bitset & DIFFUSE_MAP_BIT) != 0 ? texture(material.diffuse_map, TexCoords).rgb : material.diffuse_color);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * ((material.map_bitset & SPECULAR_MAP_BIT) != 0 ? texture(material.specular_map, TexCoords).rgb : material.specular_color);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}