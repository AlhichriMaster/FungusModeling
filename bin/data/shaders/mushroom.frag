#version 150

uniform float time;
uniform vec2 resolution;

in vec4 vertColor;
in vec3 vertNormal;
in vec2 vertTexCoord;

out vec4 outputColor;

void main() {
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    float diff = max(dot(vertNormal, lightDir), 0.0);
    outputColor = vertColor * (diff * 0.7 + 0.3);
}