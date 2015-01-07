
#include <functional>

struct DoExchangeDataTags{
	std::function<int(int Arg,wchar_t *param)> Task;
	const wchar_t *param;
}DoExchangeDataTask;


class DoExchangeData{
	public:
	DoExchangeData();
	private:
	std::function<bool(int)> fun;
};