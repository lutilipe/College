#include <iostream>

#include "time.h"

Time::Time(int dia, int hora, int min, int seg) {
    this->dia = dia;
    this->hora = hora;
    this->min = min;
    this->seg = seg;
    parse();
}

void Time::parse() {
    if (seg >= END_OF_SECOND) {
        int i = seg - END_OF_SECOND;
        seg = i;
        min++;
    } else if (seg < START_OF_SECOND) {
        int i = END_OF_SECOND + seg;
        seg = i;
        min--;
    }

    if (min >= END_OF_MINUTE) {
        int i = min - END_OF_MINUTE;
        min = i;
        hora++;
    } else if (min < START_OF_MINUTE) {
        int i = END_OF_MINUTE + min;
        min = i;
        hora--;
    }

    if (hora >= END_OF_HOUR) {
        int i = hora - END_OF_HOUR;
        hora = i;
        dia++;
    }else if (hora < START_OF_HOUR) {
        int i = END_OF_HOUR + hora;
        hora = i;
        dia--;
    }
}

int Time::getDay() {
    return dia;
}

int Time::getHour() {
    return hora;
}

int Time::getMinutes() {
    return min;
}

int Time::getSeconds() {
    return seg;
}

void Time::read() {
    for (int i=0; i<3; i++) {
        if(std::cin >> dia >> hora >> min >> seg) {
            std::cin >> dia >> hora >> min >> seg;
        }
    }
    parse();
}

void Time::print() {
    std::cout << dia << ":" << hora << ":" << min << ":" << seg << std::endl;
}

void Time::increment() {
    seg++;
    parse();
}

void Time::decrement() {
    seg--;
    parse();
}

Time Time::operator +(Time t) {
    this->dia += t.getDay();
    this->hora += t.getHour();
    this->min += t.getMinutes();
    this->seg += t.getSeconds();
    parse();
    return *this;
}