/*********************************************************************************************************
* UIWindow.cpp
* Note: ResizeUITab.cpp
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENXI_RESIZEUITAB_HPP
#define PHOENXI_RESIZEUITAB_HPP

class ResizeUITab{
private:
    RECT m_place;
public:
    ResizeUITab();
    bool Create();
    LRESULT Initialize();
    LRESULT Resize();
    LRESULT Move();
    LRESULT Draw();
    LRESULT Close();
    LRESULT Click();
};

#endif
