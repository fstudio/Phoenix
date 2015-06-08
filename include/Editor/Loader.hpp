/*********************************************************************************************************
* Loader.hpp
* Note: Phoenix Editor Loader
* Date: 2015.05.03
* Author: Force  Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_EDITOR_LOADER_HPP
#define PHOENIX_EDITOR_LOADER_HPP
#include <string>

class EditorLoader{
private:
    wchar_t *mPtr;
    bool isModify;////When is Modify close
    bool rwStatus;
    std::wstring mfile;
public:
    EditorLoader(const std::wstring &filePath);
    EditorLoader(const wchar_t *filePath);
    ~EditorLoader();
    wchar_t *BaseAddress(){
        return this->mPtr;
    }
    bool Close();
    bool Open();
    bool Save(const wchar_t *other=nullptr);//when other =nullptr not save as.
};

#endif
