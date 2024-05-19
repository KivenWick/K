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
			std::cout << "δ�ҵ�Ԫ��" << std::endl;
		}
	}
};


void menus()
{

	cout << "1����" << endl;
	cout << "2�ܳ�" << endl;
	cout << "3ɾ��" << endl;
	cout << "4�޸�" << endl;
	cout << "5����" << endl;
	cout << "6չʾ" << endl;
	cout << "0����" << endl;

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
		std::cout << "������Ҫ��ջ��Ԫ�أ�" << std::endl;
		T temp;
		std::cin >> temp;
		stack.push(temp);
		std::cout << "�ɹ���ջ" << std::endl;
		break;
	}

	case 2:
	{
		int a = stack.size();
		std::cout << "ջ��СΪ��" << a << std::endl;
		break;
	}

	case 3:
	{
		stack.pop();
		std::cout << "�ɹ���ջ" << std::endl;
		break;
	}
	case 4:
	{
		T value, newvalue;
		std::cout << "������Ŀ��Ԫ�غ��޸ĵ���Ԫ�أ�";
		std::cin >> value >> newvalue;
		stack.change(value, newvalue);
		std::cout << "�޸ĳɹ�" << std::endl;
		break;
	}
	case 5:
	{
		T value;
		std::cout << "������Ҫ���ҵ�Ԫ�أ�" << std::endl;
		std::cin >> value;
		int index = stack.findElement(value);
		if (index != -1) {
			std::cout << "Ԫ���ҵ���λ��Ϊ��" << index << std::endl;
		}
		else {
			std::cout << "δ�ҵ���Ԫ��" << std::endl;
		}
		break;
	}
	case 6:
	{
		std::cout << "ջ��Ԫ��Ϊ��" << std::endl;
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
	// ʹ�÷��Ͷ�̬����ջ
	while (1)
	{
		menus();
		jiaohuarray<int>();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}
































