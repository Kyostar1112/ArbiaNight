#ifndef _C_RESOURCE_H_
#define _C_RESOURCE_H_
#define _CRT_SECURE_NO_WARNINGS

#include "DX9Mesh.h"
#include "D3DXSKINMESH.h"

#include "Global.h"

class clsResource
{
public:
	//��è�����َ��.
	enum enStaticModel
	{
		enST_MODEL_Plane = 0,
		enST_MODEL_WALL_MIN,
		enST_MODEL_WALL_NOT_WALL,
		enST_MODEL_WALL,

		enST_MODEL_FLOOR_MIN,
		enST_MODEL_FLOOR_NOT_WALL_NORMAL,
		enST_MODEL_FLOOR_NOT_WALL_HALF_L,
		enST_MODEL_FLOOR_NOT_WALL_HALF_R,
		enST_MODEL_FLOOR_NOT_WALL_PEND,

		enST_MODEL_FLOOR_NORMAL,
		enST_MODEL_FLOOR_HALF_L,
		enST_MODEL_FLOOR_HALF_R,
		enST_MODEL_FLOOR_PEND,

		enST_MODEL_STEP_CIL,
		enST_MODEL_STEP_CIL_BIG,
		enST_MODEL_STEP_BOX,

		enST_MODEL_MON,

		enST_MODEL_TR_BOX_COL,
		enST_MODEL_GOOL,

		enST_MODEL_BLOCK,

		enST_MODEL_SPIA,//���ʑ�.
		enST_MODEL_SPIA_OF_WALL,//�Ǒ�.
		enST_MODEL_SPIA_WALL,//���̕ǔ���p.
		enST_MODEL_SPIA_WALL_HASIRA,//����.

		enST_MODEL_COVER_L,//���Ƃ����̊W.
		enST_MODEL_COVER_R,//���Ƃ����̊W.

		enST_MODEL_CEILING,

		enST_MODEL_TEST, //�e�X�g�p.

		enST_MODEL_MAX,
	};

	//������َ��.
	enum enSkinModel
	{
		enSK_MODEL_PLAYER = 0,
		enSK_MODEL_ENEMY,

		enSK_MODEL_DOOR,

		enSK_MODEL_PENDULUM,

		enSK_MODEL_TR_BOX,//�� : Treasure Box.

		enSK_MODEL_MAX,
	};

	//�ݽ�ݽ�擾(�B��̱����o�H).
	static clsResource* GetInstance()
	{
		//�B��̲ݽ�ݽ���쐬����.
		//(static�ō쐬���ꂽ�̂�2��ڂ͖��������).
		static clsResource s_Instance;
		return &s_Instance;
	}
//	clsResource();
	~clsResource();



	//��è������.
	HRESULT		InitStaticModel( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	HRESULT		CreateStaticModel( LPSTR fileName, enStaticModel enModel );
	HRESULT		ReleaseStaticModel( enStaticModel enModel );
	clsDX9Mesh* GetStaticModels( enStaticModel enModel );


	//�������.
	HRESULT		InitSkinModel( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	HRESULT		CreateSkinModel(LPSTR fileName, enSkinModel enModel);
	HRESULT		ReleaseSkinModel(enSkinModel enModel);
	clsD3DXSKINMESH*	GetSkinModels(enSkinModel enModel);

#ifdef Inoue
	enStaticModel ItoE( int Num ){
		return static_cast<enStaticModel>(Num);
	}

	int EtoI(enStaticModel Num){
		return static_cast<int>(Num);
	}
#endif//#ifdef Inoue.

private:
	//�������߰���֎~����.
	clsResource();
	clsResource( const clsResource& rhs );
	clsResource& operator = ( const clsResource& rhs );

	HWND					m_hWnd;
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pCotext11;
	CD3DXSKINMESH_INIT		m_Si;

	clsDX9Mesh**			m_ppStaticModels;
	clsD3DXSKINMESH**		m_ppSkinModels;

	//�͈͓�����������֐�.
	bool IsRangeStaticModel( enStaticModel enModel );
	bool IsRangeSkinModel( enSkinModel enModel );


	char m_FilePath[256];


};

#endif//#ifndef _C_RESOURCE_H_