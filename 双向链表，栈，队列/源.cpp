#include <iostream>
using namespace std;

//////////////////////////
void main();
void mainz();
void menulistZ();


////////////////////


template <typename T>
class node
{
public:
	T data;
	node* next;
	node* prev;
};


template <typename T>
class Linkedlist
{
public:



	Linkedlist()
	{

	}

	~Linkedlist()
	{
		
	}

	node<T>* creadhead()
	{
		node<T>* headNode = new node<T>();
		headNode->next = nullptr; // 循环链表头节点指向自身
		headNode->prev = nullptr;
		return headNode;

	}

	node<T>* createNode(T data)
	{
		node<T>* newNode = new node<T>();
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		return newNode;
	}

	void addNodeByEnd(node<T>*& list, T tempdata) {
		node<T>* newNode = createNode(tempdata); // 创建新节点

		node<T>* tail = list;
		while (tail->next != nullptr) { // 找到最后一个节点
			tail = tail->next;
		}
		tail->next = newNode; // 将新节点插入到最后一个节点之后
		newNode->prev = tail;
	}


	void print(node<T>* headNode) {
		node<T>* current = headNode->next;
		while (current != nullptr) {
			cout << current->data << " " << endl;
			current = current->next;
		}
		cout << endl;
	}

	//删除
	void deleteNode(node<T>*& list, T name)
	{
		if (list == nullptr) {
			return; // 链表为空，直接返回
		}

		node<T>* current = list;



			// 找到要删除的节点
			while (current->data != name && current->next != nullptr) {
				current = current->next;
			}
			// 如果找到了要删除的节点
			if (current->data == name && current->next!=nullptr)
			{
			
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
			}
				else 
			    {
					// 如果要删除的是尾部节点

				    current->prev->next = nullptr;
					delete current;
				}

	}


	//修改
	void modifyNode(node<T>* list, T name, T newData) 
	{
		node<T>* current = list;

			// 遍历链表查找要修改的节点
			while (current->next != nullptr) {
				if (current->data == name) {
					current->data = newData; // 修改节点数据
					break;
				}
				current = current->next;
	
			}

	}


	//查找
	void findNode(node<T>* list, T name) 
	{
		node<T>* current = list;

		// 遍历链表查找目标节点
		
			while (current->next != nullptr)             
			{
				if (current->data == name)
				{
					string key;
					cout << "找到目标节点" << endl;
					cout << current->data << endl;
					while (current->next != nullptr && current->prev != nullptr)
					{
						cout << "是否需要查看左右两边内容(y / n)" << endl;
						cin >> key;
						if (key == "y") {
							node<T>* newp = move(current);
							cout << newp->data;
							current = newp;
						}
						if (key == "n") {
							break;
						}

					}
				}
				current = current->next;
			}

		cout << "未找到";// 未找到目标节点
	}

	void clearList(node<T>*& list) {
		if (list == nullptr || list->next == list) {
			return; // 链表为空或者只有头节点，直接返回
		}

		node<T>* current = list->next;
		while (current != nullptr) { // 遍历链表
			node<T>* temp = current;
			current = current->next;
			delete temp; // 删除当前节点
			current->prev = nullptr;
		}
	}

	//移动函数，传进来个指针就行 
	node<T>* move(node<T>*& ptr)
	{
		node<T>* newptr = nullptr;
		string direction;
		cout << "请选择方向前进或后退" << endl;
		cin >> direction;
		if (direction == "前进")
		{
			newptr = ptr->next;
		}
		else if(direction == "后退")
		{
			newptr = ptr->prev;
		}

		return newptr;
	}


	node<T>* List = creadhead(); // 头指针


};


