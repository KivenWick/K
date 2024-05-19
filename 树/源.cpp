#include <iostream>
#include <iomanip>


using namespace std;


//����Ķ�����
#define capacity 20

class Node
{
public:
    
	int data;
	Node* left;
	Node* right;


	Node(int value) : data(value), left(nullptr), right(nullptr) {}
};


class Tree {
private:
	Node* array[capacity];

	

public:
	Tree() {
		for (int i = 0; i < capacity; ++i) {
			array[i] = nullptr;
		}
	}

	void add(int data) {
		Node* newNode = new Node(data);

		if (array[0] == nullptr) {
			array[0] = newNode; // ������ڵ�Ϊ�գ����½ڵ�Ϊ���ڵ�
		}
		else {
			for (int i = 0; i < capacity; i++) {
				if (array[i] != nullptr) {
					if (array[i]->left == nullptr) {
						array[i]->left = newNode; // ���ӽڵ�Ϊ�գ��������ӽڵ�
						array[2 * i + 1] = newNode;
						break;
					}
					else if (array[i]->right == nullptr) {
						array[i]->right = newNode;// ���ӽڵ�Ϊ�գ��������ӽڵ�
						array[2 * i + 2] = newNode;
						break;
					}
				}
			}
		}
	}

	void findNode(int data) {
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr && array[i]->data == data) {
				cout << array[i]->data;
				return;
			}
		}
		cout << "û�ҵ�";
	}

	void deleteNode(int data) {
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr && array[i]->data == data && (array[i]->left==nullptr&&array[i]->right==nullptr)) {
				cout << array[i]->data << " " << "ɾ���ɹ�";
				array[i] = nullptr;
				return;
			}
			else if (array[i] != nullptr && array[i]->data == data && (array[i]->left != nullptr || array[i]->right != nullptr))
			{
				cout << array[i]->data << " " << "ɾ���ɹ�";//ɾ�����֧
				//�ݹ����ɾ��
				deleteNode(array[i]->left->data);
				deleteNode(array[i]->right->data);

			}

		}
		cout << "û�ҵ�";
	}

	void changeNode(int olddata,int newdata) {
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr && array[i]->data == olddata) {
				cout << array[i]->data << " " << "�����µ�ֵ";
				array[i]->data = newdata;
				return;
			}
		}
		cout << "û�ҵ�";
	}

	//��ӡ
	
	
	void printUtil(int index, int space) {
		if (index >= capacity || array[index] == nullptr) {
			return;
		}

		space += 5;

		// �ȵݹ�������������ٴ�ӡ��ǰ�ڵ�
		printUtil(2 * index + 2, space);
		cout << setw(space) << array[index]->data << endl;
		// ���ݹ����������
		printUtil(2 * index + 1, space);
	}

	void printtree() {
		printUtil(0, 0);
	}


	//����
	Node* getarray()
	{
		return array[0];

	}



	//����
	//�������
	void inorderTraversal(Node* root) {
		if (root != nullptr) {
			inorderTraversal(root->left);
			cout << root->data << " ";
			inorderTraversal(root->right);
		}
	}
	//ǰ�����
	void preorderTraversal(Node* root) {
		if (root != nullptr) {
			cout << root->data << " ";
			preorderTraversal(root->left);
			preorderTraversal(root->right);
		}
	}

	//�������
	void postorderTraversal(Node* root) {
		if (root != nullptr) {
			postorderTraversal(root->left);
			postorderTraversal(root->right);
			cout << root->data << " ";
		}
	}

	//���
	int deepth(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			int leftdeepth = deepth(root->left);
			int rightdeepth = deepth(root->right);

			if (leftdeepth > rightdeepth)
			{
				return leftdeepth + 1;
			}
			else
			{
				return rightdeepth + 1;
			}

		}

	}


	//�ܽ����
	int getNodes(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + getNodes(root->left) + getNodes(root->right);
	}

	// ��ȡ�ܽ����
	int getTotalNodes() {
		return getNodes(array[0]);
	}

	//��һ�汾���� ���ݣ��ڵ�ѡ����룬����ʱ������ӡһ�£���Ȼ�ȡ�ȱ�����Ŀ��ڵ�Ȼ�󷵻����

};

class Treelist
{
private:
	Node* root;



public:

	Treelist() : root(nullptr) {}

