#pragma once
#include <iostream>
#define ERROR_OUTPUT(v) std::cerr << "\033[31m" << v << "\033[0m"
#define ERROR_OUTPUT_LN(v) ERROR_OUTPUT(v) << std::endl

#define WARNING_OUTPUT(v) std::cout<<std::cout << "\033[33m" << v << "\033[0m"
#define WARNING_OUTPUT_LN(v) WARNING_OUTPUT<<std::endl

#define NORMAL_OUTPUT(v) std::cout << v
#define NORMAL_OUTPUT_LN(v) NORMAL_OUTPUT(v) << std::endl
