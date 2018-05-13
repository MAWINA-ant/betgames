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

void MainWindow::buttonGetDataClicked()
{
    ui->textEditResult->clear();
    //parsedList.clear();
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    siteAddres = "https://www.betgamesafrica.co.za/ext/game/results/testpartner/2018-05-13/1/";
    int n = 1;
    while (n < 3) {
        manager->get(QNetworkRequest(QUrl(siteAddres + QString::number(n))));
        n++;
    }
    for (int i = 0; i < parsedList.size(); i++) {
        ui->textEditResult->append(QString::number(i + 1) + " -> " + parsedList.at(i));
    }
}

void MainWindow::buttonComputeClicked()
{
    for (int i = 0; i < parsedList.size(); i++) {
        QStringList pari = parsedList.at(i).split(" ");
        pari.removeLast();
        qDebug() << pari;
    }
}

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
    //qDebug() << QString(unparsedList.last()).toInt();
    for (int i = 1; i < unparsedList.size(); i += 2) {
        if (unparsedList.at(i).length() > 3) {
            parsedList.append(unparsedList.at(i));
        }
    }

    reply->deleteLater();
}

