//----------------------------------------------------------------
// renderer11.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "renderer11.h"

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
Renderer11::Renderer11(){}
Renderer11::~Renderer11(){}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void Renderer11::Init(ID3D11Device*device, ID3D11DeviceContext* immediateContext, IDXGISwapChain*swapChain)
{
	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, NULL, &_renderTargetView);
	pBackBuffer->Release();
	immediateContext->OMSetRenderTargets(1, &_renderTargetView, NULL);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	immediateContext->RSSetViewports(1, &vp);
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void Renderer11::Uninit()
{
	delete this;
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void Renderer11::Draw(ID3D11DeviceContext* immediateContext, IDXGISwapChain*swapChain)
{
	// バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	immediateContext->ClearRenderTargetView(_renderTargetView, ClearColor);

	// ポリゴン描画
	//g_polygon3d->Draw();

	// バックバッファ、フロントバッファ入れ替え
	swapChain->Present(0, 0);
}

//----------------------------------------------------------------
// CreateInstance
//----------------------------------------------------------------
Renderer11* Renderer11::CreateInstance(ID3D11Device*device, ID3D11DeviceContext* immediateContext, IDXGISwapChain*swapChain)
{
	Renderer11* instance = new Renderer11;
	instance->Init(device, immediateContext, swapChain);
	return instance;
}

// End of file