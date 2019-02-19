#include "hookhelper.h"
#include <atlconv.h>

#include <stdio.h>
#include"tlhelp32.h"
#include "Psapi.h"
#include <tchar.h>
#include <QDebug>
#include "logging.hpp"

HookHelper* HookHelper::m_pInstance = NULL;

HookHelper* HookHelper::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new HookHelper;
	}
	return m_pInstance;
}

HookHelper::HookHelper(QObject *parent)
	: QObject(parent)
{
	//����winlogon.exe����PID
	dwPID_ = GetPidByProcessName(_T("winlogon.exe"));

	//����Ȩ��
	EnableDebugPriv();
}

HookHelper::~HookHelper()
{

}

HHOOK keyHook_ = NULL;

//���̹��ӹ���
LRESULT CALLBACK keyProc_(int nCode, WPARAM wParam, LPARAM lParam)
{
	//��WH_KEYBOARD_LLģʽ��lParam ��ָ��KBDLLHOOKSTRUCT���͵�ַ
	KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
	//���nCode����HC_ACTION�������Ϣ�����С��0�������ӳ̾ͱ��뽫����Ϣ���ݸ� CallNextHookEx
	if (nCode == HC_ACTION){
		if (pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_SHIFT) & 0x8000){
			qDebug() << "Ctrl+Shift+Esc";
		}
		else if (pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000){
			qDebug() << "Ctrl+Esc";
		}
		else if (pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN){
			qDebug() << "Alt+Tab";
		}
		else if (pkbhs->vkCode == VK_ESCAPE && pkbhs->flags &LLKHF_ALTDOWN){
			qDebug() << "Alt+Esc";
		}
		else if (pkbhs->vkCode == VK_LWIN || pkbhs->vkCode == VK_RWIN){
			qDebug() << "LWIN/RWIN";
		}
		else if (pkbhs->vkCode == VK_F4 && pkbhs->flags & LLKHF_ALTDOWN){
			qDebug() << "Alt+F4";
		}
		else{
			return 0;
		}
		//����1��ʾ��ȡ��Ϣ���ٴ���,����0��ʾ��������,��Ϣ��������
		return 1;
	}
	return CallNextHookEx(keyHook_, nCode, wParam, lParam);
}

//���ù���
void setHook()
{
	keyHook_ = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc_, GetModuleHandle(NULL), 0);
}

//ע������
void unHook()
{
	UnhookWindowsHookEx(keyHook_);
}

void HookHelper::setHookFunc()
{
	OnRFreeze();

	setHook();
}

void HookHelper::unHookFunc()
{
	OnRUnfreeze();

	unHook();
}

/*
�ɽ�������ȡPID
*/
DWORD HookHelper::GetPidByProcessName(LPCTSTR pszName)
{
	PROCESSENTRY32    pe32;
	HANDLE        hSnapshot;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return -1;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe32))
	{
		CloseHandle(hSnapshot);
		return -1;
	}

	do
	{
		if (lstrcmpi(pe32.szExeFile, pszName) == 0)
		{
			CloseHandle(hSnapshot);
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);

	return -1;
}

//����Ȩ��
void HookHelper::EnableDebugPriv(void)
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		CloseHandle(hToken);
		return;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
		CloseHandle(hToken);
		return;
	}
}

//����
void HookHelper::OnRFreeze()
{
	THREADENTRY32 th32;
	th32.dwSize = sizeof(th32);

	HANDLE hThreadSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		Log::Info("CreateToolhelp32Snapshot failed !");
		return;
	}

	BOOL b = ::Thread32First(hThreadSnap, &th32);
	while (b)
	{
		if (th32.th32OwnerProcessID == dwPID_)
		{
			HANDLE oth = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (!(::SuspendThread(oth)))
			{
				Log::Info("have RFreezed !");
			}
			else
			{
				Log::Info("RFreeze failed !");
			}
			CloseHandle(oth);
			break;
		}
		::Thread32Next(hThreadSnap, &th32);
	}
	::CloseHandle(hThreadSnap);
}

//�ⶳ
void HookHelper::OnRUnfreeze()
{
	THREADENTRY32 th32;
	th32.dwSize = sizeof(th32);

	HANDLE hThreadSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		Log::Info("CreateToolhelp32Snapshot failed !");
		return;
	}

	BOOL b = ::Thread32First(hThreadSnap, &th32);
	while (b)
	{
		if (th32.th32OwnerProcessID == dwPID_)
		{
			HANDLE oth = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (::ResumeThread(oth))
			{
				Log::Info("have RUnfreezed !");
			}
			else
			{
				Log::Info("RUnfreeze failed !");
			}
			CloseHandle(oth);
			break;
		}
		::Thread32Next(hThreadSnap, &th32);
	}
	::CloseHandle(hThreadSnap);
}