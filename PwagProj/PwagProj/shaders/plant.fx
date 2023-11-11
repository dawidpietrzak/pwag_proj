[engine::vertex_part]
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

layout(location = 3) in vec4 aTransformCol1;
layout(location = 4) in vec4 aTransformCol2;
layout(location = 5) in vec4 aTransformCol3;
layout(location = 6) in vec4 aTransformCol4;
layout(location = 7) in float aTopScale;
layout(location = 8) in float aBottomScale;
layout(location = 9) in float aLength;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;


void main() {
	mat4 transformMatrix = mat4(aTransformCol1, aTransformCol2, aTransformCol3, aTransformCol4);
	vec3 pos = aPos;
	if (pos.y > 0.5) {
		pos.x *= aTopScale;
		pos.z *= aTopScale;
	}
	else {
		pos.x *= aBottomScale;
		pos.z *= aBottomScale;
	}
	gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * transformMatrix * vec4(pos, 1.0);
	FragPos = pos;
	TexCoord = aTexCoord;

	mat3 normalMatrix = transpose(inverse(mat3(transformMatrix)));
	Normal = normalize(normalMatrix * aNormal);
}

[engine::fragment_part]
#version 330

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

vec3 lightPos = vec3(-15, 20, -15);

uniform sampler2D uTexture;

void main() {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.1);
	vec4 resultColor = texture(uTexture, TexCoord) * diff;
	FragColor = vec4(resultColor.xyz, 1);
}
