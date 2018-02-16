//��۰��ٕϐ�.

//ø�����ڼ޽�t(n)
Texture2D		g_texColor: register( t0 );
//����װ��ڼ޽�s(n).
SamplerState	g_samLinear:register( s0 );



//�ݽ����ޯ̧.
cbuffer global_0	: register(b0)
{
	matrix g_mW;		//ܰ��ލs��.
	matrix g_mWVP;		//ܰ���,�ޭ�,�ˉe�̍����s��.
	float4 g_vLightDir;	//ײĂ̕����޸��.
	float4 g_vEye;		//���(���_).
	float4 g_vColor;	//�װ(���ߐF).
};
cbuffer global_1	: register(b1)
{
	float4 g_Ambient = float4( 0, 0, 0, 0 );	//����.
	float4 g_Diffuse = float4( 1, 0, 0, 0 );	//�g�U����(�F).
	float4 g_Specular= float4( 1, 1, 1, 1 );	//���ʔ���.
};

//���_����ނ̏o�����Ұ�.
struct VS_OUT
{
	float4 Pos		:	SV_Position;
	float4 Color	:	COLOR0;
	float3 Light	:	TEXCOORD0;
	float3 Normal	:	TEXCOORD1;
	float3 EyeVector:	TEXCOORD2;
	float2 Tex		:	TEXCOORD3;

	float4 PosWorld	:	TEXCOORD4;//�O���E���h�t�H�O�p.
};

//============================================================
//	���_�����.
//============================================================
VS_OUT VS_Main( float4 Pos	: POSITION,
				float4 Norm	: NORMAL,
				float2 Tex	: TEXCOORD )
{
	VS_OUT Out = (VS_OUT)0;

	Out.Pos = mul( Pos, g_mWVP );
	
	//�@����ܰ��ދ�Ԃ�.
	Norm.w = 0;//w=0�ňړ������𔽉f�����Ȃ�.
	Out.Normal	= mul( Norm, g_mW );
	//ײĕ���.
	Out.Light	= g_vLightDir;

	float3 PosWorld = mul( Pos, g_mW );
	Out.PosWorld = mul( Pos, g_mW );

	//.�����޸��.
	Out.EyeVector	= g_vEye - PosWorld;

	float3 Normal	= normalize( Out.Normal );
	float3 LightDir	= normalize( Out.Light );
	float3 ViewDir	= normalize( Out.EyeVector );
	float4 NL		= saturate( dot( Normal, LightDir ) );

	float3 Reflect	= normalize( 2* NL * Normal - LightDir );
	float4 Specular	= pow( saturate( dot( Reflect, ViewDir ) ), 4 );

	//�F.
	Out.Color	= g_Diffuse * NL + Specular * g_Specular;
	//ø������W.
	Out.Tex		= Tex;

	return Out;
}


//***********************************************************
// ׽�ײ��(�Ұ�ނ��₷���悤�ɺ��Ă���ꂽ��).
//************************************************************


//============================================================
//	�߸�ټ����.
//============================================================
float4 PS_Main( VS_OUT In )	:	SV_Target
{
	float4 color
		= g_texColor.Sample( g_samLinear, In.Tex ) /2
		+ In.Color / 2.0f;
	color *= g_vColor;



	//----- �t�H�O���� -----//.
	float fFogColor = 0.0f;
	//--- ���t�H�O ---
	float d = In.Pos.z * In.Pos.w;	//����.
	float density = 0.03f;		//���x//0.025f.
	float e = 2.71828;		//���R�ΐ��̒�(Ȳ�߱��).

	float f = pow( e, -d * density );	//̫��̧���.
	f *= 0.5f + 0.5f + 0.5f;
	f = saturate( f );
	float4 Fog = f * color + ( 1 - f ) * fFogColor;

	//--- ���t�H�O ---.
	float4 vFogColor = ( 0.0f, 0.0f, 0.0f, 1.0f );
	In.PosWorld /= In.PosWorld.w;
	float fFloorHeight = 3.0f;
	float y = In.PosWorld.y + fFloorHeight;//��΍��W�ł̍���.
	float h = -1.0f;	//��������Fog���o��.

	//���艟��.
	{
		float High = 0.0f;
		float Low = -6.0f;
		float Mid = ( High + Low ) / 2;
		y =  Mid - y;
		float ffa = ( y / 1.0f ) * ( y / 1.0f ) * ( y / 1.0f ) * ( y / 1.0f ) * ( y / 1.0f ) * ( y / 1.0f );
		vFogColor = ( 0.0f, 0.0f, 0.0f, ffa ); 
	}

	f = y / h;	//̫��̧���.
	f = saturate( f );

	f *= 1.0f;	//�t�H�O�̗�.
	f = saturate( f );
	float4 FogFloor = f * color + ( 1.0f - f ) * vFogColor;

	//----- �t�H�O���� �I�� -----//.

	color = ( FogFloor * Fog ) / color;

	return color;
}



