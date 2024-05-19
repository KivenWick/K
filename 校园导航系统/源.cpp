
#include"iostream"
#include <map>//��ص���
#include<vector>//��������ڵ�
#include<string>
#include <queue>//���У�ʵ�ֹ�����ȱ���
#include <conio.h>
#include <climits>//�����������Ͻ�˹����
#include<algorithm>//��sort����,ÿ������������С��ֵ
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;


//������
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
	arc* headedge;//�ڶ����ڵ�Ļ���
	arc* tailedge;//��һ���ڵ�Ļ���
	node* nextN;
	node* lastN;

	arc() :tailvex(), headvex(), headedge(nullptr), tailedge(nullptr), weight(0),mark(false),nextN(nullptr),lastN(nullptr) {}

}; 



class node
{
public:
	place data;
	arc* firstedge;//�߱�
	bool mark;//�Ƿ񱻷���
	int nodeidex;
	

	node(place data) :data(data), firstedge(nullptr),mark(false),nodeidex(0){}

	node() {};

};




class buildmap
{


private:
	vector<node> array;//��ڵ������
	map<string, int> onemap;//��ص�ƥ�����ţ�ʵ�ֵϽ�˹�����㷨
	int index;//��¼�����Ĵ�С
	int i = 0;//��map����ÿһ���ڵ�����

public:
	






	buildmap():array(),onemap(),index(0){}


	//��ӽڵ�
	void addnode(place Place)
	{
		this->index++;
		re_array(this->index);//���鳤�ȵ���
		node newnode(Place);
		newnode.nodeidex = i;
		array[i] = newnode;//nmd �ڵ���Ӳ�Ҫʹ��push_back�����Ѿ����������ռ䣨resize������push����ӵ������ռ�֮����
		i++;
		onemap[Place.name] = i;

	}

	
	//������������
	void re_array(int index)
	{
		array.resize(index+1);//vector�Ķ�̬����
	}


	//���ҵص��Ƿ���ڵĺ���
	bool findNodeByName(string name) {
		for (auto& n : array) {
			if (n.data.name == name) {
				return true;
			}
		}
		return false; // û�ҵ�  
	}

	//���ҵص��Ƿ���ڣ�������ڣ����ýڵ㷵�س����ĺ���
	node* findNodereturn(string name) {
		for (auto& n : array) {
			if (n.data.name == name) {
				return &n;
			}
		}
		return nullptr; // ���û�ҵ����򷵻ؿ�ָ��
	}

