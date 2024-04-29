#version 430 core

layout(location = 0) in vec3 s_normal;
layout(location = 1) in int id;
layout(std430, binding = 1) buffer velocityBuffer { vec4 velocity[]; };

layout(location = 0) out vec4 out_color;

void main() {
    vec3 normal = s_normal / s_normal.z;
    float radius = 1.0f - dot(normal.xy, normal.xy);
    if(radius < 0.0f) discard;
    normal.z = sqrt(radius);

    // roughly color particles based on velocity
    float magnitude = length(velocity[id])/5.0f;
    float B = abs(magnitude * 5.0 - 3.0) - 1.0;
    float G = 2.0 - abs(magnitude * 5.0 - 2.0);
    float R = 2.0 - abs(magnitude * 5.0 - 4.0);

    out_color = vec4(normal.z * 0.1f + pow(normal.z, 4.0f) * 0.25f + 0.25f) + vec4(vec3(R,G,B)/3.0f, 1.0f);
}
