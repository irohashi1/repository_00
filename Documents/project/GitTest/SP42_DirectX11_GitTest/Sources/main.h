//----------------------------------------------------------------
// main.h
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#pragma once

//----------------------------------------------------------------
// Include files
//----------------------------------------------------------------
#include <windows.h>
#include "common.h"

//----------------------------------------------------------------
// Front reference
//----------------------------------------------------------------
class DirectX11Bace;
class Game11Base;

//----------------------------------------------------------------
// Class
//----------------------------------------------------------------
class AppMain
{
public :
	AppMain();
	~AppMain();
	void Init();
	void Uninit();
	void Process();

	static AppMain* CreateInstance();
private:
	DirectX11Bace* _directx11Bace;
	Game11Base* _game11Base;
};

// End of file