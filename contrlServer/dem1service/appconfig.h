#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <iostream>
#include <memory>
#include "../../../../spdlog/spdlog.h"

using namespace std;

// ʹ�ú��������ʵ��
#define AppConfigHandler AppConfig::GetInstance()

namespace dem1 {
	namespace server {
class AppConfig
{
public:
	static AppConfig& GetInstance(void);		/// ʵ��(��������)

	//��ʼ����־����
	void InitialiseLog(const string &path);
	void DropSpdLog();
	void Info(const string &msg);
private:
	AppConfig();
	~AppConfig(void);
private:
	std::shared_ptr<spdlog::logger> m_daily_logger;
	std::shared_ptr<spdlog::logger> m_console_logger;
	friend class auto_ptr<AppConfig>;				/// ʹ������ָ��
	/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
	/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
	static auto_ptr<AppConfig> auto_ptr_instance;	/// Ωһʵ��
};
	}  // namespace server
} // namespace dem1
#endif // APPCONFIG_H
