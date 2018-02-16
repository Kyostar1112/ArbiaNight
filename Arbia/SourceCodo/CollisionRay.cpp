#include "CollisionRay.h"


const float WALL_HIT	= 1.01f;	//�ǂƂ̏Փˋ���.//0.8f.
const float WALL_SPACE	= WALL_HIT;	//�ǂƂ̕ǂƊJ���鋗��.//0.8f.



clsCollisionRay::clsCollisionRay()
{
}

clsCollisionRay::~clsCollisionRay()
{
}


//============================================================
//	�ǂ̂����蔻��֘A.
//============================================================
void clsCollisionRay::WallJudge( clsCharaSkin* pWalker, clsCharaStatic* pWall )// clsDX9Mesh* pWalker, clsDX9Mesh* pWall .
{
	const char MAX = 4;//.���̐�
	const float HitHeight = 0.375f;	//���ޱ�̑�������̍���.

	FLOAT		fDistance[MAX] = { 0.0f, 0.0f, 0.0f, 0.0f };	//����.
	D3DXVECTOR3	vIntersect[MAX];//��_���W.
	float		fDis, fYaw;		//�����Ɖ�].


	pWalker->m_vRay = pWalker->GetPosition();
	pWalker->m_vRay.y += HitHeight;

#if 0
	//���޸�ق̕����O��E��.
	D3DXVECTOR3 Axis[MAX] ={D3DXVECTOR3( 0.0f, 0.0f, 1.0f ),
							D3DXVECTOR3( 0.0f, 0.0f,-1.0f ),
							D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),
							D3DXVECTOR3(-1.0f, 0.0f, 0.0f ) };
	//ڲ�̌����ɂ�蓖����ǂ܂ł̋��������߂�.
	//���޸�ف@�O��E��.
	for( char i=0; i<MAX; i++ ){
		pWalker->m_vAxis = Axis[i];
		Intersect( pWalker, pWall, &fDistance[i], &vIntersect[i] );
	}
#else
	//���޸�ف@�O.
	pWalker->m_vAxis = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	Intersect( pWalker, pWall, &fDistance[0], &vIntersect[0] );
	//���޸�ف@��.
	pWalker->m_vAxis = D3DXVECTOR3( 0.0f, 0.0f,-1.0f );
	Intersect( pWalker, pWall, &fDistance[1], &vIntersect[1] );
	//���޸�ف@�E.
	pWalker->m_vAxis = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	Intersect( pWalker, pWall, &fDistance[2], &vIntersect[2] );
	//���޸�ف@��.
	pWalker->m_vAxis = D3DXVECTOR3(-1.0f, 0.0f, 0.0f );
	Intersect( pWalker, pWall, &fDistance[3], &vIntersect[3] );
