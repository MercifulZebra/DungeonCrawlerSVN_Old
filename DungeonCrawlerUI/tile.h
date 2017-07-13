#ifndef TILE_H
#define TILE_H

#include <QObject>

namespace logger {
    class Logger;
}

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = 0);

    bool init(logger::Logger *nLog);

private:

    logger::Logger *log;

signals:

public slots:
};

#endif // TILE_H
