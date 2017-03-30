"\n\
cbuffer ConstantBuffer : register( b0 )\n\
{\n\
	matrix World;\n\
	matrix View;\n\
	matrix Projection;\n\
}\n\
\n\
struct VS_OUTPUT\n\
{\n\
    float4 Pos : SV_POSITION;\n\
    float4 Color : COLOR0;\n\
};\n\
\n\
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR )\n\
{\n\
    VS_OUTPUT output = (VS_OUTPUT)0;\n\
    output.Pos = mul( Pos, World );\n\
    output.Pos = mul( output.Pos, View );\n\
    output.Pos = mul( output.Pos, Projection );\n\
	output.Color = Color;\n\
    return output;\n\
}\n\
\n\
float4 PS( VS_OUTPUT input ) : SV_Target\n\
{\n\
    return input.Color;\n\
}";
