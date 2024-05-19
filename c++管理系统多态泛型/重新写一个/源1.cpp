#include<iostream>
#include<fstream>
#include<conio.h>
#include <chrono>
#include <thread>
using namespace std;
#include<string>

///////////////////////////////������
void createUser();
bool loginUser();
int denglu();
void maicard();
void maincai();


///////////////////////////////



class base
{
public:
	base()
	{

	}
	base(string name, string sax, int year, int grade)// ���캯��
	{
		this->year = year;
		this->name = name;
		this->grade = grade;
		this->sax = sax;
	}

	virtual void show()//��ӡ�����������ʵ��
	{

	}
	~base()//��������
	{
	}
	virtual base* clone() const//����������д��벻�����ݶ��ǵ�ַ�����⣬������д�����¿ռ��һ���¶��󲢷��س������������캯����const����
	{
		return new base(*this);
	}

	virtual void setCarceer(string carceer)
	{
		// ��ʵ�֣�����û�� carceer ����
	}//���������������carceer������

	 void setyear(int year)
	{
		this->year = year;
	}
	 void setname(string name)
	{
		this->name = name;
	}

	 void setgrade(int grade)
	{
		this->grade = grade;
	}

	 void setsax(string sax)
	{
		this->sax = sax;
	}

	virtual string getcarceer()//������carceer���ԣ���㷵��һ����Ӱ�췽��д����ʱд�����getcarceer
	{
		return "k";
	}

	 int getyear()
	{
		return this->year;
	}

	 int getgrade()
	{
		return this->grade;
	}

	 string getname()
	{
		return this->name;
	}

	 string getsax()
	{
		return this->sax;
	}

private:
	string name;
	string sax;
	int year;
	int grade;
};

class sonA :public base//����ʾ��
{
public:
	sonA()//�޲ι��죬�����γɶ���
	{

	}

