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
//		static bool	GetPless		( int nKey						);//�L�[�{�[�h�Q�b�g�֐�
//		static bool	GetRepeat	( int nKey						);//���s�[�g�Q�b�g
//		static bool	GetTrigger	( int nKey						);//�g���K�[�Q�b�g
//		static bool	GetRelease	( int nKey						);
//
//	private:
//		LPDIRECTINPUTDEVICE8	m_pDIDevKeyboard;//���̓f�o�C�X�ւ̃|�C���^(�L�[�{�[�h)
//		static BYTE		m_aKeyState[256]					;//�L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
//		static BYTE		m_aKeyStateTrigger	[256]	;//�L�[�g���K�[
//		static BYTE		m_aKeyStateRelease	[256]	;//�L�[�����[�X
//		static BYTE		m_aKeyStateRepeat	[256]	;//�L�[���s�[�g
//					int		m_KeyTimeCnt[256]				;//�L�[�̃t���[���̃J�E���^�[
//
//};
//// End of file