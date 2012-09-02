#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cctype>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "respace_stl_ms.h"

#define stricmp strcasecmp

using namespace std;

int debug = 1;

void stringxy(char *string, int beginning, int end);
void stringxy2(char *string, int beginning, int end);
void load_dictionary(ifstream& in,  map<string, string>& data);
void isCharacter(char *text, int beginning, int end, list<matchStack>& mtstack);
void isEndOfLineChar(char *text, int beginning, int end, list<matchStack>& mtstack);
void isWord(char *text, int beginning, int end, map<string, string>& dictionary, list<matchStack>& mtstack);
void isPunct(char *text, int beginning, int end, list<matchStack>& mtstack);
void isNumber(char *text, int beginning, int end, list<matchStack>& mtstack);
void isSpace(char *text, int beginning, int end, list<matchStack>& mtstack);
void isMarkupTag(char *text, int beginning, int end, list<matchStack>& mtstack);
int fscanner(char *string, map<string, string>& data, list<matchStack>& mtstack);
string toLower (const string & s);
string toSpaceless (string s);
string setWordCase (string input, string dictionaryWord);
int hex_to_int(char *hex, char *string);
int interpreter();
int respacefile(char *file);
void usage(char *cmd);

int main (int argc, char *argv[])
{
	FILE *stream;
	char line [1000];
	char temp [1000];

	if (argc == 1) {
		usage(argv[0]);
		exit (1);
	}
        // run the spaceless interpreter
	if ((argc == 2) && (stricmp("--int", argv[1]) == 0)) { 
		interpreter();	
		exit(1);
	}
        // respace a file
	if ((argc == 3) && (stricmp("--file", argv[1]) == 0)) {
	  	respacefile(argv[2]); 
		exit(1);

	}
        // process a hex string
	if ((argc == 3) && (stricmp("--hex", argv[1]) == 0)) {
                std::ifstream in("dictionary.txt");
                std::map<std::string, std::string> dictionary;
                std::list<matchStack> outList;
		std::list<matchStack> stack;
		load_dictionary(in, dictionary);
		hex_to_int(argv[2], line);	
		// cout << "line " << line << endl;
		fscanner(line, dictionary, stack);
		processList(stack, outList);
		displayListWords(outList);


	}
        // stack command line execution
        // display the coordinate match stack list
        if ((argc == 3) && (stricmp("--stk", argv[1]) == 0)) {
                std::ifstream in("dictionary.txt");
                std::map<std::string, std::string> dictionary;
                std::list<matchStack> outList;
                // std::list<int, int, std::string> matchStack;
                std::list<matchStack> stack;
                load_dictionary(in, dictionary);
                fscanner(argv[2], dictionary, stack);
                stack.sort(compare);
                displayList(stack);
                processList(stack, outList);
                displayListWords(outList);
                cout << endl;
        }
        // commandline execution
	else if ((argc == 2))
	{
		std::ifstream in("dictionary.txt");
		std::map<std::string, std::string> dictionary;
		std::list<matchStack> outList;
		// std::list<int, int, std::string> matchStack;
		std::list<matchStack> stack;
		load_dictionary(in, dictionary);
		fscanner(argv[1], dictionary, stack);
		stack.sort(compare);
		// displayList(stack);
		processList(stack, outList);
		displayListWords(outList);
		cout << endl;
	}


}

// forward scanner
int fscanner(char *string, map<string, string>& data, list<matchStack>& mtstack) {
        int i = 0, j, k, ctr = 0;
        int length = 0;

	length = strlen(string) - 1;
	if (debug == 0) printf("\nforward scan %s", string);

        for(i = 0; i <= length; i++)
	    for(j = 0; j <= length; j++)
	    {
		if (j >= i) {
			if (debug == 0) stringxy(string, i, j);
			isCharacter(string, i, j, mtstack);
			isWord(string, i, j, data, mtstack);
			isPunct(string, i, j, mtstack);
			isNumber(string, i, j, mtstack);
			isEndOfLineChar(string, i, j, mtstack);
			isSpace(string, i, j, mtstack);
			isMarkupTag(string, i, j, mtstack);
		}
 	    }
	// printf("\n");
	return (0);
}



// show string from x to y
void stringxy(char *string, int beginning, int end)
{
    printf("\nString from (%i, %i) ", beginning, end);
    int i = 0;
    for (i = beginning; i <= end; i++)
    {
              printf("%c", string[i]);
    }

}

// show string from x to y stl string version
void stringxy2(char *string, int beginning, int end)
{
     printf("\nString from (%i, %i) ", beginning, end);
     int i = 0;
     for (i = beginning; i <= end; i++)
     {
         printf("%c", string[i]);
     }

}

