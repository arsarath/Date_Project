#ifndef DATE_H
#define DATE_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iosfwd>
#include <ctime>
#include <time.h>

namespace project
{
    class Date
    {
    public:
        static constexpr int year_base = 1900;       // 1   OK      OK 
        static constexpr int random_min_year = 1940; // 2   OK      OK
        static constexpr int random_max_year = 2020; // 3   OK      OK
        enum class Weekday
        {
            Sunday,
            Monday,
            Tuesday,
            Wednesday,
            Thursday,
            Friday,
            Saturday
        };                            // 4  OK      OK
        const std::string string_month[12] = {"January", "February", "March", "April", "May", "June",
                                              "July", "August", "September", "October", "November", "December"};
        const int num_of_day_of_month[12] = {31, (isleap(m_year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        Date();                       // 5  OK      OK
        Date(int d, int m, int y);    // 6  OK      OK
        Date(const char *p);          // 7  OK      tarih dısında bir deger gelince hata veriyor
        Date(std::time_t timer);      // 8  OK      OK
        int get_month_day() const;    // 9  OK      OK
        int get_month() const;        // 10 OK      OK
        int get_year() const;         // 11 OK      OK
        int get_year_day() const;     // 12 OK      OK
        Weekday get_week_day() const; // 13 OK      OK

        Date &set_month_day(int day);          // 14    OK      OK
        Date &set_month(int month);            // 15    OK      OK
        Date &set_year(int year);              // 16    OK      OK
        Date &set(int day, int mon, int year); // 17    OK      OK
        Date operator-(int day) const;         // 18    OK      OK      
        Date &operator+=(int day);             // 19    OK      OK
        Date &operator-=(int day);             // 20    OK      OK  
        Date &operator++();                    // 21    OK      OK
        Date operator++(int);                  // 22    OK      OK
        Date &operator--();                    // 23    OK      OK
        Date operator--(int);                  // 24    OK      OK
        Date &operator=(const Date &)const;

        friend bool operator<(const Date &, const Date &);  // 27  OK       OK
        friend bool operator==(const Date &, const Date &); // 27  OK       OK
        static Date random_date();                          // 25  OK       OK
        static constexpr bool isleap(int y);                // 26  OK       OK

        friend std::ostream &operator<<(std::ostream &os, const Date &date); // 31  OK  OK
        friend std::istream &operator>>(std::istream &is, Date &date);       // 32  OK  OK

        bool is_valid_date(int day, int month, int year);       
        void print_all();
        void calculate_month_day();
        void calculate_year_day();
        time_t convert_date_to_timestamp(Date object);
        time_t convert_day_to_timestamp(int day);

    private:
        int m_day;
        int m_month;
        int m_year;
        int m_year_day;
        Weekday m_wday;
    };

    bool operator<(const Date &, const Date &);  // 27  OK      OK
    bool operator<=(const Date &, const Date &); // 27  OK      OK
    bool operator>(const Date &, const Date &);  // 27  OK      OK
    bool operator>=(const Date &, const Date &); // 27  OK      OK
    bool operator==(const Date &, const Date &); // 27  OK      OK
    bool operator!=(const Date &, const Date &); // 27  OK      OK

    int operator-(const Date &d1, const Date &d2);   // 28  OK  OK
    Date operator+(const Date &date, int n);         // 29  OK  OK
    Date operator+(int n, const Date &);             // 29  OK  OK
    Date::Weekday &operator++(Date::Weekday &r);     // 30  OK  OK
    Date::Weekday operator++(Date::Weekday &r, int); // 30  OK  OK
    Date::Weekday &operator--(Date::Weekday &r);     // 30  OK  OK
    Date::Weekday operator--(Date::Weekday &r, int); // 30  OK  OK
}

#endif