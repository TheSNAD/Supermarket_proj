#ifndef LABELS_H
#define LABELS_H

#include <QWidget>
#include <QtWidgets>

// виджет дня в главном окне
//это вспомогательный класс для графического интерфейса

class Labels : public QWidget
{
    Q_OBJECT
public:

    QVBoxLayout * front;
    QLabel * lbl;
    QLabel * cashdesk;
    QLabel * advert;
    QLabel * discount;
    QLabel *r;

    Labels()
    {
        front = new QVBoxLayout;
        lbl = new QLabel("Дни");
        cashdesk = new QLabel("Кол-во касс");// инициализация элементов класса
        advert = new QLabel("Реклама");
        discount = new QLabel("Скидка %");
        r = new QLabel("");
        cashdesk->move(25,25);

        front->addWidget(lbl);
        front->addWidget(cashdesk);
        front->addWidget(advert); // добавление элементов в слой разметки
        front->addWidget(discount);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        front->addWidget(r);
        setLayout(front);
    }
signals:

};
#endif // LABELS_H
