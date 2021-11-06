#ifndef TIME_H
#define TIME_H

const int START_OF_DAY = 0;
const int START_OF_HOUR = 0;
const int END_OF_HOUR = 24;
const int START_OF_MINUTE = 0;
const int END_OF_MINUTE = 60;
const int START_OF_SECOND = 0;
const int END_OF_SECOND = 60;

class Time {
    private:
        int dia;
        int hora;
        int min;
        int seg;

        void parse();
    public:
        Time(
            int dia = START_OF_DAY, 
            int hora = START_OF_HOUR, 
            int min = START_OF_MINUTE, 
            int sec = START_OF_SECOND
        );

        int getDay();
        int getHour();
        int getMinutes();
        int getSeconds();

        Time operator+(Time t);

        void print();
        void read();
        void increment();
        void decrement();
};

#endif