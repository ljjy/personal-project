// 统计文本文件中的字符数、单词数和单词频率最高的十个单词
//

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Tools.h"
#include "ArgParser.h"
#include <fstream>
#include <cstdio>
#include "Scanner.h"
#include "ScanProcesser.h"

using namespace std;

int showResults(struct Top10Words tp, int charNum, int lineNum, int wordNum);

int main(int argc, char* argv[]){
	
	// make sure the arg valid
	ArgParser argParser(argc,argv);
	string filename = argParser.getFileName();
	if (filename.empty()){
		argParser.helpDoc();
		return 1;
	}
	
	//string filename = "input.txt";

	map<string, int>* strMap = new map<string, int>();
	ScanProcesser* scanProcesser = new ScanProcesser(strMap);
	Scanner* scanner = new Scanner(filename.c_str(), scanProcesser);
	scanner->scan();
	scanner->processTop10Words();

	struct Top10Words tp = scanner->getTop10words();


	int charNum = scanner->getCharNum();
	int lineNum = scanner->getLineNum();
	int wordNum = scanner->getWordNum();


	showResults(tp, charNum, lineNum, wordNum);


	return 0;


}


int showResults(struct Top10Words tp, int charNum, int lineNum, int wordNum) {
	cout << "characters: " << charNum << endl;
	cout << "words: " << wordNum << endl;
	cout << "lines: " << lineNum << endl;
	for (int i = 0; i < 10 && i < wordNum;i++) {
		if (!(tp.str[i].empty()))
		cout << tp.str[i] << ": " << tp.count[i] << endl;
	}
	return 0;
}