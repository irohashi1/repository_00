//----------------------------------------------------------------
// polygon3d_11.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "common.h"
#include "directx11bace.h"

//----------------------------------------------------------------
// Front reference
//----------------------------------------------------------------
class Shader11;

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class Polygon3d_11
{
public:
	Polygon3d_11();
	virtual ~Polygon3d_11();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	static Polygon3d_11* CreateInstance(ID3D11Device* d3dDevice, ID3D11DeviceContext* immediateContext, Shader11 * shader11, char* imagePath);
protected:
	Shader11 *									_shader11;
	ID3D11ShaderResourceView*	_shaderResView;
	ID3D11Device*							_d3dDevice;
	ID3D11DeviceContext*				_immediateContext;
	ID3D11Buffer*							_vertexBuffer;
	char* _imagePath;
};

// End of file