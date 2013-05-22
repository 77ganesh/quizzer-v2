// ------------------------------------------------
// !!!!!! QUIZZER v2.0 !!!!!!!!!!!
// ................................................
//
// Date: Jan 05 2012
//
// ................................................
//
// External files required:
// ------------------------
// 	1) EGAVGA.BGI 	- Graphics Driver
//	2) EURO.CHR 	- Font file
//	3) LITT.CCHR    - Font file
//	4) ani.dat	- Questions Data
//	5) geo.dat	-    "      "
//	6) invn.dat	-    "      "
//	7) it.dat       -    "      "
//	8) sci.dat      -    "      "
//
// ................................................
//
// A small Quizzing Program in C++
//
// ------------------------------------------------



#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

// No of Questions Asked
#define NoOfQues 10

// Total No of Questions
#define totNoOfQues 20

// Questions file
ifstream quiz;

void start();

// Highscore Structure
class hs_struct
{
     public:
     char name[30];
     int score;
     hs_struct()
     {
         strcpy(name, "NONE");
         score = 0;
     }
     ~hs_struct() {}
};


class Question
{
	private:

	char q[200];
	char opt[4][50];
	int ans;
	static int score;
	static void swap(Question&, Question&);
	static void loadQues();
	static void loadFile(char);
	static void randomizeQues();
	void printQues(int);
	void getans();
	void correct();
	static void hscorefile();

	public:
	static void initialize();
	static char end();
	void askQues(int k)
	    {
		printQues(k);
		getans();
	    }
	void askQues2(int k);

}Quiz[totNoOfQues];

int Question::score = 0;

void Question::askQues2(int k)
{
	clrscr();
	int i;
	cout<<"\n\n";
	cout<<k<<". ";
	cout<<q;
	cout<<"\n";
	int x;
	int big=0;
	char c;
	for(i=0; i<4; i++)
	    if(strlen(opt[i])>27)  big=1;
	for(i=0, c='A'; i<4; i++, c++)
	  {
	     if(!big)
	     {
		 x=i%2;
		 if(!x)
		     cout<<"\t";
		 cout<<c<<") ";
		 cout.setf(ios::left);
		 cout<<setw(30)<<opt[i];
		 if(x)
		    cout<<"\n";
	     }
	     else
	     {
		 cout<<"\t"<<c<<") "<<opt[i]<<"\n";
	     }
	}
	cout<<"\n";
	getans();
}

// Checks if user has a got a highscore and if yes writes it to file
void Question::hscorefile()
{
     ifstream hfile("hs.dat", ios::in|ios::binary);
     int i=0;
     hs_struct h, temp[5];
     h.score = score;
     for(i=0; i<5 && hfile; i++)
     {   hfile.read((char*)&temp[i], sizeof(temp[i]));
     }
     hfile.close();
     for(i=0; i<5; i++)
	if(h.score>=temp[i].score)
		break;
     if(i==5)
	cout<<"Sorry..... you could not make to the highscore\n";
     else
     {
	 ofstream tfile("tmp.dat", ios::binary);
	 cout<<"Great you have got a highscore!!!!!\n";
	 cout<<"Enter your name: ";
	 char x[30];
	 cin.getline(x, 30);
	 strcpy(h.name, x);
	 int j;
	 for(j=4; j>i; j--)
	     temp[j] = temp[j-1];
	 temp[j] = h;
	 for(j=0; j<5; j++)
	     tfile.write((char*)&temp[j], sizeof(temp[j]));
         tfile.close();
         remove("hs.dat");
	 rename("tmp.dat", "hs.dat");
     }
     cout<<endl;
     for(i=0; i<78; i++)
	 cout<<"-";
     cout<<"\n\t\t\t H A L L     O F     F A M E\n";
     for(i=0;i<78; i++)
	cout<<"-";
     for(i=0; i<5; i++)
	 cout<<"\n"<<setw(30)<<temp[i].name<<"-------     "<<temp[i].score;
     cout<<endl;
     for(i=0; i<78; i++)
	cout<<"-";
     cout<<"\n\n";
}

// Displays score after the end of quiz
char Question::end()
{
	clrscr();
	cout<<"Your score: \n";
	cout<<"------------\n";
	cout<<"\n";
	cout<<"No of correct answers: "<<score/10<<"\n";
	cout<<"No of wrong answers: "<<NoOfQues-score/10<<"\n";
	cout<<"\n\nFinal Score: "<<score;
	cout<<"\n\n";
	quiz.close();
	hscorefile();
	cout<<"Do you want to go quizzing again? \n";
	cout<<"(Press y for yes)   ";
	return getch();
}

// Prints random correct remarks
void Question::correct()
{
	score+=10;
	time_t t = time(NULL);
	srand(t);
	int x = rand()%4;
	switch(x)
	   {
		case 1: cout<<"Way to go. Correct!";
			break;
		case 2: cout<<"You are absolutely correct!";
			break;
		case 3: cout<<"Yeah. Correct answer!";
			break;
		default: cout<<"You got it right!";
	   }
}

