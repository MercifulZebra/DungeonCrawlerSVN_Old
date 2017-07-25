#include "mapwindow.h"

#include "logger.h"
#include "tile.h"

#include <QApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

MapWindow::MapWindow(QWidget *parent) : QOpenGLWidget(parent),
    log(NULL),
    tileArray(),
    northingOffset_inch(0.0),
    eastingOffset_inch(0.0),
    inchPerPixel(.5),
    previousMouse_pos(),
    currentMouse_pos(),
    tileWidth_inches(60),
    tileHeight_inches(60),
    paintCycleTime_s(0.0),
    debugLine1(),
    debugTextPen(),
    debugTextFont()
{
}

bool MapWindow::initWindow(QString /*config_filename*/, logger::Logger *nLog) {
    bool initSuccess_flag = true;

    log = nLog;

    setMouseTracking(true);

    //Set Up Tiles
    changeSize(5, 5, true);

    //Init Paint Tools
    debugTextPen = QPen(Qt::white);
    debugTextFont.setPixelSize(20);

    backgroundBrush = QBrush(QColor(0, 0, 0));

    return initSuccess_flag;
}

void MapWindow::mousePressEvent(QMouseEvent *e) {

    if (e->buttons() == Qt::LeftButton) {
        if (QApplication::keyboardModifiers() == Qt::ControlModifier) {

        }
        else if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {

        }
        else if (QApplication::keyboardModifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {

        }
        else {
            previousMouse_pos = e->pos();
        }
    }

    update();
}

void MapWindow::mouseReleaseEvent(QMouseEvent * /*event*/) {
    previousMouse_pos = QPoint(-1, -1);
}

void MapWindow::mouseMoveEvent(QMouseEvent *e) {

    handleMouseMove(e);

    QOpenGLWidget::mouseMoveEvent(e);
    update();
}

void MapWindow::wheelEvent(QWheelEvent *e) {
    double rotDelta = static_cast<float>(e->angleDelta().y());

    inchPerPixel = inchPerPixel - (inchPerPixel * (rotDelta / 1200.0));
    update();
}

void MapWindow::handleMouseMove(QMouseEvent *e) {

    currentMouse_pos = e->pos();

    if (e->buttons() == Qt::LeftButton) {
        northingOffset_inch = northingOffset_inch - ((currentMouse_pos.y() - previousMouse_pos.y()) * inchPerPixel);
        eastingOffset_inch = eastingOffset_inch - ((currentMouse_pos.x() - previousMouse_pos.x()) * inchPerPixel);

        previousMouse_pos = currentMouse_pos;
    }

}

void MapWindow::handleMoveLocation(QMouseEvent * /*e*/) {

}

void MapWindow::handleRightMouseMove(QMouseEvent * /*e*/) {

}

void MapWindow::handleShiftMouseMove(QMouseEvent * /*e*/) {

}

void MapWindow::handleControlMouseMove(QMouseEvent * /*e*/) {

}

void MapWindow::paintEvent(QPaintEvent *e) {
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);
    paintThis(&painter, e);
    painter.end();

}

void MapWindow::paintThis(QPainter *painter, QPaintEvent* pEvent) {

    QElapsedTimer timer;
    timer.start();

    paintBackground(painter, pEvent);
    paintTiles(painter);
    paintDebugText(painter);
    paintCenterMark(painter);

    paintCycleTime_s = timer.elapsed();
}

void MapWindow::paintBackground(QPainter *painter, QPaintEvent *pEvent) {
    painter->save();
    painter->fillRect(pEvent->rect(), backgroundBrush);

    painter->restore();
}

void MapWindow::paintDebugText(QPainter *painter) {
    painter->save();

    painter->translate(0, height());

    int dWidth          = 300;
    int dHeight         = 110;
    int dLeftBorder     = 10;
    int dBottomBorder   = 10;

    QRect dRect(QPoint(dLeftBorder, -dBottomBorder - dHeight), QPoint(dLeftBorder + dWidth, -dBottomBorder));

    QString line1 = debugLine1;
    QString line2 = QString("");
    QString line3 = QString("");
    QString line4 = QString("");
    QString line5 = QString("IPP: %1").arg(inchPerPixel);
    QString line6 = QString("NumTiles: %1 NumPool: %2").arg(getTileArraySize()).arg(tilePool.length());
    QString line7 = QString("Mouse Position: (%1, %2) North/East: (%3 / %4)").arg(currentMouse_pos.x()).arg(currentMouse_pos.y()).arg(northingOffset_inch).arg(eastingOffset_inch);
    QString line8 = QString("Last Paint Cycle Time: %1 s").arg(paintCycleTime_s / 1000, 0, 'g', 3);

    QString dText = QString("%1 \n%2 \n%3 \n%4 \n%5 \n%6 \n%7 \n%8").arg(line1).arg(line2).arg(line3).arg(line4).arg(line5).arg(line6).arg(line7).arg(line8);

    painter->drawText(dRect, dText);

    painter->restore();
}

