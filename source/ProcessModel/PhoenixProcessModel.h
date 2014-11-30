#ifndef PHOENIXPROCESSMODEL_H
#define PHOENIXPROCESSMODEL_H
#include <string>


class PhoenixProcess
{
private:
  std::string route;
  unsigned int dwId;
public:
 enum PROCESS_TYPE
 {
	MASTER_PROCESS=0,
    TASK_PROCESS=1
 }
 bool PhoCreateProcess(bool IsManager);
 bool PhoTerminateProcess(bool sdSignal=true);//if not send signal, it will kill process not sava data.
}

class PhoenixMasterProcess
{
public:
	PhoenixMasterProcess();
}



#endif
