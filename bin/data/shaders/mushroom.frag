#version 150

uniform vec3 lightPosition;

in vec4 vertColor;
in vec3 vertNormal;
in vec3 vertPosition;

out vec4 outputColor;

void main() {
    vec3 lightDir = normalize(lightPosition - vertPosition);
    vec3 normal = normalize(vertNormal);
    
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vertColor.rgb;
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vertColor.rgb;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-vertPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0);
    
    // Final color
    vec3 result = ambient + diffuse + specular;
    outputColor = vec4(result, 1.0);
}