// Add one letter character
void isCharacter(char *text, int beginning, int end, list<matchStack>& mtstack)
{
   string tmp;
   char chartmp;
   chartmp = (char) text[beginning];
   tmp = text[beginning];
   if (isalpha(chartmp) && (beginning == end) )  
   //	insertList(mtstack, beginning, end, 3, tmp);
   insertListUnique (mtstack, beginning, end, LETTERMATCH, tmp);
}

// Add one character
void isEndOfLineChar(char *text, int beginning, int end, list<matchStack>& mtstack)
{
    string tmp;
    char endc;
    endc =  text[beginning];
    tmp = text[beginning];
    if (beginning = end) {
	if ((text[beginning] == '\n') || (text[beginning] == '\r') || (text[beginning] == '\f')) {
	    insertList(mtstack, beginning, end, ENDLINEMATCH, " ");
	}
    }

}



//void isWord(char *text, int beginning, int end, map<string, string>& dictionary, list<int, int, string>& mtstack)
void isWord(char *text, int beginning, int end, map<string, string>& dictionary, list<matchStack>& mtstack)
{
	 int i = 0;
	 string tmp, tmpCase, tmpCaseB;
         for (i = beginning; i <= end; i++)
         {
            tmp += text[i];
         }

	 map <string, string>::const_iterator CIT;
	 CIT = dictionary.find(toLower(tmp));
         if (CIT != dictionary.end()) {
	     // cout << "entry found " << CIT.first << "\n";
	     if (debug == 0) cout << "\nentry found " << tmp;
	     tmpCaseB = CIT->second;
	     // cout << "entry found " << tmpCaseB << "\n";
	     tmpCase = setWordCase(tmp, tmpCaseB);
	     // cout << "entry found " << tmpCase << "\n";
	     // insertList(mtstack, beginning, end, 0, CIT->second);
	     insertListUnique(mtstack, beginning, end, WORDMATCH, tmpCase);
	   }


}

void isPunct(char *text, int beginning, int end, list<matchStack>& mtstack)
{
	// string names[] = {"", "", "", ""};

	int i = 0, value = 0;
	string tmp;
        for (i = beginning; i <= end; i++)
        {
               if(!ispunct(text[i])) {
		       value = 1;
		}
	       else {
			tmp += text[i];
		}
	}
	if (value == 0) {
		if (debug == 0) cout << "\nPunctuation found " << tmp;
		insertListUnique(mtstack, beginning, end, PUNCTUATIONMATCH, tmp);
	}


}

void isNumber (char *text, int beginning, int end, list<matchStack>& mtstack)
{
        int i = 0, value = 0;
        string tmp;
        for (i = beginning; i <= end; i++)
        {
               if(!isdigit(text[i])) {
                     value = 1;
                  }
                  else {
                     tmp += text[i];
                  }
        }
	if (value == 0) {
	    if (debug == 0) cout << "\nNumber found " << tmp;
	    insertListUnique(mtstack, beginning, end, NUMBERMATCH, tmp);
	}


}

void isSpace (char *text, int beginning, int end, list<matchStack>& mtstack)
{

        int i = 0, value = 0;
	string tmp;
	for (i = beginning; i <= end; i++)
        {
	     if(!isspace(text[i])) {
                value = 1;
             }
	     else {
	        tmp += text[i];
	     }
        }
	if (value == 0) {
            if (debug == 0) cout << "\nSpace found " << tmp;
	    insertListUnique(mtstack, beginning, end, SPACEMATCH, tmp);
        }


}

void isMarkupTag (char *text, int beginning, int end, list<matchStack>& mtstack)
{
	int i = 0, value = 1; 
	string tmp;
	if (text[beginning] == '<' && text[end] == '>') {
		value = 0;
	}
	for (i = beginning; i <= end; i++)
	{
		if ((text[i] == '<') && (i != beginning)) value++;
		tmp += text[i];

	}
	if (value == 0) { 
		if (debug == 0) cout << "\nTag found " << tmp;
		insertListUnique(mtstack, beginning, end, TAGMATCH, tmp);
	}

}

void load_dictionary(ifstream& in,  map<string, string>& data) 
{

        string key;
        string tmp;

        while (!in.eof()) {
        std::getline(in, tmp, '\n');
	key = tmp;
	key = toLower(key);
	key = toSpaceless(key); // strip out spaces
        data.insert(std::make_pair(key, tmp));
        // data.insert(std::make_pair(tmp, tmp));
	// cout << "dic " << key  << " 1 " << tmp << "\n";
        key.clear();
        tmp.clear();
        }
	if (debug == 0) cout << "dictionary size " << data.size() << "\n";
}


