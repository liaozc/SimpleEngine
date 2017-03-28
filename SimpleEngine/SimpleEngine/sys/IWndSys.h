#ifndef I_WINDOW_SYSTEM_H
#define I_WINDOW_SYSTEM_H

class seIWndSys
{
public:
	virtual ~seIWndSys() {}
	virtual void Init() = 0;
	virtual void CreateWnd(const seConfig& config) = 0;
	virtual void Run(bool& exit) = 0;
};

seIWndSys* CreateWndSystem();

#endif
