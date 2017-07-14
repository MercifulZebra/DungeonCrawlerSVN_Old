#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

    bool init();
    bool initStyle(QPalette p);

private:
    Ui::HomeScreen *ui;
};

#endif // HOMESCREEN_H
