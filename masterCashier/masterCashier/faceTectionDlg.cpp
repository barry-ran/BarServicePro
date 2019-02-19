#include "faceTectionDlg.h"
#include <QDir>
#include <QUuid>
#include <HttpAgent.h>
#include <QMessageBox>
#include <appconfig.h>

using namespace dm::server;

faceTectionDlg::faceTectionDlg(QString idCard, QString userName, QWidget *parent)
	: QDialog(parent)
	, m_idCard(idCard)
	, m_userName(userName)
	, m_counter(0)
{
	ui.setupUi(this);
	setWindowTitle(QStringLiteral("�������"));

	ui.pushButton->setRole(Material::Primary);
	ui.pushButton->setBackgroundMode(Qt::OpaqueMode);
	ui.pushButton->setOverlayStyle(Material::TintedOverlay);
	ui.pushButton->setFixedWidth(300);
	ui.pushButton->setText(QStringLiteral("��ʼ�����ɼ�"));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotOnFunc()));
	connect(HttpAgent::instance(), SIGNAL(sigOnGetFaceDetectionRespond(int, QString, int)), this, SLOT(slotOnGetFaceDetectionRespond(int, QString, int)));
	connect(HttpAgent::instance(), SIGNAL(sigOnGetCommitFaceDataRespond(int, QString, int)), this, SLOT(slotOnGetCommitFaceDataRespond(int, QString, int)));

	camera = new QCamera;//����ͷ
	viewfinder = new QCameraViewfinder(ui.label);
	imageCapture = new QCameraImageCapture(camera);//��ͼ����
	connect(imageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(SavePicture(int, QImage)));
	imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	camera->setCaptureMode(QCamera::CaptureStillImage);
	camera->setViewfinder(viewfinder);

	m_counter_timer = new QTimer(this);
	m_counter_timer->setInterval(1000);
	connect(m_counter_timer, SIGNAL(timeout()), this, SLOT(slotOnCounter()));
	m_counter_timer->start();
}

faceTectionDlg::~faceTectionDlg()
{
	
}

void faceTectionDlg::openCamera()
{
	camera->start();
}

void faceTectionDlg::closeCamera()
{
	camera->stop();
}

void faceTectionDlg::slotOnFunc()
{
	clearFiles();

	imageCapture->capture();
}

void faceTectionDlg::SavePicture(int, QImage image)
{
	image = image.convertToFormat(QImage::Format_RGB888);
	const QPixmap pixmap = QPixmap::fromImage(image);
	QString path = QApplication::applicationDirPath() + "/image/" + QUuid::createUuid().toString() + ".jpg";
	bool ret = pixmap.save(path);
	if (ret)
	{
		HttpAgent::instance()->RequestOnFaceDetection(path);
	}
}

void faceTectionDlg::slotOnCounter()
{
	QDir dir(QApplication::applicationDirPath() + "/image");
	dir.setFilter(QDir::Files);
	int fileCount = dir.count();
	if (m_counter == IMAGENUM && fileCount == IMAGENUM)
	{
		QMessageBox::about(NULL, "tip", QStringLiteral("�����ɼ��ɹ��������ϴ����ݣ�"));
		HttpAgent::instance()->RequestOnCommitFaceData(m_idCard, m_userName);
		m_counter = 0;
	}
}

void faceTectionDlg::slotOnGetFaceDetectionRespond(int nCode, QString sMsg, int nRespondCode)
{
	if (nCode != e_success)
	{
		//AppConfigHandler.Info("Request On GetFaceDetectionRespond failed : " + sMsg.toStdString());
		m_counter = 0;
		QMessageBox::warning(NULL, "warning", QStringLiteral("������������쳣--������:%1, ������Ϣ:%2").arg(nCode).arg(sMsg));
	}
	else
	{
		//AppConfigHandler.Info("Request On GetFaceDetectionRespond success");
		if (nRespondCode == 0)
		{
			if (++m_counter < IMAGENUM)
			{
				imageCapture->capture();
			}
		}
		else
		{
			m_counter = 0;
			QMessageBox::warning(NULL, "warning", QStringLiteral("�����ɼ�ʧ�ܣ������²ɼ���"));
		}
	}
}

void faceTectionDlg::slotOnGetCommitFaceDataRespond(int nCode, QString sMsg, int nRespondCode)
{
	if (nCode != e_success)
	{
		//AppConfigHandler.Info("Request On GetCommitFaceDataRespond failed : " + sMsg.toStdString());
		QMessageBox::warning(NULL, "warning", QStringLiteral("������������쳣--������:%1, ������Ϣ:%2").arg(nCode).arg(sMsg));
	}
	else
	{
		//AppConfigHandler.Info("Request On GetCommitFaceDataRespond success");
		QMessageBox::warning(NULL, "warning", QStringLiteral("���������ϴ��ɹ���"));
		closeCamera();
		hide();
	}
}

void faceTectionDlg::clearFiles()
{
	QDir dir(QApplication::applicationDirPath() + "/image");
	dir.setFilter(QDir::Files);
	int fileCount = dir.count();
	for (int i = 0; i < fileCount; i++)
	{
		dir.remove(dir[i]);
	}
}

// ɾ���ļ���
bool faceTectionDlg::DelDir(const QString &path)
{
	if (path.isEmpty()){
		return false;
	}
	QDir dir(path);
	if (!dir.exists()){
		return true;
	}
	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //���ù��� 
	QFileInfoList fileList = dir.entryInfoList(); // ��ȡ���е��ļ���Ϣ 
	foreach(QFileInfo file, fileList){ //�����ļ���Ϣ 
		if (file.isFile()){ // ���ļ���ɾ�� 
			file.dir().remove(file.fileName());
		}
		else{ // �ݹ�ɾ�� 
			DelDir(file.absoluteFilePath());
		}
	}
	return dir.rmpath(dir.absolutePath()); // ɾ���ļ��� 
}