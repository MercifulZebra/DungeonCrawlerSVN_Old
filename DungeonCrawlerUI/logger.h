#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QVector>

namespace logger {

enum LogType {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

class LogItem : QObject
{
    Q_OBJECT

public:
    LogItem(QObject *parent = 0);

    LogType type;
    QString msg;

    bool used_flag;
};

class Logger : QObject
{
    Q_OBJECT

public:
    Logger(QObject *parent = 0);
    bool init(QString config);
    bool allocateItems(int num);

    void trace(QString nMsg);
    void debug(QString nMsg);
    void info(QString nMsg);
    void warn(QString nMsg);
    void err(QString nMsg);

    QStringList getLogString();
    QString getLogError();

    QVector<LogItem*> log;
    QVector<LogItem*> log_pool;
    QString configFilename;
    int numAllocated_items;

    bool error_flag;
};

}

#endif // LOGGER_H
