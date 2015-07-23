#include <iostream>
#include <cmath>
#include<string>
#include<set>
#include <fstream>
#include<map>
#include<algorithm>

using namespace std;

set<string> words;
map<int,string> listOfValidWords;
char scoreArray[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
void permutation(string s,int i,int n);
void printPowerSet(char *word, int word_size)
{

    unsigned int pow_set_size = pow(2, word_size);
    int counter, j;
    string combination = "";
    /*Run from counter 000..0 to 111..1*/
    for(counter = pow_set_size -1 ; counter >= 0; counter--)
    {
        combination = "";
      for(j = 0; j < word_size; j++)
       {
          /* Check if jth bit in the counter is word
             If word then print jth element from word */
          if(counter & (1<<j))
                 combination += word[j];

       }
        permutation(combination,0,combination.length());

    }
}

void swap(char& a, char& b)
{
    char temp;
    temp = a;
    a = b;
    b = temp;
}



bool isValidWord(string s){
    bool is_in = words.find(s) != words.end();
    return is_in;
}

int findWordScore(string s){
	
        int i = 0 , index, score = 0;
        for(i = 0 ; i < s.length() ; i++){
            index = s[i] - 'a';
            score += scoreArray[index];
        }
        return score;
}

void insertIntoMap(int key,string word)
{
    if (listOfValidWords.find(key) != listOfValidWords.end())
	{
        listOfValidWords[key] += " " + word;
    }
    else
        listOfValidWords[key] = word;
}

void replace(string s, int j)
{
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='@')
			s[i]=j;
	}
	cout<<s<<endl;
}
/* Function to obtain permutations of string characters */
void permutation(string s,int i,int n)
{
    int j;
    int pos = s.find('@');
    if (i == n)
    {
    	if(pos != -1)
    	{
    		for(char itr='a'; itr<='z'; itr++)
    		{
    			s[pos]=itr;
            	if(isValidWord(s))
                	insertIntoMap(findWordScore(s)-scoreArray[itr-'a'],s);
    		}
		}
		else
		{
			if(isValidWord(s))
            insertIntoMap(findWordScore(s),s);
		}
		
    }
    else
    {
        for (j = i; j < s.length(); j++)
        {
            swap(s[i],s[j]);
            permutation(s, i + 1, n);
            swap(s[i],s[j]);
        }
    }
}


void printBestWords()
{
    int maxScore = 0;
    string p;
    map<int,string>::iterator ii = listOfValidWords.end();
	--ii;
	cout << (*ii).first << "  " << (*ii).second;

}

/*Driver program to test printPowerSet*/
int main()
{
    char input[] = "bera@sk";
    ifstream inFile;
    inFile.open("sowpods.txt");
    string line;
    while (!inFile.eof())
    {
       getline(inFile, line);
       words.insert(line);
     }
    printPowerSet(input, 7);
    printBestWords();
    return 0;
}
