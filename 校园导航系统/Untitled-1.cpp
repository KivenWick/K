
#include"iostream"
#include <map>//存地点编号
#include<vector>//容器，存节点
#include<string>
#include <queue>//队列，实现广度优先遍历

#include <climits>//无穷大的数，迪杰斯特拉
#include<algorithm>//用sort排序,每次排序后求出最小的值

using namespace std;


struct place
{
	string name;
	
};

class arc
{
public:
	bool mark;
	int weight;
	int tailvex, headvex;
	arc* headedge;//第二个节点的弧表
	arc* tailedge;//第一个节点的弧表

	arc() :tailvex(), headvex(), headedge(nullptr), tailedge(nullptr), weight(0),mark(false) {}

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
			arc* newarc1 = new arc;
			arc* newarc2 = new arc;

			// 获取 vector 中的节点索引
			int index1 = onemap[name1] - 1;
			int index2 = onemap[name2] - 1;

			newarc1->tailvex = index1;
			newarc1->headvex = index2;
			newarc1->weight = weight;
			newarc1->tailedge = array[index1].firstedge;
			array[index1].firstedge = newarc1;

			newarc2->tailvex = index2;
			newarc2->headvex = index1;
			newarc2->weight = weight;
			newarc2->tailedge = array[index2].firstedge;
			array[index2].firstedge = newarc2;
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
		if (edge == nullptr) {
			return nullptr;
		}

		int nextIndex = edge->headvex; // 获取弧连接的下一个节点的索引
		if (nextIndex >= 0 && nextIndex < index) {
			return &array[nextIndex]; // 返回下一个节点的指针
		}
		else {
			return nullptr; // 弧连接的下一个节点索引无效，返回空指针
		}
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
	void nodemark() {
		// 遍历所有节点
		for (int j = 0; j < index; j++) {
			// 将当前节点标记为未访问
			array[j].mark = false;

			// 遍历当前节点的所有边
			arc* p = array[j].firstedge;
			while (p != nullptr) {
				// 检查p是否为空
				
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

	void printA()
	{
		for (int j = 0; j < index; j++)
		{
			cout << array[j].firstedge << endl;

	    }
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
					cout << edge->weight << endl;
					edge = edge->tailedge;
					
				}
				break;
			}

		}



	}


void Dijkstra(const string& startNodeName) {
    unordered_map<string, int> distance; // 存储起点到各节点的距离
    unordered_map<string, string> path; // 存储路径
    // 初始化距离，起点距离为0，其他节点距离初始化为无穷大
    for (auto& n : array) {
        distance[n.data.name] = INT_MAX;
        path[n.data.name] = "";
    }
    distance[startNodeName] = 0;
    // 用于标记节点是否已被访问
    vector<bool> visited(index, false);
    // 迭代找到最短路径
    for (int i = 0; i < index; i++) {
        int minDistance = INT_MAX;
        string minNode = "";
        // 找到当前距禧起点最近的节点
        for (auto& n : array) {
            if (!visited[n.nodeidex] && distance[n.data.name] < minDistance) {
                minDistance = distance[n.data.name];
                minNode = n.data.name;
            }
        }
        if (minNode.empty()) {
            break; // 所有节点已被访问
        }
        // 标记当前节点为已访问
        visited[onemap[minNode] - 1] = true;
        // 更新相邻节点的距离
        arc* currentEdge = find_if(findNodereturn(minNode)->firstedge, [](const arc* a) { return a != nullptr; })->tailedge;
        while (currentEdge != nullptr) {
            node* nextNode = getNextNode(currentEdge);
            if (nextNode != nullptr && !visited[nextNode->nodeidex]) {
                int newDistance = distance[minNode] + currentEdge->weight;
                if (newDistance < distance[nextNode->data.name]) {
                    distance[nextNode->data.name] = newDistance;
                    path[nextNode->data.name] = minNode;
                }
            }
            currentEdge = currentEdge->tailedge;
        }
    }
    // 输出最短路径
    for (auto& node : path) {
        cout << "Shortest path from " << startNodeName << " to " << node.first << " is :";
        string currentNode = node.first;
        while (!currentNode.empty()) {
            cout << currentNode << " <- ";
            currentNode = path[currentNode];
        }
        cout << "Distance: " << distance[node.first] << endl;
    }
}










};
	//实现最短路径后提供地图类和文件
	//将地图导入文件，然后将功能包装
	//然后最终目的是实现数据库和easyx界面 
	//两点之间出行工具
	//拥挤程度，红绿灯
	//道路维修，地点维修（删除）




int main()
{
	buildmap Map;
	place a;
	place b;
	place c;
	place d; 
	place e;
	place f;
	place g;
	place h;


	a.name = "1教";
	b.name = "2教";
	c.name = "3教";
	d.name = "4教";
	e.name = "5教";
	f.name = "6教";
	g.name = "7教";
	h.name = "8教";


	Map.addnode(a);
	Map.addnode(b);
	Map.addnode(c);
	Map.addnode(d);
	Map.addnode(e);
	Map.addnode(f);
	Map.addnode(g);
	Map.addnode(h);



	Map.addarc("1教", "2教",20);
	Map.addarc("1教", "3教", 10);
	Map.addarc("2教", "4教", 32);
	Map.addarc("2教", "5教", 15);   
	Map.addarc("3教", "6教", 15);
	Map.addarc("3教", "7教", 20);
	Map.addarc("6教", "7教", 30);
	Map.addarc("4教", "8教", 5);
	Map.addarc("5教", "8教", 17);

	Map.print();
	cout << endl;
	Map.deepfind(Map.getarray());
	
	//Map.printA();
	cout << endl;
    Map.nodemark();
	//Map.BFS("1教");
	//Map.dijkstra("4教");
	Map.printarc("4教");
	


	return 0;

}



