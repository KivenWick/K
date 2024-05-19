
#include"iostream"
#include <map>//存地点编号
#include<vector>//容器，存节点
#include<string>
#include <queue>//队列，实现广度优先遍历
#include <conio.h>
#include <climits>//无穷大的数，迪杰斯特拉
#include<algorithm>//用sort排序,每次排序后求出最小的值
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;


//声明区
void jiaohu1();
void jiaohu3();



struct place
{
	string name;
	
};



class node;

class arc
{
public:
	bool mark;
	int weight;
	int tailvex, headvex;
	arc* headedge;//第二个节点的弧表
	arc* tailedge;//第一个节点的弧表
	node* nextN;
	node* lastN;

	arc() :tailvex(), headvex(), headedge(nullptr), tailedge(nullptr), weight(0),mark(false),nextN(nullptr),lastN(nullptr) {}

}; 



class node
{
public:
	place data;
	arc* firstedge;//边表
	bool mark;//是否被访问
	int nodeidex;
	

	node(place data) :data(data), firstedge(nullptr),mark(false),nodeidex(0){}

	node() {};

};




class buildmap
{


private:
	vector<node> array;//存节点的容器
	map<string, int> onemap;//存地点匹配的序号，实现迪杰斯特拉算法
	int index;//记录容量的大小
	int i = 0;//存map里做每一个节点的序号

public:
	






	buildmap():array(),onemap(),index(0){}


	//添加节点
	void addnode(place Place)
	{
		this->index++;
		re_array(this->index);//数组长度调整
		node newnode(Place);
		newnode.nodeidex = i;
		array[i] = newnode;//nmd 节点添加不要使用push_back，你已经开了两个空间（resize）。用push是添加到两个空间之后了
		i++;
		onemap[Place.name] = i;

	}

	
	//调整容器长度
	void re_array(int index)
	{
		array.resize(index+1);//vector的动态调整
	}


	//查找地点是否存在的函数
	bool findNodeByName(string name) {
		for (auto& n : array) {
			if (n.data.name == name) {
				return true;
			}
		}
		return false; // 没找到  
	}

	//查找地点是否存在，如果存在，将该节点返回出来的函数
	node* findNodereturn(string name) {
		for (auto& n : array) {
			if (n.data.name == name) {
				return &n;
			}
		}
		return nullptr; // 如果没找到，则返回空指针
	}

	void addarc(const string& name1, const string& name2, int weight)
	{
		// 检查两个地点是否存在
		if (findNodeByName(name1) && findNodeByName(name2))
		{
			node* node1 = findNodereturn(name1);
			node* node2 = findNodereturn(name2);

			arc* newarc1 = new arc;
			arc* newarc2 = new arc;

			newarc1->tailvex = node1->nodeidex;
			newarc1->headvex = node2->nodeidex;
			newarc1->weight = weight;
			newarc1->tailedge = node1->firstedge;
			node1->firstedge = newarc1;
			newarc1->nextN = findNodereturn(name2);
			newarc1->lastN = findNodereturn(name1);

			newarc2->tailvex = node2->nodeidex;
			newarc2->headvex = node1->nodeidex;
			newarc2->weight = weight;
			newarc2->tailedge = node2->firstedge;
			node2->firstedge = newarc2;
			newarc2->nextN = findNodereturn(name1);
			newarc2->lastN = findNodereturn(name2);

		}
		else
		{
			cout << "地点不存在" << endl;
		}
	}

	void print()
	{
		cout << "地点的名称:" << endl;
		for (auto& j:array)
		{
			cout << j.data.name << endl;
			
		}

	}


	// 通过弧遍历到下一个节点
	node* getNextNode(arc* edge) {
		if (edge == nullptr || edge->nextN == nullptr) {
			return nullptr;
		}

		return edge->nextN;
	}

	//深度优先遍历，广度优先遍历

	void deepfind(node* currentNode)//能用
	{
		// 标记当前节点为已访问
		currentNode->mark = true;
		cout << "访问节点：" << currentNode->data.name << endl;

		// 遍历当前节点的邻接节点
		arc* edge = currentNode->firstedge;
		while (edge != nullptr)
		{
			// 获取邻接节点
			node* nextNode = getNextNode(edge);
			if (nextNode != nullptr && !nextNode->mark)
			{
				// 递归访问未被访问过的邻接节点
				deepfind(nextNode);
			}
			// 移动到下一条弧
			edge = edge->tailedge;
		}

		// 回溯到上一个节点
		if (currentNode->firstedge != nullptr && currentNode->firstedge->tailedge != nullptr)
		{
			node* prevNode = &array[currentNode->firstedge->tailvex];
			if (!prevNode->mark)
			{
				deepfind(prevNode);//一直递归回退到仍有边可以访问的节点
			}
		}
	}