#endif

	//��Βl.
	fYaw = fabs( pWalker->GetRotationY() );	
	DirOverGuard( &fYaw );


	//�O���ǂɐڋ�.
	fDis = fDistance[0];
	if( fDis < WALL_HIT && fDis > 0.01f ){
		if( pWalker->GetRotationY() < 0.0f ){
			//���v���.
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else{										//������.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
		}
		else{
			//�����v���.
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else{										//������.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
		}
	}

	//��낪�ǂɐڋ�.
	fDis = fDistance[1];
	if( fDis < WALL_HIT && fDis > 0.01f ){
		//���v���.
		if( pWalker->GetRotationY() < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else{										//������.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else{										//������.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
		}
	}

	//�E���ǂɐڋ�.
	fDis = fDistance[2];
	if( fDis < WALL_HIT && fDis > 0.01f ){
		//���v���.
		if( pWalker->GetRotationY() < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else{										//������.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else{										//������.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
		}
	}

	//�����ǂɐڋ�.
	fDis = fDistance[3];
	if( fDis < WALL_HIT && fDis > 0.01f ){
		//���v���.
		if( pWalker->GetRotationY() < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else{										//������.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pWalker->AddPositionZ( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pWalker->AddPositionX( -( WALL_SPACE - fDis ) );
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pWalker->AddPositionZ( WALL_SPACE - fDis );
			}
			else{										//������.
				pWalker->AddPositionX( WALL_SPACE - fDis );
			}
		}
	}
}




//============================================================
//	ڲ��ү���̂����蔻��.
//============================================================
bool clsCollisionRay::Intersect(
	clsCharaSkin* pWalker,		//��̂̕���.
	clsCharaStatic* pTarget,		//�Ώۂ̂̕���.
	float* pfDistance,			//(out)����.
	D3DXVECTOR3* pvIntersect )	//(out)�������W.
{
	D3DXMATRIXA16	matRot;	//��]�s��.

	//��]�s����v�Z.
	D3DXMatrixRotationY( &matRot, pWalker->GetRotationY() );

	//���޸�ق�p��.
	D3DXVECTOR3 vecAxisZ;
	//Z���޸�ق��̂��̂����݂̉�]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vecAxisZ, &pWalker->m_vAxis, &matRot );

	D3DXVECTOR3 vecStart, vecEnd, vecDistance;
	//ڲ�̊J�n�I���ʒu��Attacker�ƍ��킹��.
	vecStart = vecEnd = pWalker->m_vRay;
	//Attacker�̍��W�ɉ�]���W����������.
	vecEnd += vecAxisZ * 1.0f;

	//�Ώۂ������Ă��镨�̂ł��A�Ώۂ�world�s��́A.
	//�t�s���p����΁A������ڲ��������.
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(
		&matWorld,
		pTarget->GetPositionX(),
		pTarget->GetPositionY(),
		pTarget->GetPositionZ() );

	//�t�s������߂�.
	D3DXMatrixInverse( &matWorld, NULL, &matWorld );
	D3DXVec3TransformCoord(
		&vecStart, &vecStart, &matWorld );
	D3DXVec3TransformCoord(
		&vecEnd, &vecEnd, &matWorld );

	//���������߂�.
	vecDistance = vecEnd - vecStart;

	BOOL bHit = false;	//�����׸�.

	DWORD dwIndex = 0;	//���ޯ���ԍ�.
	D3DXVECTOR3 vVertex[3];	//���_���W.
	FLOAT U = 0, V = 0;	//(out)�d�S˯č��W.

	//ү����ڲ�̌����𒲂ׂ�.
	D3DXIntersect(
		pTarget->m_pModel->m_pMesh,//�Ώ�ү��.
		&vecStart,		//�J�n�ʒu.
		&vecDistance,	//ڲ�̋���.
		&bHit,			//(out)���茋��.
		&dwIndex,		//(out)bHit��True���Aڲ�̎��_�ɁB.
						//		�ł��߂��̖ʂ̲��ޯ���l�ւ��߲��.
		&U, &V,			//(out)�d�S˯č��W.
		pfDistance,		//���ޯĂƂ̋���.
		NULL, NULL );

	if( bHit ){
		//���������Ƃ�.
		FindVerticesOnPoly(
			pTarget->m_pModel->m_pMeshForRay, dwIndex, vVertex );
		//�d�S���W��������_���Z�o.
		//۰�ٌ�_p�́A v0 + U*(v1-v0) + V*(v2-v0)�ŋ��܂�.
		*pvIntersect =
			vVertex[0]
			+ U * ( vVertex[1] - vVertex[0] )
			+ V * ( vVertex[2] - vVertex[0] );

		return true;
	}
	return false;
}



//============================================================
//	�����ʒu����غ�݂̒��_��������.
//		�����_���W��۰�ٍ��W.
//============================================================
HRESULT clsCollisionRay::FindVerticesOnPoly(
	LPD3DXMESH pTarget, DWORD dwPolyIndex,
	D3DXVECTOR3* pVecVertices )
{
	//���_���̃o�޲Đ����擾.
	DWORD dwStride = pTarget->GetNumBytesPerVertex();
	//���_�����擾.
	DWORD dwVertexAmt = pTarget->GetNumVertices();
	//�ʐ����擾.
	DWORD dwPolyAmt = pTarget->GetNumFaces();

	WORD* pwPoly = NULL;

	//���ޯ���ޯ̧��ۯ�(�Ǎ�Ӱ��).
	pTarget->LockIndexBuffer(
		D3DLOCK_READONLY, (VOID**)&pwPoly );
	BYTE*	pbVertices = NULL;	//���_(�޲Č^)
	FLOAT*	pfVertices = NULL;	//���_(float�^)
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;	//���_�ޯ̧.
	pTarget->GetVertexBuffer( &VB );	//���_���̎擾.

	//���_�ޯ̧��ۯ�.
	if( SUCCEEDED(
		VB->Lock( 0, 0, (VOID**)&pbVertices, 0 ) ) )
	{
		////��غ�݂̒��_��1�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 ] ];
		//pVecVertices[0].x = pfVertices[0];
		//pVecVertices[0].y = pfVertices[1];
		//pVecVertices[0].z = pfVertices[2];
		////��غ�݂̒��_��2�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + 1 ] ];
		//pVecVertices[1].x = pfVertices[0];
		//pVecVertices[1].y = pfVertices[1];
		//pVecVertices[1].z = pfVertices[2];
		////��غ�݂̒��_��3�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + 2 ] ];
		//pVecVertices[2].x = pfVertices[0];
		//pVecVertices[2].y = pfVertices[1];
		//pVecVertices[2].z = pfVertices[2];

		////��غ�݂̒��_��1�`3�ڂ��擾.
		for( int i=0; i<3; i++ ){
			pfVertices
				= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + i ] ];
			pVecVertices[i].y = pfVertices[1];
			pVecVertices[i].z = pfVertices[2];
			pVecVertices[i].x = pfVertices[0];
		}

		//ۯ�����.
		pTarget->UnlockIndexBuffer();
		VB->Unlock();
	}
	VB->Release();

	return S_OK;
}


//============================================================
//	��]�l����.
//============================================================
void clsCollisionRay::DirOverGuard( float* fYaw )
{
	if( *fYaw > (float)( D3DX_PI * 2.0 ) ){
		*fYaw -= (float)( D3DX_PI * 2.0 );
	}
	else{
		return;
	}

	//�ċA.
	if( *fYaw > (float)( D3DX_PI * 2.0 ) ){
		DirOverGuard( fYaw );
	}
}


//============================================================
//	���̂����蔻��֘A.
//============================================================
bool clsCollisionRay::FloorJudge( 
	clsCharaSkin* pWalker, 
	float fRange,
	float& fLandY,
	clsCharaStatic* pFloor,
	bool& bGround )//�ڒn�t���O.
{
	bGround = false;

	//����4��.
	D3DXVECTOR3 vOffsetWidht[4];
	vOffsetWidht[0] = { 0.0f, 0.0f, fRange };
	vOffsetWidht[1] = { 0.0f, 0.0f,-fRange };
	vOffsetWidht[2] = { fRange, 0.0f, 0.0f };
	vOffsetWidht[3] = {-fRange, 0.0f, 0.0f };

	for( int i=0; i<4; i++ ){
		//�n�ʂƂ�ڲ.
		FLOAT		fDistance;	//����.
		D3DXVECTOR3 vIntersect;	//�������W.
		const float fOffsetFoot = 0.03125f;
		//���݂̈ʒu���߰.
		pWalker->m_vRay = pWalker->GetPosition();
		pWalker->m_vRay += vOffsetWidht[i];
		//ڲ�̍��������@����ɂ���.
		pWalker->m_vRay.y += fOffsetFoot;
		//���޸�ق͐����ŉ�����.
		pWalker->m_vAxis = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );

		bool bHit = false;
		bHit = Intersect(
			pWalker, pFloor, &fDistance, &vIntersect );

		if( bHit ){
	//		SetWindowTextA( m_hWnd, "���ɒn�ʂ�����܂�" );
			//���n����ׂ������A�e�̕`�捂��.
			fLandY = vIntersect.y;

			//�n�ʂɐG�ꂽ��.
			if( pWalker->GetPositionY() - vIntersect.y <= /*-0.03125f*/0.0f ){
				//��_�̍��W����y���W�����@��y���W�Ƃ��ľ��.
				vIntersect.y += 0.0f;
				pWalker->SetPositionY( vIntersect.y );
				//�����t���O�Z�b�g.
				pWalker->SetDropoutFlg( false );

				bGround = true;//�ڒn�t���O.
			}
			return true;
		}
		else{
	//		SetWindowTextA( m_hWnd, "nasi" );
			fLandY = -100;//�ޗ�.
			//�����t���O�Z�b�g.
			pWalker->SetDropoutFlg( true );
		}
	}

	return false;
}


//�V��Ƃ̔���.
bool clsCollisionRay::CeilingJudge( 
	clsCharaSkin* pWalker, 
	float fWalkerHeight,
	clsCharaStatic* pFloor )
{
	//�n�ʂƂ�ڲ.
	FLOAT		fDistance;	//����.
	D3DXVECTOR3 vIntersect;	//�������W.
	//���݂̈ʒu���߰.
	pWalker->m_vRay = pWalker->GetPosition();
	//���޸�ق͐����ŏ����.
	pWalker->m_vAxis = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	bool bHit = false;
	bHit = Intersect(
		pWalker, pFloor, &fDistance, &vIntersect );

	if( bHit ){
		//�����V��ɐG�ꂽ��.
		if( vIntersect.y - ( pWalker->GetPositionY() + fWalkerHeight ) <= 0.0f ){
			//��_�̍��W����y���W�����@��y���W�Ƃ��ľ��.
			vIntersect.y += 0.0f;
			pWalker->SetPositionY( vIntersect.y - fWalkerHeight );
			return true;
		}
	}

	return false;
}
