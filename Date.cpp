#include"Date.h"
#include<iostream>
#include<string.h>



project::Date::Date()
{
    m_day = 01;
    m_month = 01;
    m_year = year_base;
    m_wday = (project::Date::Weekday::Sunday);
    m_year_day = 01;
}

project::Date::Date(int d, int m, int y) :m_day{d},m_month{m},m_year{y}
{
    if(m_day> 31)
        m_day = 1;
    if(m_month>12)
        m_month = 1;
    if(m_year>= 9999 || m_year< 1900)
        m_year = 1900;

    calculate_month_day();
    calculate_year_day(); 
}

project::Date::Date(const char *p)
{
    if(p == nullptr)
        return;
    
    int temp_day{}, temp_month{}, temp_year{};
    std::string string_value = p;
    int date_number{};



    string_value = string_value.erase(string_value.find('/'),1);
    string_value = string_value.erase(string_value.find('/'),1); 

    date_number = atoi(string_value.c_str());
    
    temp_day = date_number / 1'000'000;
    temp_month = (date_number / 10000) % 100;
    temp_year = date_number % 10000;

    if(is_valid_date(temp_day, temp_month, temp_year))
    {
        m_day = temp_day;
        m_month = temp_month;
        m_year = temp_year;
        m_year_day = 0;
    }

    calculate_month_day();
    calculate_year_day();
}

bool project::Date::is_valid_date(int day, int month, int year)
{
    if(day <= 31 && day >= 0)
    {
        if(month <= 12 && month >=1)
        {
            if(year <= 9999 && year >= 1900)
            {
                return true;
            }
        }
    }
    
    return false;
}

project::Date::Date(std::time_t timer)
{
    tm *source_time = localtime(&timer);

    m_year   = 1900 + source_time->tm_year;
    m_month = 1 + source_time->tm_mon;
    m_day    = source_time->tm_mday;
    m_year_day = 0;

    calculate_month_day();
    calculate_year_day();
}

int project::Date::get_month_day()const
{
    return m_day;
}

void project::Date::calculate_month_day()
{
    int temp_year;
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };

    if(m_month < 3)
        temp_year = m_year - m_month;
    m_wday = static_cast<Weekday>(( temp_year + temp_year / 4 - temp_year / 100 +
             temp_year / 400 + t[m_month - 1] + m_day) % 7);
}

int project::Date::get_month()const
{
    return m_month;
}

int project::Date::get_year()const
{
    return m_year;
}

int project::Date::get_year_day()const
{
    return m_year_day;
}

void project::Date::calculate_year_day()
{
    for(int i=0; i<m_month; i++)
    {
        if(m_month == 1)
            continue;
        m_year_day += num_of_day_of_month[i];
    }
    m_year_day += m_day;
}

constexpr bool project::Date::isleap(int year)
{
    if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)))
        return true;
    else
        return false;
    
}

project::Date::Weekday project::Date::get_week_day()const
{
    switch (m_wday)
    {
    case project::Date::Weekday::Sunday:
        return project::Date::Weekday::Sunday;
        break;

    case project::Date::Weekday::Monday:
        return project::Date::Weekday::Monday;
        break;

    case project::Date::Weekday::Tuesday:
        return project::Date::Weekday::Tuesday;
        break;

    case project::Date::Weekday::Wednesday:
        return project::Date::Weekday::Wednesday;
        break;

    case project::Date::Weekday::Thursday:
        return project::Date::Weekday::Thursday;
        break;

    case project::Date::Weekday::Friday:
        return project::Date::Weekday::Friday;
        break;

    case project::Date::Weekday::Saturday:
        return project::Date::Weekday::Saturday;
        break;

    default:
        return project::Date::Weekday::Sunday;
        break;
    }
}

project::Date   &project::Date::set_month_day(int day)
{
    m_day = day;
    return *this;
}

project::Date &project::Date::set_month(int month)
{
    m_month = month;
    return *this;
}

project::Date &project::Date::set_year(int year)
{
    m_year = year;
    return *this;
}

project::Date &project::Date::set(int day, int mon, int year)
{
    m_day   = day;
    m_month = mon;
    m_year  = year;

    return *this;
}

project::Date project::Date::operator-(int day)const
{
    time_t current_timestamp{}, remain_timestamp{};
    struct tm current_time{}, *last_time{};
    auto* p_this = const_cast<project::Date*>(this);

    current_time.tm_mday = m_day - day;
    current_time.tm_mon = m_month-1;
    current_time.tm_year = m_year-1900;

    current_timestamp = mktime(&current_time);
    last_time = localtime(&current_timestamp);
    
    p_this->m_day = last_time->tm_mday;
    p_this->m_month = last_time->tm_mon+1;
    p_this->m_year = last_time->tm_year+1900;
    
    return *this;
}

project::Date &project::Date::operator+=(int day)
{
    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t add_time = convert_day_to_timestamp(day);
    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time + add_time;
    tm_current = localtime(&sum_time);

    p_this->m_day = tm_current->tm_mday;
    p_this->m_month = tm_current->tm_mon + 1;
    p_this->m_year = tm_current->tm_year + 1900;

    return *this;
}