	sonA(string name, string sax, int year, int grade, string carceer) :base(name, sax, year, grade)//������
	{
		this->carceer = carceer;
	}
	void show()//��д��ӡ����
	{
		cout << this->getname() <<" "<< this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonA()//��������
	{

	}
	sonA* clone() const override//���������ຯ��ּ�ڸ��ǻ��ຯ���� ��д����Ŀ������캯�� override����
	{
		return new sonA(*this);
	}

	void setCarceer(string carceer)
	{
		this->carceer = carceer;
	}

	
	string getcarceer()//��дgetcarceer
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
	void show()//��д��ӡ����
	{
		cout << this->getname() << " " << this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonB()//��������
	{

	}
	sonB* clone() const override//���������ຯ��ּ�ڸ��ǻ��ຯ���� ��д����Ŀ������캯�� override����
	{
		return new sonB(*this);
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


class sonC :public base
{
public:
	sonC()
	{

	}

	sonC(string name, string sax, int year, int grade, string carceer) :base(name, sax, year, grade)
	{
		this->carceer = carceer;
	}
	void show()//��д��ӡ����
	{
		cout << this->getname() << " " << this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonC()
	{

	}
	sonC* clone() const override//���������ຯ��ּ�ڸ��ǻ��ຯ����  
	{
		return new sonC(*this);
	}

	void setCarceer(string carceer)
	{
		this->carceer = carceer;
	}

	string getcarceer()
	{
		return this->carceer;
	}

	string carceer = "������";
};
 




class Node//ʵ�������̬����������ָ����е���
{
public:
	base* data;//���ﴫ�ľͲ������ݶ��ǵ�ַ��
	Node* next;

};

Node* list = NULL;//ͷָ��

Node* createhead()//ͷ�ڵ㺯��
{
	Node* headnode = new Node;
	headnode->next = NULL;
	return headnode;
}

//�ø���ָ�룬�������ַ������ʵ�ֶ�̬
Node* createnode(const base& obj)//���ĺ�����ͨ���������뿽������������ͬһƬ��ַ�����⡣�������൱�ڴ������󸱱����µĶ���
{
	Node* newnode = new Node;
	newnode->data = obj.clone(); // ʹ�û����еĿ�¡�������������������ĸ���
	newnode->next = NULL;
	return newnode;
}

void addnodebyhead(Node* headnode, base& obj)//ͨ����temp�������ٹ���temp����
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
	while (posnode != NULL && posnode->data->getname() != name)//string name������ʹ��strcmpy
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
	while (posnode != NULL && posnode->data->getname() != name)
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

//�����ռ�
void deleteList(Node* headNode)
{
	Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		Node* temp = pMove;
		pMove = pMove->next;
		delete temp->data; // �ͷŽڵ�ָ��Ķ����ڴ�
		delete temp; // �ͷŽڵ��ڴ�
	}
	headNode->next = NULL; // ��ͷ�ڵ��ָ�����ÿ�
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

			if (q->data->getgrade() > q->next->data->getgrade())
			{
				base* tempdata = q->data;
				q->data = q->next->data;
				q->next->data = tempdata;
			}
		}
	}
	printflist(headNode);
}



void saveToFile(Node* headNode)
{
	ofstream file("data.txt"); // ���ļ�
	if (file.is_open())
	{
		Node* pMove = headNode->next;
		while (pMove != NULL)
		{
			file << pMove->data->getname() << " " << pMove->data->getsax() << " " << pMove->data->getyear() << " " << pMove->data->getgrade() << " " << pMove->data->getcarceer() << endl;
			pMove = pMove->next;
		}
		file.close(); // �ر��ļ�
		cout << "�����ѱ��浽�ļ�" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}

void loadFromFile(Node* headNode)
{
	ifstream file("data.txt"); // ���ļ�
	if (file.is_open())
	{
		string name, sax, carceer;
		int year, grade;
		while (file >> name >> sax >> year >> grade >> carceer)
		{
			if (carceer == "�������")
			{
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			else if (carceer == "�˹�����")
			{
				sonB temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			else if (carceer == "������")
			{
				sonC temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			
		}
		file.close(); // �ر��ļ�
		cout << "���ļ��������ݳɹ�" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}


void menu()
{

	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               ����ϵͳ                 " << endl;
	cout << "               0.�˳�ϵͳ" << endl;
	cout << "               1.�Ǽ�" << endl;
	cout << "               2.������" << endl;
	cout << "               3.�޸���Ϣ" << endl;
	cout << "               4.����" << endl;
	cout << "               5.ɾ��" << endl;
	cout << "               6.����" << endl;
	cout << "               7.���浽�ļ�" << endl; // ����ѡ��
	cout << "               8.���ļ�����" << endl; // ����ѡ��
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

}


void jiaohu()
{
	int key = 0;
	int a;
	base temp;
	string tempname;
	Node* result = NULL;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{//��ͬ����Ҫʵ�ֲ�ͬ�Ľڵ���ӣ�������ͬ�Ľڵ���ʱ����

		int type;
		cout << "��ѡ��Ҫ��ӵ�ѧ����רҵ���ͣ�" << endl;
		cout << "1. �������" << endl;
		cout << "2. �˹�����" << endl;
		cout << "3. ������" << endl;
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
			result = searchbyname(list,name);
			if (result == NULL)
			{
				printf("�����������\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("�����ظ�");
			}
			
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
			result = searchbyname(list, name);
			if (result == NULL)
			{
				printf("�����������\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("�����ظ�");
			}
		}
		else if (type == 3) {
			// ��� sonC �ڵ�
			int year = 0;
			string name;
			int grade;
			string sax;
			string carceer = "������";
			cout << "������ڵ�����ԣ�";
			cout << "name sax year grade " << endl;
			cin >> name >> sax >> year >> grade;
			result = searchbyname(list, name);
			if (result == NULL)
			{
				printf("�����������\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("�����ظ�");
			}
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
		cin >> tempname;
		modify(list, tempname);
		break;
	}
	case 4:
		printf("����\n");
		bubblesortlist(list);
		break;
	case 5:
		printf("ɾ��\n");
		printf("������ɾ��������");
		cin >> tempname;
		deletebyname(list, tempname);
		break;
	case 6:
		printf("����\n");
		printf("���������֣�");
		cin >> tempname;
		result = searchbyname(list, tempname);
		if (result == NULL)
			printf("δ�ҵ�\n");
		else
		{
			printf("\n");
			result->data->show();
		}
		break;
	case 7:
		saveToFile(list);
		break;
	case 8:
		loadFromFile(list);
		break;
	case 0:
		printf("��лʹ��\n");
		exit(0);
	default:
		system("cls");
		break;

	}

}

//����
void original()
{

	list = createhead();
	while (1) {
		menu();
		jiaohu();
		system("pause");
		system("cls");
	}
	deleteList(list); // �ڳ������ǰ�ͷ������ڴ�ռ�
	system("pause");
}

//////�ܵ�¼
void menufirst()
{
	cout << "*******************************" << endl;
	cout << "*                             *" << endl;
	cout << "*   ��ӭʹ��У԰����ϵͳ��    *" << endl;
	cout << "*                             *" << endl;
	cout << "*******************************" << endl;

	cout << endl;
	cout << "���ڼ��أ����Ժ�";

	// ģ����ع��̣�ÿ��500�������һ��'.'���ܹ����10����
	for (int i = 0; i < 10; ++i) {
		this_thread::sleep_for(chrono::milliseconds(500));  // ��ͣ500����
		cout << "->";
		cout.flush();  // ˢ�������������ȷ����������ʾ
	}

	cout << endl << endl;
	cout << "��ѡ�����ĵ�¼��ݣ�" << endl;
	cout << "1. ѧ��" << endl;
	cout << "2. ����Ա" << endl;

}

  
//�����¼
int main()
{
	menufirst();
	int kt;
	cin >> kt;

	if(kt==2)
	{
		string username, password;
		int loginAttempts = 0;
		bool isLoggedIn = false;

		while (loginAttempts < 3 && !isLoggedIn)
		{
			cout << "�������û�����";
			cin >> username;

			cout << "���������룺";
			password = "";
			char ch;
			while ((ch = _getch()) != '\r') // ���»س���������������
			{
				if (ch == '\b') // ��������˸������ɾ�����һ���ַ�
				{
					if (password.length() > 0)
					{
						password.pop_back();
						_putch('\b'); // ɾ����Ļ�ϵ����һ���ַ�
						_putch(' '); // �ÿո񸲸�ɾ�����ַ�
						_putch('\b'); // �ٴν�����ƶ������һ���ַ���λ��
					}
				}
				else
				{
					password.push_back(ch);
					_putch('*'); // ����Ļ����ʾ�Ǻ�
				}
			}

			// �����������Խ�������û��������������ݿ��е���Ϣ���бȶ���֤

			if (username == "admin" && password == "123456")
			{
				isLoggedIn = true;
				cout << endl << "��½�ɹ���" << endl;
				original();
			}
			else
			{
				loginAttempts++;
				cout << endl << "�û���������������������룡" << endl;
			}
		}

		if (!isLoggedIn)
		{
			cout << "��½ʧ�ܣ����Ѿ�������3�Σ����Ժ����ԣ�" << endl;
		}

	}
	else if (kt == 1)
	{
		denglu();
	}
	return 0;
}


class computer
{
public:
	void setifuse(string ifuse)
	{
		this->ifuse = ifuse;
	}

	void setuser(string user)
	{
		this->user = user;
	}

	void setnum(int num)
	{
		this->num = num;
	}

	string getifuse()
	{
		return this->ifuse;
	}

	string getuser()
	{
		return this->user;
	}

	int getnum()
	{
		return this->num;
	}
	void showcom()
	{
		cout << this->getifuse() << " " << this->getuser() << " " << this->getnum() << endl;
	}

private:
	string ifuse;
	string user;
	int num;
};

class nodecom
{
public:
	computer data;
	nodecom* next;

};
   
nodecom* comlist = NULL;

//ͷ�ڵ㺯��
nodecom* createheadcom()
{
	nodecom* headnode = new nodecom;
	headnode->next = NULL;
	return headnode;
}

nodecom* createnodecom(computer data)//�����ڵ�ĺ�������������ʹ��
{
	nodecom* newnode = new nodecom;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;//���ص���ָ��
}

//ͷ�巨��ʵ������Ĵ�������
void addNodebyheadcom(nodecom* headnode, computer data)
{
	nodecom* newnode = createnodecom(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

//�����ӡ
void printflistcom(nodecom* headnode)
{
	nodecom* pMove = headnode->next;
	while (pMove != NULL)
	{
		pMove->data.showcom();
		printf("\n");
		pMove = pMove->next;
	}

}

//����
nodecom* searchbynum(nodecom* headnode, int num)
{
	nodecom* posnode = headnode->next;
	while (posnode != NULL && posnode->data.getnum()!= num)
	{
		posnode = posnode->next;
	}
	return posnode;
}

//������޸�
void changecom(nodecom* headnode, int num)
{
	nodecom* posnode = headnode;
	while (posnode != NULL && posnode->data.getnum() != num)
	{
		posnode = posnode->next;
	}
	if (posnode == NULL)
	{
		printf("δ���ҵ�");
		return;
	}
	else
	{
		posnode->data.showcom();
		printf("�������µ���Ϣ");
		string changeifuse;
		string changeuser;
		int changenum;
		cin >> changeifuse >> changeuser >> changenum;
		posnode->data.setifuse(changeifuse);
		posnode->data.setuser(changeuser);
		posnode->data.setnum(changenum);
		printf("�޸ĳɹ�");
	}
}

//�����ɾ��
void deletebynum(nodecom* headnode, int num)
{
	nodecom* leftposnode = headnode;
	nodecom* posnode = headnode->next;
	while (posnode != NULL && posnode->data.getnum() != num)
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

void menucom()
{
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               ����                 " << endl;
	cout << "               1.�Ǽ�" << endl;
	cout << "               2.������" << endl;
	cout << "               3.�޸���Ϣ" << endl;
	cout << "               4.ɾ��" << endl;
	cout << "               5.����" << endl;
	cout << "               6.���浽�ļ�" << endl; 
	cout << "               7.���ļ�����" << endl; 
	cout << "               0.�˳�ϵͳ" << endl;
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

}
///////////////////////////////
void saveToFilecom(nodecom* headnode, string filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		nodecom* pMove = headnode->next;
		while (pMove != NULL)
		{
			file << pMove->data.getifuse() << " " << pMove->data.getuser() << " " << pMove->data.getnum() << endl;
			pMove = pMove->next;
		}
		file.close();
		cout << "�����ѳɹ����浽�ļ�" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}

// ���ļ���������
void loadFromFilecom(nodecom* headnode, string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		string ifuse, user;
		int num;
		while (file >> ifuse >> user >> num)
		{
			computer data;
			data.setifuse(ifuse);
			data.setuser(user);
			data.setnum(num);
			addNodebyheadcom(headnode, data);
		}
		file.close();
		cout << "�����ѳɹ����ļ�����" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}



////////

//����
void jiaohucom()
{
	int keycom = 0;
	computer tempcom;
	string tempifuse;
	string tempuser;
	int tempnum;
	string filenamecom = "computer_data.txt";
	nodecom* resultcom = NULL;
	scanf_s("%d", &keycom);
	switch (keycom)
	{
	case 1:
		printf("�Ǽ�\n");
		printf("��������Ϣ(ifusing user num)\n");
		cin >> tempifuse >> tempuser >> tempnum;
		tempcom.setifuse(tempifuse);
		tempcom.setuser(tempuser);
		tempcom.setnum(tempnum);
		addNodebyheadcom(comlist, tempcom);
		break;
	case 2:
		printf("���\n");
		printflistcom(comlist);
		break;
	case 3:
		printf("�޸�\n");
		printf("������Ŀ�����ĺ���\n");
		cin >> tempnum;
		changecom(comlist, tempnum);
		break;
	case 4:
		printf("ɾ��\n");
		printf("������ɾ���ĺ���");
		cin >> tempnum;
		deletebynum(comlist, tempnum);
		break;
	case 5:
		printf("����\n");
		printf("��������룺");
		cin >> tempnum;
		resultcom = searchbynum(comlist, tempnum);
		if (resultcom == NULL)
			printf("δ�ҵ�\n");
		else
		{
			printf("�Ƿ�ʹ�� ʹ���� ����\n");
			resultcom->data.showcom();
		}
		break;
	case 6:
		saveToFilecom(comlist, filenamecom);
		break;
	case 7:
		loadFromFilecom(comlist, filenamecom);
		break;
	case 0:
		printf("��лʹ��\n");
		system("cls");
		original();
	default:
		system("cls");
		break;

	}

}

//////////////////////ѧ��ע��
void createUser() {
	string username, password;

	cout << "�������û�����";
	cin >> username;

	cout << "���������룺";
	cin >> password;

	ofstream file("accounts.txt", ios::app);
	file << username << " " << password << endl;
	file.close();

	cout << "�˻������ɹ���" << endl;
}

bool loginUser() {
	string username, password;

	cout << "�������û�����";
	cin >> username;

	cout << "���������룺";
	cin >> password;

	ifstream file("accounts.txt");
	string line;
	while (getline(file, line)) {
		size_t pos = line.find(' ');
		string storedUsername = line.substr(0, pos);
		string storedPassword = line.substr(pos + 1);

		if (username == storedUsername && password == storedPassword) {
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

void maicom()
{
	comlist = createheadcom();
	while (1)
	{
		menucom();
		jiaohucom();
		system("pause");//��ֹ����
		system("cls");//���� 
	}

	nodecom* pMove = comlist->next;
	while (pMove != NULL)
	{
		nodecom* temp = pMove;
		pMove = pMove->next;
		delete temp;
	}
	delete comlist;

	system("pause");
	return;
}


int denglu() {
	int choice;

	while (true) {
		cout << "��ѡ�������" << std::endl;
		cout << "1. �����˻�" << std::endl;
		cout << "2. ��¼" << std::endl;
		cout << "3. �˳�" << std::endl;

		cout << "����ѡ�";
		cin >> choice;

		switch (choice) {
		case 1:
			createUser();
			break;

		case 2:
			if (loginUser()) {
				cout << "��¼�ɹ���" << endl;
				system("cls");
				cout << "1ѧ������ѯ 2����ԤԼ 3ѧ�����²�Ʒ������" << endl;
				int fenk;
				cin >> fenk;
				if (fenk == 2)
				{
					maicom();
				}
				else if (fenk == 1)
				{
					maicard();
				}
				else if (fenk == 3)
				{
					maincai();
				}

			}
			else {
				cout << "�û�����������������ԡ�" << endl;
			}
			break;

		case 3:
			system("cls");
			printf("��лʹ��\n");
			exit(0);

		default:
			cout << "��Ч��ѡ������ԡ�" << endl;
			break;
		}
	}

	return 0;
}



////////////////////////////////////
//����
//����
class card
{
public:
	
	void setuser(string user)
	{
		this->user = user;
	}

	void setnum(float num)
	{
		this->num = num;
	}

	void sethelpnum(int helpnum)
	{
		this->helpnum = helpnum;
	}

	string getuser()
	{
		return this->user;
	}

	float getnum()
	{
		return this->num;
	}

	int gethelpnum()
	{
		return this->helpnum;
	}

	void showcard()
	{
		cout  << this->getuser() << " " << this->getnum() << " "<<this->gethelpnum() << endl;
	}



private:
	string user;
	float num;
	int helpnum;//����
};

class nodecard
{
public:
	card data;
	nodecard* next;

};

nodecard* cardlist = NULL;

//ͷ�ڵ㺯��
nodecard* createheadcard()
{
	nodecard* headnode = new nodecard;
	headnode->next = NULL;
	return headnode;
}

nodecard* createnodecard(card data)//�����ڵ�ĺ�������������ʹ��
{
	nodecard* newnode = new nodecard;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;//���ص���ָ��
}

//ͷ�巨��ʵ������Ĵ�������
void addNodebyheadcard(nodecard* headnode, card data)
{
	nodecard* newnode = createnodecard(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

//�����ӡ
void printflistcard(nodecard* headnode)
{
	nodecard* pMove = headnode->next;
	while (pMove != NULL)
	{
		pMove->data.showcard();
		printf("\n");
		pMove = pMove->next;
	}

}

//����//������������� �Ը��ַ�ʽȥ����




template<typename T>
nodecard* searchbycard(nodecard* headnode, T date)
{
	nodecard* posnode = headnode->next;
	while (posnode != NULL)
	{
		if constexpr (std::is_same_v<T, std::string>)
		{
			if (posnode->data.getuser() == date)
				return posnode;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			if (posnode->data.gethelpnum() == date)
				return posnode;
		}
		posnode = posnode->next;
	}
	return nullptr; // ���δ�ҵ����򷵻�nullptr
}

nodecard* searchbycarduser(nodecard* headnode, string user)
{
	return searchbycard<string>(headnode, user);
}
nodecard* searchbycardhelpnum(nodecard* headnode, int helpnum)
{
	return searchbycard<int>(headnode, helpnum);
}



//�����ɾ��
void deletebycarduser(nodecard* headnode, string user)
{
	nodecard* leftposnode = headnode;
	nodecard* posnode = headnode->next;
	while (posnode != NULL && posnode->data.getuser() != user)
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

void menucard()
{
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               У԰��               " << endl;
	cout << "               1.�Ǽ�" << endl;
	cout << "               2.����" << endl;
	cout << "               3.����" << endl;
	cout << "               4.��Ǯ" << endl;
	cout << "               5.���浽�ļ�" << endl;
	cout << "               6.���ļ�����" << endl;
	cout << "               0.�˳�ϵͳ" << endl;
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

}
///////////////////////////////
void saveToFilecard(nodecard* headnode, string filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		nodecard* pMove = headnode->next;
		while (pMove != NULL)
		{
			file << pMove->data.getuser() << " " << pMove->data.getnum() << " " << pMove->data.gethelpnum() << endl;
			pMove = pMove->next;
		}
		file.close();
		cout << "�����ѳɹ����浽�ļ�" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}

// ���ļ���������
void loadFromFilecard(nodecard* headnode, string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		string user;
		float num;
		int helpnum;
		while (file >> user >> num >> helpnum)
		{
			card data;
			data.setuser(user);
			data.setnum(num);
			data.sethelpnum(helpnum);
			addNodebyheadcard(headnode, data);
		}
		file.close();
		cout << "�����ѳɹ����ļ�����" << endl;
	}
	else
	{
		cout << "�޷����ļ�" << endl;
	}
}



////////

//����
void jiaohucard()
{
	int keycard = 0;
	card tempcard;
	string tempuser;
	float tempnum;
	int temphelpnum;
	string filenamecard = "card_data.txt";
	nodecard* resultcard = NULL;
	scanf_s("%d", &keycard);
	switch (keycard)
	{
	case 1:
		printf("�Ǽ�\n");
		printf("��������Ϣ(user num helpnum)\n");
		cin >> tempuser >> tempnum >> temphelpnum;
		tempcard.setuser(tempuser);
		tempcard.setnum(tempnum);
		tempcard.sethelpnum(temphelpnum);
		addNodebyheadcard(cardlist, tempcard);
		break;
	case 2:
		printf("ɾ��\n");
		printf("������ɾ��������");
		cin >> tempuser;
		deletebycarduser(cardlist, tempuser);
		break;
	case 3:
		printf("����\n");
		printf("�������ֲ���1 ����������2");
			int poke;
			cin >> poke;
			if (poke == 1)
			{
				printf("���������֣�");
				cin >> tempuser;
				resultcard = searchbycarduser(cardlist, tempuser);
				if (resultcard == NULL)
					printf("δ�ҵ�\n");
				else
				{
					printf(" ʹ���� ��� ����\n");
					resultcard->data.showcard();
				}
			}

			if (poke == 2)
			{
				printf("�����벹����");
				cin >> temphelpnum;
				resultcard = searchbycardhelpnum(cardlist, temphelpnum);
				if (resultcard == NULL)
					printf("δ�ҵ�\n");
				else
				{
					printf(" ʹ���� ��� ����\n");
					resultcard->data.showcard();
				}

			}

		break;
	case 4:
		printf("������Ҫ��ֵ���˻����֣�");
		cin >> tempuser;
		float addnum;
		resultcard = searchbycarduser(cardlist, tempuser);
		if (resultcard == NULL) {
			printf("δ�ҵ����˻�\n");
		}
		else {
			printf("������Ҫ��ֵ�Ľ�");
			cin >> addnum;
			float currentAmount = resultcard->data.getnum();
			float newAmount = currentAmount + addnum;
			resultcard->data.setnum(newAmount);
			printf("��ֵ�ɹ�����ǰ���Ϊ��%f\n", newAmount);
		}
		break;
	case 5:
		saveToFilecard(cardlist, filenamecard);
		break;
	case 6:
		loadFromFilecard(cardlist, filenamecard);
		break;
     case 0:
		printf("��лʹ��\n");
		system("cls");
	default:
		system("cls");
		break;

	}

}

void maicard()
{
	cardlist = createheadcard();
	while (1)
	{
		menucard();
		jiaohucard();
		system("pause");//��ֹ����
		system("cls");//���� 
	}

	nodecard* pMove = cardlist->next;
	while (pMove != NULL)
	{
		nodecard* temp = pMove;
		pMove = pMove->next;
		delete temp;
	}
	delete cardlist;

	system("pause");
	return;
}


/////////////////////////////////


template<typename T>
class node {
public:
	T data; // �洢������
	node* next; // ָ����һ���ڵ��ָ��

	// ���캯��
	node(T data) : data(data), next(nullptr) {}
};


template<typename T>
class LinkedList {
private:
	node<T>* head; // �����ͷ�ڵ�

public:
	// ���캯��
	LinkedList() : head(nullptr) {}

	// ��������
	~LinkedList() {
		clear();
	}

	// ��ӽڵ㵽����ͷ��
	void addAtHead(T data) {
		node<T>* newNode = new node<T>(data);
		newNode->next = head;
		head = newNode;
	}

	// ��ӡ����
	void print() {
		node<T>* current = head;
		while (current != nullptr) {
			current->data.show(); // ����T������һ��show()����
			cout << endl;
			current = current->next;
		}
	}

	// �������
	void clear() {
		while (head != nullptr) {
			node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}

	node<T>* getHead() const {
		return head;
	}

};

///////////////////////
class Test1 {
private:
	string name;
	int num;
public:
	Test1(string name, int num) : name(name), num(num) {}

	void show() {
		cout << "Name: " << name << ", Num: " << num << endl;
	}

	// ���л�����
	string serialize() const {
		return name + "," + to_string(num);
	}

	// ��̬�����л�����
	static Test1 deserialize(const string& data) {
		size_t pos = data.find(',');
		string name = data.substr(0, pos);
		int num = stoi(data.substr(pos + 1));
		return Test1(name, num);
	}

	friend ostream& operator<<(ostream& os, const Test1& obj) {
		os << "Name: " << obj.name << ", Num: " << obj.num;
		return os;
	}

};


	class Test2 {
	private:
		string name;
		int num;
	public:
		Test2(string name, int num) : name(name), num(num) {}

		void show() {
			cout << "Name: " << name << ", Num: " << num << endl;
		}

		// ���л�����
		string serialize() const {
			return name + "," + to_string(num);
		}

		// ��̬�����л�����
		static Test2 deserialize(const string& data) {
			size_t pos = data.find(',');
			string name = data.substr(0, pos);
			int num = stoi(data.substr(pos + 1));
			return Test2(name, num);
		}

		friend ostream& operator<<(ostream& os, const Test2& obj) {
			os << "Name: " << obj.name << ", Num: " << obj.num;
			return os;

		}

	};
	class Test3 {
	private:
		string name;
		int num;
	public:
		Test3(string name, int num) : name(name), num(num) {}

		void show() {
			cout << "Name: " << name << ", Num: " << num << endl;
		}

		// ���л�����
		string serialize() const {
			return name + "," + to_string(num);
		}

		// ��̬�����л�����
		static Test3 deserialize(const string& data) {
			size_t pos = data.find(',');
			string name = data.substr(0, pos);
			int num = stoi(data.substr(pos + 1));
			return Test3(name, num);
		}

		friend ostream& operator<<(ostream& os, const Test3& obj) {
			os << "Name: " << obj.name << ", Num: " << obj.num;
			return os;

		}

	};


template<typename T>
void saveListToFileal(const LinkedList<T>& list, const string& filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		cerr << "�޷����ļ� " << filename << endl;
		return;
	}

	node<T>* current = list.getHead();
	while (current != nullptr) {
		file << current->data.serialize() << endl;
		current = current->next;
	}
	file.close();
	cout << "����ɹ�" << endl;
}

template<typename T>
void loadListFromFileal(LinkedList<T>& list, const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "�޷����ļ� " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		list.addAtHead(T::deserialize(line));
	}
	file.close();
	cout << "���سɹ�" << endl;
}


template<typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& list) {
	node<T>* current = list.getHead();
	while (current != nullptr) {
		os << current->data << endl; // ʹ�����ص� << �����
		current = current->next;
	}
	return os;
}

void menu3()
{
	cout << "1�����²�" << endl;
	cout << "2�鿴�˵�" << endl;
	cout << "5����" << endl;
	cout << "6��ȡ" << endl;
}


void jiaohual()
{
///////////
//����Щ�������Щ�����Զ�����������
 static LinkedList<Test1> list1;
 static LinkedList<Test2> list2;
 static LinkedList<Test3> list3;
////////////

	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "��ѡ������" << endl;
		cout << "1��ʳ 2���� 3��" << endl;
		int inkey;
		cin >> inkey;
		if (inkey == 1)
		{
			
			cout << "�������� ����" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list1.addAtHead(Test1(tempname, tempnum));
		}
		else if (inkey == 2)
		{
			
			cout << "�������� ����" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list2.addAtHead(Test2(tempname, tempnum));

		}
		else if (inkey == 3)
		{
			
			cout << "�������� ����" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list3.addAtHead(Test3(tempname, tempnum));

		}

		break;
	}
		
	case 2:
	{
		cout << "��ѡ��Ԥ��ʳƷ" << endl;
		cout << "1��ʳ 2���� 3��" << endl;
		int key2 = 0;
		cin >> key2;
		if (key2 == 1)
		{
			cout << list1;
		}
		else if (key2 == 2)
		{
			cout << list2;
		}
		else if (key2 == 3)
		{
			cout << list3;
		}

		break;
	}
		
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		saveListToFileal(list1, "list1.txt");
		saveListToFileal(list2, "list2.txt");
		saveListToFileal(list3, "list3.txt");
		break;
	case 6:
		loadListFromFileal(list1, "list1.txt");
		loadListFromFileal(list2, "list1.txt");
		loadListFromFileal(list3, "list1.txt");
		break;
	case 0:
		printf("��лʹ��\n");
		system("cls");
	default:
		system("cls");
		break;

	}

}



void maincai() 
{	
		while (1)
		{	
			menu3();
			jiaohual();
			system("pause");//��ֹ����
			system("cls");//���� 
		}
	
		system("pause");
		return;

}
















