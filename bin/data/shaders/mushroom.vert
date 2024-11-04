#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 normal;
in vec4 color;
in vec2 texcoord;

out vec4 vertColor;
out vec3 vertNormal;
out vec2 vertTexCoord;

void main() {
    gl_Position = modelViewProjectionMatrix * position;
    vertColor = color;
    vertNormal = normal.xyz;
    vertTexCoord = texcoord;
}