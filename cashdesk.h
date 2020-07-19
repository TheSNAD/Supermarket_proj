#ifndef CASHDESK_H
#define CASHDESK_H
#include "customer.h"
#include <list>

class CashDesk
{
    // класс для хранения очереди и прибыли на одной кассе
public:
    std::list<Customer> queue;
    int profit = 0;
    CashDesk(){}
    void clear () {profit = 0;}
};

#endif // CASHDESK_H
