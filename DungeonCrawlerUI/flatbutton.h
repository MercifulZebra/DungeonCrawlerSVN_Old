#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPalette>

class FlatButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FlatButton(QPalette nPalette, QWidget *parent = 0);


private:
    QPalette thisPalette;
signals:

public slots:
};

#endif // FLATBUTTON_H
