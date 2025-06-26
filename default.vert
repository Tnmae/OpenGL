#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTex;

uniform mat4 model;
uniform mat4 camMatrix;

out vec2 texCoord;

void main() {
  gl_Position = camMatrix * model * vec4(aPos, 1.0f);
  texCoord= aTex;
}
