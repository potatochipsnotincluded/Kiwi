#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float roughnessValue;   // 0.0 = shiny, 1.0 = rough
uniform float metallicValue;    // 0.0 = dielectric, 1.0 = metal

// Output fragment color
out vec4 finalColor;


#define     MAX_LIGHTS              4
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specularTotal = vec3(0.0);

    vec4 tint = colDiffuse * fragColor;

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
                light = -normalize(lights[i].target - lights[i].position);
            else if (lights[i].type == LIGHT_POINT)
                light = normalize(lights[i].position - fragPosition);

            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb * NdotL;

            // Calculate specular strength based on roughness (rough = less spec)
            float shininess = mix(64.0, 2.0, roughnessValue); // Shiny surface: 64, Rough: 2
            float specStrength = 1.0 - roughnessValue;

            float specCo = 0.0;
            if (NdotL > 0.0)
                specCo = pow(max(dot(viewD, reflect(-light, normal)), 0.0), shininess);

            specularTotal += lights[i].color.rgb * specCo * specStrength;
        }
    }

    // Metals reflect more light; non-metals reflect mostly diffuse
    vec3 diffuse = texelColor.rgb * tint.rgb * (1.0 - metallicValue);
    vec3 specular = specularTotal * mix(vec3(1.0), texelColor.rgb, metallicValue); // metals tint their reflections

    vec3 result = diffuse * lightDot + specular;
    result += texelColor.rgb * ambient.rgb * tint.rgb * 0.1;

    finalColor = vec4(result, texelColor.a);

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));
}
