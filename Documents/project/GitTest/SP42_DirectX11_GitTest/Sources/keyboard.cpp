////----------------------------------------------------------------
//// keyboard.cpp
//// Author : Kazuki Kagohashi
////----------------------------------------------------------------
//
////----------------------------------------------------------------
//// Include files
////----------------------------------------------------------------
//#include "input.h"
//#include "keyboard.h"
//
////----------------------------------------------------------------
//// Global properties
////----------------------------------------------------------------
//BYTE	CKeyboard :: m_aKeyState[ 256 ];
//BYTE	CKeyboard :: m_aKeyStateTrigger[ 256 ];
//BYTE	CKeyboard :: m_aKeyStateRelease[ 256 ];
//BYTE	CKeyboard :: m_aKeyStateRepeat[ 256 ];
//
////===============================================================
////CKeyboardコンストラクタ
////引数：無し　戻り値：無し
////===============================================================
//CKeyboard :: CKeyboard(){}
//
//
////===============================================================
////CKeyboardデストラクタ
////引数：無し　戻り値：無し
////===============================================================
//CKeyboard :: ~CKeyboard()
//{
//}
//
//
////===============================================================
////CKeyboard初期化
////引数：無し　戻り値：無し
////===============================================================
//HRESULT CKeyboard :: Init( HINSTANCE hInstance , HWND hWnd )
//{
//
//	HRESULT hr;
//	CInput :: Init ( hInstance , hWnd );
//
//	hr = m_pDInput -> CreateDevice( GUID_SysKeyboard , &m_pDIDevKeyboard , NULL );
//	if( FAILED(hr) )
//	{
//		//キーボードがねえ
//		return hr;
//	}
//
//	//データフォーマットの設定
//	hr = m_pDIDevKeyboard -> SetDataFormat( &c_dfDIKeyboard );
//	if( FAILED(hr) )
//	{
//		//データフォーマット設定できねえ
//		return hr;
//	}
//
//	//協調モードの設定
//	hr = m_pDIDevKeyboard ->SetCooperativeLevel( hWnd , DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
//	if( FAILED(hr) )
//	{
//		//協調モード設定できねえ
//
//		return 0;
//	}
//
//	for( int nCnt = 0 ; nCnt < 256 ; nCnt ++ )
//	{
//		m_KeyTimeCnt[ nCnt ] = 0;
//	}
//
//	//キーボードへのアクセス権を取得(入力制御開始)
//	m_pDIDevKeyboard -> Acquire();
//	return S_OK;
//}
//
//
////===============================================================
////CKeyboard終了
////引数：無し　戻り値：無し
////===============================================================
//void CKeyboard :: Uninit()
//{
//
//	if( m_pDIDevKeyboard != NULL )
//	{
//
//		//キーボードのアクセス権を解放
//		m_pDIDevKeyboard -> Unacquire();
//		m_pDIDevKeyboard -> Release();
//		m_pDIDevKeyboard = NULL;
//
//	}
//
//	CInput :: Uninit();
//
//	delete this;
//}
//
//
////===============================================================
////CKeyboard更新
////引数：無し　戻り値：無し
////===============================================================
//HRESULT CKeyboard :: Update( )
//{
//
//	BYTE aKeyState[256];
//
//	//デバイスからキーボード情報を取得
//	if( SUCCEEDED( m_pDIDevKeyboard -> GetDeviceState( sizeof( aKeyState ) , &aKeyState[0] ) ) )//ここまで生データ
//	{
//		for( int nCntKey = 0 ; nCntKey < 256 ; nCntKey ++ )
//		{
//			//キートリガー
//			m_aKeyStateTrigger[nCntKey] = ( aKeyState[nCntKey] ^ m_aKeyState[nCntKey] ) & aKeyState[nCntKey];
//
//			//押している間
//			if( aKeyState[nCntKey] )
//			{
//				m_KeyTimeCnt[nCntKey] ++;
//			}
//			else
//			{
//				m_KeyTimeCnt[nCntKey] = 0;
//			}
//
//			//キーリリース
//			m_aKeyStateRelease[nCntKey]	= ( m_aKeyState[nCntKey] ^ aKeyState[nCntKey] ) & m_aKeyState[nCntKey] ;
//
//			
//			//キーリピート
//			if( ( m_KeyTimeCnt[nCntKey] == 1 ) || ( m_KeyTimeCnt[nCntKey] > 20 )  )
//			{
//				m_aKeyStateRepeat[nCntKey] = 0x80;
//			}
//			else
//			{
//				m_aKeyStateRepeat[nCntKey] = 0x00;
//			}
//
//			m_aKeyState[nCntKey] = aKeyState[nCntKey];
//		}
//	}
//	else
//	{
//		m_pDIDevKeyboard -> Acquire();
//	}
//
//	return S_OK;
//}
//
//
////===============================================================
////Key取得
////引数：int　戻り値：bool
////===============================================================
//bool CKeyboard :: GetPless( int nKey	 )
//{
//	return	( m_aKeyState[nKey]&0x80 ) ? true : false;
//}
//bool CKeyboard :: GetRepeat( int nKey	 )
//{
//	return	( m_aKeyStateRepeat[nKey]&0x80 ) ? true : false;
//}
//bool CKeyboard :: GetTrigger( int nKey	 )
//{
//	return	( m_aKeyStateTrigger[nKey]&0x80 ) ? true : false;
//}
//bool CKeyboard :: GetRelease( int nKey	 )
//{
//	return	( m_aKeyStateRelease[nKey]&0x80 ) ? true : false;
//}