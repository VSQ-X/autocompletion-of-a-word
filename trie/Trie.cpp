
#include "Trie.h"
using namespace std;
// ��������� ����� ���� � ������� ������
void fullfillvec(vector<string>& vec) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        vec.push_back("");
    }
}
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}
// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (index < 0)
        {
            return false;
        }
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}

TrieNode* moveStartPrefix(TrieNode* root, string& output)
{
    TrieNode* move = root;
    int i = 0;
    int index = 0;
    while (i != output.length())
    {
        index = output[i] - 'a';
        if (index < 0)
        {
            move = root;
            i++;
            continue;
        }
        if(move->children[index])
            move = move->children[index];
        else
        {
            return root;
        }
        i++;
    }
    //_str += output;
    return move;
}
void autocomplete(TrieNode* move, TrieNode* root, string& output, string result, int& element_counter, vector<string>& str_arr, int jk)
{
    if(jk!=-1)
        result += 'a' + jk;
    if (search(root, output+result))
    {
        str_arr[element_counter] = output+result;
        std::cout << str_arr[element_counter]<<std::endl;
        element_counter++;
        return;
    }
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (move->children[j])
        {
            jk = j;
            autocomplete(move->children[j], root, output, result, element_counter, str_arr, jk);
        }
    }
   
}
string autocorrect(vector<string>& str_arr, string output) {
    std::cout << "Select a number from the suggested words in the list, if any: " << std::endl;
    std::cout << "Press 404 to skip changes\n";
    int choice;
    int i = 0;
    if (str_arr[0] == "")
    {
        std::cout << "there are no autocomplete words for this word" << std::endl;
        return output;
    }
    for (; i < ALPHABET_SIZE; i++)
    {
        if (str_arr[i]=="")
            break;
        std::cout << str_arr[i] << " - " << i << std::endl;
    }
    while (str_arr[0] != "")
    {
        std::cin >> choice;
        if (choice == 404)
            return output;
        if(choice<0 || choice > i)
        {
            std::cout << "wrong index";
        }
        else
        {
            return str_arr[choice];
        }
    }

}