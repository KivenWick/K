
#include<iostream>
#include<fstream>
using namespace std;
#include<string>

//�����ļ�������������Ŀ�����׿����ƹ���
//��̬��ѡ��
//ϸ���޸ģ��������
//ѧ������ϵͳ




class base
{
public:
	base()
	{

	}
	base(string name, string sax, int year, int grade)
	{
		this->year = year;
		this->name = name;
		this->grade = grade;
		this->sax = sax;
	}

	virtual void show()
	{

	}
	~base()
	{
	}
	virtual base* clone() const//����������д��벻�����ݶ��ǵ�ַ�����⣬������д�����¿ռ��һ���¶��󲢷��س�����
	{
		return new base(*this);
	}

	virtual void setCarceer(string carceer)
	{
		// ��ʵ�֣�����û�� carceer ����
	}//���������������carceer������

	virtual void setyear(int year)
	{
		this->year = year;
	}
	virtual void setname(string name)
	{
		this->name = name;
	}

	virtual void setgrade(int grade)
	{
		this->grade = grade;
	}

	virtual void setsax(string sax)
	{
		this->sax = sax;
	}


	virtual string getcarceer()
	{
		return "k";
	}


	string name;
	string sax;
	int year;
	int grade;
};

class sonA:public base
{
public:
	sonA()
	{

	}

	sonA(string name,string sax,int year, int grade,string carceer) :base(name,sax,year,grade)
	{
		this->carceer = carceer;
	}
	void show()
	{
		cout << this->name<< this->sax<< this->year<< this->grade<< this->carceer << endl;
	}
	~sonA()
	{

	}
	sonA* clone() const override//���������ຯ��ּ�ڸ��ǻ��ຯ����  
	{
		return new sonA(*this);
	}

	virtual void setyear(int year)
	{
		this->year = year;
	}
	virtual void setname(string name)
	{
		this->name = name;
	}
	virtual void setsax(string sax)
	{
		this->sax = sax;
	}
	void setgrade(int grade) override
	{
		this->grade = grade;
	}
	void setCarceer(string carceer)
	{
		this->carceer = carceer;
	}


	string getcarceer()
	{
		return this->carceer;
	}

	string carceer = "�������";
};

class sonB :public base
{
public:
	sonB()
	{

	}

	sonB(string name, string sax, int year, int grade, string carceer) :base(name, sax, year, grade)
	{
		this->carceer = carceer;
	}
	void show()
	{
		cout << this->name<< this->sax<< this->year<< this->grade<< this->carceer << endl;
	}
	~sonB()
	{

	}
	sonB* clone() const override//���������ຯ��ּ�ڸ��ǻ��ຯ����  
	{
		return new sonB(*this);
	}

	virtual void setyear(int year)
	{
		this->year = year;
	}
	virtual void setname(string name)
	{
		this->name = name;
	}
	virtual void setsax(string sax)
	{
		this->sax = sax;
	}
	void setgrade(int grade) override
	{
		this->grade = grade;
	}

	void setCarceer(string carceer)
	{
		this->carceer = carceer;
	}

	string getcarceer()
	{
		return this->carceer;
	}

	string carceer = "�˹�����";
};



class Node
{
public:
	base* data;
	Node* next;

};

Node* list = NULL;




Node* createhead()//ͷ�ڵ㺯��
{
	Node* headnode = new Node;
	headnode->next = NULL;
	return headnode;
}

//�ø���ָ�룬�������ַ������ʵ�ֶ�̬
Node* createnode(const base& obj)
{
	Node* newnode = new Node;
	newnode->data = obj.clone(); // ʹ�û����еĿ�¡�������������������ĸ���
	newnode->next = NULL;
	return newnode;
}




