//----------------------------------------------------------------
// directx11bace.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "main.h"
#include "windowBace.h"

//----------------------------------------------------------------
// Gloval variables
//----------------------------------------------------------------
AppMain* g_appMain = NULL;

//----------------------------------------------------------------
// Static properties
//----------------------------------------------------------------
WindowBace* WindowBace::_windowMain = NULL;
HINSTANCE WindowBace::_hInstance = NULL;
int WindowBace::_cmdShow = 0;

//----------------------------------------------------------------
// Prototype method
//----------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//----------------------------------------------------------------
// Main loop
//----------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowBace::_hInstance = hInstance;
	WindowBace::_cmdShow = nCmdShow;
	
	// Main window����
	WindowBace::_windowMain = WindowBace::CreateInstance(CLASS_NAME, WINDOW_NAME);

	// Main application����
	g_appMain = AppMain::CreateInstance();

	// Message loop
	MSG *msg = WindowBace::_windowMain->GetMsg();
	while (true)
	{
		if (PeekMessage(msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (WindowBace::_windowMain->Update()) break;// �I���R�[���Ń��C�����[�v�𔲂���
		}
		else
		{
			if (g_appMain) g_appMain->Process();
		}
	}

	// �I������
	g_appMain->Uninit();
	WindowBace::_windowMain->Uninit();
	
	// Out
	return (int)msg->wParam;
}

//----------------------------------------------------------------
// CreateInstance
//----------------------------------------------------------------
WindowBace * WindowBace::CreateInstance(char* windowName, char* className)
{
	WindowBace * instance = new WindowBace();
	
	instance->_className = className;
	instance->_windowName = windowName;
	
	instance->Init();
	instance->BeginWindow();

	return instance;
}

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
WindowBace::WindowBace()
{
}
WindowBace::~WindowBace(){}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void WindowBace::Init()
{
	EntryWindow();
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void WindowBace::Uninit()
{
	UnregisterClass(_className, _wcex.hInstance);
	delete this;
}

//----------------------------------------------------------------
// Update
//----------------------------------------------------------------
bool WindowBace::Update()
{
	bool result = false;

	if (_msg.message == WM_QUIT)
	{
		result = true;
	}
	else
	{
		// ���b�Z�[�W�̖|��Ƒ��o
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
		result = false;
	}

	return result;
}

//----------------------------------------------------------------
// EntryWindow
//----------------------------------------------------------------
void WindowBace::EntryWindow()
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		_hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		_className,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	_hWnd = CreateWindowEx(0,
		_className,
		_windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		_hInstance,
		NULL);
}

//----------------------------------------------------------------
// CallMessageBox
//----------------------------------------------------------------
void WindowBace::CallMessageBox(bool onHWnd, char* text, char* caption, __in UINT type)
{
	HWND hWnd = NULL;
	if (onHWnd) hWnd = _hWnd;
	MessageBox(hWnd, text, caption, MB_OK | MB_ICONERROR);
}

//----------------------------------------------------------------
// ShowWindow
//----------------------------------------------------------------
void WindowBace::BeginWindow()
{
	ShowWindow(_hWnd, _cmdShow);
	UpdateWindow(_hWnd);
}

//----------------------------------------------------------------
// �E�C���h�E�v���V�[�W��
//----------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// End of file