	Node* insertNode(Node* root, int data) {
		if (root == nullptr) {
			// �����ǰ�ڵ�Ϊ�գ���ֱ���ڴ�λ�ô����½ڵ�
			return new Node(data);
		}
		else if (root->left != nullptr && root->right != nullptr) {
			// ��������ӽڵ㶼�ǿգ�ѯ���û���Ҫ�������ĸ������в���
			cout << "��ǰ�ڵ�������ӽڵ㶼�ǿա�ѡ�������������(1)��������(2)�в��룬��ֹͣ(3)��" << endl;
			int choice;
			cin >> choice;
			if (choice == 1) {
				root->left = insertNode(root->left, data); // �������������в���
			}
			else if (choice == 2) {
				root->right = insertNode(root->right, data); // �������������в���
			}
			else if (choice == 3) {
				// �û�ѡ��ֹͣ���룬������һ��ĸ��ڵ�
				return root;
			}
		}
		else if (root->left == nullptr) {
			// ������ӽڵ�Ϊ�գ��������ӽڵ㴦����
			root->left = insertNode(root->left, data);
		}
		else if (root->right == nullptr) {
			// ������ӽڵ�Ϊ�գ��������ӽڵ㴦����
			root->right = insertNode(root->right, data);
		}

		return root;
	}
	void insert(int data) {
		root = insertNode(root, data);
	}

	//ɾ��

	Node* deleteNode(Node* root, int data) {
		if (root == nullptr) {
			return root;
		}

		if (root->data == data && root->left == nullptr && root->right == nullptr) {
			delete root;
			return nullptr;
		}

		if (root->left != nullptr) {
			if (root->left->data == data) {
				delete root->left;
				root->left = nullptr;
			}
			else {
				deleteNode(root->left, data);
			}
		}

		if (root->right != nullptr) {
			if (root->right->data == data) {
				delete root->right;
				root->right = nullptr;
			}
			else {
				deleteNode(root->right, data);
			}
		}

		return root;
	}
	// �޸Ľڵ�ֵ
	void modifyNode(Node* root, int oldData, int newData) {
		if (root == nullptr) {
			return;
		}

		if (root->data == oldData) {
			root->data = newData;
		}

		modifyNode(root->left, oldData, newData);
		modifyNode(root->right, oldData, newData);
	}

	// ���ҽڵ�
	Node* findNode(Node* root, int data) {
		if (root == nullptr || root->data == data) {
			return root;
		}

		Node* leftResult = findNode(root->left, data);
		if (leftResult != nullptr) {
			return leftResult;
		}

		return findNode(root->right, data);
	}


	// �������
	void preOrderTraversal(Node* root) {
		if (root != nullptr) {
			cout << root->data << " ";
			preOrderTraversal(root->left);
			preOrderTraversal(root->right);
		}
	}

	// �������
	void inOrderTraversal(Node* root) {
		if (root != nullptr) {
			inOrderTraversal(root->left);
			cout << root->data << " ";
			inOrderTraversal(root->right);
		}
	}

	// �������
	void postOrderTraversal(Node* root) {
		if (root != nullptr) {
			postOrderTraversal(root->left);
			postOrderTraversal(root->right);
			cout << root->data << " ";
		}
	}


	// ��ȡ���������
	int getDepth(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		int leftDepth = getDepth(root->left);
		int rightDepth = getDepth(root->right);

		return 1 + max(leftDepth, rightDepth);
	}

	// ����������ڵ�����
	int getNodeCount(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + getNodeCount(root->left) + getNodeCount(root->right);//���������ڵ���
	}

	Node* getroot()
	{
		return root;
	}

	// ��ӡ������
	void printTree(Node* root, int space) {
		// �������������ڵ�Ϊ�գ��򷵻�
		if (root == nullptr) {
			return;
		}

		// ���ӿո�ʹ���Ľṹ������
		space += 5;

		// �ݹ��ӡ������
		printTree(root->left, space);

		// ��ӡ��ǰ�ڵ㣬��������
		cout << setw(space) << root->data << endl;

		// �ݹ��ӡ������
		printTree(root->right, space);
	}

	// ��ӡ��������������ں���
	void printWholeTree() {
		printTree(root, 0); // �Ӹ��ڵ㿪ʼ��ӡ����ʼ����Ϊ0
	}




};













