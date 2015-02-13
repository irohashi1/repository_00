//----------------------------------------------------------------
// polygon3d_11.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "polygon3d_11.h"
#include "main.h"
#include "shader.h"

//----------------------------------------------------------------
// Factory method
//----------------------------------------------------------------
Polygon3d_11* Polygon3d_11::CreateInstance(ID3D11Device* d3dDevice, ID3D11DeviceContext* immediateContext, Shader11 * shader11, char* imagePath)
{
	Polygon3d_11* instance = new Polygon3d_11;

	instance->_d3dDevice = d3dDevice;
	instance->_immediateContext = immediateContext;
	instance->_imagePath = imagePath;
	instance->_shader11 = shader11;

	instance->Init();
	return instance;
}

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
Polygon3d_11::Polygon3d_11()
{
	_d3dDevice = NULL;
	_immediateContext = NULL;
	_imagePath = NULL;
	_vertexBuffer = NULL;
	_imagePath = NULL;
}
Polygon3d_11::~Polygon3d_11()
{
}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void Polygon3d_11::Init()
{
	HRESULT hr = S_OK;

	// ���_�o�b�t�@����
	Vertex3D *vertex = new Vertex3D[4];

	vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex3D)* 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	hr = _d3dDevice->CreateBuffer(&bd, &sd, &_vertexBuffer);

	delete[] vertex;


	// �e�N�X�`������
	if (_imagePath)
	{
		D3DX11CreateShaderResourceViewFromFile(_d3dDevice,
			_imagePath,
			NULL,
			NULL,
			&_shaderResView,
			NULL);
	}

	// ���C���[�t���[��
	ID3D11RasterizerState* hpRasterizerState = NULL;
	D3D11_RASTERIZER_DESC hRasterizerDesc = {
		D3D11_FILL_WIREFRAME,// ���C���[�t���[��
		D3D11_CULL_NONE,	//�|���S���̗��\�𖳂���
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};
	if (FAILED(_d3dDevice->CreateRasterizerState(&hRasterizerDesc, &hpRasterizerState)))
	{
		return;
	}

	//���X�^���C�U�[���R���e�L�X�g�ɐݒ�
	_immediateContext->RSSetState(hpRasterizerState);
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void Polygon3d_11::Uninit()
{
	if (_vertexBuffer) _vertexBuffer->Release();
	delete this;
}

//----------------------------------------------------------------
// Update
//----------------------------------------------------------------
void Polygon3d_11::Update()
{
}

//----------------------------------------------------------------
// Draw
//----------------------------------------------------------------
void Polygon3d_11::Draw()
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	_immediateContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	// �v���~�e�B�u�^�C�v�ݒ�
	_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	// �V�F�[�_�[�Z�b�g
	_shader11->SetShader(_immediateContext, true, true);
	
	// �e�N�X�`���ݒ�
	_immediateContext->PSSetShaderResources(0, 1, &_shaderResView);

	// Constant buffer
	_shader11->SetConstantBuffer(_immediateContext);
	
	// �|���S���`��
	_immediateContext->Draw(4, 0);

	_shader11->UnSetShader(_immediateContext);
}

// End of file