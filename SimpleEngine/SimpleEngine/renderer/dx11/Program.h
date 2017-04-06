#ifndef PROGRAM_H
#define PROGRAM_H

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class seProgram
{
public:
	seProgram(ID3D11Device* device);
	~seProgram();
	bool FromSource(const char* src,D3D11_INPUT_ELEMENT_DESC layout[],int numLayout);
	void Apply(ID3D11DeviceContext* context);
	void UpdateVSConstantBuffer(ID3D11DeviceContext* context, ID3D11Buffer* vsCB, UINT slot);
	void UpdatePSConstantBuffer(ID3D11DeviceContext* context, ID3D11Buffer* psCB, UINT slot);
	void UpdatePSTexture(ID3D11DeviceContext* context, ID3D11ShaderResourceView* tex, UINT slot);
	void UpdatePSSampleState(ID3D11DeviceContext* context, ID3D11SamplerState* sampleState, UINT slot);
protected:
	ID3D11VertexShader*     mVS;
	ID3D11PixelShader*      mPS;
	ID3D11InputLayout*		mLayout;
	ID3D11Device*			mDevice;
};

#endif
