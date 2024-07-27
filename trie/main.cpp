#include "Trie.h"
auto main() -> int {
	TrieNode* word=getNewNode();
	insert(word, "cat");
	insert(word, "call");
	insert(word, "cult");
	insert(word, "run");
	insert(word, "rut");
	insert(word, "root");
	insert(word, "seek");
	insert(word, "play");
	insert(word, "destroy");
	insert(word, "loop");
	insert(word, "grind");
	insert(word, "collapse");
	insert(word, "bab");
	std::cout << "Input ur word: " << std::endl;
	string result_str;
	int choice = 0;
	string example_str;
	TrieNode* move = word;
	vector<string> str_arr;
	int counter = 0;
	while (1)
	{
		fullfillvec(str_arr);
		std::cin >> example_str;
		std::cout << "If u want to use dictionary, press: 1\n" << "If u want to exit, press any number\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			move = moveStartPrefix(move, example_str);
			autocomplete(move, word, example_str, result_str, counter, str_arr);
			move = word;
			example_str = autocorrect(str_arr, example_str);
			std::cout << example_str;
			str_arr.clear();
			return 0;
		}
		default:
			std::cout << example_str;
			return 0;
		}
		


	}
}