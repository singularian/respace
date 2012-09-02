# respace
=======

Respace is an engine to convert spaceless text to spaced text
This engine is currently alpha and needs a lot of work. In the future it
will be able to use an SQL DB backend and support Unicode and multiple languages.

There are two parts the despacer and respacer within the engine.

The engine consists of an interpreter and command line parser and file parser. 
It uses the concept of a coordinate string to create the spaced text.

# Building the code

To build the c++ engine under Linux.  
[respace_cpp]$ make testscanner_stl  

# Usage

This a simplified usage from the program  

> % testscanner_stl  
> Respace Decoder version .450b  
> Command Path: testscanner_stl  

> USAGE [-option] [INPUT FILE]  
> USAGE [-option]  
> testscanner_stl --file [file]     -  Despace a command line string.  
> testscanner_stl --int             -  Execute the interpreter.  
> testscanner_stl --hex             -  Execute and despace the hex code argument.  
> testscanner_stl spacelessstring   -  Despace a argument string.  

# File Respace Execution

In the following a file is respaced.

[respace_cpp]$ cat noon.txt  
Thisisanexample!2222,getmetheball!  
[respace_cpp]$ testscanner_stl --file noon.txt  
This is an example! 2222, get me the ball!  

# Command line Respace Execution

This is the spaceless text conversion with a command line listing of the coordinate match stack.

* ./testscanner_stl aman
* (0:0) 3 a
* (0:1) 0 am
* (0:2) 0 ama
* (0:3) 0 a man
* (1:1) 3 m
* (1:2) 0 ma
* (1:3) 0 man
* (2:2) 3 a
* (2:3) 0 an
* (3:3) 3 n
* a man
* ./testscanner_stl amanandahorse
* (0:0) 3 a
* (0:1) 0 am
* (0:2) 0 ama
* (0:3) 0 a man
* (0:7) 0 a man and a
* (1:1) 3 m
* (1:2) 0 ma
* (1:3) 0 man
* (1:4) 0 mana
* (2:2) 3 a
* (2:3) 0 an
* (2:4) 0 ana
* (3:3) 3 n
* (3:5) 0 nan
* (4:4) 3 a
* (4:5) 0 an
* (4:6) 0 and
* (5:5) 3 n
* (5:6) 0 nd
* (6:6) 3 d
* (7:7) 3 a
* (7:8) 0 ah
* (8:8) 3 h
* (8:9) 0 ho
* (8:12) 0 horse
* (9:9) 3 o
* (9:10) 0 or
* (10:10) 3 r
* (11:11) 3 s
* (11:12) 0 se
* (12:12) 3 e
* a man and a horse

# Spaceless interpreter

This is an example of a spaceless interpreter. It doesn't currently have a large dictionary so there are some bugs.  
I also had a time crunch so this is just a fraction of it's potential.


[respace_cpp]$ testscanner_stl --int

Interpreter 1.0

Enter 10 sentences!!  
Sentence 0: whoareyou?I  
whoa re you? I  
Sentence 1: whatisyourname?  
what is your name?  
Sentence 2: canYOUSpellthis?  
can YOU Spell this?  
Sentence 3: SaysomethingtoME?  
Say something toME?  
Sentence 4: Saythisis  
Say this is     

# Spaceless search execution

This is a simple alpha prototype for a spaceless search form.  
It can handle punctuation and numbers and text unlike   
Google or Bing. This is better than Google search which was a cheap knockoff and don't implement
full spaceless text searching with numbers or punctuation and words. This is the first.
A spaceless search engine should be able to handle numbers, punctuation and words as well as spaces and case together
to be considered one.

http://interblock.org/testprocessor.html

For this input query:
99,bottlesofbear,inmyfathers!house.

Becomes
99, bottles of bear, in my fathers! house.

# TODO
Add a better dictionary.  
Add a SQL dictionary.  
Add multi lingual support.  
Improve the parser.  
Add the SQL Lite processor.  
Improve the accuracy.  
Implement a better coordinate system.  
Eliminate the bugs.
Add despace code.  
Add more spacing rules.

# License
=============================================
Copyright 2012 Nathan Ross  

The MIT license

Permission is hereby granted, free of charge, to any person obtaining  
a copy of this software and associated documentation files (the  
"Software"), to deal in the Software without restriction, including  
without limitation the rights to use, copy, modify, merge, publish,  
distribute, sublicense, and/or sell copies of the Software, and to  
permit persons to whom the Software is furnished to do so, subject to  
the following conditions:  

The above copyright notice and this permission notice shall be  
included in all copies or substantial portions of the Software.  

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,  
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF  
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND  
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE  
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION  
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION  
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  