void addnodebyhead(Node *headnode,base &obj)
{
	Node* newnode = createnode(obj);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

void printflist(Node* headnode)
{
	Node* pMove = headnode->next;
	while (pMove != NULL)
	{
		pMove->data->show();
		printf("\n");
		pMove = pMove->next;
	}

}

// ����
Node* searchbyname(Node* headnode, string name)
{
	Node* posnode = headnode->next;
	while (posnode != NULL && posnode->data->name!=name)
	{
		posnode = posnode->next;
	}
	return posnode;
}



void modify(Node* headnode, string name) {
	Node* posnode = searchbyname(headnode, name);
	if (posnode == NULL) {
		printf("δ�ҵ��ڵ�\n");
		return;
	}
	else {
		printf("ԭ�ڵ����ݣ�\n");
		posnode->data->show();
		printf("\n�������µ���Ϣ��\n");
		string newname;
		string newsax;
		int newyear;
		int newgrade;;

		cin >> newname >> newsax >> newyear >> newgrade;
		posnode->data->setyear(newyear);
		posnode->data->setname(newname);
		posnode->data->setsax(newsax);
		posnode->data->setgrade(newgrade);
		//printf("�Ƿ���Ҫ�޸����");
		//printf("�� 1   �� 2\n");
		//int i = 0;
		//cin >> i;
		//if (i == 1)
		//{
		//	string carceer;
		//	cin >> carceer;
		//	posnode->data->setCarceer(carceer); // �޸����������� grade ����
		//}
		printf("�޸ĳɹ�\n");
	}
}


//�����ɾ��
void deletebyname(Node* headnode, string name)
{
	Node* leftposnode = headnode;
	Node* posnode = headnode->next;
	while (posnode != NULL && posnode->data->name != name)
	{
		leftposnode = posnode;
		posnode = leftposnode->next;
	}
	if (posnode == NULL)
	{
		printf("δ���ҵ�");
		return;
	}
	else//���ҵ�Ŀ�� 
	{
		printf("ɾ���ɹ�");
		leftposnode->next = posnode->next;//����һ�����Ӳ�������Ŀ���ұ߽ڵ�ĵ�ַ��ֵ��Ŀ����ߵ�ָ����Ȼ���ͷ�Ŀ��ڵ� 
		free(posnode);
		posnode = NULL;//�ܿգ���ֹ����й¶ 
	}

}


//����Ӣ��ɼ�����
void bubblesortlist(Node* headNode) 
{
	Node* p;
	Node* q;
	for (p = headNode->next; p != NULL; p = p->next)
	{
		for (q = headNode->next; q->next != NULL; q = q->next)//��P��һ�ε�ʱ��Q��Ҫ��ǰһֱ����ֱ�����ҵ�Ŀ�� 
		{

			if (q->data->year > q->next->data->year)
			{
				base* tempdata = q->data;
				q->data = q->next->data;
				q->next->data = tempdata;
			}
		}
	}
	printflist(headNode);
}


//���ļ�����

void saveToFile(Node* headnode, const string& filename) {
	ofstream fout(filename);
	if (!fout) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	Node* pMove = headnode->next;
	while (pMove != NULL) {
		fout << pMove->data->name << " ";
		fout << pMove->data->sax << " " ;
		fout << pMove->data->year << " ";
		fout << pMove->data->grade << " ";
		fout << pMove->data->getcarceer();  // ������ carceer ����
		pMove = pMove->next;
	}

	fout.close();
	cout << "���ݱ���ɹ�" << endl;
}


//���ļ���������һ�δ򿪳�����һ�δ����ļ������ݼ��ؽ������У���������

void loadFromFile(Node* headnode, const string& filename) {
	ifstream fin(filename);
	if (!fin) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	string name;
	string sax;
	int year;
	int grade;
	string carceer;

	while (fin >> name >> sax >> year >> grade >> carceer) {
		if (carceer == "�������") {
			sonA tempa(name, sax, year, grade, carceer);
			addnodebyhead(headnode, tempa);
		}
		else if (carceer == "�˹�����") {
			sonB tempb(name, sax, year, grade, carceer);
			addnodebyhead(headnode, tempb);
		}
	}

	fin.close();
	cout << "���ݼ��سɹ�" << endl;
}


void menu()//����ҳ�� 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               ����ϵͳ                 \n");
	printf("               0.�˳�ϵͳ\n");
	printf("               1.�Ǽ�\n");
	printf("               2.������\n");
	printf("               3.�޸���Ϣ\n");
	printf("               4.����\n");
	printf("               5.ɾ��\n");
	printf("               6.����\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

}

void jiaohu()
{
	int key = 0;
	int a;
	base temp;
	Node* result = NULL;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		
			int type;
			cout << "��ѡ��Ҫ��ӵĽڵ����ͣ�" << endl;
			cout << "1. sonA" << endl;
			cout << "2. sonB" << endl;
			cin >> type;

			if (type == 1) {
				// ��� sonA �ڵ�
				int year;
				string name;
				int grade;
				string sax;
				string carceer = "�������";
				cout << "������ڵ�����ԣ�";
				cout << "name sax year grade " << endl;
				cin >> name >> sax >> year >> grade;
				sonA temp(name,sax,year,grade,carceer);
				addnodebyhead(list, temp);
				saveToFile(list, "data.txt");
			}
			else if (type == 2) {
				// ��� sonB �ڵ�
				int year = 0;
				string name;
				int grade;
				string sax;
				string carceer = "�˹�����";
				cout << "������ڵ�����ԣ�";
				cout << "name sax year grade " << endl;
				cin >> name >> sax >> year >> grade;
				sonB temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
				saveToFile(list, "data.txt");
			}
			else {
				cout << "��Ч��ѡ��" << endl;
			}
			break;
		}
	case 2:
		printf("���\n");
		printflist(list);
		break;
	case 3:
	{
		printf("�޸�\n");
		printf("������Ŀ����������\n");
		cin >> temp.name;
		modify(list, temp.name);
		// ���¶�Ӧ�ڵ�����ݵ��ļ���
		saveToFile(list, "data.txt");
		break;
	}
	case 4:
		printf("����\n");
		bubblesortlist(list);
		break;
	case 5:
		printf("ɾ��\n");
		printf("������ɾ��������");
		cin >> temp.name;
		deletebyname(list, temp.name);
		// ���ļ���ɾ����Ӧ������
		saveToFile(list, "data.txt");
		break;
	case 6:
		printf("����\n");
		printf("���������֣�");
		cin >> temp.name;
		result = searchbyname(list, temp.name);
		if (result == NULL)
			printf("δ�ҵ�\n");
		else
		{
			printf("\n");
			result->data->show();
		}
		break;
	case 0:
		printf("��лʹ��\n");
		exit(0);
	default:
		system("cls");
		break;

	}


}

//���Ժ�������
//void test(base* b)
//{
//	b->show();
//}
//
//void main()
//{
//	
//
//		sonA a1(1, "cc", 2);
////		test(&a1);
//		Node *t=createnode(&a1);
//		t->data->show();
//
//	system("pause");
//	return;
//}



void main()
{
	

	list = createhead();
	
	// ���ļ��������ݵ�����

	loadFromFile(list, "data.txt");


	while (1) {
		menu();
		jiaohu();
		system("pause");
		system("cls");
	}

	// �������ݵ��ļ�
	saveToFile(list, "data.txt");

	

	system("pause");
	return;

}










































































