#include<iostream>
#include<map>//����ֵȥ��Ϲ���������
#include<string>
#include<vector>//�����ֵ
#include<algorithm>//��sort����
using namespace std;


class TreeNode {
public:
    char character; // �洢�ַ�
    int frequency; // �洢�ַ�����Ƶ��
    TreeNode* left;
    TreeNode* right;

    TreeNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
private:
    TreeNode* root;

public:
    HuffmanTree() : root(nullptr) {}


    // ������������
    void buildTree(map<char, int>& freqMap)
    {
        vector<TreeNode*> nodes;
        //Ϊʲôʹ��vector�أ���Ϊvector��������Ӽ�㡣�����������Ҫ����������ƽ��µ�����
        //vector�����࣬����֮��ɾ��ǰ������С��Ҳ����
        //ʹ��mapͳ���ַ����ֵ�Ƶ�ʣ����map�ٴ��vec


        // ��Ƶ�ʷ�����ַ�����Ϊ�ڵ㲢���뵽vector��
        for (auto& entry : freqMap) {
            if (entry.second > 0) {
                nodes.push_back(new TreeNode(entry.first, entry.second));
            }
        }

        // ������������
        while (nodes.size() > 1) {
            // ��Ƶ������
            sort(nodes.begin(), nodes.end(), [](const TreeNode* a, const TreeNode* b) {
                return a->frequency < b->frequency;
                });

            // ȡ��Ƶ����С�������ڵ�
            TreeNode* left = nodes[0];
            TreeNode* right = nodes[1];

            // �����½ڵ���Ϊ���ǵĸ��ڵ�
            TreeNode* parent = new TreeNode('*', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            // ɾ���Ѿ�������������ڵ�
            nodes.erase(nodes.begin(), nodes.begin() + 2);

            // ���½ڵ����ڵ�������
            nodes.push_back(parent);
        }

        // ���ʣ�µĽڵ㼴Ϊ���ڵ�
        root = nodes.front();
    }

    // ���ɹ���������
    void generateCodes(TreeNode* node, string code, map<char, string>& codes) {
        if (node == nullptr) return;

        // �����Ҷ�ӽڵ㣬���ַ��Ͷ�Ӧ�ı�����뵽�������
        if (node->left == nullptr && node->right == nullptr) {
            codes[node->character] = code;//��Ƶ�ʸ��滻��
        }

        // �ݹ����ɱ���
        generateCodes(node->left, code + "0", codes);
        generateCodes(node->right, code + "1", codes);
    }

    // ��ӡ����������
    void printCodes(map<char, string>& codes) {
        cout << "����������:" << endl;
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

    // �������������Ϊԭ��
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

            // ����Ҷ�ӽڵ�
            if (current->left == nullptr && current->right == nullptr) {
                decodedText += current->character;
                current = root; // ���õ�ǰ�ڵ�Ϊ���ڵ㣬�Ա���һ�ν���
            }
        }

        return decodedText;
    }





};

int main() {
    string input;

    // ʹ��getline()��ȡ�������룬�����ո�
    getline(cin, input);

    map<char, int> freqMap;

    // ͳ���ַ�Ƶ��
    for (char ch : input) {
        freqMap[ch]++;
    }

    HuffmanTree huffmanTree;
    huffmanTree.buildTree(freqMap);  // mapת��Ϊvec
    map<char, string> codes;//�����������
    huffmanTree.generateCodes(huffmanTree.getRoot(), "", codes);

    // �������������
    for (auto& entry : codes) {
        cout << entry.first << " : " << entry.second << endl;
    }

    // ���Ƶ��
    for (auto& ent : freqMap) {
        cout << ent.first << " : ���ִ��� " << ent.second << endl;
    }



    // ��ԭ��ת��Ϊֻ�� '0' �� '1' ����ʽ
    string encodedBinary = huffmanTree.encodeToBinary(input, codes);
    cout << "���� " << encodedBinary << endl;



    cout << "�Ƿ����ɽ���y/n" << endl;
    char T;
    cin >> T;

    if (T == 'y')
    {
        string encodedbinary;
        cin >> encodedbinary;
        // �������������
        string decodedText = huffmanTree.decodeFromBinary(encodedbinary);
        cout << "���� " << decodedText << endl;
    }

    return 0;
}








//
//
//class tree
//{
//public:
//	//Ȩ��ͳ��·���ϵ�Ȩ�����������������Ӹ��ڵ㿪ʼ��������������Ϊ0��������������Ϊ1����¼��ÿ��Ҷ�ӽڵ���������·�����õ����Ӧ�ı��롣��
//	int data;//Ƶ��
//	char cac;
//	tree* parent;
//	tree* left;
//	tree* right;
//	string huffmanCode; // ����������
//
//	tree() :cac(), data(-1), parent(nullptr), left(nullptr), right(nullptr), huffmanCode() {}
//
//	
//
//
//};
//
//
////��������������2n-1���ڵ㣬����0.�����С2n
//
//
//
//class buildtree
//{
//public:
//	map<char,int> codes; // �洢�ַ���Ӧ�ı���
//	tree* array[1000];
//	int idx = 0;
//
//	//�����ַ�����ͳ�Ƶĺ���
//
//	void transform(string bunch)//bunch�Ǵ�����˼
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
//		//cout << "�ַ�������Ϊ" << size;
//	}
//
//	
//
//	//��mapת����vec�����򣬷��س�����vec��Ϊ�����������������ݵ��ַ����ֱ�
//
//	vector<pair<char, int>> sor(map<char, int> codes)
//	{
//		// ����һ���Զ���ıȽϺ�������ֵ��С��������
//		auto comp = [](const pair<char, int>& a, const pair<char, int>& b) {
//			return a.second < b.second;
//		};
//
//		// ��mapת��Ϊvector������ֵ����
//		vector<pair<char, int>> vec(codes.begin(), codes.end());
//		sort(vec.begin(), vec.end(), comp);
//
//		return vec;
//	}
//	//����vec����Ҫ���ɽڵ�����
//
//
//
//	tree* trans(vector<pair<char, int>>& vec)
//	{
//		// ���������½ڵ�
//		tree* a = new tree();
//		tree* b = new tree();
//
//		// ��Ƶ����С�������ַ��ֱ�ֵ���������½ڵ�
//		a->data = vec[0].second;
//		a->cac = vec[0].first;
//		b->data = vec[1].second;
//		b->cac = vec[1].first;
//
//		// ����һ���½ڵ���Ϊ���ǵĸ��ڵ�
//		tree* c = new tree();
//		c->data = vec[0].second + vec[1].second;
//
//		// ��Ƶ����С�������ڵ���Ϊ�½ڵ�������ӽڵ�
//		c->left = a;
//		c->right = b;
//		a->parent = c;
//		b->parent = c;
//
//		// ɾ���Ѿ��������������СƵ�ʵĽڵ�
//		vec.erase(vec.begin(), vec.begin() + 2);
//
//		// ����һ���µļ�ֵ�ԣ������½ڵ�
//		pair<char, int> spair('*', c->data);
//
//		// ���½ڵ���뵽Ƶ�������λ��
//		vec.push_back(spair);
//		sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
//			return a.second < b.second;
//			});
//
//		// ���������ɵ����ڵ� c
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
//				return i.first; // ����ƥ����ַ�
//			}
//		}
//		return '\0'; // ���û���ҵ�ƥ����ַ������ؿ��ַ�
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