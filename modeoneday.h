#ifndef MODEONEDAY_H
#define MODEONEDAY_H
//#include <QString>

class ModeOneDay
{   
    // класс для хранения параметров дня
public:
    int countCashDesks;
    bool ad;
    int disc;
    ModeOneDay(int count, bool advert, int discount)
    {
        countCashDesks = count;
        ad = advert;
        disc = discount;

    }
};

#endif // MODEONEDAY_H
