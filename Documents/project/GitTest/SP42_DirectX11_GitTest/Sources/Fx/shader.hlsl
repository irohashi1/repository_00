//----------------------------------------------------------------
// shader.hlsl
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
struct VI_POLYGON
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};
struct VO_POLYGON
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};
// Method
void VertexShaderPolygon(in VI_POLYGON inParam,out VO_POLYGON outParam)
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

// Method
void PixelShaderPolygon(
	in float4 inPosition : POSITION0,
	out float4 outDiffuse : SV_Target,
	in float2 inTexCoord : TEXCOORD)
{
	outDiffuse = g_texture.Sample(g_samplerState, inTexCoord);
}