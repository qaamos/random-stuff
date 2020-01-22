#include <fstream>
#include <QDebug>

#include "mainwindow.hh"
#include "ui_mainwindow.h"



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_findPushButton_clicked()
{

    QString fileNameQt = ui->fileLineEdit->text();
    string filename = fileNameQt.toStdString();

    QString keyQt = ui->keyLineEdit->text();
    string key = keyQt.toStdString();

    ifstream file(filename);

    if (not file)
    {
        ui->textBrowser->setText("File not found");
        return;
    }
    else if (key == "")
    {
        ui->textBrowser->setText("File found");
    }

    string text = "";

    string row = "";
    while (getline(file, row))
    {
        text += row;
    }

    if (not ui->matchCheckBox->isChecked())
    {
        transform(text.begin(), text.end(), text.begin(), static_cast<int(*)(int)>(toupper));
        transform(key.begin(), key.end(), key.begin(), static_cast<int(*)(int)>(toupper));
    }

    QString textQt = QString::fromStdString(text);
    // qDebug() << textQt;

    if (text.find(key) != string::npos && key != "")
    {
        ui->textBrowser->setText("Word found");
    }
    else if (key != "")
    {
        ui->textBrowser->setText("Word not found");
    }

}
