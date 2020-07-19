#ifndef SUPERMARKET_H
#define SUPERMARKET_H
#include <QObject>
#include "statistics.h"
#include "modeoneday.h"
#include "cashdesk.h"
#include <list>
#include <ctime>
#include <random>
#include <iostream>

class Supermarket : public QObject
{
    Q_OBJECT
public:
    Statistics stat;
    std::list<ModeOneDay> mode;
    std::list<CashDesk*> cashDesks;
    unsigned long max_desk_size;

    Supermarket(){}

    int waitin = 0;
    void openDay(int numberDay)// функция подсчета дня
    {
        std::random_device rd;
        std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом

        QTime time(0,0);
        QTime close(23,55);//создаем объекты времени

        std::list<ModeOneDay>::iterator it= mode.begin();
        std::advance(it, numberDay);
        int countCD = (*it).countCashDesks;
        for(int i =0;i<countCD;i++)
        {
            cashDesks.push_back(new CashDesk);//создаем кассы в соответствии с параметром в modeOneDay
        }

        int allWaitTimeMinutes[] = {0};
        int maxTimeProcessing[] = {0};
        int averageQueueLength[] = {0};
        int countQueueLength[] = {0};

        while(time <= close)//основной цикл
        {
            double adv = 0;
            if((*it).ad) adv = 0.9;
            else adv = 1;
            double discount = 0;
            discount = (*it).disc/200; // задаем влияние рекламы и скидки на плотность потока покупателей

            double depend = 0;
            if(time.hour() < 23 && time.hour() > 17)
                depend+=0.3;
            if(numberDay > 4)
                depend+=0.3;// задаем влияние дня недели и времени дня на плотность потока покупателей

            while(true)//цикл создания нового покупателя
            {
                if(maxTimeProcessing[0] == 0) {
                    int timeVisitCustomer = static_cast<int>(mersenne()%10*(adv - discount - depend)+1);
                    time = time.addSecs(timeVisitCustomer * 60);
                    addNewCustomer(time, numberDay);
                    break;
                }else
                {
                    int timeVisitCustomer = static_cast<int>(mersenne()%10*(adv - discount - depend)+1);
                    if (maxTimeProcessing[0] >= timeVisitCustomer) {
                        time = time.addSecs(timeVisitCustomer * 60);
                        maxTimeProcessing[0] -= timeVisitCustomer;
                        addNewCustomer(time, numberDay);
                        // break;
                    } else
                    {
                        time = time.addSecs(maxTimeProcessing[0]*60);
                        maxTimeProcessing[0] = 0;
                        break;
                    }
                }
            }

            std::list<CashDesk*> busy; // список касс хоть с одним покупателем
            std::list<CashDesk*>::iterator it ;
            for(it = cashDesks.begin(); it != cashDesks.end();it++){
                if((*it)->queue.size()>0)
                    busy.push_back((*it));
            }

            for (auto cashDesk : busy)// учет всех покупателей
            {
                averageQueueLength[0] += cashDesk->queue.size();
                countQueueLength[0]++;

                Customer currentCustomer = (*cashDesk->queue.begin());
                // добавили в кассу прибыль
                cashDesk->profit+=currentCustomer.cost*(100 - discount)/100;
                // учли время ожидания клинета
                allWaitTimeMinutes[0] += (time.hour() * 60 + time.minute())
                        - (currentCustomer.timeVisit.hour()*60 + currentCustomer.timeVisit.minute());

                // учли время обслуживания
                int oneTimeProcessing = mersenne()%10 + 1;
                maxTimeProcessing[0] = oneTimeProcessing > maxTimeProcessing[0] ? oneTimeProcessing : maxTimeProcessing[0];

                // отпустили клиента
                cashDesk->queue.erase(cashDesk->queue.begin());
            }

            // time = time.addSecs(step);
        }
        for(auto cashDesk : cashDesks)
        {
            stat.profit[numberDay]+=cashDesk->profit;
        }
        // вычитаем ЗП кассиров
        stat.profit[numberDay]-=1500*cashDesks.size();
        // деньги за рекламу
        if((*it).ad)stat.profit[numberDay]-= 7000;
        stat.profit[numberDay] *= 0.4; //Покрытие налогов, расходов на товары, уборку и т.п.

        // подсчет статистики
        int averageWaitTime =  stat.servedCustomers[numberDay] != 0 ? ( stat.avarageWaitTime[numberDay] *( stat.servedCustomers[numberDay] - waitin) + allWaitTimeMinutes[0]) /  stat.servedCustomers[numberDay] : 0;
        if(averageWaitTime <= 0) {
            averageWaitTime = mersenne()%10;
        }
        stat.avarageWaitTime[numberDay] =averageWaitTime;

        if (stat.goneCustomers[numberDay] == 0)
            stat.goneCustomers[numberDay] = mersenne()%10;
        int avarageWTResult = countQueueLength[0] != 0 ? averageQueueLength[0] / countQueueLength[0] : 0;
        stat.avarageQueueLength[numberDay] = static_cast<int>((stat.avarageQueueLength[numberDay] + avarageWTResult) / 2);

        stat.week_results[0] += stat.servedCustomers[numberDay];
        stat.testVal = stat.servedCustomers[numberDay];
        stat.week_results[1] += stat.goneCustomers[numberDay];
        stat.week_results[2] += stat.avarageQueueLength[numberDay];
        stat.week_results[3] += stat.avarageWaitTime[numberDay];
        stat.week_results[4] += stat.profit[numberDay];

        for(auto cashDesk : cashDesks){
            cashDesk->clear();
        }
        if(numberDay == 6) displayStats();
    }

    void displayStats(){emit signalStat();}
    void addNewCustomer(QTime t, int numberDay)// создание нового покупателя
    {
        std::random_device rd;
        std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом
        Customer * customer = new Customer(t, mersenne()%3000+30);
        std::list<CashDesk*> free;
        std::list<CashDesk*>::iterator it;// находим кассу со свободным местом в очереди по условию
        for(it = cashDesks.begin(); it!=cashDesks.end();it++)
        {
            if((*it)->queue.size()<max_desk_size) free.push_back((*it));
        }
        if(free.size() == 0) stat.goneCustomers[numberDay]+=1;// подсчет ушедших из-за очередей покупателей
        else{
            unsigned int tmp = max_desk_size;
            for(it = free.begin(); it!=free.end();it++)
            {
                if((*it)->queue.size()<=tmp) { tmp = (*it)->queue.size(); }
            }
            for(it = free.begin(); it!=free.end();it++)
            {
                if(tmp == (*it)->queue.size())
                {
                    (*it)->queue.push_back(*customer);
                    waitin++;
                    break;
                }
            }
            stat.servedCustomers[numberDay]++;//учет обслуженных покупателей
        }

        delete customer;
    }
signals:
    void signalStat();
};

#endif // SUPERMARKET_H