	//广度优先遍历
	void BFS(string startNodeName) 
	{
    // 找到起始节点
    node* startNode = findNodereturn(startNodeName);
    if (startNode == nullptr) {
        cout << "起始地点不存在" << endl;
        return;
    }

    // 创建一个队列来实现广度优先遍历
    queue<node*> q;

    // 将起始节点标记为已访问并加入队列
    startNode->mark = true;
    q.push(startNode);

    while (!q.empty()) //如果队列不为空
	{
        // 取出队列的第一个节点
        node* currentNode = q.front();
        q.pop();

        // 访问当前节点（这里可以进行相关操作）
        cout << "访问节点: " << currentNode->data.name << endl;

        // 遍历当前节点的所有邻接弧
        arc* currentEdge = currentNode->firstedge;
        while (currentEdge != nullptr) 
		{
            // 获取连接的下一个节点
            node* nextNode = getNextNode(currentEdge);

            // 如果下一个节点未被访问过
            if (nextNode != nullptr && !nextNode->mark)
			{
                // 将其标记为已访问并加入队列
                nextNode->mark = true;
                q.push(nextNode);
            }

            // 移动到下一个弧
            currentEdge = currentEdge->tailedge;
        }
    }

    // 遍历结束后，重置所有节点的标记
   
}

	//更新节点是否被访问，更新弧是否被访问
	void nodemark()
	{
		// 遍历所有节点
		for (int i = 0; i < index; i++)
		{
			node* n = &array[i];
			// 将当前节点标记为未访问
			n->mark = false;

			// 遍历当前节点的所有边
			arc* p = n->firstedge;
			while (p != nullptr)
			{
				// 将当前边标记为未访问
				p->mark = false;

				// 移动到下一条边
				p = p->tailedge;
			}
		}
	}

	//返回数组的地址，供深度搜索使用
	node* getarray()
	{
		return &array[0];
	}

	

	//传节点打印他的所有边
	void printarc(string name)
	{
		for (auto n : array)
		{
			if (n.data.name == name)
			{
				arc* edge = n.firstedge;
				while (edge!=nullptr)
				{
					cout << "从" << edge->lastN->data.name << "到" << edge->nextN->data.name << "有" << edge->weight << "那么远" << endl;
					edge = edge->tailedge;	
				}
				break;
			}

		}



	}

	void dijkstra(string startNodeName,string name2)
	{
		// 找到起始节点
		node* startNode = findNodereturn(startNodeName);
		if (startNode == nullptr) {
			cout << "起始地点不存在" << endl;
			return;
		}

		// 初始化距离数组和优先队列
		vector<int> distances(index, INT_MAX);
		distances[startNode->nodeidex] = 0;//nodeidex元素下标
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({ 0, startNode->nodeidex });

		// 迪杰斯特拉算法
		while (!pq.empty())
		{
			// 取出当前最小距离节点
			int currentNodeIndex = pq.top().second;
			pq.pop();
			node* currentNode = &array[currentNodeIndex];

			// 如果当前节点已被处理，跳过
			if (currentNode->mark)
				continue;

			// 标记当前节点为已处理
			currentNode->mark = true;

			// 遍历当前节点的所有邻接节点
			arc* currentEdge = currentNode->firstedge;
			while (currentEdge != nullptr)
			{
				// 获取连接的下一个节点
				node* nextNode = getNextNode(currentEdge);

				// 计算通过当前节点到达邻接节点的总距离
				int distanceThroughCurrentNode = distances[currentNodeIndex] + currentEdge->weight;

				// 如果这个距离小于邻接节点的已知最短距离
				if (distanceThroughCurrentNode < distances[nextNode->nodeidex])
				{
					// 更新邻接节点的最短距离
					distances[nextNode->nodeidex] = distanceThroughCurrentNode;
					// 将邻接节点插入优先队列
					pq.push({ distanceThroughCurrentNode, nextNode->nodeidex });
				}

				// 移动到下一条边
				currentEdge = currentEdge->tailedge;
			}
		}

		
		


		
		cout << startNodeName << "到" << name2 << "的最短距离为" << distances[onemap[name2] - 1];


	}

