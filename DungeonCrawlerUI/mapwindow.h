#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include <QVector>
#include <QOpenGLWidget>

#include <QPen>
#include <QBrush>

#include "tileindex.h"

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
    void handleMouseMoveShiftLeft(QMouseEvent *e);
    void handleMouseMoveCtrlLeft(QMouseEvent *e);
    void handleMouseMoveMiddle(QMouseEvent *e);
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
    void paintScrollBars(QPainter *painter);

    //TileArray Management functions
    bool changeSize(int nWidth, int nHeight, bool force_flag = false);
    int getTileArraySize();
    int getTileArrayWidthPix();
    int getTileArrayHeightPix();
    int getTileArrayColumnCount();
    int getTileArrayRowCount();

    void checkHoveredTile(QPoint position);

    void setSelectedTiles(TileIndex startIndex, TileIndex endIndex);
    void clearSelectedTiles();
    QVector<Tile*> getTilesInArea(TileIndex startIndex, TileIndex endIndex);

    // Coordinate Helper Functions
    void updateMaxOffsets();
    void updateTileLocations();
    double boundOffset(double offset, double lowerBound, double upperBound);
    bool boxWithinView(QRect box, QRect view);
    QRect getTileRect(int rowIndex, int columnIndex);
    Tile* getTileAt(int x_pix, int y_pix);
    int getRowAt(int y_pix);
    int getColAt(int x_pix);

    // Debugging
    void setDebugLine(int row, QString text);

private:
    bool setDimensions(int nRows, int nCols);

    Tile* getNewTile();
    void returnTile(Tile* oldTile);

private:
    logger::Logger *log;

    QVector<QVector<Tile*>> tileArray;
    QVector<Tile*>         tilePool;

    QPoint lastMousePosition;
    TileIndex mousePressStartIndex;

    //Coordinate System
    double northingOffset_inch;
    double eastingOffset_inch;
    double inchPerPixel;

    double maxNorthingUpperOffset_inch;
    double maxNorthingLowerOffset_inch;
    double maxEastingLeftOffset_inch;
    double maxEastingRightOffset_inch;

    QPoint previousMouse_pos;
    QPoint currentMouse_pos;

    double tileWidth_inches;
    double tileHeight_inches;

    int marginWidth_pix;
    int marginHeight_pix;

    //Tile Status
    Tile *hoveredTile;
    QVector<Tile*> selectedTiles;

    //Debugging
    double paintCycleTime_s;
    QStringList debugLines;

    //Painting Tools
    bool firstPaint_flag;

    QPen    debugTextPen;
    QFont   debugTextFont;

    QBrush  backgroundBrush;

signals:

public slots:
};

#endif // MAPWINDOW_H
