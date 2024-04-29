#version 430 core

layout(location = 0) in vec3 s_normal;

layout(location = 0) out vec4 out_color;

void main() {

    vec3 normal = s_normal / s_normal.z;
    float radius = 1.0f - dot(normal.xy, normal.xy);
    if(radius < 0.0f) discard;
    normal.z = sqrt(radius);

    out_color = vec4(normal.z * 0.5f + pow(normal.z, 4.0f) * 0.25f + 0.25f);
}
