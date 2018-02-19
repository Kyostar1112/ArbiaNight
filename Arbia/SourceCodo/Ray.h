#ifndef _CRAY_H_
#define _CRAY_H_

#include "Common.h"	//共通ｸﾗｽ.

//ﾚｲｸﾗｽ(表示のみを行う).
class clsRay
	: public clsCommon	//共通ｸﾗｽ継承.
{
public:
	//============================================================
	//	構造体.
	//============================================================
	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧのｱﾌﾟﾘ側の定義(Ray.hlsl).
	//ｼｪｰﾀﾞ内のｺﾝｽﾀﾝﾄﾊﾞｯﾌｧと一致している必要あり.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//ﾜｰﾙﾄﾞ,ﾋﾞｭｰ,射影の合成変換行列.
		D3DXVECTOR4	vColor;		//ｶﾗｰ(RGBAの型に合わせる) : ﾃｸｽﾁｬの上から色を載せる(赤っぽくも見せるためとか).
	};

	//頂点構造体.
	struct MODEL_VERTEX
	{
		D3DXVECTOR3 vPos;	//位置.
	};

	//ﾚｲ構造体.
	struct RAY
	{
		D3DXVECTOR3 vPoint[2];	//始点、終点.
		D3DXVECTOR3 vDirection;	//方向.
		D3DXVECTOR3 vPos;		//位置.
		FLOAT		fYaw;		//Y回転軸.
		RAY()
		{
			const D3DXVECTOR3 vINIT_VECTOR3 = { 0.0f, 0.0f, 0.0f };
			//ZeroMemory( this, sizeof( RAY ) );
			vPoint[0] = vPoint[1] = vINIT_VECTOR3;
			vDirection = vINIT_VECTOR3;
			vPos = vINIT_VECTOR3;
			fYaw = 0.0f;
		}
	};
	RAY	m_Ray;	//ﾚｲ構造体.

	clsRay();
	~clsRay();

	//初期化.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

	//描画.
	void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj );


private:
	//ｼｪｰﾀﾞ初期化.
	HRESULT InitShader();
	//ﾚｲ初期化.
	HRESULT InitModel();

	//↓ﾓﾃﾞﾙの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;	//頂点ｼｪｰﾀﾞ.
	ID3D11InputLayout*		m_pVertexLayout;	//頂点ﾚｲｱｳﾄ.
	ID3D11PixelShader*		m_pPixelShader;		//ﾋﾟｸｾﾙｼｪｰﾀﾞ.
	ID3D11Buffer*			m_pConstantBuffer;	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧ.

	//↓ﾓﾃﾞﾙごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;	//頂点ﾊﾞｯﾌｧ.


};




#endif//#ifndef _CRAY_H_.