	void addarc(const string& name1, const string& name2, int weight)
	{
		// ��������ص��Ƿ����
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
			cout << "�ص㲻����" << endl;
		}
	}

	void print()
	{
		cout << "�ص������:" << endl;
		for (auto& j:array)
		{
			cout << j.data.name << endl;
			
		}

	}


	// ͨ������������һ���ڵ�
	node* getNextNode(arc* edge) {
		if (edge == nullptr || edge->nextN == nullptr) {
			return nullptr;
		}

		return edge->nextN;
	}

	//������ȱ�����������ȱ���

	void deepfind(node* currentNode)//����
	{
		// ��ǵ�ǰ�ڵ�Ϊ�ѷ���
		currentNode->mark = true;
		cout << "���ʽڵ㣺" << currentNode->data.name << endl;

		// ������ǰ�ڵ���ڽӽڵ�
		arc* edge = currentNode->firstedge;
		while (edge != nullptr)
		{
			// ��ȡ�ڽӽڵ�
			node* nextNode = getNextNode(edge);
			if (nextNode != nullptr && !nextNode->mark)
			{
				// �ݹ����δ�����ʹ����ڽӽڵ�
				deepfind(nextNode);
			}
			// �ƶ�����һ����
			edge = edge->tailedge;
		}

		// ���ݵ���һ���ڵ�
		if (currentNode->firstedge != nullptr && currentNode->firstedge->tailedge != nullptr)
		{
			node* prevNode = &array[currentNode->firstedge->tailvex];
			if (!prevNode->mark)
			{
				deepfind(prevNode);//һֱ�ݹ���˵����б߿��Է��ʵĽڵ�
			}
		}
	}


	//������ȱ���
	void BFS(string startNodeName) 
	{
    // �ҵ���ʼ�ڵ�
    node* startNode = findNodereturn(startNodeName);
    if (startNode == nullptr) {
        cout << "��ʼ�ص㲻����" << endl;
        return;
    }

    // ����һ��������ʵ�ֹ�����ȱ���
    queue<node*> q;

    // ����ʼ�ڵ���Ϊ�ѷ��ʲ��������
    startNode->mark = true;
    q.push(startNode);

    while (!q.empty()) //������в�Ϊ��
	{
        // ȡ�����еĵ�һ���ڵ�
        node* currentNode = q.front();
        q.pop();

        // ���ʵ�ǰ�ڵ㣨������Խ�����ز�����
        cout << "���ʽڵ�: " << currentNode->data.name << endl;

        // ������ǰ�ڵ�������ڽӻ�
        arc* currentEdge = currentNode->firstedge;
        while (currentEdge != nullptr) 
		{
            // ��ȡ���ӵ���һ���ڵ�
            node* nextNode = getNextNode(currentEdge);

            // �����һ���ڵ�δ�����ʹ�
            if (nextNode != nullptr && !nextNode->mark)
			{
                // ������Ϊ�ѷ��ʲ��������
                nextNode->mark = true;
                q.push(nextNode);
            }

            // �ƶ�����һ����
            currentEdge = currentEdge->tailedge;
        }
    }

    // �����������������нڵ�ı��
   
}

	//���½ڵ��Ƿ񱻷��ʣ����»��Ƿ񱻷���
	void nodemark()
	{
		// �������нڵ�
		for (int i = 0; i < index; i++)
		{
			node* n = &array[i];
			// ����ǰ�ڵ���Ϊδ����
			n->mark = false;

			// ������ǰ�ڵ�����б�
			arc* p = n->firstedge;
			while (p != nullptr)
			{
				// ����ǰ�߱��Ϊδ����
				p->mark = false;

				// �ƶ�����һ����
				p = p->tailedge;
			}
		}
	}

	//��������ĵ�ַ�����������ʹ��
	node* getarray()
	{
		return &array[0];
	}

	

	//���ڵ��ӡ�������б�
	void printarc(string name)
	{
		for (auto n : array)
		{
			if (n.data.name == name)
			{
				arc* edge = n.firstedge;
				while (edge!=nullptr)
				{
					cout << "��" << edge->lastN->data.name << "��" << edge->nextN->data.name << "��" << edge->weight << "��ôԶ" << endl;
					edge = edge->tailedge;	
				}
				break;
			}

		}



	}

	void dijkstra(string startNodeName,string name2)
	{
		// �ҵ���ʼ�ڵ�
		node* startNode = findNodereturn(startNodeName);
		if (startNode == nullptr) {
			cout << "��ʼ�ص㲻����" << endl;
			return;
		}

		// ��ʼ��������������ȶ���
		vector<int> distances(index, INT_MAX);
		distances[startNode->nodeidex] = 0;//nodeidexԪ���±�
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({ 0, startNode->nodeidex });

		// �Ͻ�˹�����㷨
		while (!pq.empty())
		{
			// ȡ����ǰ��С����ڵ�
			int currentNodeIndex = pq.top().second;
			pq.pop();
			node* currentNode = &array[currentNodeIndex];

			// �����ǰ�ڵ��ѱ���������
			if (currentNode->mark)
				continue;

			// ��ǵ�ǰ�ڵ�Ϊ�Ѵ���
			currentNode->mark = true;

			// ������ǰ�ڵ�������ڽӽڵ�
			arc* currentEdge = currentNode->firstedge;
			while (currentEdge != nullptr)
			{
				// ��ȡ���ӵ���һ���ڵ�
				node* nextNode = getNextNode(currentEdge);

				// ����ͨ����ǰ�ڵ㵽���ڽӽڵ���ܾ���
				int distanceThroughCurrentNode = distances[currentNodeIndex] + currentEdge->weight;

				// ����������С���ڽӽڵ����֪��̾���
				if (distanceThroughCurrentNode < distances[nextNode->nodeidex])
				{
					// �����ڽӽڵ����̾���
					distances[nextNode->nodeidex] = distanceThroughCurrentNode;
					// ���ڽӽڵ�������ȶ���
					pq.push({ distanceThroughCurrentNode, nextNode->nodeidex });
				}

				// �ƶ�����һ����
				currentEdge = currentEdge->tailedge;
			}
		}

		
		


		
		cout << startNodeName << "��" << name2 << "����̾���Ϊ" << distances[onemap[name2] - 1];


	}

	void delatenode(string name)
	{
		// �����ҵ�Ҫɾ���Ľڵ�
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
			cout << "�ڵ� " << name << " ��������ͼ�С�" << endl;
			return;
		}

		// ��¼Ҫɾ���ڵ�����������ں������������ڵ�ı�
		int deleteIndex = nodeToDelete->nodeidex;

		// �������нڵ㣬ɾ������ָ��nodeToDelete�ı�
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
					
						// ����ǵ�һ����
						if (currentEdge == n->firstedge)
						{
							n->firstedge = nextEdge;
						}
						// ������м�ı�
						else if (nextEdge != nullptr)
						{
							currentEdge->tailedge->headedge = currentEdge->headedge;
							currentEdge->headedge->tailedge = currentEdge->tailedge;
						}

						// �ͷŵ�ǰ�ߵ��ڴ�
						cout << endl;
						cout << currentEdge->weight << endl;
						delete currentEdge;
						currentEdge = nextEdge; // ��ɾ�������currentEdge����ֹ���ʿ�ָ��
					
					
				}
				else
				{
					// �����ǰ�����ɾ���ڵ��޹أ���������
					currentEdge = nextEdge;
				}

			}
		}

		// ���������Ƴ��ڵ�
		auto it = find_if(array.begin(), array.end(), [&](const node& n) { return n.data.name == name; });
		if (it != array.end())
		{
			array.erase(it);
		}

		
		index--;




		// ����onemap���Ƴ���Ӧ����Ŀ
		onemap.erase(name);

		// ��С�����С���Է�ӳ�ڵ������ı仯
		array.resize(array.size());
	}

	// ����ڵ㵽�ļ�
	void saveNodesToFile(const std::string& filename) {
		std::ofstream outFile(filename, std::ios_base::trunc); // ���trunc��־
		if (!outFile.is_open()) {
			std::cerr << "�޷����ļ�����д��ڵ�: " << filename << std::endl;
			return;
		}

		for (int i = 0; i < index;i++) 
		{
			node* node = &array[i];
			outFile << node->data.name << "\n";
		}
		outFile.close();
	}

	// ����ߵ��ļ�
	void saveArcsToFile(const string& filename) {
		ofstream outFile(filename, ios_base::trunc);
		if (!outFile.is_open()) {
			cerr << "�޷����ļ�����д���: " << filename << endl;
			return;
		}

		set<pair<string, string>> writtenEdges; // �洢��д��ı�

		for (int i = 0; i < index; i++) {
			node* node = &array[i];
			arc* edge = node->firstedge;
			while (edge != nullptr) {
				if (edge->nextN != nullptr) {
					// �����Ƿ���д��
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
		// �ȶ�ȡ�ڵ��ļ�
		ifstream nodeFile(nodesFilename);
		if (!nodeFile.is_open()) {
			cerr << "�޷��򿪽ڵ��ļ����ж�ȡ: " << nodesFilename << endl;
			return;
		}

		clear();

		string nodeName;
		while (getline(nodeFile, nodeName)) {
			addnode({ nodeName });
		}
		nodeFile.close();

		// �ٶ�ȡ���ļ�
		ifstream arcFile(arcsFilename);
		if (!arcFile.is_open()) {
			cerr << "�޷��򿪱��ļ����ж�ȡ: " << arcsFilename << endl;
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
	//ʵ�����·�����ṩ��ͼ����ļ�
	//����ͼ�����ļ���Ȼ�󽫹��ܰ�װ
	//Ȼ������Ŀ����ʵ�����ݿ��easyx���� 
	//����֮����й���
	//ӵ���̶ȣ����̵�
	//��·ά�ޣ��ص�ά�ޣ�ɾ����

//ȫ��ͼ
buildmap Map;






void menu1()//����ҳ�� 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               У԰����ϵͳ                 \n");
	printf("               ��ѡ�����\n");
	printf("               1 �û�\n");
	printf("               2 ����Ա\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

}

void menu2()
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               У԰����ϵͳ                 \n");
	printf("               1 ѧУ���\n");
	printf("               2 ��ѯ������̾���\n");
	//printf("               *3 ��ѯ�ص���Ϣ\n");
	//printf("               4 ������з�ʽ����û��������\n");
	printf("               0 ����\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
}

void menu3()
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               У԰����ϵͳ                 \n");
	printf("               1 ���ӵص�\n");
	printf("               2 ����·\n");
	//printf("               3 *ɾ���ص�\n");
	//printf("               4 *ɾ��·\n");
	printf("               5 DFS\n");
	printf("               6 BFS\n");
	printf("               7 ��ӡ�ص�\n");
	printf("               8 ��ӡ�ص��ܱ�·��\n");
	//printf("               8 *�޸Ļ��������������\n");
	printf("               9 ǰ���û�ϵͳ\n");
	printf("               10 ϵͳ�˳�\n");
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
		cout << "�������ã���������" << endl;
		cout<<  "�̵���ĺ�" << endl;
		cout << "����ѧ�˷����" << endl;
		cout << "Ů�˿������¾�" << endl;
		cout << "��ѧУ������֢�Ŀ���" << endl;
		cout << "��ֲ���˵�����" << endl;
		cout << "�̳��˴����屣���ԹѸ���˼��Ͱ������õ�����" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << " �����湣��ѧУ���Ǻܲ���ġ�����ѧУ���̫�������ô���" << endl;

		break;
	}

	case 2:
	{
		cout << "�����������ҵ�����Ŀ���" << endl;
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
	cout << "��¼��: ";
	for (int i = 0; i < 50; i++) {
		cout << "|";
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	cout << " ���\n";
}

void keyword() {
	string username, password;
	char ch;

	cout << "��ӭ���������¼ϵͳ\n";

	cout << "�������û���: ";
	cin >> username;

	cout << "����������: ";
	ch = _getch();
	while (ch != 13) {  // 13����س���
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	cout << endl;

	if (username == "sly" && password == "123456") {
		showProgressBar();
		cout << "��¼�ɹ�����ӭ������admin��\n";
		while (1)
		{
			
			menu3();
			jiaohu3();
			system("pause");//��ֹ����
			system("cls");//���� 
		}
		

	}
	else {
		cout << "��¼ʧ�ܣ������û��������롣\n";
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
			system("pause");//��ֹ����
			system("cls");//���� 
		}
		break;
	}

	case 2:
	{
		//���õ�¼
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
		cout << "������ص����������" << endl;
		string name;
		
		cin >> name;
		place v;
		v.name = name;
		
		Map.addnode(v);
		break;
	}

	case 2:
	{
		cout << "����������Ŀ��ص��Լ��������·��" << endl;
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
		cout << "������ص���й����������" << endl;
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
		cout << "������Ŀ��ص�" << endl;
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
			system("pause");//��ֹ����
			system("cls");//���� 
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
		system("pause");//��ֹ����
		system("cls");//���� 
	

	


	system("pause");

}



