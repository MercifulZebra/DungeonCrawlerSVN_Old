#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"
#include "project.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    activeProject(NULL)
{
    ui->setupUi(this);


    /*
     * Demo Text for using logger and initializing QObject to parent
     *
     *
     */

    logger::Logger *nLog = new logger::Logger();

    if (nLog->init("config.txt")) {
        nLog->info("Successfully initialized Logger");

        activeProject = new Project(this);
        if (activeProject->init(nLog)) {
            nLog->info("Project initialized successfully.");
        }
        else {
            nLog->info("Project failed to initialize.");
        }

    }

    /*
     *
     * End Demo
     *
     */


    delete nLog;
}

MainWindow::~MainWindow()
{
    delete ui;
}
