#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "day.h"
#include "labels.h"
#include "supermarket.h"
#include "buttons.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /////элементы графического интерфейса
    QWidget *w = new QWidget;
    Supermarket * supermarket = new Supermarket;

    QHBoxLayout *main_lay = new QHBoxLayout;

    Buttons *buttons = new Buttons();
    Day *day1 = new Day("понедельник");
    Day *day2 = new Day("вторник");
    Day *day3 = new Day("среда");
    Day *day4 = new Day("четверг");
    Day *day5 = new Day("пятница");
    Day *day6 = new Day("суббота");
    Day *day7 = new Day("воскресенье");
    int step = 0;
    int st = 0;
    Labels *lbl = new Labels();
    QTextEdit *tmp[7];
    QTextEdit * result;
    bool f = false;

    MainWindow()
    {
        result = new QTextEdit("Результат за неделю:");
        tmp[0] = day1->res;
        tmp[1] = day2->res;
        tmp[2] = day3->res;
        tmp[3] = day4->res;
        tmp[4] = day5->res;
        tmp[5] = day6->res;
        tmp[6] = day7->res;

        ///////////////добавление элементов в разметку
        main_lay->addWidget(lbl);
        main_lay->addWidget(day1);
        main_lay->addWidget(day2);
        main_lay->addWidget(day3);
        main_lay->addWidget(day4);
        main_lay->addWidget(day5);
        main_lay->addWidget(day6);
        main_lay->addWidget(day7);
        main_lay->addWidget(result);
        main_lay->addWidget(buttons);

        w->setLayout(main_lay);
        setCentralWidget(w);

        //////соединение событий и реакций программы на них ,////
        connect(buttons->go, SIGNAL(clicked()), this, SLOT(slotGo()));
        connect(buttons->finish, SIGNAL(clicked()), this, SLOT(slotFinish()));
        connect(buttons->exit, SIGNAL(clicked()), this, SLOT(slotExit()));
        connect(supermarket, SIGNAL(signalStat()), this, SLOT(slotShowStat()));

    }
    ~MainWindow(){
        delete day1;
        delete day2;
        delete day3;
        delete day4;
        delete day5;
        delete day6;
        delete day7;
        delete lbl;
        delete buttons;
        delete supermarket;
        delete w;
    };

public slots:
    void slotGo()
    {
        if (f == false) {
            step = buttons->size_step->text().toInt();
            st = step;
            f = true;
        }
        if (step > 0) {
            supermarket->stat.clear();
            supermarket->max_desk_size = buttons->size_desk->text().toInt();
            // сбор и передача данных на вычисление
            // реакция программы на нажатие кнопки go

            ModeOneDay d1(day1->getCashdesck(), day1->getAdv(), day1->getDiscount());//создаем объекты
            ModeOneDay d2(day2->getCashdesck(), day2->getAdv(), day2->getDiscount());// хранящие информацию
            ModeOneDay d3(day3->getCashdesck(), day3->getAdv(), day3->getDiscount());// о параметрах каждого дня
            ModeOneDay d4(day4->getCashdesck(), day4->getAdv(), day4->getDiscount());
            ModeOneDay d5(day5->getCashdesck(), day5->getAdv(), day5->getDiscount());
            ModeOneDay d6(day6->getCashdesck(), day6->getAdv(), day6->getDiscount());
            ModeOneDay d7(day7->getCashdesck(), day7->getAdv(), day7->getDiscount());

            supermarket->mode.push_back(d1);// пихаем все в лист
            supermarket->mode.push_back(d2);
            supermarket->mode.push_back(d3);
            supermarket->mode.push_back(d4);
            supermarket->mode.push_back(d5);
            supermarket->mode.push_back(d6);
            supermarket->mode.push_back(d7);

                for (int i = 0; i < 7; i++)
                {
                    supermarket->openDay(i);// запускаем обработку по дням
                    tmp[i]->clear();
                    tmp[i]->append("Результат:");
                    tmp[i]->append("Обслуженные покупатели");
                    tmp[i]->append(QString::number(supermarket->stat.servedCustomers[i]));
                    tmp[i]->append("Потерянные покупатели");
                    tmp[i]->append(QString::number(supermarket->stat.goneCustomers[i]));
                    tmp[i]->append("Среднее время ожидания в очереди");
                    tmp[i]->append(QString::number(supermarket->stat.avarageWaitTime[i]));
                    tmp[i]->append("Выручка супермаркета");
                    tmp[i]->append(QString::number(supermarket->stat.profit[i]));
                }
            supermarket->stat.clear_week();
            step -= 1;
        } else {
            slotFinish();
        }
    };

    void slotFinish(){
        result->clear();
        result->append("Результат за все время:");
        result->append("Прошло недель:");
        result->append(QString::number(st));
        result->append("Обслуженные покупатели");
        result->append(QString::number(supermarket->stat.final_results[0]));
        result->append("Потерянные покупатели");
        result->append(QString::number(supermarket->stat.final_results[1]));
        result->append("Среднее время ожидания в очереди");
        result->append(QString::number(supermarket->stat.final_results[3]/st));
        result->append("Выручка супермаркета");
        result->append(QString::number(supermarket->stat.final_results[4]));
        setCentralWidget(result);
    }

    void slotExit(){
        qApp->exit();
    }

    void slotShowStat()
    {
        // реакция программы на завершение подсчетов
        result->clear();
        result->append("Результат за неделю:");
        result->append("Обслуженные покупатели");
        result->append(QString::number(supermarket->stat.week_results[0]));
        result->append("Потерянные покупатели");
        result->append(QString::number(supermarket->stat.week_results[1]));
        result->append("Среднее время ожидания в очереди");
        result->append(QString::number(supermarket->stat.week_results[3]/7));
        result->append("Выручка супермаркета");
        result->append(QString::number(supermarket->stat.week_results[4]));
        result->append("Осталось недель для моделирования:");
        result->append(QString::number(step - 1));
        supermarket->stat.final_results[0] += supermarket->stat.week_results[0];
        supermarket->stat.final_results[1] += supermarket->stat.week_results[1];
        supermarket->stat.final_results[2] += supermarket->stat.week_results[2];
        supermarket->stat.final_results[3] += supermarket->stat.week_results[3]/7;
        supermarket->stat.final_results[4] += supermarket->stat.week_results[4];
        //result->append("Чек:");
        //result->append(QString::number(supermarket->stat.testVal));
    }
signals:
    void signalStat();
};
#endif // MAINWINDOW_H
