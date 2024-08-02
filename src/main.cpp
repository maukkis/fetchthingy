#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "includes/getData.h"



int main()
{
  std::vector<std::string> asciiart{
    "      \x1B[90m___\x1B[0m   ",
    "     \x1B[90m(\x1B[0m..\x1B[90m \\\x1B[0m   ",
    "     \x1B[90m(\x1B[33m<>\x1B[90m |\x1B[0m   ",
    "    \x1B[90m/\x1b[0m/  \\ \x1b[90m\\\x1B[0m  ",
    "   \x1B[90m(\x1b[0m |  |\x1b[90m /|\x1B[0m ",
    "  \x1B[33m_\x1b[90m/\\ \x1B[0m__)\x1B[90m/\x1b[33m_\x1b[0m)  ",
    "  \x1B[33m\\/\x1B[90m-____\x1B[33m\\/ \x1B[0m "};
  const std::string* ptrCpu {nullptr};
  std::thread tCpu ([&ptrCpu] {ptrCpu = getCpu();});
  const std::string* ptrKernel {nullptr};
  std::thread tKernel([&ptrKernel] {ptrKernel = getKernel();});
  const std::string* ptrRelease {nullptr};
  std::thread tRelease ([&ptrRelease] {ptrRelease = getOs();});
  const std::string* ptrDesktop{nullptr};
  std::thread tDesktop([&ptrDesktop]{ ptrDesktop = getDesktop();} );
  tKernel.join();
  tRelease.join();
  tDesktop.join();
  tCpu.join();
  std::vector<std::string> infojutut{"OS: ", "Kernel: ", "DE: ", "CPU: "};
  std::vector<const std::string*> values{ptrRelease, ptrKernel, ptrDesktop, ptrCpu};
  for(int ascii{0}, info{0}; ascii < asciiart.size(); ++ascii){
    std::cout << asciiart[ascii] << '\t';
    
    if (info < values.size()) {
      std::cout << infojutut[info];
      std::cout << *values[info];
      ++info;
    }
    std::cout << '\n';
  }
  return 0;
}
