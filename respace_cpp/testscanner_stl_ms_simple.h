#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class matchStack {

      private:
      int beginning;                // starting index
      int ending;                   // ending index
      int wordtype;                 // ending index
      int wordlength;                 // ending index
      std::string word;

      public:
      void Stack(void);                 // init to empty
      void display(void);               // display match stack 
      void displayobj(matchStack*);     // display match stack 
      int  getBeg(void);        	// get the beginning index 
      int  getEnd(void);      		// get the end index 
      int  getWordType(void);      	// get the word type 
      std::string getWord(void);      	// get the word
      void add(int start, int end, int wtype, string wordtext );   // stores element on top of stack
};

void matchStack::Stack(void)
{
	beginning = 0;
	ending = 0;
	wordtype = 0;
	wordlength = 0;
}

void matchStack::add(int start, int end, int wtype, string wordtext )
{
	beginning = start;
	ending = end;
	wordtype = wtype;
	word = wordtext;
	wordlength = word.length();
}

int matchStack::getBeg(void)
{
	return ( matchStack::beginning);
}

int matchStack::getEnd(void)
{
        return ( matchStack::ending);
}

int matchStack::getWordType(void)
{
	return ( matchStack::wordtype);
}

std::string matchStack::getWord(void)
{
	return ( matchStack::word);
}

void matchStack::display(void)
{
	cout << "(" << beginning << ":" << ending << ") " << wordtype << " " << word << "\n";

}

void matchStack::displayobj(matchStack*)
{
	cout << "(" << beginning << ":" << ending << ") " << wordtype << " " << word << "\n";
}

bool compare (matchStack& a, matchStack& b) {
	if (a.getBeg() <  b.getBeg() ) {
	            return true;

	}
	else if (a.getBeg() ==  b.getBeg() ) {
		if ( a.getEnd() < b.getEnd()) {
		return true;	
		}
		else if ( a.getEnd() > b.getEnd()) {
			return false;
		}
	}
	else if (a.getBeg() >  b.getBeg()) {
		return false;
	}
}

void displayList (std::list<matchStack> l)
{
	matchStack z;
	for (list<matchStack>::iterator p = l.begin(); p != l.end(); ++p)
	{
		z = *p;
		z.display();

	}

}

void insertList (std::list<matchStack> &insertlist, int start, int end, int wtype, string wordtext)
{
        matchStack p;
	p.add(start, end, wtype, wordtext);
	insertlist.push_back(p);
}


void insertListUnique (std::list<matchStack> &insertlist, int start, int end, int wtype, string wordtext)
{
	matchStack p;
	matchStack result;
	int add = 0;

	p.add(start, end, wtype, wordtext);
	for (list<matchStack>::iterator p = insertlist.begin(); p != insertlist.end(); ++p)
	{
		result = *p;
		if ((result.getBeg() == start) && (result.getEnd() == end)) {
			add = 1;		
		}
	}
	if (add == 0) insertlist.push_back(p);
}

void processList (std::list<matchStack> l)
{
	std::list<matchStack> outList;
	matchStack z;
	matchStack result;
	z.Stack();
	result.Stack();
	int start = 0;
	// std::list<matchStack> out;
	for (list<matchStack>::iterator p = l.begin(); p != l.end(); ++p)
        {
                z = *p;
		if ((start != z.getBeg()) && (result.getEnd() != z.getEnd())) {
			if ((result.getBeg() != z.getBeg()) && (result.getEnd() != z.getEnd())) {
		//			&& (result.getWord() != z.getWord())) {
		    // outList.push_back(result);
		    insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord()); 
		    start = result.getEnd() + 1;
			}
		}
		if ((z.getBeg() == start) && (z.getEnd() > result.getEnd())) {
		result.add(z.getBeg(), z.getEnd(), z.getWordType(), z.getWord()); 
		// if ( p == l.end()) {
	//		cout << "xx";
//		insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
//			}
		}
        }
	 if ((z.getBeg() == start) && (z.getEnd() > result.getEnd())) {

		  insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
	}
	// result.display();
	//sort(outList);	
	cout << "displaying list " << endl;	
	displayList(outList);	
}

int test (void)
{
        int a = 0, b = 0;
	std::string word = "abc";
	std::list<matchStack> l;
	matchStack p;
	matchStack z;
	p.Stack();
	p.add(0, 1, 2, word);
	p.display();
	l.push_back(p);
	p.add(1, 3, 4, "new");
	l.push_back(p);
	p.add(1, 2, 4, "new");
	l.push_back(p);
	p.add(1, 8, 4, "old");
	l.push_back(p);
	insertList(l, 9, 0, 1, "Here is");
	insertList(l, 7, 8, 1, "Here's");
	cout << "Beginning " << p.getBeg() << endl;
	cout << "Ending " << p.getEnd() << endl;
	cout << "Word Type " << p.getWordType() << endl;
	cout << "Word " << p.getWord() << endl;
	displayList(l);
	l.sort(compare);
	displayList(l);
	return (0);
}
