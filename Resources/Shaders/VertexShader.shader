#version 460 core

layout(location = 0) in vec3 AttribPos;
layout(location = 1) in vec2 AttribTexCoord;
layout(location = 2) in vec3 AttribNormal;
out vec2 TexCoord;
out vec3 aPos;
out vec3 aNormal;
uniform mat4 ModelMatrix;
uniform mat4 Projectmatrix;
uniform mat4 ViewMatrix;
void main()
{
	gl_Position = Projectmatrix*ViewMatrix*ModelMatrix * vec4(AttribPos, 1.0);
	aPos = AttribPos;
	TexCoord = AttribTexCoord;
	aNormal = mat3(ModelMatrix) *AttribNormal;
}