#include <iostream>
#include <iomanip>


using namespace std;


//数组的二叉树
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
			array[0] = newNode; // 如果根节点为空，则新节点为根节点
		}
		else {
			for (int i = 0; i < capacity; i++) {
				if (array[i] != nullptr) {
					if (array[i]->left == nullptr) {
						array[i]->left = newNode; // 左子节点为空，插入左子节点
						array[2 * i + 1] = newNode;
						break;
					}
					else if (array[i]->right == nullptr) {
						array[i]->right = newNode;// 右子节点为空，插入右子节点
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
		cout << "没找到";
	}

	void deleteNode(int data) {
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr && array[i]->data == data && (array[i]->left==nullptr&&array[i]->right==nullptr)) {
				cout << array[i]->data << " " << "删除成功";
				array[i] = nullptr;
				return;
			}
			else if (array[i] != nullptr && array[i]->data == data && (array[i]->left != nullptr || array[i]->right != nullptr))
			{
				cout << array[i]->data << " " << "删除成功";//删除其分支
				//递归遍历删除
				deleteNode(array[i]->left->data);
				deleteNode(array[i]->right->data);

			}

		}
		cout << "没找到";
	}

	void changeNode(int olddata,int newdata) {
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr && array[i]->data == olddata) {
				cout << array[i]->data << " " << "输入新的值";
				array[i]->data = newdata;
				return;
			}
		}
		cout << "没找到";
	}

	//打印
	
	
	void printUtil(int index, int space) {
		if (index >= capacity || array[index] == nullptr) {
			return;
		}

		space += 5;

		// 先递归遍历右子树，再打印当前节点
		printUtil(2 * index + 2, space);
		cout << setw(space) << array[index]->data << endl;
		// 最后递归遍历左子树
		printUtil(2 * index + 1, space);
	}

	void printtree() {
		printUtil(0, 0);
	}


	//返回
	Node* getarray()
	{
		return array[0];

	}



	//遍历
	//中序遍历
	void inorderTraversal(Node* root) {
		if (root != nullptr) {
			inorderTraversal(root->left);
			cout << root->data << " ";
			inorderTraversal(root->right);
		}
	}
	//前序遍历
	void preorderTraversal(Node* root) {
		if (root != nullptr) {
			cout << root->data << " ";
			preorderTraversal(root->left);
			preorderTraversal(root->right);
		}
	}

	//后序遍历
	void postorderTraversal(Node* root) {
		if (root != nullptr) {
			postorderTraversal(root->left);
			postorderTraversal(root->right);
			cout << root->data << " ";
		}
	}

	//深度
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


	//总结点数
	int getNodes(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + getNodes(root->left) + getNodes(root->right);
	}

	// 获取总结点数
	int getTotalNodes() {
		return getNodes(array[0]);
	}

	//下一版本更新 扩容，节点选择插入，遍历时把树打印一下，深度获取先遍历到目标节点然后返回深度

};

class Treelist
{
private:
	Node* root;



public:

	Treelist() : root(nullptr) {}

	Node* insertNode(Node* root, int data) {
		if (root == nullptr) {
			// 如果当前节点为空，则直接在此位置创建新节点
			return new Node(data);
		}
		else if (root->left != nullptr && root->right != nullptr) {
			// 如果左右子节点都非空，询问用户想要继续在哪个子树中插入
			cout << "当前节点的左右子节点都非空。选择继续在左子树(1)、右子树(2)中插入，或停止(3)。" << endl;
			int choice;
			cin >> choice;
			if (choice == 1) {
				root->left = insertNode(root->left, data); // 继续在左子树中插入
			}
			else if (choice == 2) {
				root->right = insertNode(root->right, data); // 继续在右子树中插入
			}
			else if (choice == 3) {
				// 用户选择停止插入，返回上一层的根节点
				return root;
			}
		}
		else if (root->left == nullptr) {
			// 如果左子节点为空，则在左子节点处插入
			root->left = insertNode(root->left, data);
		}
		else if (root->right == nullptr) {
			// 如果右子节点为空，则在右子节点处插入
			root->right = insertNode(root->right, data);
		}

		return root;
	}
	void insert(int data) {
		root = insertNode(root, data);
	}

	//删除

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
	// 修改节点值
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

	// 查找节点
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


	// 先序遍历
	void preOrderTraversal(Node* root) {
		if (root != nullptr) {
			cout << root->data << " ";
			preOrderTraversal(root->left);
			preOrderTraversal(root->right);
		}
	}

	// 中序遍历
	void inOrderTraversal(Node* root) {
		if (root != nullptr) {
			inOrderTraversal(root->left);
			cout << root->data << " ";
			inOrderTraversal(root->right);
		}
	}

	// 后序遍历
	void postOrderTraversal(Node* root) {
		if (root != nullptr) {
			postOrderTraversal(root->left);
			postOrderTraversal(root->right);
			cout << root->data << " ";
		}
	}


