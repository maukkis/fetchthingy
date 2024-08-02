#include <iterator>
#include "includes/3rdparty/pstream.h"
#include <string>

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


