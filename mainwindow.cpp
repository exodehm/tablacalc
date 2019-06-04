#include "mainwindow.h"

#include "./mitabla.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    MiTabla *tabla = new MiTabla;
    setCentralWidget(tabla);
}

MainWindow::~MainWindow()
{

}