	// 获取二叉树深度
	int getDepth(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		int leftDepth = getDepth(root->left);
		int rightDepth = getDepth(root->right);

		return 1 + max(leftDepth, rightDepth);
	}

	// 计算二叉树节点总数
	int getNodeCount(Node* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + getNodeCount(root->left) + getNodeCount(root->right);//左右子树节点数
	}

	Node* getroot()
	{
		return root;
	}

	// 打印二叉树
	void printTree(Node* root, int space) {
		// 基本情况：如果节点为空，则返回
		if (root == nullptr) {
			return;
		}

		// 增加空格，使树的结构更清晰
		space += 5;

		// 递归打印左子树
		printTree(root->left, space);

		// 打印当前节点，带有缩进
		cout << setw(space) << root->data << endl;

		// 递归打印右子树
		printTree(root->right, space);
	}

	// 打印整个二叉树的入口函数
	void printWholeTree() {
		printTree(root, 0); // 从根节点开始打印，初始缩进为0
	}




};













void menu()
{
	cout << "1.添加节点" << endl;
	cout << "2.删除节点" << endl;
	cout << "3.修改节点" << endl;
	cout << "4.查找节点" << endl;
	cout << "5.打印二叉树" << endl;
	cout << "6.前序遍历" << endl;
	cout << "7.中序遍历" << endl;
	cout << "8.后序遍历" << endl;
	cout << "9.深度获取" << endl;
	cout << "10.总结点数" << endl;
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
				cout << "输入要添加的节点值: ";
				int data;
				cin >> data;
				tree.add(data);
				break;
			}
			case 2:
			{
				cout << "输入要删除的节点值: ";
				int data;
				cin >> data;
				tree.deleteNode(data);
				break;
			}
			case 3:
			{
				int data, newData;
				cout << "输入要修改的节点值: ";
				cin >> data;
				cout << "输入新的节点值: ";
				cin >> newData;
				tree.changeNode(data, newData);
				break;
			}
			case 4:
			{
				cout << "输入要查找的节点值: ";
				int data;
				cin >> data;
				tree.findNode(data);
				break;
			}
			case 5:
			{
				cout << "打印树:" << endl;
				tree.printtree();
				break;
			}
			case 6:
			{
				tree.printtree();
				cout << "前序遍历: ";
				tree.preorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 7:
			{
				tree.printtree();
				cout << "中序遍历: ";
				tree.inorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 8:
			{
				tree.printtree();
				cout << "后序遍历: ";
				tree.postorderTraversal(tree.getarray());
				cout << endl;
				break;
			}
			case 9:
			{
				cout << "树的深度为: " << tree.deepth(tree.getarray()) << endl;
				break;
			}
			case 10:
			{
				cout << "总结点数为: " << tree.getTotalNodes() << endl;
				break;
			}
			default:
				cout << "错误的选项" << endl;


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
		cout << "输入要添加的节点值: ";
		int data;
		cin >> data;
		treelist.insert(data);
		break;
	}
	case 2:
	{
		cout << "输入要删除的节点值: ";
		int data;
		cin >> data;
		treelist.deleteNode(treelist.getroot(), data);
		break;
	}
	case 3:
	{
		int data, newData;
		cout << "输入要修改的节点值: ";
		cin >> data;
		cout << "输入新的节点值: ";
		cin >> newData;
		treelist.modifyNode(treelist.getroot(), data, newData);
		break;
	}
	case 4:
	{
		cout << "输入要查找的节点值: ";
		int data;
		cin >> data;
		treelist.findNode(treelist.getroot(), data);
		break;
	}
	case 5:
	{
		cout << "打印树:" << endl;
		treelist.printWholeTree();
		break;
	}
	case 6:
	{
		treelist.printWholeTree();
		cout << "前序遍历: ";
		treelist.preOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 7:
	{
		treelist.printWholeTree();
		cout << "中序遍历: ";
		treelist.inOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 8:
	{
		treelist.printWholeTree();
		cout << " 后序遍历: ";
		treelist.postOrderTraversal(treelist.getroot());
		cout << endl;
		break;
	}
	case 9:
	{
		cout << "树的深度为: " << treelist.getDepth(treelist.getroot()) << endl;
		break;
	}
	case 10:
	{
		cout << "总结点数为: " << treelist.getNodeCount(treelist.getroot())<< endl;
		break;
	}
	default:
		cout << "错误的选项" << endl;


	}




}







void main() {
	int choice;
	cout << "请选择使用的类：1. 使用数组实现的二叉树（Tree） 2. 使用链表实现的二叉树（Treelist）: ";
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
			cout << "错误的选项，请重新选择。" << endl;
		}
		system("pause");//防止闪屏
		system("cls");//清屏 
	}

	system("pause");
}








