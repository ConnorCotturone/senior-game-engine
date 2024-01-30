#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuseMap;       // diffuse lighting map (texture)
    sampler2D specularMap;      // specular lighting map (texture)

    vec3 diffuseColor;
    vec3 specularColor;

    float shininess;

    bool useDiffuseMap;     // [flag] use diffuse texture (if not - diffuseColor)
    bool useSpecularMap;    // [flag] use specular texture (if not - specularColor)
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    vec3 ambient = light.ambient * (material.useDiffuseMap ? texture(material.diffuseMap, TexCoords).rgb : material.diffuseColor);

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * (material.useDiffuseMap ? texture(material.diffuseMap, TexCoords).rgb : material.diffuseColor);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * (material.useSpecularMap ? texture(material.specularMap, TexCoords).rgb : material.specularColor);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}