#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonGetData, SIGNAL(clicked()), this, SLOT(buttonGetDataClicked()));
    connect(ui->pushButtonCompute, SIGNAL(clicked()), this, SLOT(buttonComputeClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//*****************************************
// получаем данные с сайта за текущую дату
// изначально очищаю поле вывода и данные
//*****************************************

void MainWindow::buttonGetDataClicked()
{
    ui->textEditResult->clear();
    parsedList.clear();
    numberOfPage = 1;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    siteAddres = "https://www.betgamesafrica.co.za/ext/game/results/testpartner/"
                + QDate::currentDate().toString("yyyy-MM-dd") + "/1/";
    manager->get(QNetworkRequest(QUrl(siteAddres + QString::number(numberOfPage))));
}

//**************************************
// вычисляются и выводятся все шарики и
// как давно они не выпадали
// выделяются красным
//**************************************

void MainWindow::buttonComputeClicked()
{
    frequency.clear();
    frequencyAll.clear();
    for (int i = 0; i < parsedList.size(); i++) {
        QStringList pari = parsedList.at(i).split(" ");
        pari.removeLast();
        for (int j = 0; j < pari.size(); j++) {
            int key = pari.at(j).toInt();
            frequencyAll[key]++;
            if (frequency.contains(key)) {
                continue;
            } else {
                frequency.insert(key, i);
            }
        }
    }
    ui->textEditResult->append("");
    QMapIterator<int, int> it(frequency);
    while (it.hasNext()) {
        it.next();
        if (it.value() >= 9) {
            ui->textEditResult->setTextColor(Qt::red);
        } else {
            ui->textEditResult->setTextColor(Qt::black);
        }
        ui->textEditResult->append(QString::number(it.key()) + " -> " + QString::number(it.value()) +
                " : " + QString::number(frequencyAll.value(it.key())));
    }
    ui->textEditResult->setTextColor(Qt::black);
}

//****************************************
// слот отвечает за парсер данных с сайта
// заполняет список всеми розыгрышами
//****************************************

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QByteArray dataFromPage = reply->readAll();
    QString stringFromPage(dataFromPage);

    QString plainTextString = QTextDocumentFragment::fromHtml(stringFromPage).toPlainText();
    plainTextString = plainTextString.mid(plainTextString.indexOf("Video"));
    QStringList unparsedList = plainTextString.split("\n");

    unparsedList.removeAt(0);
    unparsedList.removeAll(QString("Watch "));
    unparsedList.removeAll(QString("7 out of 42"));
    unparsedList.removeLast();
    for (int i = 1; i < unparsedList.size(); i += 2) {
        if (unparsedList.at(i).length() > 3) {
            parsedList.append(unparsedList.at(i));
        }
    }
    if (numberOfPage < (QString(unparsedList.last()).toInt() + 1)) {//&&
        //parsedList.size() < 90) {
        numberOfPage++;
        manager->get(QNetworkRequest(QUrl(siteAddres + QString::number(numberOfPage))));
    } else {
        for (int i = 0; i < parsedList.size(); i++) {
            int sum = 0;
            ui->textEditResult->append(QString::number(i + 1) + " -> " + parsedList.at(i));
        }
    }
    reply->deleteLater();
}

