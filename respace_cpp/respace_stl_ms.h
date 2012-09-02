#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "respace_stl_wordtypes.h"

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

void displayListWords (std::list<matchStack> l)
{
	matchStack z;
	list<matchStack>::iterator p;
	int currentword = 9;
	int lastword = 9;
	int start = 0;
	for (p = l.begin(); p != l.end(); ++p)
	{
	     	z = *p;
	     	currentword = z.getWordType();

	     	if ((currentword == WORDMATCH)) {
			if (lastword != 9 && lastword != SPACEMATCH) cout << " ";
			cout << z.getWord();
 		}
		// punctuation
		if ((currentword == PUNCTUATIONMATCH)) {
		        cout << z.getWord() << " ";
		}
		else if ((currentword == NUMBERMATCH)) {
			if (lastword != 9) cout << " "; 
		        cout << z.getWord();
                }
		// letter
		else if ((currentword == LETTERMATCH)) {
                        if (lastword != 1 && lastword != 3 && start != 0)  cout << " ";
		        cout << z.getWord();
                }
		else if ((currentword == ENDLINEMATCH)) {
                      cout << endl;
	  	}
		// space
		else if ((currentword == SPACEMATCH)) {
			cout << z.getWord();
		}
		// Tag match is experimental
		else if ((currentword == TAGMATCH)) {
			cout << z.getWord();
		}
		else
		{
			//cout << z.getWord();
		}
		lastword = currentword;
		if (start == 0) start = 1; // The first element is no longer true 

       }
//		cout << endl;	

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


// is clearly the first entry in the matchstack or it is (0,x) and there are no other 0, xs);
bool isFirstWord (std::list<matchStack> &insertlist,  int start, int end, int wtype, string wordtext)
{
	matchStack result;
	int add = 0;

	if (start == 0) {
        	for (list<matchStack>::iterator p = insertlist.begin(); p != insertlist.end(); ++p)
        	{
			result = *p;
			if ((result.getBeg() == start) && (result.getEnd() > end)) 
			// if ((result.getBeg() == start) && (result.getEnd() <= end)) 
			add = 1;
		}
		if (add == 0) return true;

	}

	return false;
}

// is clearly the first entry in the matchstack or it is (0,x) and there are no other 0, xs);
// improved
bool isFirstWord2 (std::list<matchStack> &insertlist,  int start, int end, int wtype, string wordtext)
{
	matchStack result;
	int add = 0;

	if (start == 0) {
		for (list<matchStack>::iterator p = insertlist.begin(); p != insertlist.end(); ++p)
		{
			result = *p;
			if ((result.getBeg() == end) && (result.getEnd() > end) ) {
			 add = 1;    
			}
		}

	}
	if (add == 0) return true;
	return false;

}

// This i think is broken since result doesn't pointto  anything
bool isConjoining (std::list<matchStack> &insertlist,  int start, int end, int wtype, string wordtext)
{

	matchStack p;
	matchStack result;
	int add = 0;

	p.add(start, end, wtype, wordtext);
	for (list<matchStack>::iterator p = insertlist.begin(); p != insertlist.end(); ++p)
	{
		// result = *p; // expirament
		if ((result.getBeg() < start) && (result.getBeg() >= end)) {
			cout << "conjoining" << endl;
			return true; 
		}
		if ((start == 0) && ((result.getEnd() - 1) < end) && (result.getBeg() == 0)) {
			cout << "conjoining" << endl;
			 //   return true;
		}


	}
	return false;
}

// This is the new version of isConjoining which is corrected
bool isOverlapping (std::list<matchStack> &insertlist,  int start, int end, int wtype, string wordtext)
{
	matchStack result;
	int add = 0;
/*
	for (list<matchStack>::iterator p = insertlist.begin(); p != insertlist.end(); ++p)
        {
		result = *p;
		if ((result.getBeg() < start) && (result.getEnd() >= end)) {
			return true;
		}

	}
*/
	return false;

}

// The current hacked processList
void processList2 (std::list<matchStack> &l, std::list<matchStack> &outList)
{
	matchStack z;
	matchStack result;
	z.Stack();
	result.Stack();
	int start = 0;
	int pos = 0;

	// for (list<matchStack>::iterator p = l.begin(); p != l.end(); ++p)
	for (list<matchStack>::iterator p = l.begin(); p != l.end(); p++)
	{
		z = *p;
		pos++;

		// cout << "processlist " <<  z.getWord() << " " << pos << " " << l.size() << endl;
		
		if (isFirstWord(l, z.getBeg(), z.getEnd(), z.getWordType(), z.getWord())) { 
		 insertListUnique(outList, z.getBeg(), z.getEnd(), z.getWordType(), z.getWord());
		 // cout << "truexljskadjflksd " << z.getWord() << " " << pos << endl;
		 start = result.getEnd() + 1; 
		 result.add(z.getBeg(), z.getEnd(), z.getWordType(), z.getWord());
		}
		if ((start != z.getBeg()) && (result.getEnd() != z.getEnd())) {
			if ((result.getBeg() != z.getBeg()) && (result.getEnd() != z.getEnd()) &&
				!isConjoining(outList, z.getBeg(), z.getEnd(), z.getWordType(), z.getWord()) ) {
		//			&& (result.getWord() != z.getWord())) {
		    // outList.push_back(result);
		    // result.add(z.getBeg(), z.getEnd(), z.getWordType(), z.getWord()); 
		     insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord()); 
		    start = result.getEnd() + 1;
			}
		}
		if ((z.getBeg() == start) && (z.getEnd() > result.getEnd())) {
		result.add(z.getBeg(), z.getEnd(), z.getWordType(), z.getWord()); 
		// if ( p == l.end()) {
//			cout << "xx";
//		insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
//			}
		}
		if ((pos == l.size()) && (z.getEnd() == (start))) {
		   insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord()); 
                }
        }
       // if ((z.getBeg() == start) && (z.getEnd() > result.getEnd())) {
	 if ((z.getBeg() == start) && (z.getEnd() > result.getEnd())) {

		  insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
	}
	// result.display();
	//sort(outList);	
	// cout << "displaying list " << endl;	
	// displayList(outList);

	// erase outList
	// outList.clear();	
        // list<matchStack>::iterator iter = outList.begin();
        // outList.erase(iter);
	// cout << " " << outList.size() << endl;
	

}

