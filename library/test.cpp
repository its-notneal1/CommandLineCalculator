#include <iostream>
#include "LQueue.h"
#include "LStack.h"
#include <cstdlib>
#include <string>
void func(LQueue<int> &list) {
	LQueue<int> l2(list);
	l2.displayAll();
}

int main() {
	LQueue<int> list;
	for(int i = 1; i < 6; i++) list.addRear(i);
	func(list);

	LQueue<std::string> list2;
	list2.addRear("Hello");
	list2.addRear("World");
	list2.displayAll();

	LStack<std::string> stack1;
	stack1.push("Hello");
	stack1.push("World");
	std::cout << stack1.pop() << std::endl;
	
	return 0;
}
