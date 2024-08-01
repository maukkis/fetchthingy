#include <iostream>
#include <string>
#include <thread>
#include "includes/getData.h"

int main()
{
  const std::string* ptrKernel {nullptr};
  std::thread tKernel([&ptrKernel] {ptrKernel = getKernel();});
  const std::string* ptrRelease {nullptr};
  std::thread tRelease ([&ptrRelease] {ptrRelease = getOs();});
  const std::string* ptrDesktop{nullptr};
  std::thread tDesktop([&ptrDesktop]{ ptrDesktop = getDesktop();} );
  const std::string* ptrSession {nullptr};
  std::thread tSession ([&ptrSession] {ptrSession = getSessionType();});
  const std::string* ptrCpu {nullptr};
  std::thread tCpu ([&ptrCpu] {ptrCpu = getCpu();});
  const std::string* ptrCores {nullptr};
  std::thread tCores ([&ptrCores] {ptrCores = getCpuCores();});
  tRelease.join();
  std::cout << "OS: " << *ptrRelease << " nya~ \n";
  tKernel.join();
  std::cout << "Kernel: " << *ptrKernel << " nya~ \n";
  tDesktop.join();
  tSession.join();
  std::cout << "DE: " << *ptrDesktop << " (" << *ptrSession << ")" << " nya~\n";
  tCpu.join();
  tCores.join();
  std::cout << "CPU: " << *ptrCpu << " (" << *ptrCores <<  ')' <<" nya~ \n";
  return 0;
}
