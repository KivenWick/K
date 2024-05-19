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
		headNode->next = nullptr; // ѭ������ͷ�ڵ�ָ������
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
		node<T>* newNode = createNode(tempdata); // �����½ڵ�

		node<T>* tail = list;
		while (tail->next != nullptr) { // �ҵ����һ���ڵ�
			tail = tail->next;
		}
		tail->next = newNode; // ���½ڵ���뵽���һ���ڵ�֮��
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

	//ɾ��
	void deleteNode(node<T>*& list, T name)
	{
		if (list == nullptr) {
			return; // ����Ϊ�գ�ֱ�ӷ���
		}

		node<T>* current = list;



			// �ҵ�Ҫɾ���Ľڵ�
			while (current->data != name && current->next != nullptr) {
				current = current->next;
			}
			// ����ҵ���Ҫɾ���Ľڵ�
			if (current->data == name && current->next!=nullptr)
			{
			
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
			}
				else 
			    {
					// ���Ҫɾ������β���ڵ�

				    current->prev->next = nullptr;
					delete current;
				}

	}


	//�޸�
	void modifyNode(node<T>* list, T name, T newData) 
	{
		node<T>* current = list;

			// �����������Ҫ�޸ĵĽڵ�
			while (current->next != nullptr) {
				if (current->data == name) {
					current->data = newData; // �޸Ľڵ�����
					break;
				}
				current = current->next;
	
			}

	}


	//����
	void findNode(node<T>* list, T name) 
	{
		node<T>* current = list;

		// �����������Ŀ��ڵ�
		
			while (current->next != nullptr)             
			{
				if (current->data == name)
				{
					string key;
					cout << "�ҵ�Ŀ��ڵ�" << endl;
					cout << current->data << endl;
					while (current->next != nullptr && current->prev != nullptr)
					{
						cout << "�Ƿ���Ҫ�鿴������������(y / n)" << endl;
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

		cout << "δ�ҵ�";// δ�ҵ�Ŀ��ڵ�
	}

	void clearList(node<T>*& list) {
		if (list == nullptr || list->next == list) {
			return; // ����Ϊ�ջ���ֻ��ͷ�ڵ㣬ֱ�ӷ���
		}

		node<T>* current = list->next;
		while (current != nullptr) { // ��������
			node<T>* temp = current;
			current = current->next;
			delete temp; // ɾ����ǰ�ڵ�
			current->prev = nullptr;
		}
	}

	//�ƶ���������������ָ����� 
	node<T>* move(node<T>*& ptr)
	{
		node<T>* newptr = nullptr;
		string direction;
		cout << "��ѡ����ǰ�������" << endl;
		cin >> direction;
		if (direction == "ǰ��")
		{
			newptr = ptr->next;
		}
		else if(direction == "����")
		{
			newptr = ptr->prev;
		}

		return newptr;
	}


	node<T>* List = creadhead(); // ͷָ��


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
		cout << "����" << endl;
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
		cout << "������ɾ��������" << endl;
		T temp;
		cin >> temp;
		listb.deleteNode(listb.List, temp);
		break;
	}
	case 4:
	{
		listb.print(listb.List);
		cout << "�������޸�Ŀ�������" << endl;
		T tempn;
		cin >> tempn;
		cout << "�������޸ĵ�������" << endl;
		T templ;
		cin >> templ;
		listb.modifyNode(listb.List, tempn, templ);
		break;
	}
	case 5:
	{
		listb.print(listb.List);
		cout << "���������Ŀ�������" << endl;
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
	cout << "1����" << endl;
	cout << "2չʾ" << endl;
	cout << "3ɾ��" << endl;
	cout << "4�޸�" << endl;
	cout << "5����" << endl;
	cout << "0����" << endl;
}


void menu1()
{
	cout << "��ѡ��Ҫ����������" << endl;
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
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}


///////////////////////////////////////////////////////////////
// ջ��ʵ��
//������tm��β��βɾ����˫������ɾ����ǰһ���ڵ��next����ջ�������ˣ����ջβ��ջ��ָ��



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

	node<T>* creadheadZ()//����ջβ��û���½ڵ��ʱջβ��ջ����ָ����
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

	//β�巨��ջ
	void addNodeByEndZ(T tempdata)
	{
		node<T>* newNode = createNodeZ(tempdata); // �����½ڵ�
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

	//ջ��ɾ����ջ
	void deleteNodeZ()
	{
		headZ = headZ->prev;
		delete headZ->next;
		headZ->next = nullptr;
	}


	void clearListZ(node<T>*& list) {
		if (list == nullptr || list->next == list) {
			return; // ����Ϊ�ջ���ֻ��ͷ�ڵ㣬ֱ�ӷ���
		}

		node<T>* current = list->next;
		while (current != nullptr) { // ��������
			node<T>* temp = current;
			current = current->next;
			delete temp; // ɾ����ǰ�ڵ�
		}
	}

	
	node<T>* ListZ = creadheadZ(); // ͷָ��


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
//���е�ʵ�֣��Ȳ�����


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

	//β�巨�����
	void addNodeByEndD(T tempdata)
	{
		node<T>* newNode = createNodeD(tempdata); // �����½ڵ�
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

	//���п�ͷɾ���ӳ�
	void deleteNodeD()
	{
		headD = headD->next;
		delete headD->prev;
	}



	

	void clearListD(node<T>*& list) {
		if (list == nullptr || list->next == nullptr) {
			return; // ����Ϊ�ջ���ֻ��һ���ڵ㣬ֱ�ӷ���
		}

		node<T>* current = list->next;
		while (current != nullptr) { // ��������
			node<T>* temp = current;
			current = current->next;
			delete temp; // ɾ����ǰ�ڵ�
		}

		list->next = nullptr; // ��ͷ�ڵ����һ���ڵ�ָ�� nullptr
	}


	node<T>* ListD = creadheadD(); // ͷָ��


};


//�������


template <typename T>
class Arrayqueue {
private:
	int capacity;//����
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
	cout << "1����" << endl;
	cout << "2չʾ" << endl;
	cout << "3ɾ��" << endl;
	cout << "0����" << endl;
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
		cout << "����" << endl;
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
		cout << "����" << endl;
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

	cout << "1����" << endl;
	cout << "2�ܳ�" << endl;
	cout << "3ɾ��" << endl;
	cout << "4չʾ" << endl;
	cout << "5����" << endl;
	cout << "0����" << endl;

}



template<typename T>
void jiaohuarrayque(Arrayqueue<T>& que) {
	int key = 0;
		cin >> key;

		switch (key) {
		case 1: {
			cout << "������Ҫ����е�Ԫ�أ�" << endl;
			T temp;
			cin >> temp;
			que.push(temp);
			cout << "�ɹ������" << endl;
			break;
		}

		case 2: {
			int a =  que.size();
			cout << "���д�СΪ��" << a << endl;
			break;
		}

		case 3: {
			try {
				que.pop();
				cout << "�ɹ�������" << endl;
			}
			catch (const std::out_of_range& e) {
				cout << "����Ϊ�գ��޷�������" << endl;
			}
			break;
		}

		case 4: {
			cout << "������Ԫ��Ϊ��" << endl;
			que.printque();
			break;
		}

		case 5: {
			int a = que.allcapacity();
			cout << "��������Ϊ��" << a << endl;
			break;
		}


		case 0: {
			return;
		}

		default: {
			cout << "��Ч��ѡ�������ѡ��" << endl;
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
		cout << "������Ҫ��ջ��Ԫ�أ�" << endl;
		T temp;
		cin >> temp;
		stack.push(temp);
		cout << "�ɹ���ջ" << endl;
		break;
	}

	case 2: {
		int a = stack.size();
		cout << "ջ��СΪ��" << a << endl;
		break;
	}

	case 3: {
		try {
			stack.pop();
			cout << "�ɹ���ջ" << endl;
		}
		catch (const std::out_of_range& e) {
			cout << "ջΪ�գ��޷���ջ" << endl;
		}
		break;
	}

	case 4: {
		cout << "ջ��Ԫ��Ϊ��" << endl;
		stack.printStack();
		break;
	}

	case 5: {
		int a = stack.allcapacity();
		cout << "ջ����Ϊ��" << a << endl;
		break;
	}

	case 0: {
		return;
	}

	default: {
		cout << "��Ч��ѡ�������ѡ��" << endl;
		break;
	}

	}
}







template<typename T>
void mains() {

	DynamicArrayStack<T> stack;
	// ʹ�÷��Ͷ�̬����ջ
	while (1)
	{
		menus();
		jiaohuarray(stack);
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}

template<typename T>
void mainq() {

	Arrayqueue<T> que;
	// ʹ�÷��Ͷ�̬�������
	while (1)
	{
		menus();
		jiaohuarrayque(que);
		system("pause");//��ֹ����
		system("cls");//���� 

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
		system("pause");//��ֹ����
		system("cls");//���� 

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
		system("pause");//��ֹ����
		system("cls");//���� 

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
		cout << "δ֪ѡ��";
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
		cout << "δ֪ѡ��";
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
		cout << "δ֪ѡ��";
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
		cout << "δ֪ѡ��";
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
		cout << "δ֪ѡ��";
		break;

	}

}





void menuchioce()
{
	cout << "1˫������" << endl;
	cout << "2ջ" << endl;
	cout << "3����" << endl;
	cout << "4����ջ" << endl;
	cout << "5�������" << endl;
}



void mainZ()
{
	while (1)
	{
		menu1();
		jiaohuZ();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}

void mainA()
{
	while (1)
	{
		menu1();
		jiaohulist();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}


void mainD()
{
	while (1)
	{
		menu1();
		jiaohuD();
		system("pause");//��ֹ����
		system("cls");//���� 

	}
	 
	system("pause");

}

void mainS()
{
	while (1)
	{
		menu1();
		jiaohuS();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}

void mainQ()
{
	while (1)
	{
		menu1();
		jiaohuQ();
		system("pause");//��ֹ����
		system("cls");//���� 

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
		cout << "δ֪ѡ��";
		break;

	}

}



void main()
{
	while (1)
	{
		menuchioce();
		jiaohuall();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause"); 

}