void menu()
{
	cout << "1.��ӽڵ�" << endl;
	cout << "2.ɾ���ڵ�" << endl;
	cout << "3.�޸Ľڵ�" << endl;
	cout << "4.���ҽڵ�" << endl;
	cout << "5.��ӡ������" << endl;
	cout << "6.ǰ�����" << endl;
	cout << "7.�������" << endl;
	cout << "8.�������" << endl;
	cout << "9.��Ȼ�ȡ" << endl;
	cout << "10.�ܽ����" << endl;
}


void jiaohu()
{
	static Tree tree;
	int key;
		cin >> key;
		switch (key)
		{
			case 1:
			{
				cout << "����Ҫ��ӵĽڵ�ֵ: ";
				int data;
				cin >> data;
				tree.add(data);
				break;
			}
			case 2:
			{
				cout << "����Ҫɾ���Ľڵ�ֵ: ";
				int data;
				cin >> data;
				tree.deleteNode(data);
				break;
			}
			case 3:
			{
				int data, newData;
				cout << "����Ҫ�޸ĵĽڵ�ֵ: ";
				cin >> data;
				cout << "�����µĽڵ�ֵ: ";
				cin >> newData;
				tree.changeNode(data, newData);
				break;
			}
			case 4:
			{
				cout << "����Ҫ���ҵĽڵ�ֵ: ";
				int data;
				cin >> data;
				tree.findNode(data);
				break;
			}
			case 5:
			{
				cout << "��ӡ��:" << endl;
				tree.printtree();
				break;
			}
			case 6:
			{
				tree.printtree();
				cout << "ǰ�����: ";
				tree.preorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 7:
			{
				tree.printtree();
				cout << "�������: ";
				tree.inorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 8:
			{
				tree.printtree();
				cout << "�������: ";
				tree.postorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 9:
			{
				cout << "�������Ϊ: " << tree.deepth(tree.getarray()) << endl;
				break;
			}
			case 10:
			{
				cout << "�ܽ����Ϊ: " << tree.getTotalNodes() << endl;
				break;
			}
			default:
				cout << "�����ѡ��" << endl;


		}




}



void jiaohulist()
{
	static Treelist treelist;
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
	{
		cout << "����Ҫ��ӵĽڵ�ֵ: ";
		int data;
		cin >> data;
		treelist.insert(data);
		break;
	}
	case 2:
	{
		cout << "����Ҫɾ���Ľڵ�ֵ: ";
		int data;
		cin >> data;
		treelist.deleteNode(treelist.getroot(), data);
		break;
	}
	case 3:
	{
		int data, newData;
		cout << "����Ҫ�޸ĵĽڵ�ֵ: ";
		cin >> data;
		cout << "�����µĽڵ�ֵ: ";
		cin >> newData;
		treelist.modifyNode(treelist.getroot(), data, newData);
		break;
	}
	case 4:
	{
		cout << "����Ҫ���ҵĽڵ�ֵ: ";
		int data;
		cin >> data;
		treelist.findNode(treelist.getroot(), data);
		break;
	}
	case 5:
	{
		cout << "��ӡ��:" << endl;
		treelist.printWholeTree();
		break;
	}
	case 6:
	{
		treelist.printWholeTree();
		cout << "ǰ�����: ";
		treelist.preOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 7:
	{
		treelist.printWholeTree();
		cout << "�������: ";
		treelist.inOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 8:
	{
		treelist.printWholeTree();
		cout << " �������: ";
		treelist.postOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 9:
	{
		cout << "�������Ϊ: " << treelist.getDepth(treelist.getroot()) << endl;
		break;
	}
	case 10:
	{
		cout << "�ܽ����Ϊ: " << treelist.getNodeCount(treelist.getroot())<< endl;
		break;
	}
	default:
		cout << "�����ѡ��" << endl;


	}




}







void main() {
	int choice;
	cout << "��ѡ��ʹ�õ��ࣺ1. ʹ������ʵ�ֵĶ�������Tree�� 2. ʹ������ʵ�ֵĶ�������Treelist��: ";
	cin >> choice;

	while (1)
	{
		menu();
		if (choice == 1) {
			jiaohu();
		}
		else if (choice == 2) {
			jiaohulist();
		}
		else {
			cout << "�����ѡ�������ѡ��" << endl;
		}
		system("pause");//��ֹ����
		system("cls");//���� 
	}

	system("pause");
}








