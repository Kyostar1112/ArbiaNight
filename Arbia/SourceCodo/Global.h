#ifndef _GLOBAL_H_	//�ݸٰ�޶ް��.
#define _GLOBAL_H_


//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//���KyoStar.
#define Inoue
//���[�h���.
#define START_LOADING_DISPLAY

//����.
#define Tahara


//============================================================
//	�ݸٰ��.
//============================================================
#include	<Windows.h>

#include	<D3DX11.h>
#include	<D3D11.h>

#include	<D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include	<D3D10.h>

#include	"MyMacro.h"


//============================================================
//	ײ����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.



//============================================================
//	�萔.
//============================================================
#define WND_W 1280	//����޳��.
#define WND_H 720	//����޳����.



//�����񋓑�.
enum enDirection
{
	enDirection_Stop	= 0,//��~.
	enDirection_Foward,		//�O�i.
	enDirection_BackWard,	//���.
	enDirection_LeftTurn,	//����].
	enDirection_RightTurn	//�E��].
};



#endif//#ifndef _GLOBAL_H_