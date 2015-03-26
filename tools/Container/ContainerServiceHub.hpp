/*********************************************************************************************************
* ContainerServiceHub.hpp
* Note: Phoenix Container Service Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef CONTAINER_SERVICE_HUB_HPP
#define CONTAINER_SERVICE_HUB_HPP
#include <map>

class ContainerService{
private:
    std::map<unsigned, unsigned> taskMap;
    bool Manager(unsigned id);
public:
    ContainerService();
    bool Execute();
    void Destory();
};

#endif

