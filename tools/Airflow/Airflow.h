/*********************************************************************************************************
* Airflow.h
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef AIRFLOW_H
#define AIRFLOW_H
#include <string>

struct AirflowStructure{
    int mode;/// msi or msu or cab
    std::wstring rawfile;
    std::wstring outdir;
};


///Asynchronous report Message Id
extern int WM_ASYN_REPORT_MSG;


#endif

