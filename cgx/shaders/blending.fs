// jacob curlin
// blending.fs
// 02/02/2024


out vec4 FragColor;

int vec2 TexCoords;

void main()
{
    vec4 texColor = texture(texture1, TexCoords);
    if (texColor.a < 0.1)
        discard;
    FragColor = texColor;
}