#include<iostream>
#include<fstream>
#include<conio.h>
#include <chrono>
#include <thread>
using namespace std;
#include<string>

///////////////////////////////声明区
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
	base(string name, string sax, int year, int grade)// 构造函数
	{
		this->year = year;
		this->name = name;
		this->grade = grade;
		this->sax = sax;
	}

	virtual void show()//打印函数，父类空实现
	{

	}
	~base()//析构函数
	{
	}
	virtual base* clone() const//解决向链表中传入不是数据而是地址的问题，子类重写开辟新空间存一个新对象并返回出来。拷贝构造函数，const声明
	{
		return new base(*this);
	}

	virtual void setCarceer(string carceer)
	{
		// 空实现，基类没有 carceer 属性
	}//解决后续更改子类carceer的问题

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

	virtual string getcarceer()//假设有carceer属性，随便返回一个不影响方便写链表时写子类的getcarceer
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

class sonA :public base//子类示例
{
public:
	sonA()//无参构造，方便形成对象
	{

	}

	sonA(string name, string sax, int year, int grade, string carceer) :base(name, sax, year, grade)//赋属性
	{
		this->carceer = carceer;
	}
	void show()//重写打印函数
	{
		cout << this->getname() <<" "<< this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonA()//析构函数
	{

	}
	sonA* clone() const override//表明派生类函数旨在覆盖基类函数。 重写子类的拷贝构造函数 override声明
	{
		return new sonA(*this);
	}

	void setCarceer(string carceer)
	{
		this->carceer = carceer;
	}

	
	string getcarceer()//重写getcarceer
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
	void show()//重写打印函数
	{
		cout << this->getname() << " " << this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonB()//析构函数
	{

	}
	sonB* clone() const override//表明派生类函数旨在覆盖基类函数。 重写子类的拷贝构造函数 override声明
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

	string carceer = "人工智能";
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
	void show()//重写打印函数
	{
		cout << this->getname() << " " << this->getsax() << " " << this->getyear() << " " << this->getgrade() << " " << this->carceer << endl;
	}
	~sonC()
	{

	}
	sonC* clone() const override//表明派生类函数旨在覆盖基类函数。  
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

	string carceer = "大数据";
};
 




class Node//实现链表多态必须用数据指针进行调用
{
public:
	base* data;//这里传的就不是数据而是地址了
	Node* next;

};

Node* list = NULL;//头指针

Node* createhead()//头节点函数
{
	Node* headnode = new Node;
	headnode->next = NULL;
	return headnode;
}

//用父类指针，传子类地址。调用实现多态
Node* createnode(const base& obj)//核心函数，通过常引用与拷贝构造解决传入同一片地址的问题。我现在相当于创建对象副本传新的对象
{
	Node* newnode = new Node;
	newnode->data = obj.clone(); // 使用基类中的克隆函数来创建派生类对象的副本
	newnode->next = NULL;
	return newnode;
}

void addnodebyhead(Node* headnode, base& obj)//通过对temp的引用再构造temp副本
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
	while (posnode != NULL && posnode->data->getname() != name)//string name好像不能使用strcmpy
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
	while (posnode != NULL && posnode->data->getname() != name)
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

//析构空间
void deleteList(Node* headNode)
{
	Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		Node* temp = pMove;
		pMove = pMove->next;
		delete temp->data; // 释放节点指向的对象内存
		delete temp; // 释放节点内存
	}
	headNode->next = NULL; // 将头节点的指针域置空
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
	ofstream file("data.txt"); // 打开文件
	if (file.is_open())
	{
		Node* pMove = headNode->next;
		while (pMove != NULL)
		{
			file << pMove->data->getname() << " " << pMove->data->getsax() << " " << pMove->data->getyear() << " " << pMove->data->getgrade() << " " << pMove->data->getcarceer() << endl;
			pMove = pMove->next;
		}
		file.close(); // 关闭文件
		cout << "数据已保存到文件" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}

void loadFromFile(Node* headNode)
{
	ifstream file("data.txt"); // 打开文件
	if (file.is_open())
	{
		string name, sax, carceer;
		int year, grade;
		while (file >> name >> sax >> year >> grade >> carceer)
		{
			if (carceer == "软件工程")
			{
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			else if (carceer == "人工智能")
			{
				sonB temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			else if (carceer == "大数据")
			{
				sonC temp(name, sax, year, grade, carceer);
				addnodebyhead(headNode, temp);
			}
			
		}
		file.close(); // 关闭文件
		cout << "从文件加载数据成功" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}


void menu()
{

	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               管理系统                 " << endl;
	cout << "               0.退出系统" << endl;
	cout << "               1.登记" << endl;
	cout << "               2.浏览库存" << endl;
	cout << "               3.修改信息" << endl;
	cout << "               4.排序" << endl;
	cout << "               5.删除" << endl;
	cout << "               6.查找" << endl;
	cout << "               7.保存到文件" << endl; // 新增选项
	cout << "               8.从文件加载" << endl; // 新增选项
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
	{//不同的类要实现不同的节点添加，创建不同的节点临时对象

		int type;
		cout << "请选择要添加的学生的专业类型：" << endl;
		cout << "1. 软件工程" << endl;
		cout << "2. 人工智能" << endl;
		cout << "3. 大数据" << endl;
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
			result = searchbyname(list,name);
			if (result == NULL)
			{
				printf("无重名已添加\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("名字重复");
			}
			
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
			result = searchbyname(list, name);
			if (result == NULL)
			{
				printf("无重名已添加\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("名字重复");
			}
		}
		else if (type == 3) {
			// 添加 sonC 节点
			int year = 0;
			string name;
			int grade;
			string sax;
			string carceer = "大数据";
			cout << "请输入节点的属性：";
			cout << "name sax year grade " << endl;
			cin >> name >> sax >> year >> grade;
			result = searchbyname(list, name);
			if (result == NULL)
			{
				printf("无重名已添加\n");
				sonA temp(name, sax, year, grade, carceer);
				addnodebyhead(list, temp);
			}
			else
			{
				printf("名字重复");
			}
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
		cin >> tempname;
		modify(list, tempname);
		break;
	}
	case 4:
		printf("排序\n");
		bubblesortlist(list);
		break;
	case 5:
		printf("删除\n");
		printf("请输入删除的名字");
		cin >> tempname;
		deletebyname(list, tempname);
		break;
	case 6:
		printf("查找\n");
		printf("请输入名字：");
		cin >> tempname;
		result = searchbyname(list, tempname);
		if (result == NULL)
			printf("未找到\n");
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
		printf("感谢使用\n");
		exit(0);
	default:
		system("cls");
		break;

	}

}

//操作
void original()
{

	list = createhead();
	while (1) {
		menu();
		jiaohu();
		system("pause");
		system("cls");
	}
	deleteList(list); // 在程序结束前释放所有内存空间
	system("pause");
}

//////总登录
void menufirst()
{
	cout << "*******************************" << endl;
	cout << "*                             *" << endl;
	cout << "*   欢迎使用校园管理系统！    *" << endl;
	cout << "*                             *" << endl;
	cout << "*******************************" << endl;

	cout << endl;
	cout << "正在加载，请稍候";

	// 模拟加载过程，每隔500毫秒输出一个'.'，总共输出10个点
	for (int i = 0; i < 10; ++i) {
		this_thread::sleep_for(chrono::milliseconds(500));  // 暂停500毫秒
		cout << "->";
		cout.flush();  // 刷新输出缓冲区，确保点立即显示
	}

	cout << endl << endl;
	cout << "请选择您的登录身份：" << endl;
	cout << "1. 学生" << endl;
	cout << "2. 管理员" << endl;

}

  
//密码登录
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
			cout << "请输入用户名：";
			cin >> username;

			cout << "请输入密码：";
			password = "";
			char ch;
			while ((ch = _getch()) != '\r') // 按下回车键结束密码输入
			{
				if (ch == '\b') // 如果按下退格键，则删除最后一个字符
				{
					if (password.length() > 0)
					{
						password.pop_back();
						_putch('\b'); // 删除屏幕上的最后一个字符
						_putch(' '); // 用空格覆盖删除的字符
						_putch('\b'); // 再次将光标移动到最后一个字符的位置
					}
				}
				else
				{
					password.push_back(ch);
					_putch('*'); // 在屏幕上显示星号
				}
			}

			// 在这里您可以将输入的用户名和密码与数据库中的信息进行比对验证

			if (username == "admin" && password == "123456")
			{
				isLoggedIn = true;
				cout << endl << "登陆成功！" << endl;
				original();
			}
			else
			{
				loginAttempts++;
				cout << endl << "用户名或密码错误，请重新输入！" << endl;
			}
		}

		if (!isLoggedIn)
		{
			cout << "登陆失败，您已经尝试了3次，请稍后再试！" << endl;
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

//头节点函数
nodecom* createheadcom()
{
	nodecom* headnode = new nodecom;
	headnode->next = NULL;
	return headnode;
}

nodecom* createnodecom(computer data)//创建节点的函数，可以连续使用
{
	nodecom* newnode = new nodecom;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;//返回的是指针
}

//头插法，实现链表的创立链接
void addNodebyheadcom(nodecom* headnode, computer data)
{
	nodecom* newnode = createnodecom(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

//链表打印
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

//查找
nodecom* searchbynum(nodecom* headnode, int num)
{
	nodecom* posnode = headnode->next;
	while (posnode != NULL && posnode->data.getnum()!= num)
	{
		posnode = posnode->next;
	}
	return posnode;
}

//链表的修改
void changecom(nodecom* headnode, int num)
{
	nodecom* posnode = headnode;
	while (posnode != NULL && posnode->data.getnum() != num)
	{
		posnode = posnode->next;
	}
	if (posnode == NULL)
	{
		printf("未查找到");
		return;
	}
	else
	{
		posnode->data.showcom();
		printf("请输入新的信息");
		string changeifuse;
		string changeuser;
		int changenum;
		cin >> changeifuse >> changeuser >> changenum;
		posnode->data.setifuse(changeifuse);
		posnode->data.setuser(changeuser);
		posnode->data.setnum(changenum);
		printf("修改成功");
	}
}

//链表的删除
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

void menucom()
{
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               机房                 " << endl;
	cout << "               1.登记" << endl;
	cout << "               2.浏览库存" << endl;
	cout << "               3.修改信息" << endl;
	cout << "               4.删除" << endl;
	cout << "               5.查找" << endl;
	cout << "               6.保存到文件" << endl; 
	cout << "               7.从文件加载" << endl; 
	cout << "               0.退出系统" << endl;
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
		cout << "链表已成功保存到文件" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}

// 从文件加载链表
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
		cout << "链表已成功从文件加载" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}



////////

//交互
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
		printf("登记\n");
		printf("请输入信息(ifusing user num)\n");
		cin >> tempifuse >> tempuser >> tempnum;
		tempcom.setifuse(tempifuse);
		tempcom.setuser(tempuser);
		tempcom.setnum(tempnum);
		addNodebyheadcom(comlist, tempcom);
		break;
	case 2:
		printf("浏览\n");
		printflistcom(comlist);
		break;
	case 3:
		printf("修改\n");
		printf("请输入目标对象的号码\n");
		cin >> tempnum;
		changecom(comlist, tempnum);
		break;
	case 4:
		printf("删除\n");
		printf("请输入删除的号码");
		cin >> tempnum;
		deletebynum(comlist, tempnum);
		break;
	case 5:
		printf("查找\n");
		printf("请输入号码：");
		cin >> tempnum;
		resultcom = searchbynum(comlist, tempnum);
		if (resultcom == NULL)
			printf("未找到\n");
		else
		{
			printf("是否使用 使用人 号码\n");
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
		printf("感谢使用\n");
		system("cls");
		original();
	default:
		system("cls");
		break;

	}

}

//////////////////////学生注册
void createUser() {
	string username, password;

	cout << "请输入用户名：";
	cin >> username;

	cout << "请输入密码：";
	cin >> password;

	ofstream file("accounts.txt", ios::app);
	file << username << " " << password << endl;
	file.close();

	cout << "账户创建成功！" << endl;
}

bool loginUser() {
	string username, password;

	cout << "请输入用户名：";
	cin >> username;

	cout << "请输入密码：";
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
		system("pause");//防止闪屏
		system("cls");//清屏 
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
		cout << "请选择操作：" << std::endl;
		cout << "1. 创建账户" << std::endl;
		cout << "2. 登录" << std::endl;
		cout << "3. 退出" << std::endl;

		cout << "输入选项：";
		cin >> choice;

		switch (choice) {
		case 1:
			createUser();
			break;

		case 2:
			if (loginUser()) {
				cout << "登录成功！" << endl;
				system("cls");
				cout << "1学生卡查询 2机房预约 3学生对新菜品的申请" << endl;
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
				cout << "用户名或密码错误，请重试。" << endl;
			}
			break;

		case 3:
			system("cls");
			printf("感谢使用\n");
			exit(0);

		default:
			cout << "无效的选项，请重试。" << endl;
			break;
		}
	}

	return 0;
}



////////////////////////////////////
//泛型
//饭卡
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
	int helpnum;//补助
};

class nodecard
{
public:
	card data;
	nodecard* next;

};

nodecard* cardlist = NULL;

//头节点函数
nodecard* createheadcard()
{
	nodecard* headnode = new nodecard;
	headnode->next = NULL;
	return headnode;
}

nodecard* createnodecard(card data)//创建节点的函数，可以连续使用
{
	nodecard* newnode = new nodecard;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;//返回的是指针
}

//头插法，实现链表的创立链接
void addNodebyheadcard(nodecard* headnode, card data)
{
	nodecard* newnode = createnodecard(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

//链表打印
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

//查找//这里可以做泛型 以各种方式去查找




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
	return nullptr; // 如果未找到，则返回nullptr
}

nodecard* searchbycarduser(nodecard* headnode, string user)
{
	return searchbycard<string>(headnode, user);
}
nodecard* searchbycardhelpnum(nodecard* headnode, int helpnum)
{
	return searchbycard<int>(headnode, helpnum);
}



//链表的删除
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

void menucard()
{
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "               校园卡               " << endl;
	cout << "               1.登记" << endl;
	cout << "               2.销户" << endl;
	cout << "               3.查找" << endl;
	cout << "               4.充钱" << endl;
	cout << "               5.保存到文件" << endl;
	cout << "               6.从文件加载" << endl;
	cout << "               0.退出系统" << endl;
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
		cout << "链表已成功保存到文件" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}

// 从文件加载链表
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
		cout << "链表已成功从文件加载" << endl;
	}
	else
	{
		cout << "无法打开文件" << endl;
	}
}



////////

//交互
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
		printf("登记\n");
		printf("请输入信息(user num helpnum)\n");
		cin >> tempuser >> tempnum >> temphelpnum;
		tempcard.setuser(tempuser);
		tempcard.setnum(tempnum);
		tempcard.sethelpnum(temphelpnum);
		addNodebyheadcard(cardlist, tempcard);
		break;
	case 2:
		printf("删除\n");
		printf("请输入删除的名字");
		cin >> tempuser;
		deletebycarduser(cardlist, tempuser);
		break;
	case 3:
		printf("查找\n");
		printf("按照名字查找1 补助金额查找2");
			int poke;
			cin >> poke;
			if (poke == 1)
			{
				printf("请输入名字：");
				cin >> tempuser;
				resultcard = searchbycarduser(cardlist, tempuser);
				if (resultcard == NULL)
					printf("未找到\n");
				else
				{
					printf(" 使用人 金额 补助\n");
					resultcard->data.showcard();
				}
			}

			if (poke == 2)
			{
				printf("请输入补助金额：");
				cin >> temphelpnum;
				resultcard = searchbycardhelpnum(cardlist, temphelpnum);
				if (resultcard == NULL)
					printf("未找到\n");
				else
				{
					printf(" 使用人 金额 补助\n");
					resultcard->data.showcard();
				}

			}

		break;
	case 4:
		printf("请输入要充值的账户名字：");
		cin >> tempuser;
		float addnum;
		resultcard = searchbycarduser(cardlist, tempuser);
		if (resultcard == NULL) {
			printf("未找到该账户\n");
		}
		else {
			printf("请输入要充值的金额：");
			cin >> addnum;
			float currentAmount = resultcard->data.getnum();
			float newAmount = currentAmount + addnum;
			resultcard->data.setnum(newAmount);
			printf("充值成功，当前余额为：%f\n", newAmount);
		}
		break;
	case 5:
		saveToFilecard(cardlist, filenamecard);
		break;
	case 6:
		loadFromFilecard(cardlist, filenamecard);
		break;
     case 0:
		printf("感谢使用\n");
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
		system("pause");//防止闪屏
		system("cls");//清屏 
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
	T data; // 存储的数据
	node* next; // 指向下一个节点的指针

	// 构造函数
	node(T data) : data(data), next(nullptr) {}
};


template<typename T>
class LinkedList {
private:
	node<T>* head; // 链表的头节点

public:
	// 构造函数
	LinkedList() : head(nullptr) {}

	// 析构函数
	~LinkedList() {
		clear();
	}

	// 添加节点到链表头部
	void addAtHead(T data) {
		node<T>* newNode = new node<T>(data);
		newNode->next = head;
		head = newNode;
	}

	// 打印链表
	void print() {
		node<T>* current = head;
		while (current != nullptr) {
			current->data.show(); // 假设T类型有一个show()方法
			cout << endl;
			current = current->next;
		}
	}

	// 清除链表
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

	// 序列化方法
	string serialize() const {
		return name + "," + to_string(num);
	}

	// 静态反序列化方法
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

		// 序列化方法
		string serialize() const {
			return name + "," + to_string(num);
		}

		// 静态反序列化方法
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

		// 序列化方法
		string serialize() const {
			return name + "," + to_string(num);
		}

		// 静态反序列化方法
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
		cerr << "无法打开文件 " << filename << endl;
		return;
	}

	node<T>* current = list.getHead();
	while (current != nullptr) {
		file << current->data.serialize() << endl;
		current = current->next;
	}
	file.close();
	cout << "保存成功" << endl;
}

template<typename T>
void loadListFromFileal(LinkedList<T>& list, const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "无法打开文件 " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		list.addAtHead(T::deserialize(line));
	}
	file.close();
	cout << "加载成功" << endl;
}


