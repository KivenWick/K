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
		return Test1(name, 0); // ����ڶ�����������num�������ﲻ��Ҫ
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
		headNode->next = headNode; // ѭ������ͷ�ڵ�ָ������
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
		node<T>* newNode = createNode(tempdata); // �����½ڵ�

			node<T>* tail = list;
			while (tail->next != list) { // �ҵ����һ���ڵ�
				tail = tail->next;
			}
			tail->next = newNode; // ���½ڵ���뵽���һ���ڵ�֮��
			newNode->prev = tail;
			newNode->next = list; // �½ڵ��nextָ��ָ��ͷ�ڵ㣬�γ�ѭ��
			list->prev = newNode; // ͷ�ڵ��prevָ��ָ���½ڵ㣬�γ�ѭ��
			newNode->counter = newNode->prev->counter + 1;
			size = newNode->counter + 1;
	}


	void print(node<T>* headNode) {
		node<T>* current = headNode->next;
		while (current != headNode) {
			cout << current->data << " " << current->counter << endl;
			current = current->next;
			if (current == headNode) {
				break; // �����ǰ�ڵ��ֻص���ͷ�ڵ㣬������ѭ��
			}
		}
		cout << endl;
	}

	//ɾ��
	void deleteNode(node<T>*& list, T name,int num) {
		if (list == nullptr) {
			return; // ����Ϊ�գ�ֱ�ӷ���
		}

		node<T>* current = list;



		if (num <= size % 2)
		{
			// �ҵ�Ҫɾ���Ľڵ�
			while (current->data != name && current->next != list) {
				current = current->next;
			}
			// ����ҵ���Ҫɾ���Ľڵ�
			if (current->data == name) {
				if (current == list) {
					// ���Ҫɾ������ͷ�ڵ�
					if (current->next == list) {
						delete current;
						list = nullptr;
					}
					else {
						// ��������л��������ڵ�
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
					// ���Ҫɾ�������м��β���ڵ�

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
			}

		}


		else if (num > size % 2)
		{
			// �ҵ�Ҫɾ���Ľڵ�
			while (current->data != name && current->prev != list) {
				current = current->prev;
			}
			// ����ҵ���Ҫɾ���Ľڵ�
			if (current->data == name) {
				if (current == list) {
					// ���Ҫɾ������ͷ�ڵ�
					if (current->prev == list) {
						delete current;
						list = nullptr;
					}
					else {
						// ��������л��������ڵ�
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
					// ���Ҫɾ�������м��β���ڵ�

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
			}

		}


	}


	//�޸�
	void modifyNode(node<T>* list, T name, T newData,int num) {
		node<T>* current = list;

		if (num <= size % 2)
		{
			// �����������Ҫ�޸ĵĽڵ�
			while (current != nullptr) {
				if (current->data == name) {
					current->data = newData; // �޸Ľڵ�����
					break;
				}
				current = current->next;
				if (current == list) {
					break; // �ص�ͷ�ڵ㣬��������
				}
			}

		}

		else if (num > size % 2)
		{
			// �����������Ҫ�޸ĵĽڵ�
			while (current != nullptr) {
				if (current->data == name) {
					current->data = newData; // �޸Ľڵ�����
					break;
				}
				current = current->prev;
				if (current == list) {
					break; // �ص�ͷ�ڵ㣬��������
				}
			}

		}


	}


	//����
	void findNode(node<T>* list, T name,int num) {
		node<T>* current = list;

		// �����������Ŀ��ڵ�
		if (num <= size % 2) {
			while (current != nullptr) {
				if (current->data == name) {
					cout << current->data; // �ҵ�Ŀ��ڵ�
					return;
				}
				current = current->next;
				if (current == list) {
					break; // �ص�ͷ�ڵ㣬��������
				}
			}
		}

		else if (num > size % 2) {
			while (current != nullptr) {
				if (current->data == name) {
					cout << current->data; // �ҵ�Ŀ��ڵ�
					return;
				}
				current = current->prev;
				if (current == list) {
					break; // �ص�ͷ�ڵ㣬��������
				}
			}
		}


		cout << "δ�ҵ�";// δ�ҵ�Ŀ��ڵ�
	}


	//��Ÿ���
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
			return; // ����Ϊ�ջ���ֻ��ͷ�ڵ㣬ֱ�ӷ���
		}

		node<T>* current = list->next;
		while (current != list) { // ��������
			node<T>* temp = current;
			current = current->next;
			delete temp; // ɾ����ǰ�ڵ�
		}
		list->next = list; // ͷ�ڵ�ָ������
		list->prev = list; // ͷ�ڵ��prevҲָ�������γ�ѭ��
		list->counter = 0; // ���ü�����
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
		cout << "������ɾ�������ݺͱ��" << endl;
		T temp;
		int num;
			cin >> temp >> num;
		listb.deleteNode(listb.List, temp, num);
		break;
	}
	case 4:
	{
		listb.print(listb.List);
		cout << "�������޸�Ŀ������ݺͱ��" << endl;
		T tempn;
		int num;
		cin >> tempn >> num;
		cout << "�������޸ĵ�������" << endl;
		T templ;
		cin >> templ;
		listb.modifyNode(listb.List, tempn, templ,num);
		break;
	}
	case 5:
	{
		listb.print(listb.List);
		cout << "���������Ŀ������ֺͱ��" << endl;
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
	cout << "1����" << endl;
	cout << "2չʾ" << endl;
	cout << "3ɾ��" << endl;
	cout << "4�޸�" << endl;
	cout << "5����" << endl;
	cout << "6��Ÿ���" << endl;
	cout << "0����" << endl;
}


void menu1()
{
	cout << "��ѡ��Ҫ����������" << endl;
	cout << "1,int" << endl;
	cout << "2,float" << endl;
	cout << "3,�Զ�������" << endl;
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
		cout << "�������� ����" << endl;
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
		cout << "������ɾ�������ֺͱ��" << endl;
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
		cout << "�������޸�Ŀ������ֺͱ��" << endl;
		string tempname;
		int biannum;
			cin >> tempname >> biannum;
		T tt = T::createFromName(tempname);
		cout << "�������޸ĵ������֣�������" << endl;
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
		cout << "���������Ŀ������ֺͱ��" << endl;
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
			os << current->data << "      " << current->counter << endl; // ʹ�����ص� << �����
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
		system("pause");//��ֹ����
		system("cls");//���� 

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
		system("pause");//��ֹ����
		system("cls");//���� 

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
		cout << "δ֪ѡ��";
		break;

	}

}






void main()
{
	while (1)
	{
		menu1();
		jiaohuv();
		system("pause");//��ֹ����
		system("cls");//���� 

	}

	system("pause");

}





