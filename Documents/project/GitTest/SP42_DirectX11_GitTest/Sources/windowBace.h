//----------------------------------------------------------------
// windowBace.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include "common.h"

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class WindowBace
{
public:
	WindowBace();
	~WindowBace();
	void Init();
	void Uninit();
	bool Update();

	static WindowBace * CreateInstance(char* windowName, char* className);
	void EntryWindow();
	
	void BeginWindow();
	
	// Getter
	HINSTANCE* GetHInstance(){ return &_hInstance; };
	WNDCLASSEX* GetWcex(){ return &_wcex; };
	HWND* GetHWnd(){ return &_hWnd; };
	MSG* GetMsg(){ return &_msg; };

	void CallMessageBox(bool onHWnd, char* text, char* caption, UINT type);

	static WindowBace* _windowMain;
	static HINSTANCE _hInstance;
	static int _cmdShow;
private:
	char * _windowName;
	char * _className;
	WNDCLASSEX _wcex;
	HWND _hWnd;
	MSG _msg;
};

// End of file