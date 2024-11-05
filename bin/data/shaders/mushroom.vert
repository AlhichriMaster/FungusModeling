#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

out vec4 vertColor;
out vec3 vertNormal;
out vec3 vertPosition;

void main() {
    gl_Position = modelViewProjectionMatrix * position;
    vertColor = color;
    vertNormal = normalize((normalMatrix * normal).xyz);
    vertPosition = (modelViewMatrix * position).xyz;
}