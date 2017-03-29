#ifndef PROGRAM_H
#define PROGRAM_H

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;
struct ID3D11DeviceContext;
class seProgram
{
public:
	seProgram(ID3D11Device* device);
	~seProgram();
	bool FromSource(const char* src);
	void Apply(ID3D11DeviceContext* context);
protected:
	ID3D11VertexShader*     mVS;
	ID3D11PixelShader*      mPS;
	ID3D11InputLayout*		mLayout;
	ID3D11Device*			mDevice;
};

#endif
