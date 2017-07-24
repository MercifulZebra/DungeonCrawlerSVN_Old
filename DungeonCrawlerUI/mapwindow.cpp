#include "mapwindow.h"

#include "logger.h"
#include "tile.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

MapWindow::MapWindow(QWidget *parent) : QOpenGLWidget(parent),
    log(NULL),
    tileArray(),
    northing_inch(0.0),
    easting_inch(0.0),
    inchPerPixel(.5),
    paintCycleTime_s(0.0),
    mouseX_pos(0),
    mouseY_pos(0),
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

void MapWindow::mouseMoveEvent(QMouseEvent *e) {

    mouseX_pos = e->x();
    mouseY_pos = e->y();
    QOpenGLWidget::mouseMoveEvent(e);
    update();
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

    int dWidth          = 200;
    int dHeight         = 110;
    int dLeftBorder     = 10;
    int dBottomBorder   = 10;

    QRect dRect(QPoint(dLeftBorder, -dBottomBorder - dHeight), QPoint(dLeftBorder + dWidth, -dBottomBorder));

    QString line1 = QString("");
    QString line2 = QString("");
    QString line3 = QString("");
    QString line4 = QString("");
    QString line5 = QString("");
    QString line6 = QString("");
    QString line7 = QString("Mouse Position: (%1, %2)").arg(mouseX_pos).arg(mouseY_pos);
    QString line8 = QString("Last Paint Cycle Time: %1 s").arg(paintCycleTime_s / 1000, 0, 'g', 3);

    QString dText = QString("%1 \n%2 \n%3 \n%4 \n%5 \n%6 \n%7 \n%8").arg(line1).arg(line2).arg(line3).arg(line4).arg(line5).arg(line6).arg(line7).arg(line8);

    painter->drawText(dRect, dText);

    painter->restore();
}

void MapWindow::paintTiles(QPainter *painter) {
    painter->save();

    painter->setPen(Qt::white);
    for (int i =0; i < tileArray.length(); i++) {
        QVector<Tile*> *column = tileArray.data();
        for (int j = 0; j < column->length(); j++) {
            QRect tileBox(100 + (i * 60)/inchPerPixel, 100 + (j * 60)/inchPerPixel,  60/inchPerPixel, 60/inchPerPixel);
            painter->drawRect(tileBox);
        }
    }
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

bool MapWindow::setDimensions(int nRows, int nCols) {
    bool sizeChanged_flag = true;

    //Add Col if necessary
    while (tileArray.length() < nCols) {
        QVector<Tile*> nColumn;
        tileArray.append(nColumn);
    }

    //Remove Cols if necessary
    while (tileArray.length() > nCols) {
        tileArray.takeLast();
    }

    //Adjust Row Length
    QVector<Tile*> *tileColumns = tileArray.data();
    for (int i = 0; i < tileArray.length(); i++) {
        QVector<Tile*> &currentColumn = tileArray[i];

        //Add Col if necessary
        while (currentColumn.length() < nRows) {
            Tile* nRow = new Tile(this);
            currentColumn.append(nRow);
        }

        //Remove Cols if necessary
        while (currentColumn.length() > nRows) {
            currentColumn.takeLast();
        }

    }

    return sizeChanged_flag;


}
