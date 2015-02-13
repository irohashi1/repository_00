//----------------------------------------------------------------
// shader.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "shader.h"
#include "windowBace.h"

//----------------------------------------------------------------
// CreateInstance
//----------------------------------------------------------------
Shader11* Shader11::CreateInstance(ID3D11Device*device)
{
	Shader11* instance = new Shader11;

	instance->_d3DDevice = device;
	
	instance->Init();
	return instance;
}

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
Shader11::Shader11(){}
Shader11::~Shader11(){}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void Shader11::Init()
{
	HRESULT hr = S_OK;

	// シェーダコンパイル
	ID3DBlob* errorBlob = NULL;
	ID3DBlob* shBlob = NULL;
	if (FAILED(Compile(errorBlob, shBlob, "Sources/Fx/tessellation.hlsl", "VertexShaderPolygon", "vs_5_0")))
	{
		WindowBace::_windowMain->CallMessageBox(true, "Shader compile err", "Err", MB_ICONSTOP);
	}
	_d3DDevice->CreateVertexShader(shBlob->GetBufferPointer(), shBlob->GetBufferSize(), NULL, &_vertexShader);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	if (FAILED(_d3DDevice->CreateInputLayout(layout,
		numElements,
		shBlob->GetBufferPointer(),
		shBlob->GetBufferSize(),
		&_vertexLayout)))
	{
		WindowBace::_windowMain->CallMessageBox(true, (char*)errorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR);
	}

	// ピクセルシェーダコンパイル・生成
	if (FAILED(Compile(errorBlob, shBlob, "Sources/Fx/tessellation.hlsl", "PixelShaderPolygon", "ps_5_0")))
	{
		WindowBace::_windowMain->CallMessageBox(true, "Shader compile err", "Err", MB_ICONSTOP);
	}
	_d3DDevice->CreatePixelShader(shBlob->GetBufferPointer(), shBlob->GetBufferSize(), NULL, &_pixelShader);
	
	// ハルシェーダー コンパイル・生成
	if (FAILED(Compile(errorBlob, shBlob, "Sources/Fx/tessellation.hlsl", "HullShaderPolygon", "hs_5_0")))
	{
		WindowBace::_windowMain->CallMessageBox(true, "Shader compile err", "Err", MB_ICONSTOP);
	}
	_d3DDevice->CreateHullShader(shBlob->GetBufferPointer(), shBlob->GetBufferSize(), NULL, &_hullShader);

	// ドメインシェーダー コンパイル・生成
	if (FAILED(Compile(errorBlob, shBlob, "Sources/Fx/tessellation.hlsl", "DomainShaderPolygon", "ds_5_0")))
	{
		WindowBace::_windowMain->CallMessageBox(true, "Shader compile err", "Err", MB_ICONSTOP);
	}
	_d3DDevice->CreateDomainShader(shBlob->GetBufferPointer(), shBlob->GetBufferSize(), NULL, &_domainShader);
	
	errorBlob->Release();
	shBlob->Release();

	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	if (FAILED(_d3DDevice->CreateBuffer(&hBufferDesc, NULL, &_constantBuffer)))
	{
		WindowBace::_windowMain->CallMessageBox(true, "Create ConstantBuffer", "Err", MB_ICONSTOP);
	}
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void Shader11::Uninit()
{
	if (_vertexLayout) _vertexLayout->Release();
	if (_vertexShader) _vertexShader->Release();
	if (_pixelShader) _pixelShader->Release();
	if (_hullShader) _hullShader->Release();
	if (_domainShader) _domainShader->Release();
}

//----------------------------------------------------------------
// SetShader
//----------------------------------------------------------------
void Shader11::SetShader(ID3D11DeviceContext* immediateContext, bool onVertex, bool onPixel)
{
	// 入力レイアウト設定
	immediateContext->IASetInputLayout(_vertexLayout);

	// シェーダ設定
	immediateContext->VSSetShader(_vertexShader, NULL, 0);
	immediateContext->PSSetShader(_pixelShader, NULL, 0);
	immediateContext->HSSetShader(_hullShader, NULL, 0);
	immediateContext->DSSetShader(_domainShader, NULL, 0);
}

//----------------------------------------------------------------
// SetShader
//----------------------------------------------------------------
void Shader11::SetConstantBuffer(ID3D11DeviceContext* immediateContext)
{
	// マトリクス設定
	XMMATRIX world, view, projection, worldViewProjection;
	world = XMMatrixIdentity();
	view = XMMatrixLookAtLH(XMVectorSet(0.0f, 10.0f, -20.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	projection = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.0f, 100.0f);
	worldViewProjection = world * view * projection;

	// ライトの逆行列変換
	XMMATRIX invWorld;
	XMVECTOR det, lightDir, invLightDir;
	invWorld = XMMatrixInverse(&det, world);
	lightDir = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	invLightDir = XMVector3Transform(lightDir, invWorld);

	// Constant buffer set
	ConstantBuffer cb;
	cb.invLightDirection = invLightDir;
	cb.WorldViewProjection = XMMatrixTranspose(worldViewProjection);
	immediateContext->UpdateSubresource(_constantBuffer, 0, NULL, &cb, 0, 0);
	immediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
	immediateContext->DSSetConstantBuffers(0, 1, &_constantBuffer);
}

//----------------------------------------------------------------
// SetShader
//----------------------------------------------------------------
void Shader11::UnSetShader(ID3D11DeviceContext* immediateContext)
{
	// 入力レイアウト設定
	immediateContext->IASetInputLayout(NULL);

	// シェーダ設定
	immediateContext->VSSetShader(NULL, NULL, 0);
	immediateContext->PSSetShader(NULL, NULL, 0);
}

//----------------------------------------------------------------
// CompileVs
//----------------------------------------------------------------
HRESULT Shader11::Compile(ID3DBlob* errBlob, ID3DBlob* shBlob, char* filePath, char* methodName, char* modeName)
{
	HRESULT hr = S_OK;

	hr = D3DX11CompileFromFile(filePath, NULL, NULL, methodName, modeName, D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &shBlob, &errBlob, NULL);
	if (FAILED(hr))
	{
		WindowBace::_windowMain->CallMessageBox(true, (char*)errBlob->GetBufferPointer(), modeName, MB_OK | MB_ICONERROR);
	}
	return hr;
}

// End of file