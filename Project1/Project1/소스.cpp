//#include <ctype.h>
//#include <iostream>
//#include <string>
//
//#include "Exception.h"
//
//namespace ms
//{
//    int char_to_number(const char c)
//    {
//        ms::require(std::isdigit(c), "examine character should be digit");
//
//        return c - '0';
//    }
//}
//
//int main(void)
//{
//    try 
//    {
//        std::cout << ms::char_to_number('a');
//    }
//    catch (const std::exception& except)
//    {
//        std::cout << except.what();
//        exit(523);
//    }
//    
//}
//
