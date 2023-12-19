#version 330 core
in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D texture0;
uniform float glowIntensity;

void main()
{
    vec4 texColor = texture(texture0, fragTexCoord);
    finalColor = texColor * glowIntensity;
}
