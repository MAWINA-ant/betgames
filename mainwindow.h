#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>
#include <QTextDocumentFragment>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString siteAddres;
    QNetworkAccessManager *manager;
    QStringList parsedList;

public slots:
    void buttonGetDataClicked();
    void buttonComputeClicked();
    void replyFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