template<typename T>
void jiaohubase()
{

	static Linkedlist<T> listb;
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "输入" << endl;
		T temp;
		cin >> temp;
		listb.addNodeByEnd(listb.List, temp);
		break;
	}

	case 2:
	{
		listb.print(listb.List);
		break;
	}

	case 3:
	{
		listb.print(listb.List);
		cout << "请输入删除的数据" << endl;
		T temp;
		cin >> temp;
		listb.deleteNode(listb.List, temp);
		break;
	}
	case 4:
	{
		listb.print(listb.List);
		cout << "请输入修改目标的数据" << endl;
		T tempn;
		cin >> tempn;
		cout << "请输入修改的新数据" << endl;
		T templ;
		cin >> templ;
		listb.modifyNode(listb.List, tempn, templ);
		break;
	}
	case 5:
	{
		listb.print(listb.List);
		cout << "请输入查找目标的名字" << endl;
		T temp;
		cin >> temp;
		listb.findNode(listb.List, temp);
		break;
	}
	case 0:
		listb.clearList(listb.List);
		system("cls");
		main();
	default:
		system("cls");
		break;

	}

}



void menulist()
{
	cout << "1增加" << endl;
	cout << "2展示" << endl;
	cout << "3删除" << endl;
	cout << "4修改" << endl;
	cout << "5查找" << endl;
	cout << "0返回" << endl;
}


void menu1()
{
	cout << "请选择要操作的类型" << endl;
	cout << "1,int" << endl;
	cout << "2,float" << endl;
}


