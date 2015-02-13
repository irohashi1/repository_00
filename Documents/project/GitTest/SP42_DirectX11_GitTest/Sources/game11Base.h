//----------------------------------------------------------------
// game11Base.h
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
class Game11Base
{
public:
	Game11Base();
	~Game11Base();
	void Init();
	void Uninit();
	void Process();
	void Update();
	void Draw();
	
	static  Game11Base* CreateInstance();
private:
	
};

// End of file