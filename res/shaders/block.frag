#version 330 core
out vec4 FragColor;


uniform sampler2D texture1;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


void main()
{

    FragColor = texture2D(texture1, TexCoords);
}