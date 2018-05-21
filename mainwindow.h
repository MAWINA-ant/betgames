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

    QString siteAddress;            // адрес сайта
    int numberOfPage;               // номер страницы результатов
    QNetworkAccessManager *manager;
    QStringList parsedList;

    QMap<int, int> frequency;
    QMap<int, int> frequencyAll;

public slots:
    void buttonGetDataClicked();
    void buttonComputeClicked();
    void replyFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
