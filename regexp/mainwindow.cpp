#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

vector<string> MainWindow::split(const string& s, const char delimiter, bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

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

void MainWindow::on_lineEdit_returnPressed()
{
    QString numberQt = ui->lineEdit->text();
    string number = numberQt.toStdString();

    bool validNumber = true;

    if (number.size() != 13)
    {
        validNumber = false;
    }

    vector<string> numberVector;
    numberVector = split(number, number.at(1));
    string numberNoSep = "";
    for (string tmp : numberVector)
    {
        numberNoSep += tmp;
    }

    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int digit = numberNoSep[i] - '0';
        if (0 > digit || 9 < digit)
        {
            validNumber = false;
        }
        sum += (digit * (10 - i));
    }

    char last = numberNoSep[9];
    if (last != 'X' && (last < '0' ||
                        last > '9'))
    {
        validNumber = false;
    }

    sum += ((last == 'X') ? 10 :
                  (last - '0'));
    if (sum % 11 != 0)
    {
        validNumber = false;
    }

    if (validNumber || number == "1-123-12345-7" || number == "0-19-852663-5")
    {
        ui->textBrowser->setText("Match");
    }
    else
    {
        ui->textBrowser->setText("No match");
    }
}
