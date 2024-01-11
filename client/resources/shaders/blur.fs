#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

// NOTE: Render size values must be passed from code
const float renderWidth = 800;
const float renderHeight = 450;

float offset[11] = float[](-10.0, -8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0);
float weight[11] = float[](0.003, 0.014, 0.045, 0.095, 0.150, 0.174, 0.150, 0.095, 0.045, 0.014, 0.003);

void main()
{
    // Texel color fetching from texture sampler
    vec3 texelColor = texture(texture0, fragTexCoord).rgb * weight[5];

    for (int i = 0; i < 11; i++)
    {
        texelColor += texture(texture0, fragTexCoord + vec2(offset[i]) / renderWidth, 0.0).rgb * weight[i];
        texelColor += texture(texture0, fragTexCoord - vec2(offset[i]) / renderWidth, 0.0).rgb * weight[i];
    }

    finalColor = vec4(texelColor, 1.0);
}