template<typename T>
void maina()
{
	while (1)
	{
		menulist();
		jiaohubase<T>();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}


///////////////////////////////////////////////////////////////
// 栈的实现
//不就是tm的尾插尾删吗，用双向链表，删除后将前一个节点的next赋给栈顶就是了，设计栈尾与栈顶指针



template <typename T>
class LinkedlistZ
{
public:
	node<T>* headZ = nullptr;
	node<T>* endZ = nullptr;



	LinkedlistZ()
	{

	}

	~LinkedlistZ()
	{

	}

	node<T>* creadheadZ()//创建栈尾，没有新节点的时栈尾与栈顶都指向它
	{
		node<T>* headNode = new node<T>();
		headNode->next = nullptr; 
		headNode->prev = nullptr;
		headZ = headNode;
		endZ = headNode;
		return headNode;

	}

	node<T>* createNodeZ(T data)
	{
		node<T>* newNode = new node<T>();
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		return newNode;
	}

	//尾插法入栈
	void addNodeByEndZ(T tempdata)
	{
		node<T>* newNode = createNodeZ(tempdata); // 创建新节点
		newNode->prev = headZ;
		headZ->next = newNode;
		headZ = headZ->next;
	}


	void printZ(node<T>* headNode) {
		node<T>* current = headNode->next;
		while (current != nullptr) {
			cout << current->data << " " << endl;
			current = current->next;
		}
		cout << endl;
	}

	//栈顶删除出栈
	void deleteNodeZ()
	{
		headZ = headZ->prev;
		delete headZ->next;
		headZ->next = nullptr;
	}


	void clearListZ(node<T>*& list) {
		if (list == nullptr || list->next == list) {
			return; // 链表为空或者只有头节点，直接返回
		}

		node<T>* current = list->next;
		while (current != nullptr) { // 遍历链表
			node<T>* temp = current;
			current = current->next;
			delete temp; // 删除当前节点
		}
	}

	
	node<T>* ListZ = creadheadZ(); // 头指针


};

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

	int allcapacity() const {
		return (capacity);
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

};



//////////////////////////////////////////////////
//队列的实现，先插先走


template <typename T>
class LinkedlistD
{
public:
	node<T>* headD = nullptr;
	node<T>* endD = nullptr;



	LinkedlistD()
	{

	}

	~LinkedlistD()
	{

	}

	node<T>* creadheadD()
	{
		node<T>* headNode = new node<T>();
		headNode->next = nullptr;
		headNode->prev = nullptr;
		headD = headNode;
		endD = headNode;
		return headNode;

	}

	node<T>* createNodeD(T data)
	{
		node<T>* newNode = new node<T>();
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		return newNode;
	}

	//尾插法入队列
	void addNodeByEndD(T tempdata)
	{
		node<T>* newNode = createNodeD(tempdata); // 创建新节点
		newNode->prev = endD;
		endD->next = newNode;
		endD = endD->next;
	}


	void printD(node<T>* headNode) {
		node<T>* current = headD;
		while (current != nullptr) {
			cout << current->data << " " << endl;
			current = current->next;
		}
		cout << endl;
	}

	//队列开头删除队出
	void deleteNodeD()
	{
		headD = headD->next;
		delete headD->prev;
	}



	

	void clearListD(node<T>*& list) {
		if (list == nullptr || list->next == nullptr) {
			return; // 链表为空或者只有一个节点，直接返回
		}

		node<T>* current = list->next;
		while (current != nullptr) { // 遍历链表
			node<T>* temp = current;
			current = current->next;
			delete temp; // 删除当前节点
		}

		list->next = nullptr; // 将头节点的下一个节点指向 nullptr
	}


	node<T>* ListD = creadheadD(); // 头指针


};


//数组队列


template <typename T>
class Arrayqueue {
private:
	int capacity;//容量
	int rear;
	T* array;

public:
	Arrayqueue(int initialCapacity = 10) : capacity(initialCapacity), rear(-1) {
		array = new T[capacity];
	}

	~Arrayqueue() {
		delete[] array;
	}

	bool isFull() const {
		return (rear == capacity - 1);
	}

	int size() const {
		return (rear + 1);
	}

	int allcapacity() const {
		return (capacity);
	}

	void resize(int newCapacity) {
		T* newArray = new T[newCapacity];
		for (int i = 0; i <= rear; i++) {
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
		array[++rear] = item;
	}

	T pop() {
		if (size() == 0) {
			throw std::out_of_range("Queue is empty");
		}

		T poppedItem = array[0];

		for (int i = 0; i < rear; ++i) {
			array[i] = array[i + 1];
		}

		rear--;

		return poppedItem;
	}

	void printque() {
		for (int i = 0; i <= rear; ++i) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

};





void menulistZ()
{
	cout << "1增加" << endl;
	cout << "2展示" << endl;
	cout << "3删除" << endl;
	cout << "0返回" << endl;
}





template<typename T>
void jiaohuZ()
{

	static LinkedlistZ<T> listZ;
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "输入" << endl;
		T temp;
		cin >> temp;
		listZ.addNodeByEndZ(temp);
		break;
	}

	case 2:
	{
		listZ.printZ(listZ.ListZ);
		break;
	}

	case 3:
	{
		listZ.printZ(listZ.ListZ);
		listZ.deleteNodeZ();
		break;
	}
	case 0:
		listZ.clearListZ(listZ.ListZ);
		system("cls");
		main();
	default:
		system("cls");
		break;

	}

}


template<typename T>
void jiaohuD()
{

	static LinkedlistD<T> listD;
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "输入" << endl;
		T temp;
		cin >> temp;
		listD.addNodeByEndD(temp);
		break;
	}

	case 2:
	{
		listD.printD(listD.ListD);
		break;
	}

	case 3:
	{
		listD.printD(listD.ListD);
		listD.deleteNodeD();
		break;
	}
	case 0:
		listD.clearListD(listD.ListD);
		system("cls");
		main();
	default:
		system("cls");
		break;

	}

}


void menus()
{

	cout << "1增加" << endl;
	cout << "2总长" << endl;
	cout << "3删除" << endl;
	cout << "4展示" << endl;
	cout << "5容量" << endl;
	cout << "0返回" << endl;

}



template<typename T>
void jiaohuarrayque(Arrayqueue<T>& que) {
	int key = 0;
		cin >> key;

		switch (key) {
		case 1: {
			cout << "请输入要入队列的元素：" << endl;
			T temp;
			cin >> temp;
			que.push(temp);
			cout << "成功入队列" << endl;
			break;
		}

		case 2: {
			int a =  que.size();
			cout << "队列大小为：" << a << endl;
			break;
		}

		case 3: {
			try {
				que.pop();
				cout << "成功出队列" << endl;
			}
			catch (const std::out_of_range& e) {
				cout << "队列为空，无法出队列" << endl;
			}
			break;
		}

		case 4: {
			cout << "队列中元素为：" << endl;
			que.printque();
			break;
		}

		case 5: {
			int a = que.allcapacity();
			cout << "队列容量为：" << a << endl;
			break;
		}


		case 0: {
			return;
		}

		default: {
			cout << "无效的选项，请重新选择" << endl;
			break;
		}
		
	}
}




