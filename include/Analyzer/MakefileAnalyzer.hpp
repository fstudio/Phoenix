

class MakefileAnalyzer{
public:
    MakefileAnalyzer(){}
};

///NMake or New NMake analyzer
class NMakeAnalyzer:public MakefileAnalyzer{
public:
    NMakeAnalyzer();
};

///GNU like make analyzer
class GMakeAnalyzer:public MakefileAnalyzer{
public:
    GMakeAnalyzer();
};
