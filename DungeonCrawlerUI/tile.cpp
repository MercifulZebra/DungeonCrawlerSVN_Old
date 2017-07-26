#include "tile.h"

#include <QPainter>

Tile::Tile(QObject *parent) : QObject(parent),
    log(NULL),
    boundingBox()
{

}

bool Tile::init(logger::Logger *nLog) {
    bool initSuccess_flag = true;

    log = nLog;

    return initSuccess_flag;
}

void Tile::paintThis(QPainter *painter) {
    painter->drawRect(boundingBox);
}

QRect Tile::getBoundingBox() {
    return boundingBox;
}

void Tile::setBoundingBox(QRect nRect) {
    boundingBox = nRect;
}
