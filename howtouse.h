#ifndef HOWTOUSE_H
#define HOWTOUSE_H

#include <QDialog>

namespace Ui {
class howtouse;
}

class howtouse : public QDialog
{
    Q_OBJECT
    
public:
    explicit howtouse(QWidget *parent = 0);
    ~howtouse();
    
private:
    Ui::howtouse *ui;
};

#endif // HOWTOUSE_H
