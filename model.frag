#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 crntPos;
in vec3 Normal;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec4 lightColor;

void main()
{
    float ambient = 0.20f;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specularLight * specAmount;

    FragColor = (texture(diffuse0, TexCoords) * (diffuse + ambient) + texture(specular0, TexCoords).r * specular) * lightColor;
}
