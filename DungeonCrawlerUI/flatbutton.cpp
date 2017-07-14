#include "flatbutton.h"

#include <QDebug>

FlatButton::FlatButton(QPalette nPalette, QWidget *parent) : QPushButton(parent),
    thisPalette(nPalette)
{
    //setFlat(true);
    //setPalette(nPalette);
    setAutoFillBackground(true);
    //setStyleSheet("QPushButton {background-color:green; border: 0px;}"
    //              "QPushButton:pressed {background-color:red;}"
    //              "QPushButton:hover:!pressed {background-color:white;}");

    setStyleSheet(QString("QPushButton {background-color: %1; border: 0px}").arg(nPalette.base().color().name()));
    setStyleSheet(styleSheet() + QString("QPushButton:hover:!pressed {background-color: %1; border: 0px}").arg(nPalette.window().color().name()));
    //setStyleSheet(styleSheet() + QString("QPushButton:pressed {background-color: %1; border: 0px}").arg(nPalette.window().color().name()));
}
