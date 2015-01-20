#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "nscore.h"
#include "nsUniversalDetector.h"
class PhoenixUniversalDetector : public nsUniversalDetector
{
protected:
    std::string m_charset;

public:
    PhoenixUniversalDetector()
    : nsUniversalDetector()
    {
        m_charset = "ascii/unknown";
    }

    virtual ~PhoenixUniversalDetector()
    {}

    virtual void Report(const char* charset)
    {
        m_charset = charset;
    }

    virtual void Reset()
    {
        nsUniversalDetector::Reset();
        m_charset = "";
    }

    std::string GetCharset()
    {
        return m_charset;
    }
};


std::string GetCharSetString(std::string data)
{
    ///
    if(data.empty())
        return "Faild";
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),data.length())!=NS_OK)
    {
        delete Phdet;
        return "Faild";
    }
    Phdet->DataEnd();
    std::string charset=Phdet->GetCharset();
    delete Phdet;
    return charset;
}

int main(int argc,char **argv)
{ 
  if(argc<2)
    return 1;
   FILE *fp=nullptr;
   if((fp=fopen(argv[1],"r"))==nullptr)
     return 2;
   char buffer[65536]={0};
   if(fread(buffer,1,65536,fp)<=0)
     {
       fclose(fp);
       return 3;
     }
   std::string s=std::string(buffer);
   std::cout<<"Charset Is:"<<GetCharSetString(s)<<std::endl;  
   return 0;
}
