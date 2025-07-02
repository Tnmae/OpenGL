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

vec4 pointLight() {
    vec3 vec = lightPos - crntPos;
    float distance = length(vec);
    float a = 0.30f;
    float b = 0.70f;
    float inten = 1 / (a * distance * distance + b * distance);

    float ambient = 0.20f;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specularLight * specAmount;

    return (texture(diffuse0, TexCoords) * (distance * inten + ambient) + texture(specular0, TexCoords).r * specular * inten) * lightColor;
}

vec4 directLight() {
    float ambient = 0.20f;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specularLight * specAmount;

    return (texture(diffuse0, TexCoords) * (diffuse + ambient) + texture(specular0, TexCoords).r * specular) * lightColor;
}

vec4 spotLight() {
    float innerCone = 0.95f;
    float outerCone = 0.90f;

    float ambient = 0.20f;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specularLight * specAmount;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, TexCoords) * (diffuse * inten + ambient) +
        texture(specular0, TexCoords).r * specular * inten) * lightColor;
}

void main()
{
    FragColor = pointLight();
}
