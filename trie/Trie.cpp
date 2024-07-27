
#include "Trie.h"
using namespace std;
// Возвращет новый узел с пустыми детьми
void fullfillvec(vector<string>& vec) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        vec.push_back("");
    }
}
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}
// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
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

// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
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