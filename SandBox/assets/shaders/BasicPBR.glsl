#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec3 v_WorldPos;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    v_TexCoord = a_TexCoord;
    vec4 worldPosition = u_Transform * vec4(a_Position, 1.0);
    v_WorldPos = worldPosition.xyz;
    gl_Position = u_ViewProjection * worldPosition;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 v_WorldPos;

uniform sampler2D u_Texture;
uniform vec3 u_CameraPos;
uniform float u_Metallic;
uniform float u_Roughness;
uniform float u_AO;

void main()
{
    vec3 albedo = texture(u_Texture, v_TexCoord).rgb;
    vec3 V = normalize(u_CameraPos - v_WorldPos);
    float fresnel = pow(1.0 - max(dot(normalize(vec3(0, 0, 1)), V), 0.0), 5.0);
    vec3 F0 = mix(vec3(0.04), albedo, u_Metallic);
    vec3 fresnelTerm = F0 + (1.0 - F0) * fresnel;

    vec3 ambient = albedo * 0.2 * u_AO;
    vec3 color = ambient + fresnelTerm;

    FragColor = vec4(color, 1.0);
}