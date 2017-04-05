"\n\
cbuffer ConstantBuffer : register(b0)\n\
{\n\
	matrix World;\n\
	matrix View;\n\
	matrix Projection;\n\
	float4 vLightDir[2];\n\
	float4 vLightColor[2];\n\
}\n\
\n\
struct VS_INPUT\n\
{\n\
	float4 Pos : POSITION;\n\
	float4 Col : COLOR0;\n\
	float3 Norm : NORMAL;\n\
};\n\
\n\
struct PS_INPUT\n\
{\n\
	float4 Pos : SV_POSITION;\n\
	float3 Norm : TEXCOORD0;\n\
};\n\
\n\
PS_INPUT VS(VS_INPUT input)\n\
{\n\
	PS_INPUT output = (PS_INPUT)0;\n\
	output.Pos = mul(input.Pos, World);\n\
	output.Pos = mul(output.Pos, View);\n\
	output.Pos = mul(output.Pos, Projection);\n\
	output.Norm = mul(input.Norm, World);\n\
	return output;\n\
}\n\
\n\
float4 PS(PS_INPUT input) : SV_Target\n\
{\n\
	float4 finalColor = 0;\n\
	for (int i = 0; i<2; i++)\n\
	{\n\
		finalColor += saturate(dot((float3)vLightDir[i],input.Norm) * vLightColor[i]); \n\
	}\n\
	finalColor.a = 1;\n\
	return finalColor;\n\
}";
