#ifndef HOOKHELPER_H
#define HOOKHELPER_H

#include <QObject>
#include "Windows.h"

/*******�����ȼ�*******/

//��ע����Ŀ¼������������
#define TASKMANAGER "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"

class HookHelper : public QObject
{
	Q_OBJECT

public:
	static HookHelper* instance();

	void setHookFunc();
	void unHookFunc();

	void OnRFreeze();
	void OnRUnfreeze();
private:
	explicit HookHelper(QObject *parent = 0);
	~HookHelper();

	DWORD GetPidByProcessName(LPCTSTR pszName);
	void EnableDebugPriv(void);
private:
	static HookHelper* m_pInstance;
	DWORD dwPID_;
};

#endif // HOOKHELPER_H
