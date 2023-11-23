[engine::vertex_part]
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

uniform mat4 uLightProjectionMatrix;
uniform mat4 uLightViewMatrix;
uniform int uShadowPass;

out vec4 FragPos;
out vec2 TexCoord;
out vec3 Normal;
out vec4 FragPosLightSpace;

void main() {
	FragPos = uModelMatrix * vec4(aPos, 1);
	TexCoord = aTexCoord;
	Normal = aNormal;

	gl_Position = uProjectionMatrix * uViewMatrix * FragPos;
	if (uShadowPass == 0) {
		FragPosLightSpace = uLightProjectionMatrix * uLightViewMatrix * FragPos;
	}
}

[engine::fragment_part]
#version 330

in vec4 FragPos;
in vec2 TexCoord;
in vec3 Normal;
in vec4 FragPosLightSpace;

out vec4 FragColor;

uniform int uShadowPass;
uniform vec3 uLightPos;
uniform sampler2D uTexture;
uniform sampler2D uDepthTexture;

float shadowCalculation() {
	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	if (projCoords.z > 1.0)
		return 0.0;

	float closestDepth = texture(uDepthTexture, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float bias = 0.005;
	return currentDepth - bias > closestDepth ? 0.85 : 0.0;
}

void main() {
	if (uShadowPass == 0) {
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(uLightPos - FragPos.xyz);
		float diff = max(dot(norm, lightDir), 0.1);
		float shadow = shadowCalculation();

		vec4 ambientColor = vec4(1, 1, 1, 1);
		vec4 diffuseColor = texture(uTexture, TexCoord);

		vec4 resultColor = ambientColor * 0.05 + (1.0 - shadow) * diffuseColor * diff;
		FragColor = vec4(resultColor.xyz, 1);
	}
}
