#ifndef IENGINE_H
#define IENGINE_H

class seConfig
{
public:
	int screenWidth;
	int screenHeight;
	bool fullScreen;
};

class seRenderer;

class seEngine
{
public:
	virtual ~seEngine() {};
	virtual void Close() = 0;
	virtual void InitConfig(const seConfig& config) = 0;
	virtual void Run() = 0;
	virtual seRenderer* GetRenderer() const = 0;
	virtual bool OnSize(int width,int height) = 0;
};

DLL_INTERFACE seEngine* GetSimpleEngine();

#endif // !IENGINE_H

