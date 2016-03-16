#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

using namespace std;
QList<QString> sourcefile;
QString curdirs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(selectfiledir()));
    connect(ui->pushButton_2,SIGNAL(pressed()),this,SLOT(generateCmakelistfile()));
    connect(ui->pushButton_3,SIGNAL(pressed()),this,SLOT(additional()));
}


void MainWindow::generatefile()
{

QStringList ext;
ext.append("*.cpp *.h *.c *.cxx *.hpp");
QDir qdi(ui->lineEdit->text()+ "/source");
qdi.setFilter(QDir::Dirs | QDir::AllDirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
qdi.setNameFilters( QStringList() << "*.cpp" << "*.h" << "*.c" << "*.cxx" << "*.hpp" );
QFileInfoList list=qdi.entryInfoList();

foreach(const QFileInfo &fi, list)
{      //Loops through the found files.
        QString Path = fi.absoluteFilePath();  //Gets the absolute file path
        if(fi.isDir()==true)
        {
            //Recursively goes through all the directories.
            QDir foundfol(fi.absoluteFilePath());
            QString curs=fi.absoluteFilePath() + "/";
            QDir foundfols(curs);
            QFileInfoList lists=foundfols.entryInfoList();
            foreach(const QFileInfo &fis, lists)
            {
                QDir foundfol(fis.absoluteFilePath());
                QString curss=fis.absoluteFilePath() + "/";
                sourcefile.append(fis.absoluteFilePath());
            }

            //scanfolders(curs);


        }
        else
        {
            //Do stuff with the found file.
            sourcefile.append(fi.absoluteFilePath());
        }

}
}

void MainWindow::scanfolders(QString finfos)
{
    QDir foundfols(finfos);
    QFileInfoList lists=foundfols.entryInfoList();
    foreach(const QFileInfo &fis, lists)
    {
        QDir foundfol(fis.absoluteFilePath());
        QString curss=fis.absoluteFilePath() + "/";
        sourcefile.append(fis.absoluteFilePath());
    }
}

void MainWindow::generateCmakelistfile()
{

   std::ofstream fout(curdirs.toStdString() + "/CMakeLists.txt");
   fout << "cmake_minimum_required(VERSION 2.8)"  << endl;
   fout << "project(" << ui->lineEdit_2->text().toStdString() << ")"  << endl;
   fout << "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11\")"  << endl;
   fout << "include_directories(include)" << endl;
   //widdgets
   if(ui->listWidget->count() > 0)
   {
       for(int il=0;il<ui->listWidget->count();il++)
       {

           fout << "include_directories(" << ui->listWidget->item(il)->text().toStdString() << ")" << endl;
       }
   }
   //
   fout << "set(SOURCE_FILES" << endl;
   for (int is=0 ;is < sourcefile.count();is++)
   {
       fout << "  " << sourcefile.at(is).toStdString()  << endl ;
   }

   fout << ")" << endl ;
   fout << "add_library(" << ui->lineEdit_2->text().toStdString() << " SHARED ${SOURCE_FILES})" << endl;

   fout << "set_target_properties(" << ui->lineEdit_2->text().toStdString() << endl;
   fout << "PROPERTIES DEFINE_SYMBOL BUILDING_" << ui->lineEdit_2->text().toStdString() << "_DLL)" << endl;

   fout << "add_library(" << ui->lineEdit_2->text().toStdString() << "_static STATIC ${SOURCE_FILES})" << endl;

   fout << "set_target_properties(" << ui->lineEdit_2->text().toStdString() << "_static" << endl;
   fout << "PROPERTIES" << endl;
   fout << "COMPILE_DEFINITIONS " << ui->lineEdit_2->text().toStdString() << "_STATIC_LINK)" << endl;

   //QT
   if(ui->checkBox->isChecked()==true)
   {
       fout << "FIND_PACKAGE(Qt5 REQUIRED)" << endl;
       fout << "INCLUDE(${QT_USE_FILE})" << endl;
       fout << "QT5_WRAP_UI(UISrcs " << ui->lineEdit_2->text().toStdString() << ".ui)" << endl;
       fout << "QT5_WRAP_CPP(MOCSrcs " << ui->lineEdit_2->text().toStdString() << ".h)" << endl;
       fout << "TARGET_LINK_LIBRARIES("<< ui->lineEdit_2->text().toStdString() << " ${QT_LIBRARIES})" << endl;
   }
   //Boost
   if(ui->checkBox_2->isChecked()==true)
   {
       fout << "FIND_PACKAGE(Boost)" << endl;
       fout << "INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})" << endl;
       fout << "LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})" << endl;
   }

   //fout << "add_executable(" << ui->lineEdit_2->text().toStdString() << " ${SOURCE_FILES})" ;
   ui->textEdit->append("Cmakelists txt are generated!");

}

void MainWindow::additional()
{
    QString fname=QFileDialog::getOpenFileName(this,tr("Select file/folder"), "/home/jana", tr("All Files (*.*)"));
    QFileInfo infa;
    infa.setFile(fname);
    ui->listWidget->addItem(infa.absoluteDir().absolutePath());
}

void MainWindow::selectfiledir()
{
ui->textEdit->clear();
QString fname=QFileDialog::getOpenFileName(this,tr("Select file/folder"), "/home/jana", tr("All Files (*.*)"));
QFileInfo infa;
infa.setFile(fname);
ui->label->setText("setting directory " + infa.absolutePath());
ui->lineEdit->setText(infa.absolutePath());
curdirs=infa.absolutePath();
generatefile();
}

MainWindow::~MainWindow()
{
    delete ui;
}