//==========ø��������pø��������pø��������pø��������pø��������pø��������pø��������pø��������p==========
//==========ø��������pø��������pø��������pø��������pø��������pø��������pø��������pø��������p==========
//==========ø��������pø��������pø��������pø��������pø��������pø��������pø��������pø��������p==========
//==========ø��������pø��������pø��������pø��������pø��������pø��������pø��������pø��������p==========
//==========ø��������pø��������pø��������pø��������pø��������pø��������pø��������pø��������p==========


//============================================================
//	���_�����.
//============================================================
VS_OUT VS_NoTex( float4 Pos	: POSITION,
				 float4 Norm: NORMAL )
{
	VS_OUT Out = ( VS_OUT )0;

	Out.Pos = mul( Pos, g_mWVP );

	//�@����ܰ��ދ�Ԃ�.
	Norm.w = 0;//w=0�ňړ������𔽉f�����Ȃ�.
	Out.Normal = mul( Norm, g_mW );
	//ײĕ���.
	Out.Light = g_vLightDir;
	//.�����޸��.
	float3 PosWorld = mul( Pos, g_mW );
	Out.EyeVector = g_vEye - PosWorld;

	float3 Normal = normalize( Out.Normal );
	float3 LightDir = normalize( Out.Light );
	float3 ViewDir = normalize( Out.EyeVector );
	float4 NL = saturate( dot( Normal, LightDir ) );

	float3 Reflect = normalize( 2 * NL * Normal - LightDir );
	float4 Specular = pow( saturate( dot( Reflect, ViewDir ) ), 4 );

	//�F.
	Out.Color = g_Diffuse * NL + Specular * g_Specular;

	return Out;
}


//============================================================
//	�߸�ټ����.
//============================================================
float4 PS_NoTex( VS_OUT In ): SV_Target
{
	float4 color = In.Color;
	return color * g_vColor;
}




//==========�ȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp����==========
//==========�ȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp����==========
//==========�ȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp����==========
//==========�ȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp���ވȉ��A����غ�ݗp����==========

//============================================================
//�ݽ����ޯ̧.
//============================================================
cbuffer	Ita_Global	:	register(b2)	//ڼ޽��𐔕��ǉ�.
{
	matrix	g_WVP;		//ܰ��ނ���ˉe�܂ł̕ϊ��s��.
	float4	g_vcolor;	//�F.
	float4	g_UV;		//UV���W.
};


//============================================================
//�\����.
//============================================================
struct VS_ItaOut
{
	float4	Pos	:	SV_Position;
	float2	Tex	:	TEXCOORD;
};

//============================================================
//	���_�����.
//============================================================
VS_ItaOut	VS_Ita( float4 Pos	:	POSITION,
					float4 Tex	:	TEXCOORD )
{
	VS_ItaOut output = (VS_ItaOut)0;
	//mul����(A,B) A��B�̊|���Z.
	output.Pos = mul( Pos, g_WVP );
	output.Tex = Tex;

	//ø�����UV���W�𑀍삷��.
	output.Tex.x += g_UV.x;
	output.Tex.y += g_UV.y;


	return output;
}

//============================================================
//	�߸�ټ����.
//============================================================
float4 PS_Ita( VS_ItaOut input )	:	SV_Target
{
	float4 color = g_texColor.Sample( g_samLinear, input.Tex );
	return color * g_vcolor;//�F��Ԃ�.
}


