#include<iostream>
#include"Date.h"


int main()
{
    project::Date date1("10/01/2023");

    project::Date date2(1673199797);

    //date2++;


    std::cout << date2 << std::endl;
    std::cout << date1 << std::endl;

    

    date2.print_all();

    return 0;
}