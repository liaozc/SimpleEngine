"\n\
cbuffer ConstantBuffer : register(b0)\n\
{\n\
	matrix World;\n\
	matrix View;\n\
	matrix Projection;\n\
}\n\
struct VS_INPUT\n\
{\n\
	float4 Pos : POSITION;\n\
	float4 Color : COLOR;\n\
};\n\
struct PS_INPUT\n\
{\n\
	float4 Pos : SV_POSITION;\n\
	float4 Color : COLOR;\n\
};\n\
PS_INPUT VS(VS_INPUT input)\n\
{\n\
	PS_INPUT output = (PS_INPUT)0;\n\
	output.Pos = mul(input.Pos, World);\n\
	output.Pos = mul(output.Pos, View);\n\
	output.Pos = mul(output.Pos, Projection);\n\
	output.Color = input.Color;\n\
	return output;\n\
}\n\
\n\
float4 PS(PS_INPUT input) : SV_Target\n\
{\n\
	return input.Color;\n\
}";
