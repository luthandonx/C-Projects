#include "Levels.h"
#include <iostream>
#include "Question_Operator.h"
#include<fstream>
#include<regex>
#include<iterator>
#include <stdio.h>
#include <cctype>
#include<string>
#include <sstream>


using namespace std;

template <class t>
void emptyVectors(t &vec)
{
    while(vec.empty()==false)
    {
        vec.pop_back();
    }
}

Levels::Levels(string l)
{
    //ctor
    //Load questions from the Text file into the level
    loadQuestion(l);
    points = 0;
}
Levels::~Levels()
{
    //dtor
    emptyVectors(Qs);
    emptyVectors(WrongQsandAns);
}

void Levels::loadQuestion(string l)
{
    Question question(l);
    int x = question.GetNumOfLine();
    numberOfQuestions = x;

    QandA QA;

    for(int i = 0 ; i < x ; i++)
    {
        QA.Q = question.Getquestion(i);
        QA.A = question.GetAnswer(i);
        QA.point = question.GetScore();
        Qs.push_back(QA);
    }
}

void Levels::DisplayQuestion(int index)
{
    QandA q = Qs[index];
    cout<< q.Q<<endl;
}

void Levels::RecieveAnswer(char answer , int i)
{
    QandA q = Qs[i];
    if(q.isCorrect(answer) == true)
    {
        AddPoints(q.point);
    }
    else
    {
        q.index = i ;
        WrongQsandAns.push_back(q);
    }
}

int Levels::GetPoints()
{
    return points;
}

void Levels::DisplayWrongQsAns()
{
    vector<string>wrong ;
    QandA q;
    string word ="";
    for (int i = 0 ; i < WrongQsandAns.size() ; i++)
    {
        q = WrongQsandAns[i];
        stringstream ss;
        ss << q.index;
        ss >> word;
        word = word + ". ";
        word = word + q.Q + "\n";
        word = word + q.A;
        wrong.push_back(word);
        word = " ";
    }
    vector<string>::iterator ptr;

    for (ptr = wrong.begin() ; ptr < wrong.end() ; ptr++)
    {
        cout<<*(ptr)<<endl;
    }
    while (wrong.empty() == false){ wrong.pop_back();}
}

void Levels::AddPoints(int i)
{
    points = points + i;
}
int Levels::GetNumberOfQuestions()
{
    return numberOfQuestions;
}

