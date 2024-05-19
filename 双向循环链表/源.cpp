#include <iostream>

using namespace std;

////////////////////////

void main();
void menu3();
void jiaohubase();



/////////////////////////



class Test1 {
private:
	string name;
	int num;
public:
	Test1(string name, int num) : name(name), num(num) {}

	static Test1 createFromName(const string& name) {
		return Test1(name, 0); // 假设第二个参数（如num）在这里不重要
	}

	Test1()
	{

	}

	void show() {
		cout << "Name: " << name << ", Num: " << num << endl;
	}

	string getname() const {
		return name;
	}

	void change(string name, int num)
	{
		this->name = name;
		this->num = num;
	}


	friend ostream& operator<<(ostream& os, const Test1& obj) {
		os << "Name: " << obj.name << ", Num: " << obj.num;
		return os;
	}

};






template <typename T>
class node
{
public:
	T data;
	node* next;
	node* prev;
	int counter;
};

template <typename T>
class Linkedlist
{
public:

	int size = 1;


	Linkedlist()
	{

	}

	~Linkedlist()
	{

	}

	node<T>*creadhead()
	{
		node<T>* headNode = new node<T>();
		headNode->next = headNode; // 循环链表头节点指向自身
		headNode->prev = headNode;
		headNode->counter = 0;
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
			while (tail->next != list) { // 找到最后一个节点
				tail = tail->next;
			}
			tail->next = newNode; // 将新节点插入到最后一个节点之后
			newNode->prev = tail;
			newNode->next = list; // 新节点的next指针指向头节点，形成循环
			list->prev = newNode; // 头节点的prev指针指向新节点，形成循环
			newNode->counter = newNode->prev->counter + 1;
			size = newNode->counter + 1;
	}


	void print(node<T>* headNode) {
		node<T>* current = headNode->next;
		while (current != headNode) {
			cout << current->data << " " << current->counter << endl;
			current = current->next;
			if (current == headNode) {
				break; // 如果当前节点又回到了头节点，则跳出循环
			}
		}
		cout << endl;
	}

