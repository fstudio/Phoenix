/*********************************************************************************************************
* CMark.cc
* Note: Phoenix Editor Markdown Support
* Date: @2015.06
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "cmark_version.h"
#include "cmark_export.h"
#include "cmark.h"
#include <string>

int MarkdownToHtml(std::string &iMark,std::string &oHtml)
{
    auto p=cmark_markdown_to_html(iMark.c_str(),iMark.size(),CMARK_OPT_DEFAULT);
    oHtml=p;
    free(p);
    return 0;
}