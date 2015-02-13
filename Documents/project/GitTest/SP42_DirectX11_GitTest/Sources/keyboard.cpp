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
////CKeyboard�R���X�g���N�^
////�����F�����@�߂�l�F����
////===============================================================
//CKeyboard :: CKeyboard(){}
//
//
////===============================================================
////CKeyboard�f�X�g���N�^
////�����F�����@�߂�l�F����
////===============================================================
//CKeyboard :: ~CKeyboard()
//{
//}
//
//
////===============================================================
////CKeyboard������
////�����F�����@�߂�l�F����
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
//		//�L�[�{�[�h���˂�
//		return hr;
//	}
//
//	//�f�[�^�t�H�[�}�b�g�̐ݒ�
//	hr = m_pDIDevKeyboard -> SetDataFormat( &c_dfDIKeyboard );
//	if( FAILED(hr) )
//	{
//		//�f�[�^�t�H�[�}�b�g�ݒ�ł��˂�
//		return hr;
//	}
//
//	//�������[�h�̐ݒ�
//	hr = m_pDIDevKeyboard ->SetCooperativeLevel( hWnd , DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
//	if( FAILED(hr) )
//	{
//		//�������[�h�ݒ�ł��˂�
//
//		return 0;
//	}
//
//	for( int nCnt = 0 ; nCnt < 256 ; nCnt ++ )
//	{
//		m_KeyTimeCnt[ nCnt ] = 0;
//	}
//
//	//�L�[�{�[�h�ւ̃A�N�Z�X�����擾(���͐���J�n)
//	m_pDIDevKeyboard -> Acquire();
//	return S_OK;
//}
//
//
////===============================================================
////CKeyboard�I��
////�����F�����@�߂�l�F����
////===============================================================
//void CKeyboard :: Uninit()
//{
//
//	if( m_pDIDevKeyboard != NULL )
//	{
//
//		//�L�[�{�[�h�̃A�N�Z�X�������
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
////CKeyboard�X�V
////�����F�����@�߂�l�F����
////===============================================================
//HRESULT CKeyboard :: Update( )
//{
//
//	BYTE aKeyState[256];
//
//	//�f�o�C�X����L�[�{�[�h�����擾
//	if( SUCCEEDED( m_pDIDevKeyboard -> GetDeviceState( sizeof( aKeyState ) , &aKeyState[0] ) ) )//�����܂Ő��f�[�^
//	{
//		for( int nCntKey = 0 ; nCntKey < 256 ; nCntKey ++ )
//		{
//			//�L�[�g���K�[
//			m_aKeyStateTrigger[nCntKey] = ( aKeyState[nCntKey] ^ m_aKeyState[nCntKey] ) & aKeyState[nCntKey];
//
//			//�����Ă����
//			if( aKeyState[nCntKey] )
//			{
//				m_KeyTimeCnt[nCntKey] ++;
//			}
//			else
//			{
//				m_KeyTimeCnt[nCntKey] = 0;
//			}
//
//			//�L�[�����[�X
//			m_aKeyStateRelease[nCntKey]	= ( m_aKeyState[nCntKey] ^ aKeyState[nCntKey] ) & m_aKeyState[nCntKey] ;
//
//			
//			//�L�[���s�[�g
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
////Key�擾
////�����Fint�@�߂�l�Fbool
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