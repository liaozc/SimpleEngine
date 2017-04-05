#ifndef SAMPLE_PUBLIC_H
#define SAMPLE_PUBLIC_H

struct ID3D11DeviceContext;
struct ID3D11Device;
struct ID3D11Buffer;
class  seProgram;

class seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		mDevice = device;
		mContext = context;
	}
	virtual void Render() = 0;
	virtual void UnInit() = 0;
	virtual void OnSceneSizeChanged(int width, int height) = 0;
protected:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
};

#endif