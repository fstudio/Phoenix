///
///


#ifndef PHOENIX_IMULTILANGUAGE_H
#define PHOENIX_IMULTILANGUAGE_H

class MultiLangaugeDeter;
class PhoenixMlang{
private:
    std::wstring wcharset;
    std::string charset;
    MultiLangaugeDeter *deter;
public:
    PhoenixMlang();
    ~PhoenixMlang();
};

#endif
