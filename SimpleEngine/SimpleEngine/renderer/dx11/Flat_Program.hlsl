"\n\
float4 VS(float4 Pos : POSITION) : SV_POSITION\n\
{\n\
	return Pos;\n\
}\n\
\n\
float4 PS(float4 Pos : SV_POSITION) : SV_Target\n\
{\n\
	return float4(1.0f, 1.0f, 0.0f, 1.0f); \n\
}\n";