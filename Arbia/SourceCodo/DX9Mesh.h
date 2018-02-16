#ifndef _DX9MESH_H_
#define _DX9MESH_H_
//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

#include <Windows.h>
#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>
#include <d3dx9.h>
#include "MyMacro.h"


#include "Global.h"


#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )



//============================================================
//	�񋓑�.
//============================================================
////�����񋓑�.
//enum enDirection
//{
//	enDirection_Stop	= 0,//��~.
//	enDirection_Foward,		//�O�i.
//	enDirection_BackWard,	//���.
//	enDirection_LeftTurn,	//����].
//	enDirection_RightTurn	//�E��].
//};


////���@�����̎��.
//enum enPlayerMove
//{
//	enPM_Stop	= 0,//��~.
//	enPM_Run,		//����.
//	enPM_Atk,		//�U��.
//	enPM_JumAt,		//�ެ��ߍU��.
//	enPM_Dead		//н.
//};//m_pEnemy_A->m_enPM
//


////�G�̓����̎��.
//enum enEnemyMove
//{
//	enEM_Walk = 0,
//	enEM_Run,
//	enEM_Atk,
//	enEM_Back,
//	enEM_Damage,
//	enEM_Death
//};//	enEnemyMove m_enEnemMod;//enEnemyMove.
//







//============================================================
//	�\����.
//============================================================
//�ݽ����ޯ̧�̱��ؑ��̒�`(Mesh.hlsl).
//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
//hlsl�ƘA�����Ă���(�^�����ق��������ذ��).
struct MESHSHADER_CONSTANT_BUFFER_ZERO
{
	D3DXMATRIX	mW;			//ܰ���(�ʒu)���W�s��.
	D3DXMATRIX	mWVP;		//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
	D3DXVECTOR4 vLightDir;	//ײĕ���.
	D3DXVECTOR4	vEye;		//��׈ʒu(���_�ʒu).
	D3DXVECTOR4 vColor;		//�װ.
};
struct MESHSHADER_CONSTANT_BUFFER_FIRST
{
	D3DXVECTOR4 vAmbient;	//���޴��.
	D3DXVECTOR4 vDiffuse;	//�ި̭��ސF.
	D3DXVECTOR4	vSpecular;	//��߷�אF.
};


//���_�̍\����.
struct MeshVertex
{
	D3DXVECTOR3 vPos;	//���_���W(x,y,z).
	D3DXVECTOR3 vNormal;//�@��(�A�e�v�Z�ɕK�{).
	D3DXVECTOR2 vTex;	//ø������W.
};

//��رٍ\����.
struct MY_MATERIAL
{
	D3DXVECTOR4		Ambient;	//���޴��.
	D3DXVECTOR4		Diffuse;	//�ި̭���.
	D3DXVECTOR4		Specular;	//��߷��.
	CHAR	szTextureName[128];	//ø���̧�ٖ�.
	ID3D11ShaderResourceView*	pTexture;//ø���.
	DWORD	dwNumFace;			//������رق���غ�ݐ�.
	//�ݽ�׸�.
	MY_MATERIAL(){
		ZeroMemory( this, sizeof( MY_MATERIAL ) );
	}
	//�޽�׸�.
	~MY_MATERIAL(){}
};


//�̨��\����.
struct SPHERE
{
	D3DXVECTOR3	vCenter;	//���S.
	float		fRadius;	//���a.

};

//B�ޯ���\����.
struct BBOX
{
	D3DXVECTOR3 vPosMax;	//�ő咸�_.
	D3DXVECTOR3 vPosMin;	//�ŏ����_.
	D3DXVECTOR3 vAxisX;		//X��.
	D3DXVECTOR3 vAxisY;		//Y��.
	D3DXVECTOR3 vAxisZ;		//Z��.
	FLOAT		fLengthX;	//X����.
	FLOAT		fLengthY;	//Y����.
	FLOAT		fLengthZ;	//Z����.
	//������.
	BBOX(){
		ZeroMemory( this, sizeof( BBOX ) );
		vAxisX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
		vAxisY = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		vAxisZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f ); 
	}
};







//ү���ް���̧�ق�����o�����߂�����DirectX9���g�p����.
//�������ݸ�(�\��)��DirectX11�ōs��.
class clsDX9Mesh
{
public:
	HWND				m_hWnd;	//����޳�����.

	//Dx9.
	LPDIRECT3D9			m_pD3d;	//DX9��޼ު��.
	LPDIRECT3DDEVICE9	m_pDevice9;	//Dx9���޲���޼ު��.

	//D3DMATERIAL9*		m_pMaterials;	//��رُ��.
	//LPDIRECT3DTEXTURE9*	m_pTextures;	//ø������.
	//char				m_TexFileName[8][256];	//ø���̧�ٖ�(8���܂�).
	DWORD				m_dwNumMaterials;//��رِ�.
	LPD3DXMESH			m_pMesh;		//ү����޼ު��.

	//Dx11.
	ID3D11Device*			m_pDevice11;		//���޲���޼ު��.
	ID3D11DeviceContext*	m_pDeviceContext11;	//���޲���÷��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer0;	//�ݽ����ޯ̧0.
	ID3D11Buffer*			m_pConstantBuffer1;	//�ݽ����ޯ̧1.
//
//
	ID3D11Buffer*	m_pVertexBuffer;//���_(�ްï��)�ޯ̧.
	ID3D11Buffer**	m_ppIndexBuffer;	//���ޯ���ޯ̧.
	ID3D11SamplerState*			m_pSampleLinear;//ø����̻���װ.//ø����Ɋe��̨����������.
//
//
	MY_MATERIAL*	m_pMaterials;	//��رٍ\����.
	DWORD			m_NumAttr;		//������.
	DWORD			m_AttrID[300];	//����ID ��300�����܂�.

	bool			m_bTexture;		//ø����̗L��.


	float			m_fScale;	//�g�k.
	float			m_fYaw;		//��](Y��).
	float			m_fPitch;	//��](X��).
	float			m_fRoll;	//��](Z��).
	D3DXVECTOR3		m_vPos;		//�ʒu(X,Y,Z).
	float			m_fYawTarget;//�ڕW�p�x.



float			m_fSpd;






	SPHERE		m_Sphere;	//�̨��\����.
	BBOX		m_BBox;		//BBox�\����.

	D3DXVECTOR3	m_vRay;			//ڲ�̈ʒu.
	D3DXVECTOR3	m_vAxis;		//��]��.
	LPD3DXMESH	m_pMeshForRay;	//ڲ��ү���p.





	ID3D11BlendState*	m_pBlendState;	//�����޽ð�.


	clsDX9Mesh();	//�ݽ�׸�.
	~clsDX9Mesh();	//�޽�׸�.

	//������.
	HRESULT Init( HWND hWnd, ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, LPSTR fileName );

	//Dx9�������p.
	HRESULT InitDx9( HWND hWnd );

	//ү���Ǎ�.
	HRESULT LoadXMesh( LPSTR fileName );

	//����ލ쐬.
	HRESULT InitShader();

	//�����ݸޗp(��DX9MESH����Main����2���݂���̂Œ���).
	void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye,
				D3DXVECTOR4 vColor = D3DXVECTOR4( 1.0f,1.0f,1.0f,1.0f ),
				bool alphaFlg = false );

	//����(��̧������)�ݒ�̐؂�ւ�.
	void SetBlend( bool flg );



	//���.
	HRESULT Release();


};

#endif//#ifndef _DX9MESH_H_