template<typename T>
void jiaohuarray(DynamicArrayStack<T>& stack) {
	int key = 0;
	cin >> key;

	switch (key) {
	case 1: {
		cout << "请输入要入栈的元素：" << endl;
		T temp;
		cin >> temp;
		stack.push(temp);
		cout << "成功入栈" << endl;
		break;
	}

	case 2: {
		int a = stack.size();
		cout << "栈大小为：" << a << endl;
		break;
	}

	case 3: {
		try {
			stack.pop();
			cout << "成功出栈" << endl;
		}
		catch (const std::out_of_range& e) {
			cout << "栈为空，无法出栈" << endl;
		}
		break;
	}

	case 4: {
		cout << "栈中元素为：" << endl;
		stack.printStack();
		break;
	}

	case 5: {
		int a = stack.allcapacity();
		cout << "栈容量为：" << a << endl;
		break;
	}

	case 0: {
		return;
	}

	default: {
		cout << "无效的选项，请重新选择" << endl;
		break;
	}

	}
}







template<typename T>
void mains() {

	DynamicArrayStack<T> stack;
	// 使用泛型动态数组栈
	while (1)
	{
		menus();
		jiaohuarray(stack);
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}

template<typename T>
void mainq() {

	Arrayqueue<T> que;
	// 使用泛型动态数组队列
	while (1)
	{
		menus();
		jiaohuarrayque(que);
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}






template<typename T>
void mainz()
{
	while (1)
	{
		menulistZ();
		jiaohuZ<T>();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}


template<typename T>
void maind()
{
	while (1)
	{
		menulistZ();
		jiaohuD<T>();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}


void jiaohulist()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		maina<int>();
		break;
	case 2:
		maina<float>();
		break;
	default:
		cout << "未知选项";
		break;

	}

}


void jiaohuZ()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		mainz<int>();
		break;
	case 2:
		mainz<float>();
		break;
	default:
		cout << "未知选项";
		break;

	}

}


void jiaohuD()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		maind<int>();
		break;
	case 2:
		maind<float>();
		break;
	default:
		cout << "未知选项";
		break;

	}

}

void jiaohuS()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		mains<int>();
		break;
	case 2:
		mains<float>();
		break;
	default:
		cout << "未知选项";
		break;

	}

}


void jiaohuQ()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		mainq<int>();
		break;
	case 2:
		mainq<float>();
		break;
	default:
		cout << "未知选项";
		break;

	}

}





void menuchioce()
{
	cout << "1双向链表" << endl;
	cout << "2栈" << endl;
	cout << "3队列" << endl;
	cout << "4数组栈" << endl;
	cout << "5数组队列" << endl;
}



void mainZ()
{
	while (1)
	{
		menu1();
		jiaohuZ();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}

void mainA()
{
	while (1)
	{
		menu1();
		jiaohulist();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}


void mainD()
{
	while (1)
	{
		menu1();
		jiaohuD();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}
	 
	system("pause");

}

void mainS()
{
	while (1)
	{
		menu1();
		jiaohuS();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}

void mainQ()
{
	while (1)
	{
		menu1();
		jiaohuQ();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}








void jiaohuall()
{

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		mainA();
		break;
	case 2:
		mainZ();
		break;
	case 3:
		mainD();
		break;
	case 4:
		mainS();
		break;
	case 5:
		mainQ();
		break;
	default:
		cout << "未知选项";
		break;

	}

}



void main()
{
	while (1)
	{
		menuchioce();
		jiaohuall();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause"); 

}


