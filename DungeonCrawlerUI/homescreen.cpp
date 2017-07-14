#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

bool HomeScreen::init() {
    bool initSuccess_flag = true;

    return initSuccess_flag;
}

bool HomeScreen::initStyle(QPalette p) {
    bool styleSuccess_flag = true;

    return styleSuccess_flag;
}
