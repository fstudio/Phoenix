#ifndef PHOENIX_JOBMANAGER_HPP
#define PHOENIX_JOBMANAGER_HPP

class JobManager {
private:
  std::wstring jobNamed;
  HANDLE jobhandle;

public:
  void SetJobName(const wchar_t *name) { this->jobNamed = name; }
  JobManager();
  bool JobDestory();
  bool JobInitialize();
  bool JobSetting();
  ~JobManager();
};

#endif
