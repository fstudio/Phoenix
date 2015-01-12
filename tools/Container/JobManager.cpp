#include "Precompiled.h"
#include "ContainerAPI.h"
#include <string>
#include "JobManager.hpp"

JobManager::JobManager() : jobhandle(nullptr) {}

JobManager::~JobManager() {
  /////Clean Resource
  if (jobhandle != nullptr)
    CloseHandle(jobhandle);
}
bool JobManager::JobDestory() {
  // kill job
  jobhandle = nullptr;
  return true;
}
bool JobManager::JobInitialize() {
  if (this->jobNamed.empty())
    return false;
  return true;
}
bool JobManager::JobSetting() {
  if (jobhandle == nullptr)
    return false;
  return true;
}