project::Date &project::Date::operator-=(int day)
{
    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t subs_time = convert_day_to_timestamp(day);
    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time - subs_time;

    tm_current = localtime(&sum_time);

    p_this->m_day = tm_current->tm_mday;
    p_this->m_month = tm_current->tm_mon + 1;
    p_this->m_year = tm_current->tm_year + 1900;
    
    return *this;
}

project::Date &project::Date::operator++()
{
    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t add_time = convert_day_to_timestamp(1);
    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time + add_time;
    tm_current = localtime(&sum_time);

    p_this->m_day = tm_current->tm_mday;
    p_this->m_month = tm_current->tm_mon + 1;
    p_this->m_year = tm_current->tm_year + 1900;

    return *this;
}

project::Date project::Date::operator++(int day)
{
    project::Date temp = *this;

    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t add_time = convert_day_to_timestamp(day);

    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time + add_time;

    tm_current = localtime(&sum_time);

    p_this->m_day = tm_current->tm_mday;
    p_this->m_month = tm_current->tm_mon + 1;
    p_this->m_year = tm_current->tm_year + 1900;
    
    return temp;
}

project::Date &project::Date::operator--()
{

    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t subs_time = convert_day_to_timestamp(1);

    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time - subs_time;

    tm_current = localtime(&sum_time);

    p_this->m_day = tm_current->tm_mday;
    p_this->m_month = tm_current->tm_mon + 1;
    p_this->m_year = tm_current->tm_year + 1900;

    return *this;
}

project::Date project::Date::operator--(int day)
{
    project::Date temp {*this};

    time_t sum_time{};
    time_t current_time = convert_date_to_timestamp(*this);
    time_t subs_time = convert_day_to_timestamp(day);

    tm* tm_current{};

    auto* p_this = static_cast<project::Date*>(this);

    sum_time = current_time - subs_time;
    
    tm_current = localtime(&sum_time);

    temp.m_day = tm_current->tm_mday;
    temp.m_month = tm_current->tm_mon + 1;
    temp.m_year = tm_current->tm_year + 1900;

    return temp;
    
}

bool project::operator<(const project::Date &comp1, const project::Date &comp2)
{
    if(comp1.get_year() < comp2.get_year())
    {
        if(comp1.get_month() <= comp2.get_month())
        {
            if(comp1.get_month_day() < comp2.get_month_day())
                return true;
            
            return true;
        }
        return true;
    }
    
    return false;
}


bool project::operator==(const project::Date &comp1, const project::Date &comp2)
{
    if(comp1.get_year() == comp2.get_year())
    {
        if(comp1.get_month() == comp2.get_month())
        {
            if(comp1.get_month_day() == comp2.get_month_day())
                return true;
        }
    }
    return false;
}

project::Date project::Date::random_date()
{
    srand((unsigned int)time(NULL));
    
    Date rand_date;
    time_t timer = time(0);
    struct tm* current_time = localtime(&timer);
    

    time_t first_time = time(0);

    rand_date.m_year = rand() % (current_time->tm_year) + 1900;
    rand_date.m_month = rand() % 12 + 1;
    while(true)
    {
        if(rand_date.m_month == 2)
        {
            int day = project::Date::isleap(rand_date.m_year) ? 29 : 28;
            rand_date.m_day = rand() % day +1;
            break;
        }
        else
        {
             if(rand_date.m_month == 1 || rand_date.m_month == 3 || rand_date.m_month == 5 || rand_date.m_month == 7 || rand_date.m_month == 8 )
             {
                rand_date.m_day = rand() % 31 +1;
                break;
             }
             else
             {
                rand_date.m_day = rand() % 30 +1;
                break;
             } 
        }
    }

    return rand_date;
}


time_t project::Date::convert_day_to_timestamp(int day)
{
    time_t current_time{}, remain_timestamp{};
    struct tm tm_current{}, tm_remain{};

    
    tm_current.tm_mday = m_day;
    tm_current.tm_mon = m_month - 1;
    tm_current.tm_year = m_year - 1900;

    tm_remain.tm_mday = abs(m_day - day);
    tm_remain.tm_mon = m_month - 1;
    tm_remain.tm_year = m_year - 1900;

    remain_timestamp = mktime(&tm_remain);
    current_time = mktime(&tm_current);

    current_time = abs(current_time - remain_timestamp);

    return current_time;
}

time_t project::Date::convert_date_to_timestamp(project::Date object)
{
    time_t current_time{};
    struct tm tm_current{};

    tm_current.tm_mon = object.m_month - 1;
    tm_current.tm_mday = object.m_day;
    tm_current.tm_year = object.m_year - 1900;
    
    current_time = mktime(&tm_current);

    return current_time;
}

std::ostream &project::operator<<(std::ostream &os, const project::Date& date)
{
    os<< date.get_month_day() << " " << date.string_month[date.get_month()-1] << " " << date.get_year();
    return os;
}