	void delatenode(string name)
	{
		// 首先找到要删除的节点
		node* nodeToDelete = nullptr;
		for (auto& n : array)
		{
			if (n.data.name == name)
			{
				nodeToDelete = &n;
				break;
			}
		}

		if (nodeToDelete == nullptr)
		{
			cout << "节点 " << name << " 不存在于图中。" << endl;
			return;
		}

		// 记录要删除节点的索引，用于后续更新其他节点的边
		int deleteIndex = nodeToDelete->nodeidex;

		// 遍历所有节点，删除所有指向nodeToDelete的边
		for (int i=0;i<index;i++)
		{
			node* n = &array[i];
			cout << "*" << n->nodeidex << endl;
			arc* currentEdge = n->firstedge;
			while (currentEdge != nullptr)
			{
				arc* nextEdge = currentEdge->tailedge;
				



				if (currentEdge->headvex == deleteIndex || currentEdge->tailvex == deleteIndex)
				{
					
						// 如果是第一条边
						if (currentEdge == n->firstedge)
						{
							n->firstedge = nextEdge;
						}
						// 如果是中间的边
						else if (nextEdge != nullptr)
						{
							currentEdge->tailedge->headedge = currentEdge->headedge;
							currentEdge->headedge->tailedge = currentEdge->tailedge;
						}

						// 释放当前边的内存
						cout << endl;
						cout << currentEdge->weight << endl;
						delete currentEdge;
						currentEdge = nextEdge; // 在删除后更新currentEdge，防止访问空指针
					
					
				}
				else
				{
					// 如果当前边与待删除节点无关，继续遍历
					currentEdge = nextEdge;
				}

			}
		}

		// 从数组中移除节点
		auto it = find_if(array.begin(), array.end(), [&](const node& n) { return n.data.name == name; });
		if (it != array.end())
		{
			array.erase(it);
		}

		
		index--;




		// 更新onemap，移除对应的条目
		onemap.erase(name);

		// 缩小数组大小，以反映节点数量的变化
		array.resize(array.size());
	}

	// 保存节点到文件
	void saveNodesToFile(const std::string& filename) {
		std::ofstream outFile(filename, std::ios_base::trunc); // 添加trunc标志
		if (!outFile.is_open()) {
			std::cerr << "无法打开文件进行写入节点: " << filename << std::endl;
			return;
		}

		for (int i = 0; i < index;i++) 
		{
			node* node = &array[i];
			outFile << node->data.name << "\n";
		}
		outFile.close();
	}

	// 保存边到文件
	void saveArcsToFile(const string& filename) {
		ofstream outFile(filename, ios_base::trunc);
		if (!outFile.is_open()) {
			cerr << "无法打开文件进行写入边: " << filename << endl;
			return;
		}

		set<pair<string, string>> writtenEdges; // 存储已写入的边

		for (int i = 0; i < index; i++) {
			node* node = &array[i];
			arc* edge = node->firstedge;
			while (edge != nullptr) {
				if (edge->nextN != nullptr) {
					// 检查边是否已写入
					string edgeKey = std::min(edge->lastN->data.name, edge->nextN->data.name) + "," + std::max(edge->lastN->data.name, edge->nextN->data.name);
					if (writtenEdges.find({ edge->lastN->data.name, edge->nextN->data.name }) == writtenEdges.end()) {
						writtenEdges.insert({ edge->lastN->data.name, edge->nextN->data.name });
						outFile << node->data.name << " " << edge->nextN->data.name << " " << edge->weight << "\n";
					}
				}
				edge = edge->tailedge;
			}
		}
		outFile.close();
	}

	void loadFromFile(const string& nodesFilename, const string& arcsFilename) {
		// 先读取节点文件
		ifstream nodeFile(nodesFilename);
		if (!nodeFile.is_open()) {
			cerr << "无法打开节点文件进行读取: " << nodesFilename << endl;
			return;
		}

		clear();

		string nodeName;
		while (getline(nodeFile, nodeName)) {
			addnode({ nodeName });
		}
		nodeFile.close();

		// 再读取边文件
		ifstream arcFile(arcsFilename);
		if (!arcFile.is_open()) {
			cerr << "无法打开边文件进行读取: " << arcsFilename << endl;
			return;
		}

		string startNode, endNode, weightStr;
		while (getline(arcFile, startNode, ' ') && getline(arcFile, endNode, ' ') && getline(arcFile, weightStr)) {
			int weight = stoi(weightStr);
			addarc(startNode, endNode, weight);
		}
		arcFile.close();
	}

	void clear() {
		array.clear();
		onemap.clear();
		index = 0;
		i = 0;
	}

	

};
	//实现最短路径后提供地图类和文件
	//将地图导入文件，然后将功能包装
	//然后最终目的是实现数据库和easyx界面 
	//两点之间出行工具
	//拥挤程度，红绿灯
	//道路维修，地点维修（删除）

//全局图
buildmap Map;






void menu1()//做个页面 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               校园导航系统                 \n");
	printf("               请选择身份\n");
	printf("               1 用户\n");
	printf("               2 管理员\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

}

