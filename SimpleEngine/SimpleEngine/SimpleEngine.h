#ifndef  SIMPLE_ENGINE_H
#define  SIMPLE_ENGINE_H

#include "IEngine.h"

class seSysWnd;
class seRenderer;

class seEngine :public seIEngine
{
	friend seIEngine* GetSimpleEngine();
protected:
	seEngine();
	virtual ~seEngine();
	void init();
public:
	virtual void Close();
	virtual void InitConfig(const seConfig& config);
	virtual void Run();
	virtual seRenderer* GetRenderer() const;
private:
	seSysWnd* mSysWnd;
	seRenderer* mRenderer;
};

#endif // ! SIMPLE_ENGINE_H

