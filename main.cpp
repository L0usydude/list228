#include "list.h"
#include <iostream>
using namespace std;
int main()
{
	try
	{
		node<int>* nodetest = new node<int>(5);
		nodetest->next = new node<int>(7);
		nodetest->next->before = nodetest;
		List<int> bdfy;
		List<int> bdfytest(nodetest, 2);
		ItteratorL<int> test228 = bdfytest.begin();
		cout << *test228;

	}
	catch (const char* error)
	{
		cout << error;
	}

}