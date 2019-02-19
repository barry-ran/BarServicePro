#include "HttpCommitFaceData.h"
#include <QScriptEngine>
#include <QScriptValue>
#include <QDebug>

#include "enumData.h"
#include "HttpSignal.h"
#include "constData.h"
#include "commonFun.h"
#include "logging.hpp"

HttpCommitFaceData::HttpCommitFaceData()
{
	setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpCommitFaceDataOrderAction);
}

HttpCommitFaceData::~HttpCommitFaceData()
{

}

void HttpCommitFaceData::processResponse(QString strResult)
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode = sc.property("code").toInt32();
	QString sMsg = sc.property("message").toString();
	if (!sc.property("code").isValid())
	{
		Log::Info("HttpCommitFaceData ���ز���json��ʽ����");
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}
	if (nCode != e_success)
	{
		Log::Info("%s", this->getTestUrl().toStdString().c_str());
	}

	Log::Info("HttpCommitFaceData %s", strResult.toStdString().c_str());
	int nRespondCode = sc.property("data").property("code").toInt32();
	HttpSignal::instance()->sigOnGetCommitFaceDataRespond(nCode, sMsg, nRespondCode);
	this->deleteLater();
}

void HttpCommitFaceData::processError()
{
	HttpSignal::instance()->sigOnGetCommitFaceDataRespond(e_connectServerError, c_sNetError, -1);
	this->deleteLater();
}
