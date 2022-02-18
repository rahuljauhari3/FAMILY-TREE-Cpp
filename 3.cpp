#include <bits/stdc++.h>
using namespace std;

struct node{
	char name[50];
	int age,x;
	bool g;

	node* left;
	node* right;
	node();
	void getData();
};
node::node()
{
	left = right = NULL;
	g = 0;
	strcpy(name, "");
	age = x = 0;
}
class 	familyTree//---->class
{

public:
	node *start;

	familyTree();//--->class declare func prototype
	node *search(char[]);
	void addNew();
};

familyTree::familyTree()//---->const
{
	start = NULL;
}
void node::getData()
{
	char ch;
	cout << "\nName of the Person: ";
	cin >> name;
	cout << "Age of " << name << ": ";
	cin >> age;
	cout << name << " is (m/f): ";
	cin >> ch;
	if (ch == 'm')
		g = 1;
}

void familyTree::addNew()
{
	struct node* temp=new struct node;
	temp->getData();
	if (start == NULL)
	{
		cout<<"ROOT"<<endl;
		start = temp;
		temp->x = 0;
	}
	else
	{
		cout<<"NOT A ROOT"<<endl;
		cout << "\nEnter any relation's name: ";
		char name[50];
		cin >> name;
		cout << "\n1. Mom\n2. Dad\n\n"
			 << temp->name << " is ____ to " << name << " : ";
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1:
			addChild(search(name), temp);
			break;
		case 2:
			addSib(search(name), temp);
		 	break;
		}
	}
	cout << "\nPerson sucessfully added.\n";

}
node *familyTree::search(char s[50])
{
	/*
		Searches for the given name from start
		Returns the pointer of node where the name is present
	*/

	node *ptr = start;

	if (strcmp(ptr->name, s) == 0)
		return ptr;
	else if (traverseRight(start, s) != NULL)
		return traverseRight(start, s);
	else if (traverseDown(start, s) != NULL)
		return traverseDown(start, s);
	else
	{
		return NULL;
		cout << "***Not found***8";
	}
}

void familyTree::addSib(node *a, node *b)
{
	// b is added as sibling of a

	while (a->ns != NULL)
		a = a->ns;
	a->ns = b;

	b->x = a->x;
}

void familyTree::addChild(node *a, node *b)
{

	// b is added as child as a (or) b is added as sibiling to last child of a

	if (a->fc == NULL)
		a->fc = b;
	else
		addSib(a->fc, b);

	b->x = a->x + 1;
}


int main()
{
	familyTree f;
	int z=1,opt,c;
	while(z)
	{
		cout<<"Enter no"<<endl;
		cin>>opt;
		switch(opt)
		{
			case 1:
				f.addNew();
				break;
			case 7:
				z=0;
				return 0;

		}
		cout << "\n\nPress any key to continue.....";
		cin >> c;
	}

}	