string toLower (const string & s)
{
	string d (s);

	std::transform (d.begin (), d.end (), d.begin (), (int(*)(int)) tolower);
        return d;
}

string toSpaceless (string s)
{
	std::string::iterator it = std::remove_if(s.begin(), s.end(),
	std::bind2nd(std::equal_to<char>(), ' '));
	s = std::string(s.begin(), it);
	return s;
}

// set the matchstack word to the input case
string setWordCase (string input, string dictionaryWord)
{
	string tmp;
	string::const_iterator inputIter = input.begin();
	for (string::const_iterator p = dictionaryWord.begin(); p != dictionaryWord.end(); ++p)
	{
		if (isspace(*p)) {
			tmp += " ";
		}
		else if (ispunct(*inputIter)) {
			tmp += *p;
		}
		else if (isupper(*inputIter) && (!isspace(*p))) {
			tmp += toupper(*p);
			++inputIter;
		}
		else if (islower(*inputIter) && (!isspace(*p))) {
			tmp += tolower(*p);
			++inputIter; 	
		}
	}

	return tmp;
}


int hex_to_int(char *hex, char *string)
{

	int sum = 0, i = 0, j = 0, k = 0;
	int length;
	length = strlen(hex) / 2;
	char res[5], *stop;
	char b;
	res[0] = '0';
	res[1] = 'x';
	res[4] = 0;
	for (i = 0; i < length; i++) {
		if (i != 0) j = j + 2;
		res[2] = hex[j];
		res[3] = hex[j + 1];
	 	sum = strtol(res, &stop, 16);
	 	string[k]  = sum;
		k++;
		string[k] = 0;
	}


	return 0;

} 

// Call an instance of the interpreter
int interpreter()
{
	std::ifstream in("dictionary.txt");
	std::map<std::string, std::string> dictionary;
	std::list<matchStack> stack;
	std::list<matchStack> outList;
	load_dictionary(in, dictionary);

	char array[1000];

	printf("\nInterpreter 1.0\n");
	printf("\nEnter 10 sentences!!\n");
	for (int i = 0; i < 10; i++) {
		 printf("Sentence %i: ", i);
		 fgets(array, 999, stdin);
		 fscanner(array, dictionary, stack);
		 stack.sort(compare);
		 processList(stack, outList);
		 // displayList(outList);
		 displayListWords(outList);
		 list<matchStack>::iterator iter;
		 stack.erase( stack.begin(),  stack.end());
		 list<matchStack>::iterator iterb;
		 outList.erase(outList.begin(), outList.end());
		 array[0] = '\0';


	}
	return (0);
}

/// respace a text file 
int respacefile(char *file)
{
	        FILE *stream;
		char line [1000];
		std::ifstream in("dictionary.txt");
		std::map<std::string, std::string> dictionary;
                std::list<matchStack> stack;
                std::list<matchStack> outList;
                load_dictionary(in, dictionary);

		// Open the Dictionary file or display an error if not present
		if ((stream = fopen(file, "r")) == NULL)
		{
			fprintf(stderr, "\nDictionary Error\n");
			exit(1);
		}

		while( !feof( stream ) )
		{
			/* Attempt to read in 10 bytes: */
			if (fgets( line, 999, stream )) {
			fscanner(line, dictionary, stack);
			// cout << "line " << endl;
			stack.sort(compare);
		        // displayList(stack);
		        processList(stack, outList);
		        // displayList - Display the coordinate list
		        // displayList(outList);
			displayListWords(outList);
			list<matchStack>::iterator iter;
			stack.erase( stack.begin(),  stack.end());
			list<matchStack>::iterator iterb;
			outList.erase(outList.begin(), outList.end());
			}
		}

		cout << endl;

		fclose(stream);



}



void usage(char *cmd)
{

	       printf("\n\nRespace Decoder version .450b");
	       printf("\nCommand Path: %s\n", cmd);

	       printf("\nUSAGE [-option] [INPUT FILE] \n");
	       printf("USAGE [-option]\n\n");
	       // printf("--version       -  Display the program version.\n");
	       printf("%s --file [file]     -  Respace a command line string.\n", cmd);
	       printf("%s --int             -  Execute the interpreter.\n", cmd);
	       printf("%s --hex             -  Execute and despace the hex code argument.\n", cmd);
	       printf("%s --stk             -  Respace a argument string and display the matchstack.\n", cmd);
	       printf("%s spacelessstring   -  Respace a argument string.\n", cmd);
	       printf("\n\nUSAGE Examples:\n");
	       printf("   cmdline: respace Iamhereinavalleyoffame\n");
	       printf("   I am here in a valley of fame\n");
	       printf("   cmdline: respace --file test\n");
	       printf("   This is a test!!\n");

}
