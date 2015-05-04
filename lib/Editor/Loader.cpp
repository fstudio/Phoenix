/*********************************************************************************************************
* Loader.cpp
* Note: Phoenix Editor Loader
* Data: 2015.05.03
* Author: Force  Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Editor/Loader.hpp>

/// IOExperimental
/// Load Big big file,
///
class IOExperimental{
public:
    IOExperimental()
    {
        /////
    }
};

EditorLoader::EditorLoader(const std::wstring &filePath):mfile(filePath)
{
    ///
}

EditorLoader::EditorLoader(const wchar_t *filePath):mfile(filePath)
{
    ///
}

bool EditorLoader::Close()
{
    if(isModify)
    {
        ////
    }
    return true;
}


bool EditorLoader::Open()
{
    ///GetFileAttribute
    return true;
}

bool EditorLoader::Save(const wchar_t *other)
{
    return true;
}
