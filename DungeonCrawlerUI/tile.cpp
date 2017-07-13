#include "tile.h"

Tile::Tile(QObject *parent) : QObject(parent)
{

}

bool Tile::init(logger::Logger *nLog) {
    bool initSuccess_flag = true;

    log = nLog;

    return initSuccess_flag;
}
