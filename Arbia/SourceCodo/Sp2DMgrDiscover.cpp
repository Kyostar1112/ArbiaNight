#include "Sp2DMgrDiscover.h"

const LPSTR FILE_PATH_ICON = "Data\\Image\\IconDisc.png";


namespace MainSceneDisc{
	const WHSIZE_FLOAT ICONPOS = { 500.0f, 5.0f };
	const WHSIZE_FLOAT ICONSIZE = { 108.0f, 108.0f };

	const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };
}

const float fICON_ANIM_W = 2.0f;
const float fICON_STRIDE_W = 1.0f;

clsDiscover::clsDiscover()
{
}

clsDiscover::~clsDiscover()
{
}


//ç≈èâÇÃèâä˙âª.
void clsDiscover::Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_smpIcon = make_unique<clsSprite2D>();
	m_smpIcon->Create( pDevice11, pContext11, FILE_PATH_ICON, fICON_ANIM_W );
	m_smpIcon->SetDispW( MainSceneDisc::ICONSIZE.w );
	m_smpIcon->SetDispH( MainSceneDisc::ICONSIZE.h );
	m_smpIcon->SetPatarnU( fICON_STRIDE_W );

	m_smpLives = make_unique<clsNumGrp>();
	m_smpLives->Create( pDevice11, pContext11 );
	m_smpLives->SetPos( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );

	ReSet();
}


//ìÒâÒñ⁄à»ç~ÇÃèâä˙âª.
void clsDiscover::ReSet()
{
	m_vPos = D3DXVECTOR3( MainSceneDisc::ICONPOS.w, MainSceneDisc::ICONPOS.h, 0.0f );
	SetPos( m_vPos );
//	m_smpIcon->SetPos( MainSceneDisc::ICONPOS.w, MainSceneDisc::ICONPOS.h );
	m_smpLives->ReSet();
	SetNum( 0 );
}
