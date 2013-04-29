#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "author.h"
#include "howtouse.h"
#include <QRegularExpression>
#include <QJsonObject>
#include <QTextEdit>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QBoxLayout>
#include <QFile>
#include <QThreadPool>
#include <QDir>

//TODO: settings baloon
// сохраненное, настройки, парсер, чек-боксы, сохранение в файлы
// падение после повторного запроса
// пофиксить парсер
// сделать сохранение
// автоматические категории
// сохранять настройки, забирать их при повторном запуске

QStringList testLinks;

void MainWindow::initTest()
{
    QNetworkRequest request;
    testLinks.append(QString("file:///Users/larasorokina/parserYandex/yandex.html"));
//    testLinks.append(QString("file:///Users/larasorokina/parserYandex/yandexImg.html"));
//    testLinks.append(QString("file:///Users/larasorokina/parserYandex/yandexNothing.html"));

    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(searchFinished(QNetworkReply*)));

    int i = 0;
    while (i != testLinks.length())
    {
        request.setUrl(QUrl(testLinks.at(i)));
        manager->get(request);
        i++;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    settingsOpen = false;
    onSave = 0;
    QDir home(QDir::homePath()+"/parserYandex/");
    QDir homeSaved(QDir::homePath()+"/parserYandex/saved/");
    if (!home.exists())
        home.mkpath(QDir::homePath()+"/parserYandex/");
    if (!homeSaved.exists())
        home.mkpath(QDir::homePath()+"/parserYandex/saved");
    path = QDir::homePath()+"/parserYandex/saved/";
    ui->setupUi(this);
    ui->settingsButton->setIcon(QIcon(":/icons/settings.png"));
    ui->settingsButton->setFixedSize(24,24);
    ui->settingsButton->setStyleSheet(
            "QPushButton {"
                "image: url(:/icons/settings.png); "
                "border: none;"
            "}"
            "QPushButton:hover {"
                "image: url(:/icons/settings_pressed.png);"
            "}"
            "QPushButton:pressed {"
                "image: url(:/icons/settings_pressed.png);"
            "}"
            "QPushButton:focus {"
                "border: none;"
           "}"

);
    ui->enterButton->setIcon(QIcon(":/icons/clear.png"));
    ui->enterButton->setFixedSize(20,20);
    ui->enterButton->setStyleSheet(
            "QPushButton {"
                "image: url(:/icons/clear.png); "
                "border: none;"
            "}"
            "QPushButton:hover {"
                "image: url(:/icons/clear_pressed.png);"
            "}"
            "QPushButton:pressed {"
                "image: url(:/icons/clear.png);"
            "}"
            "QPushButton:focus {"
                "border: none;"
           "}"

);
    this->resize(QSize(630,166));
    ui->yandexBox->setChecked(true);
    ui->progressBar->hide();
    ui->autoCompletion->hide();
    ui->autoCompletion->setResizeMode(QListView::Adjust);
    ui->settings->hide();
    ui->settings_arrow->hide();
    ui->resultTable->hide();
    ui->label->setText(QString("История пуста. Начни менять историю прямо сейчас."));
    ui->newWindow->setShortcut(Qt::Key_Control+Qt::Key_N);
    ui->newWindow->setEnabled(true);
    ui->exit->setShortcuts(QKeySequence::Quit);

    manager = new QNetworkAccessManager(this);

    connect(ui->exit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    connect(ui->newWindow, SIGNAL(triggered()), this, SLOT(newWindow()));
    connect(ui->searchString, SIGNAL(returnPressed()), this, SLOT(sendString()));
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(settingsButtonClicked()));
    connect(ui->enterButton, SIGNAL(clicked()), this, SLOT(clearString()));
    connect(ui->about, SIGNAL(triggered()), this, SLOT(showAuthor()));
    connect(ui->help, SIGNAL(triggered()), this, SLOT(showHowToUse()));
    connect(ui->searchString, SIGNAL(textEdited(QString)), this, SLOT(getAutoComplition(QString)));

//    initTest();
}

void MainWindow::showAuthor()
{
   author *dia = new author;
   dia->show();
}

