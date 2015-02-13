//----------------------------------------------------------------
// shader.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "common.h"
#include "directx11bace.h"

//----------------------------------------------------------------
// Structs
//----------------------------------------------------------------
struct Vertex3D
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
};
struct ConstantBuffer
{
	XMMATRIX WorldViewProjection;
	XMVECTOR invLightDirection;
};

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class Shader11
{
public:
	Shader11();
	~Shader11();
	void Init();
	void Uninit();

	void SetShader(ID3D11DeviceContext* immediateContext, bool onVertex, bool onPixel);
	void SetConstantBuffer(ID3D11DeviceContext* immediateContext);
	void UnSetShader(ID3D11DeviceContext* immediateContext);

	static  Shader11* CreateInstance(ID3D11Device*device);

	// Compiler
	HRESULT Compile(ID3DBlob* errBlob, ID3DBlob* shBlob, char* filePath, char* methodName, char* modeName);	

	// Getter
	ID3D11VertexShader* GetShaderVertex(){ return _vertexShader; };
	ID3D11PixelShader* GetShaderPixel(){ return _pixelShader; };
	ID3D11InputLayout* GetVertexLayout(){ return _vertexLayout; };
	ID3D11VertexShader* GetVertexShader(){ return _vertexShader; };
	ID3D11Buffer* GetConstantBuffer(){ return _constantBuffer; };
	
private:
	ID3D11Device* _d3DDevice;
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	ID3D11HullShader* _hullShader;
	ID3D11DomainShader* _domainShader;
	ID3D11InputLayout* _vertexLayout;
	ID3D11Buffer* _constantBuffer;
};

// End of file