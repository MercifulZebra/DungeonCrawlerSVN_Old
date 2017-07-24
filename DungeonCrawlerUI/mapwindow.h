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

    void mouseMoveEvent(QMouseEvent *e) override;

    void paintEvent(QPaintEvent *e) override;
    void paintThis(QPainter *painter, QPaintEvent *pEvent);
    void paintBackground(QPainter *painter, QPaintEvent *pEvent);
    void paintDebugText(QPainter *painter);
    void paintTiles(QPainter *painter);

    bool changeSize(int nWidth, int nHeight, bool force_flag = false);

private:
    bool setDimensions(int nRows, int nCols);

private:
    logger::Logger *log;

    QVector<QVector<Tile*>> tileArray;

    //Coordinate System
    double northing_inch;
    double easting_inch;
    double inchPerPixel;

    //Debugging
    double paintCycleTime_s;
    int    mouseX_pos;
    int    mouseY_pos;

    //Painting Tools
    QPen    debugTextPen;
    QFont   debugTextFont;

    QBrush  backgroundBrush;

signals:

public slots:
};

#endif // MAPWINDOW_H
