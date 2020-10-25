Texture2D tex;

SamplerState splr;

float4 main(float2 tc : TexCoord) : SV_Target
{
	float4 col = tex.Sample(splr,tc);
	if (col.r == 1.0f && col.b == 1.0f && col.g == 0.0f) {
		discard;
	}
	return col;
}