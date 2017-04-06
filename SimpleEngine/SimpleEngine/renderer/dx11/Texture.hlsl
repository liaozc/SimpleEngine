"\n\
Texture2D txDiffuse : register(t0);\n\
SamplerState samLinear : register(s0);\n\
\n\
cbuffer cbNeverChanges : register(b0)\n\
{\n\
	matrix View;\n\
};\n\
\n\
cbuffer cbChangeOnResize : register(b1)\n\
{\n\
	matrix Projection;\n\
};\n\
\n\
cbuffer cbChangesEveryFrame : register(b2)\n\
{\n\
	matrix World;\n\
	float4 vMeshColor;\n\
};\n\
\n\
struct VS_INPUT\n\
{\n\
	float4 Pos : POSITION;\n\
	float2 Tex : TEXCOORD0;\n\
};\n\
\n\
struct PS_INPUT\n\
{\n\
	float4 Pos : SV_POSITION;\n\
	float2 Tex : TEXCOORD0;\n\
};\n\
\n\
PS_INPUT VS(VS_INPUT input)\n\
{\n\
	PS_INPUT output = (PS_INPUT)0;\n\
	output.Pos = mul(input.Pos, World);\n\
	output.Pos = mul(output.Pos, View);\n\
	output.Pos = mul(output.Pos, Projection);\n\
	output.Tex = input.Tex;\n\
\n\
	return output;\n\
}\n\
\n\
float4 PS(PS_INPUT input) : SV_Target\n\
{\n\
	return txDiffuse.Sample(samLinear, input.Tex) * vMeshColor;\n\
}";
