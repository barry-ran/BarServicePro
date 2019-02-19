#pragma once

#include <memory>
#include <list>
#include <map>

using namespace std;

namespace dm {
	namespace server {
class EventHandler
{
private:
	friend class auto_ptr<EventHandler>;				/// ʹ������ָ��
	/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
	/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
	static auto_ptr<EventHandler> auto_ptr_instance;	/// Ωһʵ��
private:
	EventHandler();
	~EventHandler(void);
public:
	static EventHandler& GetInstance(void);		/// ʵ��(��������)


	void rebootClientHandler();   //���������ն��豸
	void shutdownClientHandler();  //����ػ�����
};
	}  // namespace server
} // namespace dm
