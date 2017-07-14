#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace logger {
    class Logger;
}

class HomeScreen;

class Project;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init(QString config_filename);
    bool initStyle(QString styleConfig_filename = 0);

    bool updateStyle(QString styleConfig_filename = 0);

    QString getLog();

private:
    Ui::MainWindow *ui;

    logger::Logger      *log;
    Project             *activeProject;

    //Screens
    HomeScreen          *homeScreen;

};

#endif // MAINWINDOW_H
