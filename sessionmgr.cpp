#include "sessionmgr.h"

QString SessionMgr::host = QString("http://localhost:8081");
QString SessionMgr::session_id = QString("");
QNetworkAccessManager SessionMgr::manager;

QString SessionMgr::getUrl(const QString url)
{
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString result = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());
    delete reply;
    return result;
}

void SessionMgr::login(const QString username, const QString password)
{
    QString pwd_hash = "";
    pwd_hash.append(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex());
    QString url = host + "/user/login?username=" + username + "&pwdhash=" + pwd_hash;
    delete &pwd_hash;
    QJsonObject json = QJsonDocument::fromJson(getUrl(url).toUtf8()).object();
    delete &url;
    if (json.value("result").toInt() != 0) {
        throw std::logic_error(json.value("errmsg").toString().toUtf8().data());
    }
    session_id = json.value("sessid").toString();
    delete &json;
}
