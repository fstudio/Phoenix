#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct  Node{
	int num;
	string str;
	Node(int x,string s):num(x),str(s)
	{
		
	}
};


int main()
{
	std::cout<<"Range-based for loop"<<std::endl;
	vector<Node> vn;
	for(auto i=0;i<20;i++)
	{
		std::string s=std::to_string(i);
		vn.push_back(Node(i,s));
	}
	for(auto &iter:vn)
	{
		std::cout<<"Number: "<<iter.num<<" String: "<<iter.str<<std::endl;
	}
	return 0;
}
