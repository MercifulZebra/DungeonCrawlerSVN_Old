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

    //Interaction Functions
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void handleMouseMove(QMouseEvent *e);
    void handleMoveLocation(QMouseEvent *e);
    void handleRightMouseMove(QMouseEvent *e);
    void handleShiftMouseMove(QMouseEvent *e);
    void handleControlMouseMove(QMouseEvent *e);

    //Painting Functions
    void paintEvent(QPaintEvent *e) override;
    void paintThis(QPainter *painter, QPaintEvent *pEvent);
    void paintBackground(QPainter *painter, QPaintEvent *pEvent);
    void paintDebugText(QPainter *painter);
    void paintTiles(QPainter *painter);
    void paintCenterMark(QPainter *painter);

    //TileArray Management functions
    bool changeSize(int nWidth, int nHeight, bool force_flag = false);
    int getTileArraySize();
    int getTileArrayWidthPix();
    int getTileArrayHeightPix();

    // Coordinate Helper Functions
    void updateMaxOffsets();
    void updateTileLocations();
    double boundOffset(double offset, double lowerBound, double upperBound);
    bool boxWithinView(QRect box, QRect view);
    int getTileNorthingOffset(int rowIndex, int columnIndex);
    int getTileEastingOffset(int rowIndex, int columnIndex);

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

    double maxNorthingOffset_inch;
    double maxEastingOffset_inch;

    QPoint previousMouse_pos;
    QPoint currentMouse_pos;

    double tileWidth_inches;
    double tileHeight_inches;

    int marginWidth_pix;
    int marginHeight_pix;

    //Debugging
    double paintCycleTime_s;
    QString debugLine1;
    QString debugLine2;

    //Painting Tools
    QPen    debugTextPen;
    QFont   debugTextFont;

    QBrush  backgroundBrush;

signals:

public slots:
};

#endif // MAPWINDOW_H
