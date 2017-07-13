#include "logger.h"
#include <QFile>
#include <QDebug>
#include <QDir>
using namespace logger;

LogItem::LogItem(QObject* parent): QObject(parent),
type(LogType::LOG_INFO),
msg(""),
used_flag(false)
{

}

Logger::Logger(QObject* parent): QObject(parent),
log(),
configFilename(),
numAllocated_items(500),
error_flag(false)
{

}

bool Logger::init(QString config) {
    bool initSuccess_flag = true;
    bool fileOpen_flag = false;

    //Look For config Options
    configFilename = config;
    QFile configFile(configFilename);

    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileOpen_flag = true;


        configFile.close();
    }
    else {
        initSuccess_flag = false;
    }

    //Init LogItems

    if (allocateItems(numAllocated_items)) {
        if (!fileOpen_flag) {
            warn(QString("Unable to open config file %1/%2.").arg(QDir::currentPath()).arg(configFilename));
        }

        info(QString("Allocated %1 LogItems.").arg(numAllocated_items));

    }
    else { //allocateItems(numAllocated_items)
        initSuccess_flag = false;
        qDebug() << "Error - Unable to allocate Log Items";
    }



    return initSuccess_flag;
}

bool Logger::allocateItems(int num) {
    bool return_flag = true;
    int numSuccess_items = 0;
    for (int i = 0; i < numAllocated_items; i++) {
        LogItem *nItem = new LogItem(this);

        if (nItem != NULL) {
            log_pool.append(nItem);
            numSuccess_items++;
        }
    }

    if (numSuccess_items < num) {
        return_flag = false;
    }

    return return_flag;
}

void Logger::trace(QString nMsg) {
    if (log_pool.empty()) {
        if (!allocateItems(numAllocated_items)) {
            qDebug () << "Unable to allocate new Items";
            error_flag = true;
        }
    }

    if (!error_flag) {
        LogItem* nItem = log_pool.takeLast();

        nItem->type = LogType::LOG_TRACE;
        nItem->msg = "TRACE - " + nMsg;

        log.append(nItem);
        qDebug().noquote() << nItem->msg;
    }
}

void Logger::debug(QString nMsg) {
    if (log_pool.empty()) {
        if (!allocateItems(numAllocated_items)) {
            qDebug () << "Unable to allocate new Items";
            error_flag = true;
        }
    }

    if (!error_flag) {
        LogItem* nItem = log_pool.takeLast();

        nItem->type = LogType::LOG_DEBUG;
        nItem->msg = "DEBUG - " + nMsg;

        log.append(nItem);
        qDebug().noquote() << nItem->msg;
    }
}

void Logger::info(QString nMsg) {
    if (log_pool.empty()) {
        if (!allocateItems(numAllocated_items)) {
            qDebug() << "Unable to allocate new Items";
            error_flag = true;
        }
    }

    if (!error_flag) {
        LogItem* nItem = log_pool.takeLast();

        nItem->type = LogType::LOG_INFO;
        nItem->msg = "INFO  - " + nMsg;

        log.append(nItem);
        qDebug().noquote() << nItem->msg;
    }
}

void Logger::warn(QString nMsg) {
    if (log_pool.empty()) {
        if (!allocateItems(numAllocated_items)) {
            qDebug () << "Unable to allocate new Items";
            error_flag = true;
        }
    }

    if (!error_flag) {
        LogItem* nItem = log_pool.takeLast();

        nItem->type = LogType::LOG_WARN;
        nItem->msg = "WARN  - " + nMsg;

        log.append(nItem);
        qDebug().noquote() << nItem->msg;
    }
}

void Logger::err(QString nMsg) {
    if (log_pool.empty()) {
        if (!allocateItems(numAllocated_items)) {
            qDebug () << "Unable to allocate new Items";
            error_flag = true;
        }
    }

    if (!error_flag) {
        LogItem* nItem = log_pool.takeLast();

        nItem->type = LogType::LOG_ERROR;
        nItem->msg = "ERROR - " + nMsg;

        log.append(nItem);
        qDebug().noquote() << nItem->msg;
    }

}

QStringList Logger::getLogString() {

    QStringList rList;

    for (int i = 0; i < log.count(); i++) {
        rList << log.at(i)->msg;
    }

    return rList;
}

QString Logger::getLogError() {
    QString rList;

    for (int i = 0; i < log.count(); i++) {
        if (log.at(i)->type == LogType::LOG_ERROR) {
            rList.append(log.at(i)->msg);
            rList.append("\n");
        }
    }

    return rList;
}
