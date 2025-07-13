#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 crntPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;

void main()
{
    Normal = aNormal;
    crntPos = vec3(model * vec4(aPos, 1.0f));
    TexCoords = aTexCoords;
    gl_Position = view * vec4(crntPos, 1.0f);
}
