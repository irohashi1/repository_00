//----------------------------------------------------------------
// directx11bace.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

//----------------------------------------------------------------
// Link librarys
//----------------------------------------------------------------
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11d.lib")

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "common.h"
#include "polygon3d_11.h"

//----------------------------------------------------------------
// Front reference
//----------------------------------------------------------------
class Renderer11;
class Shader11;
class Polygon3d_11;

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class DirectX11Bace
{
public:
	DirectX11Bace();
	~DirectX11Bace();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Process();

	static  DirectX11Bace* CreateInstance(HWND hwnd);
private:
	Renderer11 *					_renderer11;
	Shader11 *						_shader11;
	HWND								_hwnd;
	ID3D11Device*				_d3DDevice;
	D3D_FEATURE_LEVEL		_featureLevel;
	ID3D11DeviceContext*	_immediateContext;
	IDXGISwapChain*			_swapChain;
	ID3D11InputLayout*		_vertexLayout;
	Polygon3d_11 *				_polygon3d;
};

// End of file