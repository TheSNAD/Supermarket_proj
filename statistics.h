#ifndef STATISTICS_H
#define STATISTICS_H


class Statistics // класс для хранения статистики
{
public:
    int week_results[5];
    int final_results[5];
    int servedCustomers[7];
    int goneCustomers[7];
    int avarageQueueLength[7];
    int avarageWaitTime[7];
    int profit[7];
    int testVal = 0;

    Statistics()
    {
        for (int i = 0; i < 7; i++){
             servedCustomers[i] = 0;
             goneCustomers[i] = 0;
             avarageQueueLength[i] = 0;
             avarageWaitTime[i] = 0;
             profit[i] = 0;
        }
        for (int i = 0; i < 5; i++){
            final_results[i] = 0;
            week_results[i] = 0;
        }
    }

    ~Statistics(){}

    void clear(){
        for (int i = 0; i < 7; i++){
             servedCustomers[i] = 0;
             goneCustomers[i] = 0;
             avarageQueueLength[i] = 0;
             avarageWaitTime[i] = 0;
             profit[i] = 0;
        }
    };

    void clear_week(){
        for (int i = 0; i < 5; i++){
            week_results[i] = 0;
        }
    }
};

#endif // STATISTICS_H
