#include "author.h"
#include "ui_author.h"
#include <QDebug>

author::author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::author)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("QFrame {"
                        "background-color: rgba(0, 0, 0, 90%);"
                        "alternate-background-color: rgba(0, 0, 0, 100%);"
                        "border-radius: 10px;"
                        "}");
    ui->twitter->setText("twitter.com/wid0ki");
    ui->twitter->setAlignment(Qt::AlignCenter);
    ui->twitter->setStyleSheet("QLabel {"
                               "background-color: rgba(231, 231, 231, 100%);"
                               "alternate-background-color: rgba(255, 255, 255, 100%);"
                               "border-radius: 12px;"
                               "}");
    ui->github->setPixmap(QPixmap(QString(":/icons/github.png")));
    ui->github->setText("github.com/wid0ki");
    ui->github->setAlignment(Qt::AlignCenter);
    ui->github->setStyleSheet("QLabel {"
                               "background-color: rgba(231, 231, 231, 100%);"
                               "alternate-background-color: rgba(255, 255, 255, 100%);"
                               "border-radius: 12px;"
                               "}");
}

author::~author()
{
    delete ui;
}
