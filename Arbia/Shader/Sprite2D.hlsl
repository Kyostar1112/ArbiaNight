//��۰��ٕϐ�.
//ø�����ڼ޽�� t(n).
Texture2D		g_Texture	: register( t0 );
//����װ��ڼ޽�� s(n).
SamplerState	g_Sampler	: register( s0 );

//�ݽ����ޯ̧.
cbuffer	global	: register( b0 )
{
	matrix	g_mW			: packoffset( c0 );
	float	g_fViewPortW	: packoffset( c4 );
	float	g_fViewPortH	: packoffset( c5 );
	float	g_fAlpha		: packoffset( c6 );
	float2	g_vUV			: packoffset( c7 );
};


//�ްï������ނ̏o�����Ұ�.
struct VS_OUT
{
	float4	Pos	: SV_Position;
	float2	UV	: TEXCOORD;
};

//�ްï�������.
VS_OUT VS_Main( float4 Pos	: POSITION,
				float2 UV	: TEXCOORD )
{
	//������.
	VS_OUT	output = ( VS_OUT )0;

	output.Pos = mul( Pos, g_mW );

	//��ذݍ��W�ɍ��킹��v�Z.
	output.Pos.x = ( output.Pos.x / g_fViewPortW ) * 2 - 1;
	output.Pos.y = 1 - ( output.Pos.y / g_fViewPortH ) * 2;

	//UV�ݒ�.
	output.UV = UV;

	//UV���W�����炷.
	output.UV.x += g_vUV.x;
	output.UV.y += g_vUV.y;

	return output;
}

//�߸�ټ����.
float4 PS_Main( VS_OUT input )	: SV_Target
{
	float4 color =
		g_Texture.Sample( g_Sampler, input.UV );//�F��Ԃ�.

	color.a *= g_fAlpha;

	return color;
}
