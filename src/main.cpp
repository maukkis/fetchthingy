#include <iostream>
#include <iterator>
#include <pstreams/pstream.h>
#include <string>
#include <thread>


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

std::string* getSessionType(){
  redi::ipstream proc("echo $XDG_SESSION_TYPE");
  static std::string session(ibuf_it(proc.rdbuf()), ibuf_it());
  session.erase(std::remove(session.begin() , session.end(), '\n'), session.end()); 
  return &session;
}


int main()
{
  const std::string* ptrKernel {nullptr};
  std::thread t1([&ptrKernel] {ptrKernel = getKernel();});
  const std::string* ptrRelease {nullptr};
  std::thread t2 ([&ptrRelease] {ptrRelease = getOs();});
  const std::string* ptrDesktop{nullptr};
  std::thread t3([&ptrDesktop]{ ptrDesktop = getDesktop();} );
  const std::string* ptrSession {nullptr};
  std::thread t4 ([&ptrSession] {ptrSession = getSessionType();});
  t2.join();
  std::cout << "OS: " << *ptrRelease << " nya~ \n";
  t1.join();
  std::cout << "Kernel: " << *ptrKernel << " nya~ \n";
  t3.join();
  t4.join();
  std::cout << "DE: " << *ptrDesktop << " (" << *ptrSession << ")" << " nya~\n";
  return 0;
}
