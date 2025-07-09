// CPU‑side vertex struct for reference only
// struct Vertex
// {
//     float3 position;
//     float3 normal;   // Ignored
//     float2 texCoord; // Ignored
// };
// --------------------------------------------

// ───── Uniforms ─────────────────────────────
//  * b0, space0 for D3D12
//  * set = 0, binding = 0 for Vulkan via the
//    [[vk::binding]] attribute.

#ifdef VULKAN
[[vk::binding(0, 0)]]
#endif
cbuffer Globals : register(b0, space0)
{
    float4 uColour;          // RGBA, linear space
}

// ───── Vertex I/O ───────────────────────────
struct VSIn
{
    float3 position : POSITION;
    float3 normal   : NORMAL;     // Unused
    float2 texCoord : TEXCOORD0;  // Unused
};

struct VSOut
{
    float4 position : SV_Position;
};

// ───── Vertex Shader ────────────────────────
[shader("vertex")]
VSOut VSMain(VSIn v)
{
    VSOut o;

    // No projection: assume incoming coordinates
    // are already in clip‑space (−1…1).  Just add w.
    o.position = float4(v.position, 1.0);

    return o;
}

// ───── Pixel / Fragment Shader ──────────────
[shader("pixel")]
float4 PSMain(VSOut i) : SV_Target0
{
    // Solid colour from the uniform buffer
    return uColour;
}
