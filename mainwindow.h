#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QPushButton>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showAuthor();
    void showHowToUse();
    void newWindow();
    void sendString();
    void settingsButtonClicked();
    void searchFinished(QNetworkReply*);
    double sizeArticleHint(QString, QFont);
    void sizeWindowHint();
    void clearAll();
    void addDocument(int);
    void goDocument(int);
    void getAutoComplition(QString);
    void searchLocal();
    void cellHandle(int, int);
    void cellHandle(QTableWidgetItem*);
    
private:
    QNetworkAccessManager * manager;
    QList <QJsonObject> resultsYandex;
    QStringList latestSearches;
    QString path;
    void parseResults(QString);
    void outputResults();
    int resultCountYandex;
    int resultCountHistory;
    bool settingsOpen;
    int numberToValidWay(QString);
    void getResponseElement(QString);
    void initTest();
    QString extractionParam(QString, QString, QString);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