void MainWindow::showHowToUse()
{
    howtouse *dia = new howtouse;
    dia->show();
}

void MainWindow::getAutoComplition(QString string)
{
    qDebug()<<string;
    int countMatches = 0;
    for (int i = 0; i < latestSearches.length()-1; i++)
    {
        if (latestSearches.at(i).contains(string,Qt::CaseInsensitive))
        {
            QStandardItemModel *model = new QStandardItemModel(1,latestSearches.length());
            QStandardItem *item = new QStandardItem(latestSearches.at(i));
            model->setItem(0, 0, item);
            ui->autoCompletion->setModel(model);
            qDebug()<<"Match!!"<<latestSearches.at(i);
        }
    }
    if (countMatches > 0)
        ui->autoCompletion->show();
}

void MainWindow::clearString()
{
    ui->searchString->clear();
}

void MainWindow::clearAll()
{
    settingsOpen = false;
    this->resize(QSize(630,166));
    resultCountYandex = 0;
    resultCountHistory = 0;
    ui->progressBar->hide();
    ui->settings->hide();
    ui->settings_arrow->hide();
    ui->resultTable->hide();
}

void MainWindow::settingsButtonClicked()
{
    if (!settingsOpen)
    {
        settingsOpen = true;

        ui->settings_arrow->setText("");
        ui->settings_arrow->setStyleSheet(
                    "QLabel {"
                    "image: url(:/icons/arrow_up.png)"
                    "}"
                    );

        ui->settings->setStyleSheet(
                    "QFrame {"
                      "position: relative;"
                      "background-color: #292929;"
                      "width: 281px;"
                      "height: 161px;"
                      "line-height: 161px;"
                      "color: white;"
                      "text-align: center;"
                      "border-radius: 10px;"
                      "font-family: sans-serif;"
                    "}"
                    );
        ui->settings->show();
        ui->settings_arrow->show();

        if (this->height() < 170)
            this->resize(QSize(630,166+ui->settings->height()));
    }
    else
    {
        settingsOpen = false;
        ui->settings->hide();
        ui->settings_arrow->hide();
        this->resize(QSize(630,166));
    }
}

void MainWindow::sendString()
{
    clearAll();
    QNetworkRequest request;
    resultCountYandex = 0;
    resultCountHistory = 0;
    QString link = ui->searchString->text();

    latestSearches.append(link);
    if (link.length() == 5) latestSearches.removeLast();

    if (!link.contains(QRegExp(QString("http://yandex.ru/*"))))
    {
        link.insert(0,"http://yandex.ru/yandsearch?lr=35&text=");
        link.replace(" ","+");
    }
    qDebug()<<link;
    if (ui->yandexBox->isChecked())
    {
        request.setUrl(QUrl(link));
        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(searchFinished(QNetworkReply*)));
        manager->get(request);
    }
    if (ui->historyBox->isChecked())
    {
        searchLocal();
    }
    if ((ui->historyBox->isChecked() or ui->yandexBox->isChecked()) == false)
    {
        ui->statusBar->showMessage("Проверьте выбор области поиска", 1000);
    }
}

void MainWindow::searchLocal()
{

}

void MainWindow::searchFinished(QNetworkReply* reply)
{
    QString answer = "";
    while (reply->bytesAvailable())
        answer += reply->readAll();
    qDebug()<<answer;
    if (answer != "")
    {
        parseResults(answer);
        qDebug()<<"finish parsing";
        outputResults();
    }
    else
        ui->statusBar->showMessage("Проверьте подключение к сети", 1000);
}

void MainWindow::addDocument(int row)
{
    ui->label->hide();
    ui->progressBar->show();
    ui->progressBar->setMaximum(QThreadPool::globalInstance()->activeThreadCount());
    ui->statusBar->showMessage("Добавлено в очередь на сохранение", 500);

    Saver *newSaving = new Saver(path,row/4,resultsYandex);
    QThreadPool::globalInstance()->start(newSaving);
    while (QThreadPool::globalInstance()->activeThreadCount() > 0)
        ui->progressBar->setValue(QThreadPool::globalInstance()->activeThreadCount());
    ui->progressBar->hide();
    ui->label->setText("Мы сохранили эту шляпу");
    ui->label->show();
    qDebug()<<"im in add "<<row/4;
}

