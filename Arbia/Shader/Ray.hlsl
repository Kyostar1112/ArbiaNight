//��۰���.

cbuffer global
{
	matrix	g_mWVP;	//WorldViewProj�̕ϊ��s��.
	float4	g_vColor;//�F.
};

//�ްï�������.
float4 VS( float4 Pos : POSITION ) : SV_Position
{
	Pos = mul( Pos, g_mWVP );
	return Pos;
}

//�߸�ټ����.
float4 PS( float4 Pos : SV_Position ) : SV_Target
{
	return g_vColor;
}
