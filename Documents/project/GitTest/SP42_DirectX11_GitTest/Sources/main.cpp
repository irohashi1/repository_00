//----------------------------------------------------------------
// main.cpp
// Author : Kazuki Kagohashi
//----------------------------------------------------------------
#include "main.h"
#include "windowBace.h"
#include "directx11bace.h"
#include "game11Base.h"

//----------------------------------------------------------------
// CreateInstance
//----------------------------------------------------------------
AppMain* AppMain::CreateInstance()
{
	AppMain* instance = new AppMain();
	instance->Init();
	return instance;
}

//----------------------------------------------------------------
// Constructor,Destructor
//----------------------------------------------------------------
AppMain::AppMain()
{
	_directx11Bace = NULL;
}
AppMain::~AppMain(){}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------
void AppMain::Init()
{
	// DirectX11
	_directx11Bace = DirectX11Bace::CreateInstance(*WindowBace::_windowMain->GetHWnd());

	// Game
	_game11Base = Game11Base::CreateInstance();
}

//----------------------------------------------------------------
// Uninit
//----------------------------------------------------------------
void AppMain::Uninit()
{
	if (_game11Base) _game11Base->Uninit();
	if (_directx11Bace)_directx11Bace->Uninit();
	delete this;
}

//----------------------------------------------------------------
// Process
//----------------------------------------------------------------
void AppMain::Process()
{
	if (_directx11Bace)_directx11Bace->Process();
	if (_game11Base) _game11Base->Process();
}

// End of file