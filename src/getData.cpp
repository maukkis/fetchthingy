#include <cmath>
#include <cstdio>
#include <iterator>
#include "includes/3rdparty/pstream.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using ibuf_it = std::istreambuf_iterator<char>;
std::string* getKernel(){
  redi::ipstream proc("uname -r");
  static std::string kernel(ibuf_it(proc.rdbuf()), ibuf_it());
  kernel.erase(std::remove(kernel.begin() , kernel.end(), '\n'), kernel.end()); 
  return &kernel;
}

std::string* getOs(){
  redi::ipstream proc("lsb_release -s -d");
  static std::string release(ibuf_it(proc.rdbuf()), ibuf_it());
  release.erase(std::remove(release.begin() , release.end(), '\n'), release.end()); 
  return &release;
}

std::string* getDesktop(){
  redi::ipstream proc("echo $XDG_CURRENT_DESKTOP");
  static std::string desktop(ibuf_it(proc.rdbuf()), ibuf_it());
  desktop.erase(std::remove(desktop.begin() , desktop.end(), '\n'), desktop.end()); 
  return &desktop;
}

std::string* getCpu(){
  redi::ipstream proc("awk -F ' *: | @' \\ '/model name|Hardware|Processor|^cpu model|chip type|^cpu type/ { cpu=$2; if ($1 == Hardware) exit } END { print cpu }' /proc/cpuinfo");
  static std::string cpu(ibuf_it(proc.rdbuf()), ibuf_it());
  cpu.erase(std::remove(cpu.begin() , cpu.end(), '\n'), cpu.end());
  return &cpu;
}

std::string* getUptime(){
  redi::ipstream proc("uptime -p");
  static std::string uptime(ibuf_it(proc.rdbuf()), ibuf_it());
  uptime.erase(std::remove(uptime.begin(), uptime.end(), '\n'), uptime.end());
  return &uptime;
}

const std::string* getMem(){
  std::string line;
  std::ifstream mem("/proc/meminfo");
  double maxmem;
  double usedmem;
  std::cout << line;
  while(getline(mem, line)){
    if(line.find("MemTotal:") == 0){
      std::istringstream iss(line);
      iss.ignore(256, ' ');
      double meow;
      iss >> meow;
      maxmem = meow / 1048576;
      
    } else if(line.find("Active:") == 0){
      std::istringstream iss(line);
      iss.ignore(256, ' ');
      double meow;
      iss >> meow;
      usedmem = meow / 1048576;
      break;
    }
  }
  static const std::string meow{std::to_string(usedmem) + '/' + std::to_string(maxmem) + " GiB"};
  return &meow;
} 
