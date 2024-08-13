#ifndef _MEOW_H
#define _MEOW_H
#include <iostream>
std::string* getKernel();
std::string* getOs();
std::string* getDesktop();
std::string* getCpu();
std::string* getUptime();
const std::string* getMem();
#endif // !_MEOW_H