	//删除
	void deleteNode(node<T>*& list, T name,int num) {
		if (list == nullptr) {
			return; // 链表为空，直接返回
		}

		node<T>* current = list;



		if (num <= size % 2)
		{
			// 找到要删除的节点
			while (current->data != name && current->next != list) {
				current = current->next;
			}
			// 如果找到了要删除的节点
			if (current->data == name) {
				if (current == list) {
					// 如果要删除的是头节点
					if (current->next == list) {
						delete current;
						list = nullptr;
					}
					else {
						// 如果链表中还有其他节点
						node<T>* temp = current;
						while (temp->next != list) {
							temp = temp->next;
						}
						temp->next = current->next;
						list = current->next;
						list->prev = temp;
						delete current;
					}
				}
				else {
					// 如果要删除的是中间或尾部节点

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
			}

		}


		else if (num > size % 2)
		{
			// 找到要删除的节点
			while (current->data != name && current->prev != list) {
				current = current->prev;
			}
			// 如果找到了要删除的节点
			if (current->data == name) {
				if (current == list) {
					// 如果要删除的是头节点
					if (current->prev == list) {
						delete current;
						list = nullptr;
					}
					else {
						// 如果链表中还有其他节点
						node<T>* temp = current;
						while (temp->prev != list) {
							temp = temp->prev;
						}
						temp->prev = current->prev;
						list = current->prev;
						list->next = temp;
						delete current;
					}
				}
				else {
					// 如果要删除的是中间或尾部节点

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
			}

		}


	}


	//修改
	void modifyNode(node<T>* list, T name, T newData,int num) {
		node<T>* current = list;

		if (num <= size % 2)
		{
			// 遍历链表查找要修改的节点
			while (current != nullptr) {
				if (current->data == name) {
					current->data = newData; // 修改节点数据
					break;
				}
				current = current->next;
				if (current == list) {
					break; // 回到头节点，结束遍历
				}
			}

		}

		else if (num > size % 2)
		{
			// 遍历链表查找要修改的节点
			while (current != nullptr) {
				if (current->data == name) {
					current->data = newData; // 修改节点数据
					break;
				}
				current = current->prev;
				if (current == list) {
					break; // 回到头节点，结束遍历
				}
			}

		}


	}


	//查找
	void findNode(node<T>* list, T name,int num) {
		node<T>* current = list;

		// 遍历链表查找目标节点
		if (num <= size % 2) {
			while (current != nullptr) {
				if (current->data == name) {
					cout << current->data; // 找到目标节点
					return;
				}
				current = current->next;
				if (current == list) {
					break; // 回到头节点，结束遍历
				}
			}
		}

		else if (num > size % 2) {
			while (current != nullptr) {
				if (current->data == name) {
					cout << current->data; // 找到目标节点
					return;
				}
				current = current->prev;
				if (current == list) {
					break; // 回到头节点，结束遍历
				}
			}
		}


		cout << "未找到";// 未找到目标节点
	}


	//编号更新
	void updatenum(node<T>* list)
	{
		int newnum = 0;
		node<T>* current = list;
		current->counter = newnum;
		while (current->next != list)
		{
			current = current->next;
			current->counter = ++newnum;
		}
	}


	void clearList(node<T>*& list) {
		if (list == nullptr || list->next == list) {
			return; // 链表为空或者只有头节点，直接返回
		}

		node<T>* current = list->next;
		while (current != list) { // 遍历链表
			node<T>* temp = current;
			current = current->next;
			delete temp; // 删除当前节点
		}
		list->next = list; // 头节点指向自身
		list->prev = list; // 头节点的prev也指向自身，形成循环
		list->counter = 0; // 重置计数器
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
		cout << "请输入删除的数据和编号" << endl;
		T temp;
		int num;
			cin >> temp >> num;
		listb.deleteNode(listb.List, temp, num);
		break;
	}
	case 4:
	{
		listb.print(listb.List);
		cout << "请输入修改目标的数据和编号" << endl;
		T tempn;
		int num;
		cin >> tempn >> num;
		cout << "请输入修改的新数据" << endl;
		T templ;
		cin >> templ;
		listb.modifyNode(listb.List, tempn, templ,num);
		break;
	}
	case 5:
	{
		listb.print(listb.List);
		cout << "请输入查找目标的名字和编号" << endl;
		T temp;
		int num;
		cin >> temp >> num;
		listb.findNode(listb.List, temp,num);
		break;
	}
	case 6:
		listb.updatenum(listb.List);
		break;
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
	cout << "6编号更新" << endl;
	cout << "0返回" << endl;
}


void menu1()
{
	cout << "请选择要操作的类型" << endl;
	cout << "1,int" << endl;
	cout << "2,float" << endl;
	cout << "3,自定义类型" << endl;
}



template<typename T>
void jiaohubyme()
{

	static Linkedlist<T> list;
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "输入名字 数量" << endl;
		string tempname;
		int tempnum = 0;
		cin >> tempname >> tempnum;
		T tempt(tempname, tempnum);
		list.addNodeByEnd(list.List, tempt);

		break;
	}

	case 2:
	{
		list.print(list.List);
		break;
	}

	case 3:
	{
		list.print(list.List);
		cout << "请输入删除的名字和编号" << endl;
		string tempname;
		int biannum;
		cin >> tempname >> biannum;
		T tt = T::createFromName(tempname);
		list.deleteNode(list.List,tt,biannum);
		break;
	}
	case 4:
	{
		list.print(list.List);
		cout << "请输入修改目标的名字和编号" << endl;
		string tempname;
		int biannum;
			cin >> tempname >> biannum;
		T tt = T::createFromName(tempname);
		cout << "请输入修改的新名字，新数量" << endl;
		T templist;
		string tempname1;
		int tempnum;
		cin >> tempname1 >> tempnum;
		templist.change(tempname1, tempnum);
		list.modifyNode(list.List, tt, templist,biannum);

		break;
	}
	case 5:
	{
		list.print(list.List);
		cout << "请输入查找目标的名字和编号" << endl;
		string tempname;
		int biannum;
		cin >> tempname >> biannum;
		T tt = T::createFromName(tempname);
		list.findNode(list.List,tt,biannum);
		break;
	}
	case 6:
		list.updatenum(list.List);
		break;
	case 0:
		list.clearList(list.List);
		system("cls");
		main();
	default:
		system("cls");
		break;

	}

}


/////////////////////////////////////
template<typename T>
ostream& operator<<(ostream& os, const Linkedlist<T>& list) {
	node<T>* headNode = list.List;
	if (headNode == nullptr) {
		os << "Empty list" << endl;
	}
	else {
		node<T>* current = headNode->next;
		while (current != headNode) {
			os << current->data << "      " << current->counter << endl; // 使用重载的 << 运算符
			current = current->next;
		}
	}
	return os;
}


template<typename T>
bool operator==(const T& lhs, const T& rhs) {
	return lhs.getname() == rhs.getname();
}

template<typename T>
bool operator!=(const T& lhs, const T& rhs) {
	return !(lhs == rhs);
}

////////////////////////////////////////////////////

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

template<typename T>
void mainb()
{
	while (1)
	{
		menulist();
		jiaohubyme<T>();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}








void jiaohuv()
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
	case 3:
		mainb<Test1>();
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
		menu1();
		jiaohuv();
		system("pause");//防止闪屏
		system("cls");//清屏 

	}

	system("pause");

}





