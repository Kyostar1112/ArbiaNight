#ifndef _CEFFECTS_H_
#define _CEFFECTS_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���B4005:�Ē�`.
#pragma warning( disable : 4005 )

//==================================================
//	��ɂ��Ă����ׂ�ͯ�ށAײ���؂̓Ǎ�.
//==================================================
#include <stdio.h>

#include <D3D11.h>
#include <XAudio2.h>
#pragma comment( lib, "d3d11.lib" )

//==================================================
//	��������Effekseer�֌W ͯ�ށAײ���؂̓Ǎ�.
//==================================================
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>


#if _DEBUG
#pragma comment( lib, "VS2013\\Debug\\Effekseer.lib" )
#pragma comment( lib, "VS2013\\Debug\\EffekseerRendererDX11.lib" )
#pragma comment( lib, "VS2013\\Debug\\EffekseerSoundXAudio2.lib" )
#else//#if _DEBUG
#pragma comment( lib, "VS2013\\Release\\Effekseer.lib" )
#pragma comment( lib, "VS2013\\Release\\EffekseerRendererDX11.lib" )
#pragma comment( lib, "VS2013\\Release\\EffekseerSoundXAudio2.lib" )
#endif//#if _DEBUG


//�uD3DX�`�v�g�p�ŕK�{.
//����:Effekseer�֌W����ɓǂݍ��ނ���.
#include <D3DX10.h>
#pragma comment( lib, "d3dx10.lib" )


//==================================================
//	�t���[�\�t�gEffekseer���ް����g�����߂̸׽.
//==================================================
class clsEffects
{
public:
	//�̪�Ď�ޗ񋓑�.
	enum enEfcType
	{
		//Arbia.
		enEfcType_STEP = 0,	//asiato.v
		enEfcType_ARBIA_ATK,//arbia_kougeki.v
		enEfcType_WAVE,		//syougekiha.v
		enEfcType_KICK_HIT,	//kougeki.v

		//Enemy.
		enEfcType_ENEMY_ATK,//teki_kougeki.
		enEfcType_SLASH_HIT,//yarare.v

		//Pendulum.
		enEfcType_PEND_FIRE,//hibana.v
		enEfcType_PEND_WIND,//pen_kaze.v

		//TreasureBox.
		enEfcType_TRB_OPEN,	//takara_hasira.v
		enEfcType_TRB_LOOP,	//takara_nakami.v

		//Door.
		enEfcType_DOOR_DUST,//takara_nakami.v

		enEfcType_Max
	};


	//�ݽ�ݽ�擾(�B��̱����o�H).
	static clsEffects* GetInstance()
	{
		//�B��̲ݽ�ݽ���쐬����.
		//(static�ō쐬���ꂽ�̂�2��ڂ͖��������).
		static clsEffects s_Instance;
		return &s_Instance;
	}

	~clsEffects();

	//�\�z�֐�.
	HRESULT Create( ID3D11Device* pDevice,
					ID3D11DeviceContext* pContext );
	//�j���֐�.
	HRESULT Destroy();
	//�ް��Ǎ��֐�.
	HRESULT LoadData();
	//�ް�����֐�.
	HRESULT ReleaseData();

