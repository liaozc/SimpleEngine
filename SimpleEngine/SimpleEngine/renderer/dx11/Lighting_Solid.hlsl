"\n\
cbuffer ConstantBuffer : register(b0)\n\
{\n\
	matrix World;\n\
	matrix View;\n\
	matrix Projection;\n\
	float4 vColor; \n\
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
	float4 Col : COLOR0;\n\
};\n\
\n\
PS_INPUT VS(VS_INPUT input)\n\
{\n\
	PS_INPUT output = (PS_INPUT)0;\n\
	output.Pos = mul(input.Pos, World);\n\
	output.Pos = mul(output.Pos, View);\n\
	output.Pos = mul(output.Pos, Projection);\n\
	return output;\n\
}\n\
\n\
float4 PS( PS_INPUT input) : SV_Target\n\
{\n\
	return vColor;\n\
}";
