#include<iostream>
using namespace std;
class Circularlist
{

public:
Circularlist* next;
char letter;
Circularlist()
{
next = nullptr;
}
};
class Word
{
public:
void addway()
{
Circularlist* temp = start;
if (start->letter == 'a' || start->letter == 'e' || start->letter == 'i' || start->letter == 'o' || start->letter == 'u')
{
while (temp->next)
{
temp = temp->next;
}
temp->next = new Circularlist;
temp->next->letter = '-';
temp->next->next = new Circularlist;
temp->next->next->letter = 'w';
temp->next->next->next = new Circularlist;
temp->next->next->next->letter = 'a';
temp->next->next->next->next = new Circularlist;
temp->next->next->next->next->letter = 'y';
temp->next->next->next->next->next=nullptr;
}
else
{
while (temp->next)
{
temp = temp->next;
}
temp->next = new Circularlist;
temp->next->letter = '-';
while (start->letter != 'a' && start->letter != 'e' && start->letter != 'i' && start->letter != 'o' && start->letter != 'u'&& start->letter!='y')
{
rotate(1);
}
temp = start;
while (temp->next)
{
temp = temp->next;
}
temp->next = new Circularlist;
temp->next->letter = 'a';
temp->next->next = new Circularlist;
temp->next->next->letter = 'y';
}

}
void addletter(char p);
Word()
{
start = nullptr;
}
void print()
{
Circularlist* temp = start;
while (temp)
{
cout << temp->letter << " ";
temp = temp->next;
}
}
void rotate(int k)
{
Circularlist** head_ref = &start;
if (k == 0)
return;


Circularlist* current = *head_ref;

int count = 1;
while (count < k && current != NULL) {
current = current->next;
count++;
}


if (current == NULL)
return;


Circularlist* kthNode = current;


while (current->next != NULL)
current = current->next;


current->next = *head_ref;


*head_ref = kthNode->next;


kthNode->next = NULL;
}
private:
Circularlist* start;
};


void Word::addletter(char p)
{
Circularlist* temp = start;
if (!start)
{
start = new Circularlist;
start->letter = p;
}
else
{
while (temp->next)
{
temp = temp->next;
}
temp->next = new Circularlist;
temp->next->letter = p;
}
}
int main()
{
Word word;
cout << "Enter the word" << endl;
char* p;
p = new char[10];
cin.getline(p, 10);
for (int i = 0;p[i] != '\0';i++)
{
word.addletter(p[i]);
}
word.addway();
word.print();
}
