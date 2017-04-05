#ifndef  SIMPLE_ENGINE_H
#define  SIMPLE_ENGINE_H

#include "engine_public.h"

class seInputEventSystem;
class seSysWnd;
class seRenderer;

class seEngine_Simple :public seEngine
{
	friend seEngine* GetSimpleEngine();
protected:
	seEngine_Simple();
	virtual ~seEngine_Simple();
	void init();
public:
	virtual void Close();
	virtual void InitConfig(const seConfig& config);
	virtual void Run();
	virtual seRenderer* GetRenderer() const;
	virtual bool OnSize(int width, int height);
private:
	seInputEventSystem* mInuptEventSys;
	seSysWnd* mSysWnd;
	seRenderer* mRenderer;
};

#endif // ! SIMPLE_ENGINE_H

