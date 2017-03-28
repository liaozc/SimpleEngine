#ifndef IENGINE_H
#define IENGINE_H

class seConfig
{
public:
	int screenWidth;
	int screenHeight;
	bool fullScreen;
};

class seIEngine 
{
public:
	virtual ~seIEngine() {};
	virtual void Close() = 0;
	virtual void InitConfig(const seConfig& config) = 0;
	virtual void Run() = 0;
};

DLL_INTERFACE seIEngine* GetSimpleEngine();

#endif // !IENGINE_H

