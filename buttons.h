#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>
#include <QtWidgets>

class Buttons : public QWidget
{
    Q_OBJECT
public:

    QVBoxLayout * front = new QVBoxLayout;
    QLabel *lbl_desk = new QLabel("Максимальная длина очереди:");
    QLabel *lbl_step = new QLabel("Количество недель для моделирования (1-12):");
    QLabel *tmp = new QLabel("");
    QPushButton *go = new QPushButton("Начать / Следующая неделя");
    QPushButton *finish = new QPushButton("Закончить моделирование");
    QPushButton *exit = new QPushButton("Выйти");
    QLineEdit *size_desk = new QLineEdit("6");
    QLineEdit *size_step = new QLineEdit("1");

    Buttons()
    {
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(tmp);
        front->addWidget(lbl_desk);
        front->addWidget(size_desk);
        front->addWidget(lbl_step);
        front->addWidget(size_step);
        front->addWidget(go);
        front->addWidget(finish);
        front->addWidget(exit);
        setLayout(front);
    }
signals:

};

#endif // BUTTONS_H
