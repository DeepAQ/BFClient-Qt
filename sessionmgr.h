#ifndef SESSIONMGR_H
#define SESSIONMGR_H

#include <QtNetwork>

class SessionMgr
{
public:
    static QString host;
    static QString getUrl(const QString &url);
    static void login(const QString &username, const QString &password);
    static void logout();
    static QString saveFile(const QString &code, const QString &filename);
    static std::pair<QString, QString> execute(const QString &code, const QString &input);

private:
    static QString session_id;
    static QNetworkAccessManager manager;
};

#endif // SESSIONMGR_H
