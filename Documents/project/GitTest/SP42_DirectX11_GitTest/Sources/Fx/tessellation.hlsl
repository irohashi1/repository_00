//----------------------------------------------------------------
// tessellation.hlsl
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Constant buffer
//----------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
};

//----------------------------------------------------------------
// Struct
//----------------------------------------------------------------
struct VS_OUT
{
	float3 Position    : POSITION;
};

//----------------------------------------------------------------
// Vs method
//----------------------------------------------------------------
void VertexShaderPolygon( in float3 inPosition : POSITION0,
						  in float2 inTexCoord : TEXCOORD0,
						  out float3 outPosition : POSITION0 )
{
	outPosition = inPosition;
}

//----------------------------------------------------------------
// Hull shadder method
//----------------------------------------------------------------
void ConstantsHullShaderPolygon( out float outEdges[4] : SV_TessFactor,
								 out float outInside[2] : SV_InsideTessFactor )
{
	outEdges[0] = outEdges[1] = outEdges[2] = outEdges[3] = 5.0f;
	outInside[0] = outInside[1] = 5.0f;
}

//----------------------------------------------------------------
// ?
//----------------------------------------------------------------
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstantsHullShaderPolygon")]

//----------------------------------------------------------------
// Hull shadder method
//----------------------------------------------------------------
VS_OUT HullShaderPolygon(in InputPatch<VS_OUT, 4> inPatch,
						  in uint inID : SV_OutputControlPointID )
{
	return inPatch[inID];
}

//----------------------------------------------------------------
// ?
//----------------------------------------------------------------
[domain("quad")]

//----------------------------------------------------------------
// Domain shadder method
//----------------------------------------------------------------
void DomainShaderPolygon( in float inEdges[4] : SV_TessFactor,
							in float inInside[2] : SV_InsideTessFactor,
							in float2 inUV : SV_DomainLocation,
							in const OutputPatch<VS_OUT, 4> inPatch,
							out float4 outPosition : SV_POSITION )
{
  
	float3 p1 = lerp( inPatch[1].Position, inPatch[0].Position, inUV.x );
	float3 p2 = lerp( inPatch[3].Position, inPatch[2].Position, inUV.x );
	float3 position = lerp( p1, p2, inUV.y );
	
	outPosition =  mul( float4( position, 1.0f ), WorldViewProjection );

}

//----------------------------------------------------------------
// Ps method
//----------------------------------------------------------------
void PixelShaderPolygon( out float4 outDiffuse : SV_Target )
{
	outDiffuse = 1.0f;
}