	//�`��.
	void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vEye );

	//�ޭ��s��ݒ�.
	void SetViewMatrix( D3DXMATRIX& mView );
	//��ۼު���ݍs��ݒ�.
	void SetProjectionMatrix( D3DXMATRIX& mProj );


	//�Đ��֐�.
	::Effekseer::Handle Play(  enEfcType EfcType, D3DXVECTOR3 vPos ){
		return m_pManager->Play(
			m_pEffect[EfcType], vPos.x, vPos.y, vPos.z );
	};
	//�ꎞ��~.
	void Paused( ::Effekseer::Handle handle, bool bFlag ){
		m_pManager->SetPaused( handle, bFlag );	//bFlag:true = �ꎞ��~.
	}
	//��~.
	void Stop( ::Effekseer::Handle handle ){
		m_pManager->StopEffect( handle );
	}
	//���ׂĒ�~.
	void StopAll( ::Effekseer::Handle handle ){
		m_pManager->StopAllEffects();
	}

	//���ގw��.
	void SetScale( ::Effekseer::Handle handle, D3DXVECTOR3 vScale ){
		m_pManager->SetScale( handle,
			vScale.x, vScale.y, vScale.z );
	}
	//�X�s�[�h�w��.
	void SetSpd( ::Effekseer::Handle handle, float fSpd ){
		m_pManager->SetSpeed( handle, fSpd );
	}
	//��]�w��.
	void SetRotation( ::Effekseer::Handle handle, D3DXVECTOR3 vRot ){
		m_pManager->SetRotation( handle,
			vRot.x, vRot.y, vRot.z );
	}
	void SetRotation( ::Effekseer::Handle handle,
			D3DXVECTOR3 vAxis, float fAngle ){
		m_pManager->SetRotation( handle,
			::Effekseer::Vector3D( vAxis.x, vAxis.y, vAxis.z ),
			fAngle );
	}
	//�ʒu�w��.
	void SetLocation( ::Effekseer::Handle handle, D3DXVECTOR3 vPos ){
		m_pManager->SetLocation( handle,
			::Effekseer::Vector3D( vPos.x, vPos.y, vPos.z ) );
	}

	//�����Ă�?.
	bool PlayCheck( ::Effekseer::Handle handle )
	{
		return m_pManager->Exists( handle );
	}



	//�޸���ϊ��֐�.
	::Effekseer::Vector3D Vector3DDxToEfk( 
					const D3DXVECTOR3* pSrcVec3Dx );
	D3DXVECTOR3 Vector3EfkToDx( 
					const ::Effekseer::Vector3D* pSrcVec3Efk );

	//�s��ϊ��֐�.
	::Effekseer::Matrix44 MatrixDxToEfk(
					const D3DXMATRIX* pSrcMatDx );
	D3DXMATRIX MatrixEfkToDx(
					const ::Effekseer::Matrix44* pSrcMatEfk );


private:
	//�������߰���֎~����.
	clsEffects();
	clsEffects( const clsEffects& rhs );
	clsEffects& operator = ( const clsEffects& rhs );

	//�̪�Ă��쓮�����邽�߂ɕK�v.
	::Effekseer::Manager*			m_pManager;
	::EffekseerRenderer::Renderer*	m_pRender;
	::EffekseerSound::Sound*		m_pSound;
	//�̪���ް��Ɋ܂܂�鉹�Đ��ɕK�v.
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;


	//�̪�Ă̎�ނ��ƂɕK�v.
	::Effekseer::Effect*			m_pEffect[ enEfcType_Max ];


};

//=======================================================
//	�g����.
//=======================================================

//.	//Main��Create�ɂ���
//	clsEffects::GetInstance()->Create( m_pDevice, m_pDeviceContext );
//	clsEffects::GetInstance()->LoadData();




//	//�G�t�F�N�g���o�������N���X�̃w�b�_�[��.
//	//����Ɠ����^�̕ϐ���錾����.
//	::Effekseer::Handle		m_Handle;


//	//----- h�ł̎g�p�� -----//.
//	//���O�ȗ��p.
//	clsEffects*				m_pEffect;
//	//�n���h�� eh = EffekseerHandle.
//	::Effekseer::Handle		m_ehBomb;


//	//----- cpp�ł̎g�p�� -----//.
//	//�R���X�g���N�^��Create�ɂ�.
//	m_pEffect = nullptr;.
//	if( m_pEffect == nullptr ){
//		m_pEffect = clsEffects::GetInstance();
//	}

//	//�o�������^�C�~���O.
//	if( !m_pEffect->PlayCheck( m_ehBomb ) ){
//		m_ehBomb = m_pEffect->Play( clsEffects::enEfcType_MgcDrk, m_vPos );
//	}
//	m_pEffect->SetLocation( m_ehBomb, m_vPos );

//	main�֐���Render��
//	clsEffects::GetInstance()->Render( m_mView, m_mProj, m_Camera.vEye );



//	//Release()�֐��ɂ�.
//	 m_pEffect = nullptr;.
//	���e�N���X�ł����delete�͂��Ă͂Ȃ�Ȃ�.


//�����.
	//�̪�Ė��ɕK�v(�����̪�Ă�3�o���Ȃ�3�K�v).


#endif//#ifndef _CEFFECTS_H_