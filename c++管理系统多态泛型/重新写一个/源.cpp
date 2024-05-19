
#include<iostream>
#include<fstream>
using namespace std;
#include<string>

//进行文件操作，并对项目进行套壳完善功能
//多态的选择
//细节修改，功能添加
//学生管理系统




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
	virtual base* clone() const//解决向链表中传入不是数据而是地址的问题，子类重写开辟新空间存一个新对象并返回出来。
	{
		return new base(*this);
	}

	virtual void setCarceer(string carceer)
	{
		// 空实现，基类没有 carceer 属性
	}//解决后续更改子类carceer的问题

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
	sonA* clone() const override//表明派生类函数旨在覆盖基类函数。  
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

	string carceer = "软件工程";
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
	sonB* clone() const override//表明派生类函数旨在覆盖基类函数。  
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

	string carceer = "人工智能";
};



class Node
{
public:
	base* data;
	Node* next;

};

Node* list = NULL;




Node* createhead()//头节点函数
{
	Node* headnode = new Node;
	headnode->next = NULL;
	return headnode;
}

//用父类指针，传子类地址。调用实现多态
Node* createnode(const base& obj)
{
	Node* newnode = new Node;
	newnode->data = obj.clone(); // 使用基类中的克隆函数来创建派生类对象的副本
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

// 查找
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
		printf("未找到节点\n");
		return;
	}
	else {
		printf("原节点内容：\n");
		posnode->data->show();
		printf("\n请输入新的信息：\n");
		string newname;
		string newsax;
		int newyear;
		int newgrade;;

		cin >> newname >> newsax >> newyear >> newgrade;
		posnode->data->setyear(newyear);
		posnode->data->setname(newname);
		posnode->data->setsax(newsax);
		posnode->data->setgrade(newgrade);
		//printf("是否需要修改类别");
		//printf("是 1   否 2\n");
		//int i = 0;
		//cin >> i;
		//if (i == 1)
		//{
		//	string carceer;
		//	cin >> carceer;
		//	posnode->data->setCarceer(carceer); // 修改派生类对象的 grade 属性
		//}
		printf("修改成功\n");
	}
}


//链表的删除
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
		printf("未查找到");
		return;
	}
	else//查找到目标 
	{
		printf("删除成功");
		leftposnode->next = posnode->next;//这是一个链接操作，将目标右边节点的地址赋值给目标左边的指针域，然后释放目标节点 
		free(posnode);
		posnode = NULL;//架空，防止数据泄露 
	}

}


//按照英语成绩排序
void bubblesortlist(Node* headNode) 
{
	Node* p;
	Node* q;
	for (p = headNode->next; p != NULL; p = p->next)
	{
		for (q = headNode->next; q->next != NULL; q = q->next)//当P动一次的时候Q需要向前一直遍历直到查找到目标 
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


//存文件操作

void saveToFile(Node* headnode, const string& filename) {
	ofstream fout(filename);
	if (!fout) {
		cout << "文件打开失败" << endl;
		return;
	}

	Node* pMove = headnode->next;
	while (pMove != NULL) {
		fout << pMove->data->name << " ";
		fout << pMove->data->sax << " " ;
		fout << pMove->data->year << " ";
		fout << pMove->data->grade << " ";
		fout << pMove->data->getcarceer();  // 假设有 carceer 属性
		pMove = pMove->next;
	}

	fout.close();
	cout << "数据保存成功" << endl;
}


//读文件操作从下一次打开程序将上一次存入文件的数据加载进程序中，生成链表

void loadFromFile(Node* headnode, const string& filename) {
	ifstream fin(filename);
	if (!fin) {
		cout << "文件打开失败" << endl;
		return;
	}

	string name;
	string sax;
	int year;
	int grade;
	string carceer;

	while (fin >> name >> sax >> year >> grade >> carceer) {
		if (carceer == "软件工程") {
			sonA tempa(name, sax, year, grade, carceer);
			addnodebyhead(headnode, tempa);
		}
		else if (carceer == "人工智能") {
			sonB tempb(name, sax, year, grade, carceer);
			addnodebyhead(headnode, tempb);
		}
	}

	fin.close();
	cout << "数据加载成功" << endl;
}


void menu()//做个页面 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               管理系统                 \n");
	printf("               0.退出系统\n");
	printf("               1.登记\n");
	printf("               2.浏览库存\n");
	printf("               3.修改信息\n");
	printf("               4.排序\n");
	printf("               5.删除\n");
	printf("               6.查找\n");
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
			cout << "请选择要添加的节点类型：" << endl;
			cout << "1. sonA" << endl;
			cout << "2. sonB" << endl;
			cin >> type;

			if (type == 1) {
				// 添加 sonA 节点
				int year;
				string name;
				int grade;
				string sax;
				string carceer = "软件工程";
				cout << "请输入节点的属性：";
				cout << "name sax year grade " << endl;
				cin >> name >> sax >> year >> grade;
				sonA temp(name,sax,year,grade,carceer);
				addnodebyhead(list, temp);
				saveToFile(list, "data.txt");
			}
			else if (type == 2) {
				// 添加 sonB 节点
				int year = 0;
				string name;
				int grade;
				string sax;
				string carceer = "人工智能";
				cout << "请输入节点的属性：";
				cout << "name sax year grade " << endl;
				cin >> name >> sax >> year >> grade;
				sonB temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
				saveToFile(list, "data.txt");
			}
			else {
				cout << "无效的选择" << endl;
			}
			break;
		}
	case 2:
		printf("浏览\n");
		printflist(list);
		break;
	case 3:
	{
		printf("修改\n");
		printf("请输入目标对象的名字\n");
		cin >> temp.name;
		modify(list, temp.name);
		// 更新对应节点的数据到文件中
		saveToFile(list, "data.txt");
		break;
	}
	case 4:
		printf("排序\n");
		bubblesortlist(list);
		break;
	case 5:
		printf("删除\n");
		printf("请输入删除的名字");
		cin >> temp.name;
		deletebyname(list, temp.name);
		// 从文件中删除对应的数据
		saveToFile(list, "data.txt");
		break;
	case 6:
		printf("查找\n");
		printf("请输入名字：");
		cin >> temp.name;
		result = searchbyname(list, temp.name);
		if (result == NULL)
			printf("未找到\n");
		else
		{
			printf("\n");
			result->data->show();
		}
		break;
	case 0:
		printf("感谢使用\n");
		exit(0);
	default:
		system("cls");
		break;

	}


}

//测试函数调用
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
	
	// 从文件加载数据到链表

	loadFromFile(list, "data.txt");


	while (1) {
		menu();
		jiaohu();
		system("pause");
		system("cls");
	}

	// 保存数据到文件
	saveToFile(list, "data.txt");

	

	system("pause");
	return;

}










































































