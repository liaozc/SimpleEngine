#ifndef  SIMPLE_ENGINE_H
#define  SIMPLE_ENGINE_H

#include "IEngine.h"

class seIWndSys;

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
private:
	seIWndSys* mWndSys;
};

#endif // ! SIMPLE_ENGINE_H

