#ifndef _END_ENEMY_H_
#define _END_ENEMY_H_

#include "CharaSkin.h"

class clsEndEnemy
		: public clsCharaSkin
{
public:
	clsEndEnemy();
	~clsEndEnemy();

	void Create( 
		HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11 );

	virtual void Init();

	void Update();


private:


	void Release();

};


#endif //#ifndef _END_ENEMY_H_