#include <string>
#include <vector>
#include <map>
#include <iostream>


template<class T>//T  wstring or string
class IniResolve{
public:
	struct ParamKV{
		T key;
		T value;
		ParamKV(T k, T v) :key(k), value(v)
		{
			////
		}
	};
	//typedef decltype(m_iniFile.c_str()) TC;
protected:
	T m_iniFile;
	std::map<T, std::vector<ParamKV> > treeMode;///Node as a map->
	typedef typename T::const_pointer Ptr;
public:
	IniResolve(T &inifile) :m_iniFile(inifile)
	{
	}
	IniResolve(){}
	T Get(Ptr str)
	{
		return T(str);
	}

};

class  IniResolveUnicode :public IniResolve<std::wstring>{
public:
	bool InsertKeyV()
	{
		std::wcout<<this->Get(L"typename T::const_pointer")<<std::endl;
		return true;
	}
};

int main()
{
	IniResolveUnicode iru;
	iru.InsertKeyV();
	return 0;
}
