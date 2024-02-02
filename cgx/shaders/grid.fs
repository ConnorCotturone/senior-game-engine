#version 330 core

in vec2 uv;
out vec4 fragColor;

uniform mat4 world_transform;
uniform float grid_size;
uniform float cell_size;
uniform vec4 thin_lines_color;
uniform vec4 thick_lines_color;

void main() {
    // Find screen-space derivatives of grid space.
    vec2 dudv = vec2(length(vec2(dFdx(uv.x), dFdy(uv.x))),
                     length(vec2(dFdx(uv.y), dFdy(uv.y))));

    // Define minimum number of pixels between cell lines before LOD switch should occur.
    const float min_pixels_between_cells = 1.0;

    // Calculate LOD level.
    float cs = cell_size;
    float lod_level = max(0.0, (log((length(dudv) * min_pixels_between_cells) / cs) / log(10.0)) + 1.0);
    float lod_fade = fract(lod_level);

    // Calculate cell sizes for lod0, lod1, and lod2.
    float lod0_cs = cs * pow(10.0, floor(lod_level));
    float lod1_cs = lod0_cs * 10.0;
    float lod2_cs = lod1_cs * 10.0;

    // Allow each anti-aliased line to cover up to 2 pixels.
    dudv *= 2.0;

    // Calculate unsigned distance to cell line center for each lod.
    vec2 lod0_cross_a = 1.0 - abs(clamp(mod(uv, lod0_cs) / dudv, -1.0, 1.0) * 2.0 - 1.0);
    float lod0_a = max(lod0_cross_a.x, lod0_cross_a.y);

    vec2 lod1_cross_a = 1.0 - abs(clamp(mod(uv, lod1_cs) / dudv, -1.0, 1.0) * 2.0 - 1.0);
    float lod1_a = max(lod1_cross_a.x, lod1_cross_a.y);

    vec2 lod2_cross_a = 1.0 - abs(clamp(mod(uv, lod2_cs) / dudv, -1.0, 1.0) * 2.0 - 1.0);
    float lod2_a = max(lod2_cross_a.x, lod2_cross_a.y);

    // Load sRGB colors from VisualGrid (converted into 0-1 range).
    vec4 thin_color = thin_lines_color;
    vec4 thick_color = thick_lines_color;

    // Blend between falloff colors to handle LOD transition.
    vec4 c = (lod2_a > 0.0) ? thick_color : (lod1_a > 0.0) ? mix(thick_color, thin_color, lod_fade) : thin_color;

    // Calculate opacity falloff based on distance to grid extents and gracing angle.
    vec3 view_dir = normalize(vec3(1.0, 0.0, 0.0)); // Replace with your input.view_dir if available.
    float op_gracing = 1.0 - pow(1.0 - abs(dot(view_dir, world_transform[0].xyz)), 16.0);
    float op_distance = (1.0 - clamp(length(uv) / grid_size, 0.0, 1.0));

    // Blend between LOD level alphas and scale with opacity falloff.
    c.a *= (lod2_a > 0.0) ? lod2_a : (lod1_a > 0.0) ? lod1_a : (lod0_a * (1.0 - lod_fade)) * op_gracing * op_distance;

    fragColor = c;
}