// This is the proccess List Refactored
// Doesn't work yet
void processListNew (std::list<matchStack> &l, std::list<matchStack> &outList)
{
	matchStack current;
	matchStack result;
	current.Stack();
	result.Stack();
	int start = 0;

	int cbeg = 0, cend = 0, cwordtype = 0;
	int pos = 0;

        for (list<matchStack>::iterator p = l.begin(); p != l.end(); ++p)
	{
		current = *p;
		pos++;

		cbeg = current.getBeg();
		cend = current.getEnd();
		cwordtype = current.getEnd();
		
		if (isFirstWord2(l, cbeg, cend, cwordtype, current.getWord())) {
		insertListUnique(outList, cbeg, cend, cwordtype, current.getWord());
		// cout << "truexljskadjflksd " << z.getWord() << " " << pos << endl;
		 start = result.getEnd() + 1;
		result.add(cbeg, cend, cwordtype, current.getWord());
		//  start = result.getEnd() + 1;
		}


		if ((start != cbeg) && (result.getEnd() != cend)) {
		    if ((result.getBeg() != cbeg) && (result.getEnd() != cend) &&
		       // !isOverlapping(outList, cbeg, cend, current.getWordType(), current.getWord()) ) {
		       !isConjoining(outList, cbeg, cend, current.getWordType(), current.getWord()) ) {

			// result.add(cbeg, cend, cwordtype, current.getWord());
			insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
			start = result.getEnd() + 1;
                    }
                }

		 if ((cbeg == start) && (cend > result.getEnd())) 
			  result.add(cbeg, cend, cwordtype, current.getWord());


		if ((pos == l.size()) && (current.getEnd() == (start))) {
        insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
        	}
	}
            if ((cbeg == start) && (cend > result.getEnd())) {
            insertListUnique(outList, result.getBeg(), result.getEnd(), result.getWordType(), result.getWord());
            }
}


// This method will Set the processList function to use
void processList (std::list<matchStack> &l, std::list<matchStack> &outList)
{
	processList2 (l,outList);
	// processListNew (l, outList);
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
