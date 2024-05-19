#include<iostream>
#include<map>//键与值去配合哈夫曼编码
#include<string>
#include<vector>//存键和值
#include<algorithm>//用sort排序
using namespace std;


class TreeNode {
public:
    char character; // 存储字符
    int frequency; // 存储字符出现频率
    TreeNode* left;
    TreeNode* right;

    TreeNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
private:
    TreeNode* root;

public:
    HuffmanTree() : root(nullptr) {}


    // 构建哈夫曼树
    void buildTree(map<char, int>& freqMap)
    {
        vector<TreeNode*> nodes;
        //为什么使用vector呢，因为vector的排序更加简便。数组的排序需要重新排序后复制进新的数组
        //vector排序简洁，排序之后删除前两个最小的也方便
        //使用map统计字符出现的频率，存进map再存进vec


        // 将频率非零的字符创建为节点并加入到vector中
        for (auto& entry : freqMap) {
            if (entry.second > 0) {
                nodes.push_back(new TreeNode(entry.first, entry.second));
            }
        }

        // 构建哈夫曼树
        while (nodes.size() > 1) {
            // 按频率排序
            sort(nodes.begin(), nodes.end(), [](const TreeNode* a, const TreeNode* b) {
                return a->frequency < b->frequency;
                });

            // 取出频率最小的两个节点
            TreeNode* left = nodes[0];
            TreeNode* right = nodes[1];

            // 创建新节点作为它们的父节点
            TreeNode* parent = new TreeNode('*', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            // 删除已经处理过的两个节点
            nodes.erase(nodes.begin(), nodes.begin() + 2);

            // 将新节点加入节点数组中
            nodes.push_back(parent);
        }

        // 最后剩下的节点即为根节点
        root = nodes.front();
    }

    // 生成哈夫曼编码
    void generateCodes(TreeNode* node, string code, map<char, string>& codes) {
        if (node == nullptr) return;

        // 如果是叶子节点，则将字符和对应的编码加入到编码表中
        if (node->left == nullptr && node->right == nullptr) {
            codes[node->character] = code;//将频率给替换了
        }

        // 递归生成编码
        generateCodes(node->left, code + "0", codes);
        generateCodes(node->right, code + "1", codes);
    }

    // 打印哈夫曼编码
    void printCodes(map<char, string>& codes) {
        cout << "哈夫曼编码:" << endl;
        for (auto& entry : codes) {
            cout << entry.first << " : " << entry.second << endl;
        }
    }
    TreeNode* getRoot() const {
        return root;
    }

    string encodeToBinary(string text, map<char, string>& codes) {
        string encodedBinary;
        for (char ch : text) {
            encodedBinary += codes[ch];
        }
        return encodedBinary;
    }

    // 解码哈夫曼编码为原文
    string decodeFromBinary(string encodedBinary) {
        TreeNode* current = root;
        string decodedText;

        for (char bit : encodedBinary) {
            if (bit == '0') {
                current = current->left;
            }
            else if (bit == '1') {
                current = current->right;
            }

            // 到达叶子节点
            if (current->left == nullptr && current->right == nullptr) {
                decodedText += current->character;
                current = root; // 重置当前节点为根节点，以便下一次解码
            }
        }

        return decodedText;
    }





};

int main() {
    string input;

    // 使用getline()读取整行输入，包括空格
    getline(cin, input);

    map<char, int> freqMap;

    // 统计字符频率
    for (char ch : input) {
        freqMap[ch]++;
    }

    HuffmanTree huffmanTree;
    huffmanTree.buildTree(freqMap);  // map转化为vec
    map<char, string> codes;//哈夫曼编码表
    huffmanTree.generateCodes(huffmanTree.getRoot(), "", codes);

    // 输出哈夫曼编码
    for (auto& entry : codes) {
        cout << entry.first << " : " << entry.second << endl;
    }

    // 输出频率
    for (auto& ent : freqMap) {
        cout << ent.first << " : 出现次数 " << ent.second << endl;
    }



    // 将原文转换为只含 '0' 和 '1' 的形式
    string encodedBinary = huffmanTree.encodeToBinary(input, codes);
    cout << "编码 " << encodedBinary << endl;



    cout << "是否生成解码y/n" << endl;
    char T;
    cin >> T;

    if (T == 'y')
    {
        string encodedbinary;
        cin >> encodedbinary;
        // 解码哈夫曼编码
        string decodedText = huffmanTree.decodeFromBinary(encodedbinary);
        cout << "解码 " << decodedText << endl;
    }

    return 0;
}








//
//
//class tree
//{
//public:
//	//权，统计路径上的权（遍历哈夫曼树，从根节点开始，沿着左子树走为0，沿着右子树走为1，记录下每个叶子节点所经过的路径，得到其对应的编码。）
//	int data;//频率
//	char cac;
//	tree* parent;
//	tree* left;
//	tree* right;
//	string huffmanCode; // 哈夫曼编码
//
//	tree() :cac(), data(-1), parent(nullptr), left(nullptr), right(nullptr), huffmanCode() {}
//
//	
//
//
//};
//
//
////哈夫曼树，共有2n-1个节点，不用0.数组大小2n
//
//
//
//class buildtree
//{
//public:
//	map<char,int> codes; // 存储字符对应的编码
//	tree* array[1000];
//	int idx = 0;
//
//	//接受字符串并统计的函数
//
//	void transform(string bunch)//bunch是串的意思
//	{
//		string s;
//		s = bunch;
//
//		for (auto& i : s)
//		{
//			codes[i]++;
//		}
//
//		for (auto& i : codes)
//		{
//			cout << i.first << " " << i.second << endl;
//			//size = size + i.second;
//		}
//
//		//cout << "字符串长度为" << size;
//	}
//
//	
//
//	//将map转化入vec并排序，返回出来的vec则为真正用来做建树根据的字符数字表
//
//	vector<pair<char, int>> sor(map<char, int> codes)
//	{
//		// 定义一个自定义的比较函数，按值从小到大排序
//		auto comp = [](const pair<char, int>& a, const pair<char, int>& b) {
//			return a.second < b.second;
//		};
//
//		// 将map转换为vector，并按值排序
//		vector<pair<char, int>> vec(codes.begin(), codes.end());
//		sort(vec.begin(), vec.end(), comp);
//
//		return vec;
//	}
//	//根据vec则需要生成节点造树
//
//
//
//	tree* trans(vector<pair<char, int>>& vec)
//	{
//		// 创建两个新节点
//		tree* a = new tree();
//		tree* b = new tree();
//
//		// 将频率最小的两个字符分别赋值给这两个新节点
//		a->data = vec[0].second;
//		a->cac = vec[0].first;
//		b->data = vec[1].second;
//		b->cac = vec[1].first;
//
//		// 创建一个新节点作为它们的父节点
//		tree* c = new tree();
//		c->data = vec[0].second + vec[1].second;
//
//		// 将频率最小的两个节点作为新节点的左右子节点
//		c->left = a;
//		c->right = b;
//		a->parent = c;
//		b->parent = c;
//
//		// 删除已经处理过的两个最小频率的节点
//		vec.erase(vec.begin(), vec.begin() + 2);
//
//		// 创建一个新的键值对，代表新节点
//		pair<char, int> spair('*', c->data);
//
//		// 将新节点插入到频率排序的位置
//		vec.push_back(spair);
//		sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
//			return a.second < b.second;
//			});
//
//		// 返回新生成的树节点 c
//		return c;
//	}
//
//	
//	char dataTrans(int data)
//	{
//		for (auto& i : codes)
//		{
//			if (i.second == data)
//			{
//				return i.first; // 返回匹配的字符
//			}
//		}
//		return '\0'; // 如果没有找到匹配的字符，返回空字符
//	}
//
//	
//
//	
//};
//
//
//int main()
//{
//	
//	return 0;
//}
//
//
//
//
//
//