[engine::vertex_part]
#version 330

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

void main() {
    TexCoords = aPos;
    vec4 pos = uProjectionMatrix * uViewMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

[engine::fragment_part]
#version 330

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube uTexture;

void main() {
    FragColor = texture(uTexture, TexCoords);
}
