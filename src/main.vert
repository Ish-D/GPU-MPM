#version 430 core

layout(location = 0) in vec4 in_position;

layout(std140, row_major, binding = 0) uniform CommonParameters {
    mat4 projection;
    mat4 modelview;
    float radius;
};

layout(location = 0) out vec3 s_normal;


void main() {

    vec4 position = vec4(in_position.xyz, 1.0f);
    gl_Position = projection * (modelview * position);

    uint index = gl_VertexIndex;
    vec2 texcoord = vec2(-1.0f, -1.0f);
    if(index >= 1u && index <= 2u) texcoord.x = 1.0f;
    if(index >= 2u) texcoord.y = 1.0f;

    vec2 size = vec2(projection[0].x, projection[1].y) * radius;
    gl_Position.xy += texcoord * size;

    s_normal = vec3(texcoord * size.x, size.x);
}