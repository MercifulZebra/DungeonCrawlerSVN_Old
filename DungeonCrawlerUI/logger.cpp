#include "logger.h"

#include <QFile>
#include <QDebug>
#include <QDir>

using namespace logger;


Logger::Logger(QObject* parent): QObject(parent),
log(),
configFilename(),
error_flag(false)
{

}

bool Logger::init(QString config) {
    bool initSuccess_flag = true;
    bool fileOpen_flag = false;

    //Look For config Options
    configFilename = config;
    QFile configFile(configFilename);

    qDebug() << QDir::current();

    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileOpen_flag = true;

        configFile.close();
    }
    else {
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

void Logger::trace(QString nMsg) {

    if (!error_flag) {
        QString logMsg("TRACE - " + nMsg + "\n");
        log.append(logMsg);
        qDebug().noquote() << logMsg;
    }
}

void Logger::debug(QString nMsg) {
    if (!error_flag) {
        QString logMsg("DEBUG - " + nMsg + "\n");
        log.append(logMsg);
        qDebug().noquote() << logMsg;
    }
}

void Logger::info(QString nMsg) {
    if (!error_flag) {
        QString logMsg("INFO - " + nMsg + "\n");
        log.append(logMsg);
        qDebug().noquote() << logMsg;
    }
}

void Logger::warn(QString nMsg) {
    if (!error_flag) {
        QString logMsg("WARN - " + nMsg + "\n");
        log.append(logMsg);
        qDebug().noquote() << logMsg;
    }
}

void Logger::err(QString nMsg) {
    if (!error_flag) {
        QString logMsg("ERROR - " + nMsg + "\n");
        log.append(logMsg);
        qDebug().noquote() << logMsg;
    }
}

QString Logger::getLogString() {
    return log;
}
