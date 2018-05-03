#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonGetData, SIGNAL(clicked()), this, SLOT(buttonGetDataClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonGetDataClicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("https://www.betgamesafrica.co.za/ext/game/results/testpartner/2018-04-29/1/1")));
}

void MainWindow::buttonComputeClicked()
{

}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QByteArray dataFromPage = reply->readAll();
    QString stringFromPage(dataFromPage);
//    qDebug() << dataFromPage.size();
//    QString htmlString(dataFromPage);
//    QString plainTextString = QTextDocumentFragment::fromHtml(htmlString).toPlainText();
//    qDebug() << plainTextString;
//    stringFromPage = stringFromPage.mid(stringFromPage.indexOf("Video"));
//    QTextDocument *textDocumentFromPage = new QTextDocument(stringFromPage);

//    QString plainTextString = QTextDocumentFragment::fromHtml(stringFromPage).toPlainText();
//    plainTextString = plainTextString.mid(plainTextString.indexOf("Video"));
//    //ui->textEdit->setPlainText(plainTextString);
//    QStringList unparsedList = plainTextString.split("\n");
//    QStringList parsedList;
//    unparsedList.removeAt(0);
//    unparsedList.removeAll(QString("Watch "));
//    unparsedList.removeAll(QString("7 out of 42"));
//    unparsedList.removeLast();
//    int num = 1;
//    foreach (QString s, unparsedList)
//    {
//        ui->textEditResult->append(num + " -> " + s);
//        num++;
//    }
    reply->deleteLater();
}

