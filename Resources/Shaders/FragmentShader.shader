#version 460 core

out vec4 FinalColor;
in vec3 aPos;
in vec2 TexCoord;
in vec3 aNormal;

uniform sampler2D Texture;
uniform vec3 LightLoc;
uniform vec3 LightColorLoc;
void main()
{
	vec3 lightDir = normalize(LightLoc - aPos);
	float LightFacingRatio = max(dot(lightDir, aNormal), 0.0);

	vec4 ColorOffset = vec4(LightColorLoc, 1);
	FinalColor = texture(Texture, TexCoord) * (LightFacingRatio + .5) * ColorOffset;
}