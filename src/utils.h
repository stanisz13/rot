#pragma once
#include <iostream>

#define LOG(x) std::cout<<"| "<<__FILE__<<'-'<<__LINE__<<" | "<<#x<<":  "<<x<<std::endl;
