/*********************************************************************************************************
* ContainerServiceHub.hpp
* Note: Phoenix Container Service Manager
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
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