template<typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& list) {
	node<T>* current = list.getHead();
	while (current != nullptr) {
		os << current->data << endl; // 使用重载的 << 运算符
		current = current->next;
	}
	return os;
}

void menu3()
{
	cout << "1增加新菜" << endl;
	cout << "2查看菜单" << endl;
	cout << "5保存" << endl;
	cout << "6读取" << endl;
}


void jiaohual()
{
///////////
//有哪些类就有哪些对象自定义生成链表
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
		cout << "请选择类型" << endl;
		cout << "1主食 2炒菜 3汤" << endl;
		int inkey;
		cin >> inkey;
		if (inkey == 1)
		{
			
			cout << "输入名字 数量" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list1.addAtHead(Test1(tempname, tempnum));
		}
		else if (inkey == 2)
		{
			
			cout << "输入名字 数量" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list2.addAtHead(Test2(tempname, tempnum));

		}
		else if (inkey == 3)
		{
			
			cout << "输入名字 数量" << endl;
			string tempname;
			int tempnum = 0;
			cin >> tempname >> tempnum;
			list3.addAtHead(Test3(tempname, tempnum));

		}

		break;
	}
		
	case 2:
	{
		cout << "请选择预制食品" << endl;
		cout << "1主食 2炒菜 3汤" << endl;
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
		printf("感谢使用\n");
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
			system("pause");//防止闪屏
			system("cls");//清屏 
		}
	
		system("pause");
		return;

}
