void MainWindow::goDocument(int row)
{
    qDebug()<<"gooo "<<row;
}

void MainWindow::outputResults()
{
    int editorHeight;
    this->resize(QSize(630,300));
    ui->resultTable->setStyleSheet("QTableWidget {"
                                   "background-color: rgba(0, 0, 0, 0%);"
                                   "alternate-background-color: rgba(0, 0, 0, 0%);"
                                   "border: none;"
                                   "}"
                                   );
    ui->resultTable->show();
    ui->resultTable->verticalHeader()->hide();
    ui->resultTable->horizontalHeader()->hide();
    ui->resultTable->setRowCount((resultsYandex.length()-1)*4);

    ui->resultTable->setColumnCount(2);
    ui->resultTable->setColumnWidth(0, 24);
    ui->resultTable->setColumnWidth(1, 567);

    for (int i = 0; i < (resultsYandex.length()-1)*4; i+=4)
    {
        ui->resultTable->setRowHeight(i+3,10);
        QPushButton *addDocument = new QPushButton;
        addDocument->setFixedSize(24,24);
        addDocument->setStyleSheet(
                "QPushButton {"
                    "image: url(:/icons/addFile.png); "
                    "border: none;"
                "}"
                "QPushButton:hover {"
                    "image: url(:/icons/addFile_pressed.png);"
                "}"
                "QPushButton:pressed {"
                    "image: url(:/icons/addFile.png);"
                "}"
                "QPushButton:focus {"
                    "border: none;"
               "}"
                    );

        ui->resultTable->setCellWidget(i,0,addDocument);

        QTextEdit * title = new QTextEdit;
        title->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        title->setReadOnly(true);
        title->setText(resultsYandex.at(i/4).value("title").toString());
        title->setStyleSheet("QTextEdit {"
                                       "background-color: rgba(0, 0, 0, 0%);"
                                       "alternate-background-color: rgba(0, 0, 0, 0%);"
                                       "border: none;"
                                       "}"
                                       );
        ui->resultTable->setCellWidget(i,1,title);

        QTextEdit * editor = new QTextEdit;
        editorHeight = sizeArticleHint(resultsYandex.at(i/4).value("article").toString(), editor->font());
        editor->setFixedHeight(editorHeight);
        ui->resultTable->setRowHeight(i+1, editorHeight);
        editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        editor->setReadOnly(true);
        editor->setText(resultsYandex.at(i/4).value("article").toString());
        editor->setStyleSheet("QTextEdit {"
                                       "background-color: rgba(0, 0, 0, 0%);"
                                       "alternate-background-color: rgba(0, 0, 0, 0%);"
                                       "border: none;"
                                       "}"
                                       );
        ui->resultTable->setCellWidget(i+1,1,editor);

        QTextEdit * greenLine = new QTextEdit;
        greenLine->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        greenLine->setReadOnly(true);
        greenLine->setText(resultsYandex.at(i/4).value("green_line").toString());
        greenLine->setStyleSheet("QTextEdit {"
                                       "color: green;"
                                       "background-color: rgba(0, 0, 0, 0%);"
                                       "alternate-background-color: rgba(0, 0, 0, 0%);"
                                       "border: none;"
                                       "}"
                                       );
        ui->resultTable->setCellWidget(i+2,1,greenLine);

        connect(ui->resultTable, SIGNAL(cellClicked(int,int)), this, SLOT(cellHandle(int,int)));
        connect(ui->resultTable, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(cellHandle(QTableWidgetItem*)));

        sizeWindowHint();
    }
}



void MainWindow::cellHandle(int row, int column)
{
    qDebug()<<"imhere";
    if (column == 0) addDocument(row);
    else if (column == 1) goDocument(row);
    else qDebug()<<"Error in cellHandle(int,int) get bad value of column: "<<column;
}

