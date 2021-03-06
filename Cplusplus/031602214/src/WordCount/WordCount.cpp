#include"stdafx.h"
#include<iostream>
#include<algorithm>
#include<ctype.h>
#include<string>
#include<string.h>
#include<fstream>
#include<vector>
#include<queue> 
#include"iomanip"
using namespace std;
#define ALPHABET_SIZE 36
string Lines[200];
string Words[1000];
string str[10];
int ans[10];
int rows = 0, ct = 0, d = 0, a = 0;
struct FrequentWord
{
	string word;
	int c = 0;
	friend bool operator < (FrequentWord a, FrequentWord b)
	{
		if (a.c == b.c)
			return a.word<b.word;
		else
			return a.c > b.c;
	}
}fqtWord;
priority_queue<FrequentWord> q;
typedef struct trie_node
{
	int count;
	string word;
	trie_node *children[ALPHABET_SIZE];
}*trie;

trie_node* create_trie_node()
{
	trie_node* pNode = new trie_node();
	pNode->count = 0;
	for (int i = 0; i<ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	return pNode;
}

void trie_insert(trie root, string key)
{
	trie_node* node = root;
	string p = key;
	string w;
	int  c = 0;
	for (int i = 0;i<p.length();i++)
	{
		if (p[i] >= 'A' && p[i] <= 'Z')
		{
			p[i] += 32;
		}
		if (p[i] >= '0' && p[i] <= '9' && node->children[p[i] - '0'] == NULL)
		{
			node->children[p[i] - '0'] = create_trie_node();
		}
		else if (p[i] >= 'a' && p[i] <= 'z' && node->children[p[i] - 'a' + 10] == NULL)
		{
			node->children[p[i] - 'a' + 10] = create_trie_node();
		}

		if (p[i] >= '0' && p[i] <= '9')
			node = node->children[p[i] - '0'];
		else if (p[i] >= 'a' && p[i] <= 'z')
			node = node->children[p[i] - 'a' + 10];
		w += p[i];
	}
	node->count += 1;
	node->word = w;
	//return node;
}


int trie_search(trie root, string key)
{
	string p = key;
	trie_node* node = root;
	int i = 0;
	while (i<p.length() && node != NULL)
	{
		if (p[i] >= 'A' && p[i] <= 'Z')
		{
			p[i] += 32;
		}
		if (p[i] >= '0' && p[i] <= '9')
			node = node->children[p[i] - '0'];
		else if (p[i] >= 'a' && p[i] <= 'z')
			node = node->children[p[i] - 'a' + 10];
		i++;
	}

	if (node == NULL)
		return 0;
	else
		return node->count;
}
/*
void triePreorderTraversal(trie root)
{
//cout<<"root:"<<root<<endl;;
if( root == NULL )
return;
if( root->count != 0 )
{
//cout<<"ssf";
while(root->count--)
{
//DCWord[d] = root->word;
d++;
}
//ofstream out(".txt");
//out.write(str1,strlen(str1));//把字符串str1全部写到yyy.yyy中
}
for(int i = 0; i<ALPHABET_SIZE; i++ )
{
//cout<<"root->children[i]:"<<root->children[i]<<"     "<<i<<endl;
triePreorderTraversal( root->children[i] );
}
}*/



int CharacterCount(char *fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "文件无法打开" << endl;
		return 0;
	}
	int words = 0;
	rows = 0;
	char text[1000];

	while (!file.eof() && file.peek() != EOF)
	{
		file.getline(text, 1000);
		words += strlen(text);
		Lines[rows] = text;
		//cout<<rows<<"     "<<Lines[rows]<<"   "<<text<<endl;;
		rows++;

	}
	//cout << "rows:" << rows << endl;
	//cout << "words" << words << endl; 
	file.close();
	return rows + words - 1;
}

int WordCount()
{
	int len, i, j, k;
	for (i = 0;i<rows;i++)
	{
		len = Lines[i].length();
		for (j = 0;j<len;j++)
		{
			if (Lines[i][j] >= 'A' && Lines[i][j] <= 'Z')
			{
				Lines[i][j] += 32;
			}
		}
	}
	for (i = 0;i<rows;i++)
	{
		len = Lines[i].length();
		for (j = 0;j <= len - 4;j++)
		{
			int m = j;
			//cout<<"len:"<<len<<" "<<"j"<<j<<endl;
			if (isalpha(Lines[i][j]) && isalpha(Lines[i][j + 1]) && isalpha(Lines[i][j + 2]) && isalpha(Lines[i][j + 3]))
			{
				for (k = j + 4;k<len;k++)
				{
					if (!isalnum(Lines[i][k]))
					{
						break;
					}
				}
				j = k;
				Words[ct] = Lines[i].substr(m, k - m);
				//cout<<"i:"<<i<<"    "<<"j:"<<m<<"  "<<"k"<<k<<"   "<<Words[ct]<<endl; 
				ct++;

			}
		}
	}
	return ct;
}
trie_node* FrequentWordCount()
{
	int flag = 1;
	sort(Words, Words + ct);
	//cout<<"F:"<<endl;;
	//for(int i=0;i<ct;i++)
	//	cout<<Words[i]<<"  "<<i+1<<endl;
	trie root = create_trie_node();
	for (int i = 0;i<ct;i++)
	{
		trie_insert(root, Words[i]);
	}

	for (int i = 0;i<ct;i++)
	{
		flag = 1;
		for (int j = 0;j<i;j++)
		{
			if (Words[i] == Words[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		int ct = trie_search(root, Words[i]);
		fqtWord.c = ct;
		fqtWord.word = Words[i];
		if (q.size()<10)
		{
			q.push(fqtWord);
		}
		else
		{
			q.push(fqtWord);
			q.pop();
		}
	}
	while (!q.empty())
	{
		fqtWord = q.top();
		str[d] = fqtWord.word;
		ans[d] = fqtWord.c;
		d++;
		q.pop();
	}
	return root;
}
int EffectiveLinesCount()
{
	int c = 0;
	int flag;
	for (int i = 0;i<rows;i++)
	{
		int len = Lines[i].length();
		flag = 1;
		for (int j = 0;j<len;j++)
		{
			if (Lines[i][j] != ' ' && Lines[i][j] != '\t' && Lines[i][j] != '\n')
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			c++;
	}
	return c;
}
int main(int argc, char* argv[])
{
	ofstream out("result.txt");

	if (argv[1] == NULL)
	{
		cout << "输入为空" << endl;
		return 0;
	}

	int word, line, character;
	trie root = create_trie_node();
	while (1)
	{
		character = CharacterCount(argv[1]);
		if (character != -1)
			break;
	}
	word = WordCount();
	line = EffectiveLinesCount();
	FrequentWordCount();

	out << "characters：" << character << endl;
	out << "words: " << word << endl;
	out << "lines: " << line << endl;
	for (int i = d - 1;i >= 0;i--)
	{
		if (out.is_open())
		{
			out << "<" << str[i] << ">: " << ans[i] << endl;
		}
		else
		{
			cout << "写文件失败" << endl;
		}
	}

	out.close();

	return 0;
}
