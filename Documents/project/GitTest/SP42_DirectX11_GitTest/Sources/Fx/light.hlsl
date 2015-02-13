//----------------------------------------------------------------
// light.hlsl
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Constant buffer
//----------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix WorldViewProjection;
	float4 InvLightDirection;
}

//----------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------
//Struct
struct VI_LIGHT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
	float4 diffuse : COLOR0;
};
struct VO_LIGHT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float4 diffuse : COLOR0;
};
// Method
void VertexShaderLight(in VI_LIGHT inParam, out VO_LIGHT outParam)
{
	outParam.position = mul(inParam.position, WorldViewProjection);
	outParam.texCoord = inParam.texCoord;
}

//----------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------
// Global
Texture2D g_texture : register(t0);
SamplerState g_samplerState : register(s0);

//Struct
struct PI_LIGHT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
	float4 diffuse : COLOR0;
};
struct PO_LIGHT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float4 diffuse : SV;// ‚Ü‚¾
};

// Method
void PixelShaderLight(
	in float4 inPosition : POSITION0,
	out float4 outDiffuse : SV_Target,
	in float2 inTexCoord : TEXCOORD)
{
	outDiffuse = g_texture.Sample(g_samplerState, inTexCoord);
}