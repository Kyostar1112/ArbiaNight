//��۰��ٕϐ�.

//ø�����ڼ޽��t(n).
Texture2D		g_texColor	: register(t0);
//����װ��ڼ޽��s(n).
SamplerState	g_samLinear	: register(s0);

//�ݽ����ޯ̧.
cbuffer global
{
	matrix	g_mWVP;		//ܰ���,�ޭ�,��ۼު���ݍ����s��.
	float4	g_vColor;	//�F.
	float4	g_fAlpha;	//���ߒl.
};

//���_����ނ̏o�����Ұ�.
struct VS_OUT
{
	float4	Pos	: SV_Position;	//�ʒu.
	float2	Tex : TEXCOORD;		//ø���.
};

//���_�����.
VS_OUT	VS( float4 Pos	: POSITION,
			float2 Tex	: TEXCOORD )
{
	VS_OUT Out = (VS_OUT)0;
	Out.Pos = mul( Pos, g_mWVP );
	//ø������W.
	Out.Tex = Tex;

	return Out;
}

//�߸�ټ����.
float4 PS( VS_OUT In )	: SV_Target
{
	float4 color
		= g_vColor * g_texColor.Sample( g_samLinear, In.Tex );

	return color * g_fAlpha.x;
}