// Gets answer from the user
void Question::getans()
{
	char temp[20];
	do
	  {     cout<<"  Your Answer: ";
		cin.getline(temp, 20);
		temp[0] = toupper(temp[0]);
		if(temp[0]>='A'&& temp[0]<='D' && strlen(temp)==1)
			break;
		cout<<"     Invalid option. Please try again\n";
	  }  while(1);
	cout<<"  ";
	if(temp[0]-65==ans-1)
		correct();
	else
		cout<<"Oops! The correct answer is "<<opt[ans-1];
//cout<<endl<<"\n";
//system("pause");
}

// Randomizes the order of questions
void Question::randomizeQues()
{
	int i, x;
	time_t t;
	t = time(NULL);
	srand(t);
	for(i=0; i<totNoOfQues; i++)
	    {	x = rand()%totNoOfQues;
		swap(Quiz[i], Quiz[x]);
	    }
}


// Prints a formatted question to the user
void Question::printQues(int qno)
{
	cout<<"\n\n";
	cout<<qno<<". ";
	cout<<q;
	cout<<"\n";
	int i, x;
	int big=0;
	char c;
	for(i=0; i<4; i++)
	    if(strlen(opt[i])>27)  big=1;
	for(i=0, c='A'; i<4; i++, c++)
	  {
	     if(!big)
	     {
		 x=i%2;
		 if(!x)
		     cout<<"\t";
		 cout<<c<<") ";
		 cout.setf(ios::left);
		 cout<<setw(30)<<opt[i];
		 if(x)
		    cout<<"\n";
	     }
	     else
	     {
		 cout<<"\t"<<c<<") "<<opt[i]<<"\n";
	     }
}
}


// Swaps two Question classes
void Question::swap(Question& a, Question& b)
{
	Question tmp = a;
	a = b;
	b = tmp;
}

// Connects file containing quiz data to ifstream quiz
void Question::loadFile(char k)
{
	switch(k)
	{
		case '1': quiz.open("it.dat", ios::in);
			break;
		case '2': quiz.open("ani.dat", ios::in);
			break;
		case '3': quiz.open("geo.dat", ios::in);
			break;
		case '4': quiz.open("invn.dat", ios::in);
			break;
		case '5': quiz.open("sci.dat", ios::in);
			break;
	}
}

// Loads questions from file into "Question" array
void Question::loadQues()
{
	int i, j;
	for(i=0; i<totNoOfQues; i++)
		{
		quiz.getline(Quiz[i].q, 200);
		for(j=0; j<4;j++)
			quiz.getline(Quiz[i].opt[j], 50);
		quiz>>Quiz[i].ans;
		quiz.ignore(2);
		}
}

// Initialises the quiz
void Question::initialize()
{
	score = 0;
	char topic[20];
	clrscr();
	cout<<"Welcome to QUIZZER v2.0\n";
	cout<<"-----------------------\n\n";
	cout<<"Brace yourself to answer some QUIZZER questions\n";
	cout<<"\nTopics:\n";
	cout<<"\t1. Information Technology\n";
	cout<<"\t2. Animals and Birds\n";
	cout<<"\t3. Geography and History\n";
	cout<<"\t4. Inventions and Discoveries\n";
	cout<<"\t5. Science and Technology\n";
	cout<<"\nThere will be "<<NoOfQues<<" questions. Please choose"
	    <<" your topic to get started\n\n";
	do
	{
	cout<<"Chosen topic : ";
	cin.getline(topic,20);
	if(topic[0]>='1' && topic[0]<='5' && strlen(topic)==1)
		break;
	cout<<"Sorry. Invalid Topic. Try again.\n";
	} while(1);
	loadFile(topic[0]);
	loadQues();
	randomizeQues();
	clrscr();
}

// Checks if all required files are present
void check()
{
ifstream f[8];
int i;
for(i=0; i<8; i++)
{ 
  switch(i)
   {
     case 0: f[i].open("it.dat");
	     break;

     case 1: f[i].open("ani.dat");
	     break;

     case 2: f[i].open("geo.dat");
	     break;

     case 3: f[i].open("invn.dat");
	     break;

     case 4: f[i].open("sci.dat");
	     break;

     case 5: f[i].open("EGAVGA.bga");
	     break;

     case 6: f[i].open("LITT.chr");
	     break;

     case 7: f[i].open("EURO.chr");
	     break;
   }
}
for(i=0; i<8; i++)
    if(!f[i])
       {  clrscr();
          cout<<"  ... SORRY SOME FILES ARE MISSING!!!!!!!!!\n";
          cout<<"  Press any key.. ";
	  getch();
	  exit(1);
	}
      else
          f[i].close();
}

int main()
{
start();
char quit;
do  {
	Question::initialize();
	for(int i=0; i<NoOfQues; i++)
		Quiz[i].askQues(i+1);
	quit=Question::end();
    } while(quit=='y'||quit=='Y');
return 0;
}

// Displays graphical start screen
void start()
{
      clrscr();
      int gd=DETECT, gm, i;
      initgraph(&gd, &gm, "");
      settextstyle(9, 0, 8);
      outtextxy( 40 , 40 ,"QUIZZER");
      settextstyle(9, 0, 6);
      outtextxy(40, 190,"\nv2.0");
      for(i=1; i<=25; i++) 
      cout<<"\n";
      cout<<"\n\n\t\t\tPress any key to continue";
      getch();
      closegraph();
      clrscr();
}
