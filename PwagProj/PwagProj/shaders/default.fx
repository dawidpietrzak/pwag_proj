[engine::vertex_part]
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;


void main() {
	gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.0);
	FragPos = aPos;
	TexCoord = aTexCoord;
	Normal = aNormal;
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
