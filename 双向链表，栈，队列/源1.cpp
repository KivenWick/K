#include <iostream>
using namespace std;


template <typename T>
class DynamicArrayStack {
private:
	int capacity;
	int top;
	T* array;

public:
	DynamicArrayStack(int initialCapacity = 10) : capacity(initialCapacity), top(-1) {
		array = new T[capacity];
	}

	~DynamicArrayStack() {
		delete[] array;
	}

	bool isFull() const {
		return (top == capacity - 1);
	}

	int size() const {
		return (top + 1);
	}

	void resize(int newCapacity) {
		T* newArray = new T[newCapacity];
		for (int i = 0; i <= top; i++) {
			newArray[i] = array[i];
		}
		capacity = newCapacity;
		delete[] array;
		array = newArray;
	}

	void push(const T& item) {
		if (isFull()) {
			resize(2 * capacity);
		}
		array[++top] = item;
	}

	T pop() {
		if (top < 0) {
			throw std::out_of_range("Stack is empty");
		}
		T item = array[top];
		top--;
		if (top > 0 && top == capacity / 4) {
			resize(capacity / 2);
		}
		return item;
	}

	void printStack() {
		for (int i = 0; i <= top; ++i) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

	int findElement(const T& value) const {
		for (int i = 0; i <= top; ++i) {
			if (array[i] == value) {
				return i;
			}
		}
		return -1;
	}

	void change(const T& value, const T& newValue) {
		int index = findElement(value);
		if (index != -1) {
			array[index] = newValue;
		}
		else {
			std::cout << "未找到元素" << std::endl;
		}
	}
};


void menus()
{

	cout << "1增加" << endl;
	cout << "2总长" << endl;
	cout << "3删除" << endl;
	cout << "4修改" << endl;
	cout << "5查找" << endl;
	cout << "6展示" << endl;
	cout << "0返回" << endl;

}


template<typename T>
void jiaohuarray()
{
	DynamicArrayStack<T> stack;
	int key = 0;


	std::cin >> key;

	switch (key)
	{
	case 1:
	{
		std::cout << "请输入要入栈的元素：" << std::endl;
		T temp;
		std::cin >> temp;
		stack.push(temp);
		std::cout << "成功入栈" << std::endl;
		break;
	}

	case 2:
	{
		int a = stack.size();
		std::cout << "栈大小为：" << a << std::endl;
		break;
	}

	case 3:
	{
		stack.pop();
		std::cout << "成功出栈" << std::endl;
		break;
	}
	case 4:
	{
		T value, newvalue;
		std::cout << "请输入目标元素和修改的新元素：";
		std::cin >> value >> newvalue;
		stack.change(value, newvalue);
		std::cout << "修改成功" << std::endl;
		break;
	}
	case 5:
	{
		T value;
		std::cout << "请输入要查找的元素：" << std::endl;
		std::cin >> value;
		int index = stack.findElement(value);
		if (index != -1) {
			std::cout << "元素找到，位置为：" << index << std::endl;
		}
		else {
			std::cout << "未找到该元素" << std::endl;
		}
		break;
	}
	case 6:
	{
		std::cout << "栈中元素为：" << std::endl;
		stack.printStack();
		break;
	}
	case 0:
		system("cls");
		jiaohuarray<T>();
	default:
		system("cls");
		break;
	}
}




void main() {
	// 使用泛型动态数组栈
	while (1)
	{
		menus();
		jiaohuarray<int>();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}
































