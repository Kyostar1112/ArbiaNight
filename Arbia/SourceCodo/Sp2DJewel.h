#ifndef _SP_2D_JEWEL_H_
#define _SP_2D_JEWEL_H_


#include "Sprite2D.h"

class clsJewel
	: public clsSprite2D
{

public:
	clsJewel();
	~clsJewel();

	////”√ﬁŸçÏê¨.
	virtual HRESULT InitModel( SPRITE_STATE ss );

	//ï`âÊ(⁄›¿ﬁÿ›∏ﬁ)(Å¶DX9MESHì‡Ç∆Mainì‡Ç≈2Ç¬ë∂ç›Ç∑ÇÈÇÃÇ≈íçà”).
	virtual void Render();

	void AddPos( D3DXVECTOR3 vPos ){
		m_vPos += vPos;
	};

	float	m_fScale;

private:




};




#endif//#ifndef _SP_2D_JEWEL_H_