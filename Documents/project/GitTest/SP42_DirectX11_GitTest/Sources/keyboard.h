////----------------------------------------------------------------
//// keyboard.h
//// Author : Kazuki Kagohashi
////----------------------------------------------------------------
//#pragma once
//
////----------------------------------------------------------------
//// Include files
////----------------------------------------------------------------
//#include	"input.h"
//
////----------------------------------------------------------------
//// Class[CInput]
////----------------------------------------------------------------
//class CKeyboard : public CInput
//{
//	public:
//		CKeyboard();
//		 ~CKeyboard();
//		 HRESULT Init( HINSTANCE hInstance , HWND hWnd );
//		 void Uninit( void );
//		 HRESULT Update( void );
//
//		static bool	GetPless		( int nKey						);//キーボードゲット関数
//		static bool	GetRepeat	( int nKey						);//リピートゲット
//		static bool	GetTrigger	( int nKey						);//トリガーゲット
//		static bool	GetRelease	( int nKey						);
//
//	private:
//		LPDIRECTINPUTDEVICE8	m_pDIDevKeyboard;//入力デバイスへのポインタ(キーボード)
//		static BYTE		m_aKeyState[256]					;//キーボードの状態を受け取るワーク
//		static BYTE		m_aKeyStateTrigger	[256]	;//キートリガー
//		static BYTE		m_aKeyStateRelease	[256]	;//キーリリース
//		static BYTE		m_aKeyStateRepeat	[256]	;//キーリピート
//					int		m_KeyTimeCnt[256]				;//キーのフレームのカウンター
//
//};
//// End of file