void menu2()
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               校园导航系统                 \n");
	printf("               1 学校简介\n");
	printf("               2 查询两点最短距离\n");
	//printf("               *3 查询地点信息\n");
	//printf("               4 建议出行方式（还没做出来）\n");
	printf("               0 返回\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
}

void menu3()
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               校园导航系统                 \n");
	printf("               1 增加地点\n");
	printf("               2 增加路\n");
	//printf("               3 *删除地点\n");
	//printf("               4 *删除路\n");
	printf("               5 DFS\n");
	printf("               6 BFS\n");
	printf("               7 打印地点\n");
	printf("               8 打印地点周边路径\n");
	//printf("               8 *修改弧（用特殊遍历）\n");
	printf("               9 前往用户系统\n");
	printf("               10 系统退出\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
}

void jiaohu2()
{
	
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "南阳理工好，南阳理工妙" << endl;
		cout<<  "教的真的好" << endl;
		cout << "男人学了发神金" << endl;
		cout << "女人看了来月经" << endl;
		cout << "这学校是抑郁症的克星" << endl;
		cout << "是植物人的闹钟" << endl;
		cout << "教出了村里五保户对寡妇的思念和爱而不得的心情" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << " 纯属玩梗，学校还是很不错的。就是学校简介太长我懒得打啦" << endl;

		break;
	}

	case 2:
	{
		cout << "请输入所查找的两个目标点" << endl;
		string name1, name2;
		cin >> name1 >> name2;
		Map.dijkstra(name1, name2);
		Map.nodemark();
		break;
	}

	case 3:
	{
		break;
	}

	case 4:
	{
		break;
	}
	case 0:
	{
		system("cls");
		menu1();
		jiaohu1();
	}

	default:
		system("cls");
		break;

	}

}

void showProgressBar() {
	cout << "登录中: ";
	for (int i = 0; i < 50; i++) {
		cout << "|";
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	cout << " 完成\n";
}

void keyword() {
	string username, password;
	char ch;

	cout << "欢迎来到密码登录系统\n";

	cout << "请输入用户名: ";
	cin >> username;

	cout << "请输入密码: ";
	ch = _getch();
	while (ch != 13) {  // 13代表回车键
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	cout << endl;

	if (username == "sly" && password == "123456") {
		showProgressBar();
		cout << "登录成功！欢迎回来，admin。\n";
		while (1)
		{
			
			menu3();
			jiaohu3();
			system("pause");//防止闪屏
			system("cls");//清屏 
		}
		

	}
	else {
		cout << "登录失败，请检查用户名和密码。\n";
		system("cls");
		keyword();
	}

	return;
}


void jiaohu1()
{

	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		system("cls");
		while (1)
		{
			
			menu2();
			jiaohu2();
			system("pause");//防止闪屏
			system("cls");//清屏 
		}
		break;
	}

	case 2:
	{
		//调用登录
		keyword();
		break;
	}


	default:
		system("cls");
		break;

	}

}


void jiaohu3()
{
	
	int key = 0;
	scanf_s("%d", &key);
	switch (key)
	{
	case 1:
	{
		cout << "请输入地点名进行添加" << endl;
		string name;
		
		cin >> name;
		place v;
		v.name = name;
		
		Map.addnode(v);
		break;
	}

	case 2:
	{
		cout << "请输入两个目标地点以及距离添加路径" << endl;
		string name1, name2;
		int weight;
		cin >> name1 >> name2 >> weight;
		Map.addarc(name1, name2,weight);
		break;
	}


	case 3:
	{
		break;
	}


	case 4:
	{
		break;
	}


	case 5:
	{
		Map.deepfind(Map.getarray());
		Map.nodemark();
		break;
	}


	case 6:
	{
		cout << "请输入地点进行广度优先搜索" << endl;
		string name;
		cin >> name;
		Map.BFS(name);
		Map.nodemark();
		break;
	}
	case 7:
	{
		Map.print();
		break;
	}
	case 8:
	{
		cout << "请输入目标地点" << endl;
		string name;
		cin >> name;
		Map.printarc(name);
		break;
	}
	case 9:
	{
		system("cls");
		while (1)
		{

			menu2();
			jiaohu2();
			system("pause");//防止闪屏
			system("cls");//清屏 
		}

		Map.saveNodesToFile("node_data.text");
		Map.saveArcsToFile("arc_data.text");
		break;
	}

	case 10:
	{
		Map.saveNodesToFile("node_data.text");
		Map.saveArcsToFile("arc_data.text");
		exit(0);
		break;
	}







	default:
		system("cls");
		break;

	}

	

}





void main()
{

	

	Map.loadFromFile("node_data.text", "arc_data.text");
		menu1();
		jiaohu1();
		system("pause");//防止闪屏
		system("cls");//清屏 
	

	


	system("pause");

}



