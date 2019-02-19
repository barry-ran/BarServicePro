#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMutex>
#include <QPixmap>
#include <QProcess>
#include <QSystemTrayIcon>

#include "tcpclient.hpp"

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "KillExe.h"

class QPushButton;
class QCheckBox;
class QLabel;
class QSlider;
class QMenu;
class QAction;

using namespace dm::server;
using namespace dm::client;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   
	void showAutoRunApp();
private:
	//��ʼ��TCP
	void initTcpSocket();
	//��ʼ������
	void initUI();
	//��ʼ����������
	void initConnect();
	//�첽TcpReader
	void RunCommSocketThreadFunc();
	//ע��
	void registerToServer();
	//��ʼ������
	void initSystemtray();
	//�ύ���������仯
	void commitCallVoiceChanged();

	void handle_json_header(boost::property_tree::ptree header, std::string headTitle, std::string &json_str);
protected:
	void paintEvent(QPaintEvent *event);
	void showEvent(QShowEvent *event);
private slots:
	//SocketMonitorManager�����źŲۣ�����֪ͨ������״̬
	void slot0nSocketConnectStatus(int status);
	void slotOnShowSystemTray();
	void activated(QSystemTrayIcon::ActivationReason reason);
	void slotOnShowNormal();
	void slotOnCallVoiceChanged(int value);
	void slotOnPlayVoiceChanged(int value);
private:
	QSystemTrayIcon *m_trayIcon;
	KillExe kill_exe_;
	boost::shared_ptr<boost::thread> comm_socket_thread_;
	//ͨ��socket
	boost::shared_ptr<dm::client::tcpclient> tc_comm_ptr_;

	QPushButton *btn_min;
	QPushButton *btn_close;
	QPushButton *btn_confirm;
	QCheckBox *cbox_auto_exec;
	QSlider *slider_call;
	QSlider *slider_play;
	QLabel *lbl_call_num;
	QLabel *lbl_play_num;
	QLabel *lbl_tip;
	QMenu *trayIconMenu;
	QAction *quitAction;
	QAction *showAction;
};

#endif // MAINWINDOW_H
