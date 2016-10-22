#ifndef SESSIONMGR_H
#define SESSIONMGR_H

#include <QtNetwork>

class SessionMgr
{
public:
    static QString host;
    static QString getUrl(const QString);
    static void login(const QString, const QString);

private:
    static QString session_id;
    static QNetworkAccessManager manager;
};

#endif // SESSIONMGR_H
