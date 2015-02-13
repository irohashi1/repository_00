//----------------------------------------------------------------
// renderer11.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "common.h"
#include "directx11bace.h"

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class Renderer11
{
public:
	Renderer11();
	~Renderer11();
	void Init(ID3D11Device*device, ID3D11DeviceContext* immediateContext, IDXGISwapChain*_swapChain);
	void Uninit();
	void Draw(ID3D11DeviceContext* immediateContext, IDXGISwapChain*swapChain);

	static  Renderer11* CreateInstance(ID3D11Device*device, ID3D11DeviceContext* immediateContext, IDXGISwapChain*swapChain);

	ID3D11RenderTargetView* GetRendererTargetView(){ return _renderTargetView; };
private:
	ID3D11RenderTargetView* _renderTargetView;
};

// End of file