std::istream &project::operator>>(std::istream &is, Date &date)
{
    std::cout<< "Enter a day : ";
    is >>date.m_day;
    std::cout<<"\n";

    std::cout<< "Enter a month : ";
    is >>date.m_month;
    std::cout<<"\n";

    std::cout<< "Enter a year : ";
    is >>date.m_year;
    std::cout<<"\n";

    return is;
}


bool project::operator<=(const Date &comp1, const Date &comp2)
{
    if(comp1.get_year() <= comp2.get_year())
    {
        if(comp1.get_month() <= comp2.get_month())
        {
            if(comp1.get_month_day() <= comp2.get_month_day())
                return true;
            
            return true;
        }
        return true;
    }
    
    return false;
}

bool project::operator>(const Date &comp1, const Date &comp2)
{
    if(comp1.get_year() > comp2.get_year())
    {
        if(comp1.get_month() > comp2.get_month())
        {
            if(comp1.get_month_day() > comp2.get_month_day())
                return true;
            
            return true;
        }
        return true;
    }
    
    return false;
}



int project::operator-(const Date &d1, const Date &d2)
{
    int sum1{},sum2{};
    int d1_day{d1.get_month_day()};
    int d1_month{d1.get_month()};
    int d1_year{d1.get_year()};

    int d2_day{d2.get_month_day()};
    int d2_month{d2.get_month()};
    int d2_year{d2.get_year()};

    if(d1_month < 3)
    {
        d1_year--;
        d1_month += 12;
    }
    sum1 = 365 * d1_year + d1_year/4 - d1_year/100 + d1_year/400 + (153*d1_month - 457)/5 + d1_day - 306;

    if(d2_month < 3)
    {
        d2_year--;
        d2_month += 12;
    }
    sum2 = 365 * d2_year + d2_year/4 - d2_year/100 + d2_year/400 + (153*d2_month - 457)/5 + d2_day - 306;

    return abs(sum1-sum2);
}

project::Date project::operator+(const project::Date &date, int n)
{
    project::Date date_opr;

    int sum1{};
    int date_day{date.get_month_day()};
    int date_month{date.get_month()};
    int date_year{date.get_year()};
    int add_year;
    int remains_day;


    add_year = n/365;
    remains_day = n % 365;

    date_year +=add_year;

    for(int i=0; i<remains_day ;i++)
    {
        if(date_day < date.num_of_day_of_month[date_month -1])
            date_day++;
        else if((date_day == date.num_of_day_of_month[date_month -1]) && (date_month < 12))
        {
            date_day =1;
            date_month++;
        }
        else if((date_day == date.num_of_day_of_month[date_month -1]) && (date_month == 12))
        {
            date_day = 1;
            date_month = 1;
            date_year++;
        }
    }
    
    date_opr.set_month(date_month);
    date_opr.set_month_day(date_day);
    date_opr.set_year(date_year);

    return date_opr;

}

project::Date project::operator+(int n, const project::Date &date)
{
    project::Date date_opr;

    int sum1{};
    int date_day{date.get_month_day()};
    int date_month{date.get_month()};
    int date_year{date.get_year()};
    int add_year;
    int remains_day;


    add_year = n/365;
    remains_day = n % 365;

    date_year +=add_year;

    for(int i=0; i<remains_day ;i++)
    {
        if(date_day < date.num_of_day_of_month[date_month -1])
            date_day++;
        else if((date_day == date.num_of_day_of_month[date_month -1]) && (date_month < 12))
        {
            date_day =1;
            date_month++;
        }
        else if((date_day == date.num_of_day_of_month[date_month -1]) && (date_month == 12))
        {
            date_day = 1;
            date_month = 1;
            date_year++;
        }
    }
    
    date_opr.set_month(date_month);
    date_opr.set_month_day(date_day);
    date_opr.set_year(date_year);

    return date_opr;

}

project::Date::Weekday &project::operator++(Date::Weekday &r)
{
    const int i = static_cast<int>(r);
    r = static_cast<project::Date::Weekday>((i+1) % 7);
    return r;
}

project::Date::Weekday project::operator++(Date::Weekday &r, int k)
{
    project::Date::Weekday pre_inc_weekday;
    const int i = static_cast<int>(r);
    pre_inc_weekday = static_cast<project::Date::Weekday>((i+k) % 7);
    return pre_inc_weekday;
}

project::Date::Weekday &project::operator--(Date::Weekday &r)
{
    const int i = static_cast<int>(r);
    int subs = i - 1;
    if(subs < 0)
    {
        subs = 6;
    }
    
    r = static_cast<project::Date::Weekday>(subs % 7);
    return r;
}

project::Date::Weekday project::operator--(Date::Weekday &r, int k)
{
    project::Date::Weekday pre_dec_weekday;
    int i = static_cast<int>(r);

    k = k % 7;

    for(int m = k; m>0; m--)
    {
        i--;
        if(i == 0)
            i = 6;
    }

    pre_dec_weekday = static_cast<project::Date::Weekday>(i);
    return pre_dec_weekday;
}

void project::Date::print_all()
{
    std::cout << "Day : " << m_day << "Month : " << m_month << "Year : " << m_year << std::endl;
}

