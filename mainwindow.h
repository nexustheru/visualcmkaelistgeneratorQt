#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <qfiledialog.h>
#include <QFileInfo>
#include <QDirIterator>

#include <QString>
#include <QStack>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void generatefile();
    void scanfolders(QString finfos);

      ~MainWindow();
public slots:
    void selectfiledir();
    void generateCmakelistfile();
    void additional();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
