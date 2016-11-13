#include "parser.h"
#include <fstream>
#include <sstream>

using namespace std;

void replace_char_codes(string &word){
	size_t found = word.find("\\x20");
	if (found != string::npos)
	{
		word.replace(found, 4, " " );
	}
}

vector<string> split(const string &line){
	/*
	line=int_string____string_string_int
	split_line= {int, string, string, string, int}
	>> str
	*/
	string word;

	istringstream iss = istringstream(line);
	vector <string> split_line;
	
	while (!iss.eof())
	{
		
		iss>>word;
		replace_char_codes(word);
		split_line.push_back(word);
}

	return split_line;
}




// / - корень диска
// . - текущая папка
// .. - выше на один уровень
// dir - папка dir

// /dir - корень диска



/*
Вход: 1 текстовый файл (=БД)
Выход: динамический двумерный массив Element'ов
*/

vector <vector <string> > parse(string file_name){
	ifstream cin = ifstream("data/" + file_name +".txt");
	if (!cin.good())
		throw ParseFailedException("File does not exist");
	string line;
	vector <vector <string> > a;
	vector<string> split_line;


	while(!cin.eof())
	{
		getline(cin, line);
		split_line=split(line);
		a.push_back(split_line);
	}

	return a;
}


