/*********************************************************************************************************
* ContainerServiceHub.hpp
* Note: Phoenix Container Service Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef CONTAINER_SERVICE_HUB_HPP
#define CONTAINER_SERVICE_HUB_HPP
#include <unordered_map>

struct Parameters;
class ContainerService{
private:
    Parameters m_param;
    bool Manager(unsigned id);
public:
    ContainerService(Parameters &param);
    ~ContainerService();
    bool Execute();
    void Destory();
    void ActiveSemaphore();
};

#endif

