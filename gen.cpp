#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>
#include <random>
using namespace std;

int main()
{
	fstream fin, fout;
	vector<string> words;
	std::random_device rd;
	std::mt19937 gen(rd());
	
	
	fin.open("sorteddict.txt", ios::in);
	fout.open("gensorted3gramscpp.txt", ios::out|ios::trunc);
	
	for(;;)
	{
		string s;
		if(!getline(fin, s))
			break;
		words.push_back(s);
	}
	
	int a = 0;
	int b = words.size() - 1;
	int t = b/80;
	int N = 150000000;
	for(int n = 0; n < N; n += 80, a++)
	{
		int ii2 = -1;
		
		for(int i = 0; i < 80; i++)
		{
			int i1 = a;
			std::uniform_int_distribution<> i2(ii2+1, t*(i+1));
			std::uniform_int_distribution<> i3(a, b);
			ii2 = i2(gen);
			std::uniform_int_distribution<> i4a(1, 100000000);
			std::uniform_int_distribution<> i4b(1, 50000);
			int i4 = i4a(gen)/i4b(gen) + 1;
			
			fout<<words[i1]+" "+words[i2(gen)]+" "+words[i3(gen)]+" "+to_string(i4)+"\n";
		}
	}
	
	return 0;
}
