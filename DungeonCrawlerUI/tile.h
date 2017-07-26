#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QRect>

namespace logger {
    class Logger;
}
/*
 * Tile Types
 */

//Straight Wall
//Inside Corner Wall
//Outside Corner Wall
//Double Inside Corner
//LeftWallRightCorner
//RightWallLeftCorner
//Straight Tunnel
//Corner Tunnel

class QPainter;

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = 0);

    bool init(logger::Logger *nLog);

    void paintThis(QPainter *painter);

    QRect getBoundingBox();
    void setBoundingBox(QRect nRect);
private:

    logger::Logger *log;
    QRect           boundingBox;

signals:

public slots:
};

#endif // TILE_H
