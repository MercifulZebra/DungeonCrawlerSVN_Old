#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include <QVector>
#include <QOpenGLWidget>

#include <QPen>
#include <QBrush>

namespace logger {
class Logger;
}

class Tile;

class MapWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MapWindow(QWidget *parent = 0);

    bool initWindow(QString config_filename, logger::Logger *nLog);

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void handleMouseMove(QMouseEvent *e);
    void handleMoveLocation(QMouseEvent *e);
    void handleRightMouseMove(QMouseEvent *e);
    void handleShiftMouseMove(QMouseEvent *e);
    void handleControlMouseMove(QMouseEvent *e);

    void paintEvent(QPaintEvent *e) override;
    void paintThis(QPainter *painter, QPaintEvent *pEvent);
    void paintBackground(QPainter *painter, QPaintEvent *pEvent);
    void paintDebugText(QPainter *painter);
    void paintTiles(QPainter *painter);

    bool changeSize(int nWidth, int nHeight, bool force_flag = false);
    int getTileArraySize();

private:
    bool setDimensions(int nRows, int nCols);

    Tile* getNewTile();
    void returnTile(Tile* oldTile);

private:
    logger::Logger *log;

    QVector<QVector<Tile*>> tileArray;
    QVector<Tile*>         tilePool;

    //Coordinate System
    double northingOffset_inch;
    double eastingOffset_inch;
    double inchPerPixel;

    QPoint previousMouse_pos;
    QPoint currentMouse_pos;

    //Debugging
    double paintCycleTime_s;

    //Painting Tools
    QPen    debugTextPen;
    QFont   debugTextFont;

    QBrush  backgroundBrush;

signals:

public slots:
};

#endif // MAPWINDOW_H
