////
#include "Precompiled.h"
#include <string>
#include <list>


class ContainerPool{
private:
    std::list<unsigned> ContainerId;
public:
    ContainerPool();
protected:
    bool CleanPool();
};

ContainerPool::ContainerPool()
{
    ///ContainerPool
}

bool ContainerPool::CleanPool()
{
    return false;
}
