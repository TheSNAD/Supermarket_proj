#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QTime>
class Customer
{
    // класс покупателя
public:
    int cost;
    QTime timeVisit;
    Customer(QTime t, int randCost)// при создании покупателя мы получаем текущее время из симуляции
    {
        timeVisit = t;
        cost = randCost;
    }
};

#endif // CUSTOMER_H
