#ifndef DAY_H
#define DAY_H

#include <QWidget>
#include <QtWidgets>

// виджет дня в главном окне
//это вспомогательный класс для графического интерфейса

class Day : public QWidget
{
    Q_OBJECT
public:

    QVBoxLayout * front;
    QLabel * lbl;
    QLineEdit * cashdesk;
    QComboBox * advert;
    QLineEdit * discount;
    QTextEdit * res;

    Day(QString day)
    {
        front = new QVBoxLayout;
        lbl = new QLabel(day);
        cashdesk = new QLineEdit("1");// инициализация элементов класса
        advert = new QComboBox();
        advert->setCurrentText("Нет");
        advert->addItem("Нет");
        advert->addItem("Да");
        discount = new QLineEdit("0");
        res =  new QTextEdit("Результат:");

        front->addWidget(lbl);
        front->addWidget(cashdesk);
        front->addWidget(advert); // добавление элементов в слой разметки
        front->addWidget(discount);
        front->addWidget(res);
        setLayout(front);
    }

    int getCashdesck()
    {
        return cashdesk->text().toInt();
    }
    bool getAdv()
    {
        if(advert->currentText() == "Нет") return false;
        else return true;
    }
    int getDiscount()
    {
        return discount->text().toInt();
    }

signals:

};

#endif // DAY_H
