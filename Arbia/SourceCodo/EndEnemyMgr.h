#ifndef _END_ENEMY_MANAGER_H_
#define _END_ENEMY_MANAGER_H_

#include <random>
#include "EndEnemy.h"


const int iEND_ENEMY_MAX = 32;


class clsEndEnemMgr
{
public:
	clsEndEnemMgr();
	~clsEndEnemMgr();

	std::random_device Rnd;//ƒ‰ƒ“ƒ_ƒ€.


	void Create(
		HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11 );

	void Init( D3DXVECTOR3 vPlayerPos, int DiscNum );

	void Update();

	void Render( 
		D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vLight, D3DXVECTOR3& vEye );

private:

	void Release();

	clsEndEnemy* m_pEnemy;

	int		m_iEnemMax;

	D3DXVECTOR3 vEndPos[iEND_ENEMY_MAX];
};


#endif //#ifndef _END_ENEMY_MANAGER_H_