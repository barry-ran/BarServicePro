#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <io.h> 
#include <iostream>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include "KillExe.h"

using namespace std;

KillExe kill_exe_;
//����DOS�ڴ���
//#pragma comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"" ) 

//����·�����̶�
#define MAX_PATH 4096
//�����ػ���������
#define PROCCESS_NAME "FaceTection.exe"
//����д���ע���·��
#define SELFSTART_REGEDIT_PATH "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"

//���ñ�����������
BOOL SetSelfStart()
{
	//��ȡ������������
	char pName[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, pName, MAX_PATH);

	//��ע�����д��������Ϣ
	HKEY hKey = NULL;
	LONG lRet = NULL;
	lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, SELFSTART_REGEDIT_PATH, 0, KEY_ALL_ACCESS, &hKey);

	//�ж��Ƿ�ɹ�
	if (lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	lRet = RegSetValueExA(hKey, "DaemonTool", 0, REG_SZ, (const unsigned char*)pName, strlen(pName) + sizeof(char));
    
	//�ж��Ƿ�ɹ�
	if (lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	//�ر�ע���
	RegCloseKey(hKey);
	return TRUE;
}

int main()
{
	kill_exe_.KillProcess(_T("Daemon.exe"));
	Sleep(500);

	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, true);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

	//��ȡ������������
	char pName[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, pName, MAX_PATH);
	std::string workingFolder(pName);
	size_t pos = workingFolder.find_last_of("\\");
	workingFolder = workingFolder.substr(0, pos + 1);

	//���ó��򿪻�������
	if (!SetSelfStart())
	{
		cout << "�ػ����̿���������ʧ��" << endl;
		return -1;
	}

	STARTUPINFOA si;
	//���̶���
	PROCESS_INFORMATION pi;
	//��ʼ��
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//��ȡ��ǰ�����·��
	char pPath[MAX_PATH] = { 0 };
	memcpy(pPath, workingFolder.c_str(), workingFolder.length());

	//ƴ����Ҫ�ػ��ĳ���
//	strcat_s(pPath, "");
	strcat_s(pPath, PROCCESS_NAME);

	//����cmdִ���ػ����̵��ַ���
	char pCmd[MAX_PATH] = { 0 };
	strcat_s(pCmd, "cmd /c ");
	strcat_s(pCmd, pPath);
	cout << pCmd << endl;

	//����ѭ���������ػ�����
	do{
		//����ػ������Ƿ����
		if (_access(pPath, 0) != -1)
		{
			//�����ӽ��̣��ж��Ƿ�ִ�гɹ�
			if (!CreateProcessA(NULL, pCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				cout << "�ػ���������ʧ�ܣ����򼴽��˳�" << endl;
				return -1;
			}
			//�����ɹ�����ȡ���̵�ID
			cout << "�ػ����̳ɹ���ID:" << pi.dwProcessId << endl;
			cout << "������������������5����Զ��رմ��ڣ������ĵȴ�������"<<endl;
			Sleep(500);
			for (int i = 0; i < 5; ++i)
			{
				cout << "********"<< 5 - i <<"����˳�********"<< endl;
				Sleep(1000);
			}
			ShowWindow(hwnd, false);
			//���޵ȴ��ӽ����˳�
			WaitForSingleObject(pi.hProcess, INFINITE);
			//����˳���
			cout << "�ػ������˳��ˡ�����" << endl;
			//�رս��̺;��
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		else
		{
			cout << "�ػ����򲻴���" << endl;
		}
		//˯һ�£�����
		Sleep(5000);
	} while (true);

	return 0;
}