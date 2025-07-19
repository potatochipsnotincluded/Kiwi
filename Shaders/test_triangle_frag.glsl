#version 460 core

out vec4 FragColor;

uniform sampler2D u_AlbedoMap;

uniform vec3 u_SunPosition; // World-space position of sun
uniform vec3 u_SunColour;
uniform float u_Ambient;

uniform float u_Metallic;    
uniform float u_Roughness;

in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal;

const float PI = 3.14159265359;

// GGX Normal Distribution Function
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return a2 / denom;
}

// Schlick-GGX Geometry Function
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    float denom = NdotV * (1.0 - k) + k;
    return NdotV / denom;
}

// Smith Geometry Function
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    return GeometrySchlickGGX(NdotV, roughness) * GeometrySchlickGGX(NdotL, roughness);
}

// Fresnel Schlick Approximation
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 getNormal()
{
    return normalize(v_Normal);
}

void main()
{
    vec3 N = getNormal();
    vec3 V = normalize(-v_FragPos); // View direction assuming camera at origin

    vec3 albedo = pow(texture(u_AlbedoMap, v_TexCoord).rgb, vec3(2.2)); // sRGB to linear

    // Reflectance at normal incidence
    vec3 F0 = mix(vec3(0.04), albedo, u_Metallic);

    // Light direction from sun to origin
    vec3 L = normalize(vec3(0.0) - u_SunPosition);
    vec3 H = normalize(V + L);

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, u_Roughness);
    float G   = GeometrySmith(N, V, L, u_Roughness);
    vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 1e-5;
    vec3 specular     = numerator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - u_Metallic;

    float NdotL = max(dot(N, L), 0.0);
    vec3 diffuse = (albedo / PI);

    vec3 radiance = u_SunColour;

    vec3 colour = (kD * diffuse + specular) * radiance * NdotL;

    vec3 mbient = u_Ambient * albedo * (1.0 - u_Metallic);
    colour += mbient;

    // Gamma correction
    colour = pow(colour, vec3(1.0 / 2.2));

    FragColor = vec4(colour, 1.0);
}