void MapWindow::paintTiles(QPainter *painter) {
    painter->save();
    painter->translate(this->width() / 2, this->height() / 2);

    int leftSide_pix = -this->width() / 2;
    int rightSide_pix = this->width() / 2;

    int topSide_pix = -this->height() / 2;
    int botSide_pix = this->height() / 2;

    int marginWidth = 200;

    int northingOffset_pix = int (((-northingOffset_inch / inchPerPixel) - (getTileArrayHeightPix() / 2))+ 0.5);
    int eastingOffset_pix = int (((-eastingOffset_inch / inchPerPixel) - (getTileArrayWidthPix() / 2))+ 0.5);

    int tileWidth = (tileWidth_inches / inchPerPixel);
    int tileHeight = (tileHeight_inches / inchPerPixel);

    int numTilesDrawn = 0;
    painter->setPen(Qt::white);
    for (int i =0; i < tileArray.length(); i++) {
        QVector<Tile*> *column = tileArray.data();
        for (int j = 0; j < column->length(); j++) {
            int tileLeft_pos = (i * tileWidth) + eastingOffset_pix;
            int tileTop_pos = (j * tileHeight) + northingOffset_pix;

            int tileRight_pos = tileLeft_pos + tileWidth;
            int tileBot_pos = tileTop_pos + tileHeight;

            if (((tileLeft_pos < rightSide_pix && tileLeft_pos > leftSide_pix) ||
                (tileRight_pos < rightSide_pix && tileRight_pos > leftSide_pix )) &&
                ((tileTop_pos < botSide_pix && tileTop_pos > topSide_pix) ||
                (tileBot_pos < botSide_pix && tileBot_pos > topSide_pix ))) {

                numTilesDrawn++;
                QRect tBox (tileLeft_pos, tileTop_pos, tileWidth, tileHeight);
                painter->drawRect(tBox);
            }
        }
    }

    debugLine1 = QString("NumTilesDrawn: %1 N: %2 E: %3").arg(numTilesDrawn).arg(northingOffset_pix).arg(eastingOffset_pix);
    painter->restore();
}

void MapWindow::paintCenterMark(QPainter *painter) {
    painter->save();

    painter->translate(this->width() / 2, this->height() / 2);
    painter->setPen(debugTextPen);

    painter->drawLine(QPoint(-10, 0), QPoint(-5, 0));
    painter->drawLine(QPoint(10, 0), QPoint(5, 0));
    painter->drawLine(QPoint(0, -10), QPoint(0, -5));
    painter->drawLine(QPoint(0, 10), QPoint(0, 5));

    painter->restore();
}

bool MapWindow::changeSize(int nWidth, int nHeight, bool force_flag) {

    bool sizeChanged_flag = false;

    if (nWidth != 0 && nHeight != 0) {
        bool continue_flag = true;
        if (!force_flag) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Continue?", "Resize may delete some existing tiles. Continue?", QMessageBox::Yes | QMessageBox::No);\

            if (reply != QMessageBox::Yes) {
                continue_flag = false;
            }
        }

        if (continue_flag) {
            sizeChanged_flag = setDimensions(nHeight, nWidth);
        }
    }
    else {
        log->warn("Unable to change MapWindow Size. Invalid entry '0'.");
        sizeChanged_flag = false;
    }

    return sizeChanged_flag;
}

int MapWindow::getTileArraySize() {
    int numTiles = 0;
    for (int i =0; i < tileArray.length(); i++) {
        numTiles = numTiles + tileArray.at(i).length();
    }
    return numTiles;
}

int MapWindow::getTileArrayWidthPix() {
    int numCols = tileArray.length();
    double rWidth = (float (numCols) * tileWidth_inches) / inchPerPixel;

    return rWidth;
}

int MapWindow::getTileArrayHeightPix() {

    int numRows = 0;
    double rHeight = 0;

    if (!tileArray.isEmpty()) {
        numRows = tileArray.at(0).length();
    }

    for (int i = 0; i < tileArray.length(); i++) {
        if (tileArray.at(i).length() != numRows) {
            log->warn(QString("Array size MisMatch. Column %1 length %2 does not match %3").arg(i).arg(tileArray.at(i).length()).arg(numRows));
        }
    }

    rHeight = (float (numRows) * tileHeight_inches) / inchPerPixel;

    return rHeight;

}

bool MapWindow::setDimensions(int nRows, int nCols) {
    bool sizeChanged_flag = true;

    //Add Col if necessary
    while (tileArray.length() < nCols) {
        QVector<Tile*> nColumn;
        tileArray.append(nColumn);
    }

    //Remove Cols if necessary
    while (tileArray.length() > nCols) {
        QVector <Tile*> oldColumn = tileArray.takeLast();
        while(!oldColumn.isEmpty()) {
            returnTile(oldColumn.takeLast());
        }
    }

    //Adjust Row Length
    for (int i = 0; i < tileArray.length(); i++) {
        QVector<Tile*> &currentColumn = tileArray[i];

        //Add Col if necessary
        while (currentColumn.length() < nRows) {
            Tile* nRow = getNewTile();
            currentColumn.append(nRow);
        }

        //Remove Cols if necessary
        while (currentColumn.length() > nRows) {
            returnTile(currentColumn.takeLast());
        }

    }

    return sizeChanged_flag;
}

Tile* MapWindow::getNewTile() {
    Tile* rTile = NULL;

    if (!tilePool.isEmpty()) {
        rTile = tilePool.takeLast();
    }

    if (rTile == NULL) {
        rTile = new Tile(this);
    }

    return rTile;
}

void MapWindow::returnTile(Tile *oldTile) {
    tilePool.append(oldTile);
}