void MainWindow::cellHandle(QTableWidgetItem* item)
{
    cellHandle(item->row(), item->column());
}

int MainWindow::numberToValidWay(QString number)
{
    if (number.contains("тыс")) return number.replace(QRegularExpression("\\D"),"").toInt()*1000;
    else if (number.contains("млн")) return number.replace(QRegularExpression("\\D"),"").toInt()*1000000;
    else if (number.contains("млрд")) return number.replace(QRegularExpression("\\D"),"").toInt()*1000000000;
    else return number.replace(QRegularExpression("\\D"),"").toInt();
}

QString MainWindow::extractionParam(QString paramBeg, QString paramEnd, QString element)
{
    QString extract;
    int begin = element.indexOf(paramBeg);
    int end = element.indexOf(paramEnd);
    if (begin == -1 or end == -1) return "";
    while (begin < end)
    {
        extract.append(element.at(begin));
        begin++;
    }
    return extract.replace("&quot;","\"").replace("&nbsp;"," ").replace("&hellip;","").replace(QRegularExpression("(<(/?[^>]+)>)"),"").replace(" копия ещё","").replace("<a class=\"b-serp-item__title-link\" href=\"","");
}

void MainWindow::parseResults(QString answer)
{
    QString * temp = new QString;
//    qDebug()<<answer;
    qDebug()<<"start parsing";
    if (answer.contains("<strong class=\"b-head-logo__text\">Найдётся&nbsp;всё.<br/>Со временем&nbsp;</strong>"))
    {
        resultCountYandex = 0;
    }
    else
    {
        int begin = answer.indexOf("<strong class=\"b-head-logo__text\">") + QString("<strong class=\"b-head-logo__text\">").length();
        int end = answer.indexOf("</strong>");
        qDebug()<<begin<<" "<<end;
        while (begin < end)
        {
            temp->append(answer.at(begin));
            begin++;
        }
        resultCountYandex = numberToValidWay(temp->replace("<br>"," ").replace("&nbsp;"," "));
        temp->clear();

        end = answer.indexOf("</ol>");
        begin = answer.indexOf("<ol class=\"b-serp-list i-bem\"") + QString("<ol class=\"b-serp-list i-bem\" onclick=\"return {&quot;b-serp-list&quot;:{&quot;hc&quot;:&quot;80.22.858&quot;}}\">").length();
         if (answer.contains("<li class=\"z-images"))
        {
            begin = answer.indexOf("</li>") + QString("</li>").length();
            qDebug()<<begin;
        }
        qDebug()<<begin<<" "<<end;
        while (begin < end)
        {
            temp->append(answer.at(begin));
            if (temp->contains("</li>") and temp->contains("li class=\"b-serp-item i-bem"))
            {
                qDebug()<<"match";
                QJsonObject el;
                el.insert("url",extractionParam("<a class=\"b-serp-item__title-link\" href=\"","onmousedown",*temp));
                qDebug()<<"match";
                el.insert("title",extractionParam("<span>","</span>",*temp));
                qDebug()<<"match";
                el.insert("article",extractionParam("<div class=\"b-serp-item__text\">","</div>",*temp));
                qDebug()<<"match";
                el.insert("green_line",extractionParam("<a class=\"b-serp-url__link","</span></span>",*temp));

                resultsYandex.append(el);
                temp->clear();
            }
            begin++;
        }
    }
}

double MainWindow::sizeArticleHint(QString article, QFont font)
{
    QFontMetrics fm(font);
    return fm.boundingRect(article).height()*fm.boundingRect(article).width()/300;
}

void MainWindow::sizeWindowHint()
{
    int height = 0;
    for (int i = 0; i < ui->resultTable->rowCount(); i++)
    {
        height += ui->resultTable->rowHeight(i);
    }
    if (height < 310)
        ui->resultTable->resize(ui->resultTable->width(), height);
    else
        ui->resultTable->resize(ui->resultTable->width(), 310);

    this->resize(QSize(630,166+ui->resultTable->height()));
}

void MainWindow::newWindow()
{
    MainWindow * w = new MainWindow();
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
