#include "sessionmgr.h"

QString SessionMgr::host = QString("http://localhost:8081");
QString SessionMgr::session_id = QString("");
QNetworkAccessManager SessionMgr::manager;

QString SessionMgr::getUrl(const QString &url)
{
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString result = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());
    if (result.isEmpty()) {
        throw std::logic_error("Network error");
    }
    return result;
}

void SessionMgr::login(const QString &username, const QString &password)
{
    QString pwd_hash = "";
    pwd_hash.append(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex());
    QString url = host + "/user/login?username=" + username + "&pwdhash=" + pwd_hash;
    QJsonObject json = QJsonDocument::fromJson(getUrl(url).toUtf8()).object();
    if (json.value("result").toInt() < 0) {
        throw std::logic_error(json.value("errmsg").toString().toUtf8().data());
    }
    session_id = json.value("sessid").toString();
}

void SessionMgr::logout()
{
    session_id = "";
}

QString SessionMgr::saveFile(const QString &code, const QString &filename)
{
    QString enc_code = QString(code.toUtf8().toPercentEncoding().toPercentEncoding());
    QString url = host + "/io/save?sessid=" + session_id + "&code=" + enc_code + "&filename=" + filename;
    QJsonObject json = QJsonDocument::fromJson(getUrl(url).toUtf8()).object();
    if (json.value("result").toInt() < 0) {
        throw std::logic_error(json.value("errmsg").toString().toUtf8().data());
    }
    return json.value("version").toString();
}

std::pair<QString, QString> SessionMgr::execute(const QString &code, const QString &input)
{
    QString enc_code = QString(code.toUtf8().toPercentEncoding().toPercentEncoding());
    QString enc_input = QString(input.toUtf8().toPercentEncoding().toPercentEncoding());
    QString url = host + "/io/execute?sessid=" + session_id + "&code=" + enc_code + "&input=" + enc_input;
    QJsonObject json = QJsonDocument::fromJson(getUrl(url).toUtf8()).object();
    if (json.value("result").toInt() < 0) {
        throw std::logic_error(json.value("errmsg").toString().toUtf8().data());
    }
    return std::make_pair(json.value("output").toString(), json.value("time").toString());
}
