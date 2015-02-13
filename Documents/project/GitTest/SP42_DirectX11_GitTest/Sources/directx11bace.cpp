//----------------------------------------------------------------
// directx11bace.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "directx11bace.h"
#include "renderer11.h"
#include "shader.h"

//----------------------------------------------------------------
// CreateInstance
//----------------------------------------------------------------
DirectX11Bace* DirectX11Bace::CreateInstance(HWND hwnd)
{
	DirectX11Bace* instance = new DirectX11Bace;
	instance->_hwnd = hwnd;
	instance->Init();
	return instance;
}

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
DirectX11Bace::DirectX11Bace()
{
	_hwnd = NULL;
	_d3DDevice = NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_immediateContext = NULL;
	_swapChain = NULL;
	_vertexLayout = NULL;
	_renderer11 = NULL;
}
DirectX11Bace::~DirectX11Bace(){}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void DirectX11Bace::Init()
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_WARP,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&_swapChain,
		&_d3DDevice,
		&_featureLevel,
		&_immediateContext);

	// Renderer set
	_renderer11 = Renderer11::CreateInstance(_d3DDevice, _immediateContext, _swapChain);

	// Shader
	_shader11 = Shader11::CreateInstance(_d3DDevice);

	// �|���S���̏���������
	_polygon3d = Polygon3d_11::CreateInstance(_d3DDevice, _immediateContext,_shader11, "Data/Image/water.jpg");
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void DirectX11Bace::Uninit()
{
	if (_immediateContext)_immediateContext->Release();
	if (_swapChain)_swapChain->Release();
	if (_vertexLayout)_vertexLayout->Release();
	if (_renderer11) _renderer11->Uninit();
	delete this;
}

//----------------------------------------------------------------
// Update
//----------------------------------------------------------------
void DirectX11Bace::Update(){}

//----------------------------------------------------------------
// Draw
//----------------------------------------------------------------
void DirectX11Bace::Draw()
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	_immediateContext->ClearRenderTargetView(_renderer11->GetRendererTargetView(), ClearColor);

	// �|���S���`��
	_polygon3d->Draw();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	_swapChain->Present(0, 0);
}

//----------------------------------------------------------------
// Process
//----------------------------------------------------------------
void DirectX11Bace::Process()
{
	Update();
	Draw();
}

// End of file