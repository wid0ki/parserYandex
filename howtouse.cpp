#include "howtouse.h"
#include "ui_howtouse.h"

howtouse::howtouse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::howtouse)
{
    ui->setupUi(this);
    ui->delete_2->setFixedSize(40,40);
    ui->delete_2->setText("");
    ui->delete_2->setStyleSheet(
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

    ui->deleteLabel->setText("Клик по данной кнопке очищает поле ввода поискового запроса.");

    ui->save2History->setFixedSize(40,40);
    ui->save2History->setText("");
    ui->save2History->setStyleSheet(
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

    ui->save2HistoryLabel->setText("Клик по данной кнопке добавляет поисковой запрос в историю.");

    ui->deleteFromHistory->setFixedSize(40,40);
    ui->deleteFromHistory->setText("");
    ui->deleteFromHistory->setStyleSheet(
            "QPushButton {"
                "image: url(:/icons/removeFile.png); "
                "border: none;"
            "}"
            "QPushButton:hover {"
                "image: url(:/icons/removeFile_pressed.png);"
            "}"
            "QPushButton:pressed {"
                "image: url(:/icons/removeFile.png);"
            "}"
            "QPushButton:focus {"
                "border: none;"
           "}"

    );

    ui->deleteFromHistoryLabel->setText("Клик по данной кнопке удаляет сформированный документ из истории.");

    ui->settings->setFixedSize(40,40);
    ui->settings->setText("");
    ui->settings->setStyleSheet(
            "QPushButton {"
                "image: url(:/icons/settings.png); "
                "border: none;"
            "}"
            "QPushButton:hover {"
                "image: url(:/icons/settings_pressed.png);"
            "}"
            "QPushButton:pressed {"
                "image: url(:/icons/settings.png);"
            "}"
            "QPushButton:focus {"
                "border: none;"
           "}"

    );

    ui->settingsLable->setText("Клик по данной кнопке открывает окно настройти поиска.");
}

howtouse::~howtouse()
{
    delete ui;
}
