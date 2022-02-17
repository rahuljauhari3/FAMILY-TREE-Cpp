#include <bits/stdc++.h>
using namespace std;

struct node
{
	char name[50];
	int age;
	bool gender;

	struct node *left,*right;

	void getdata();
};

void node::getdata()
{
	char g,name[50];
	int a;
	cin>>g;
	cin>>name;
	cin>>a;
}
void add_new()
{
	cout<<1<<endl;
}
void find_relation()
{
	cout<<2<<endl;

}
void display_relation()
{
	cout<<3<<endl;

}
void destroy()
{
	cout<<4<<endl;

}
void display()
{
	cout<<5<<endl;
	
}
void ansestor()
{
	cout<<6<<endl;

}

int main()
{
	char family_tree[50];
	int opt,n,c;
	cout<<"\nEnter name of family tree: ";
	cin>>family_tree;

	while (1)
	{
		cout << "\n\n\n\tFamily tree name = " << family_tree << "\n\n\t1. Add new person\n\t2. Find relationship b/w two persons\n\t3. Display Relation\n\t4. Destroy\n\t5. Display\n\t6. ansestor\n\t7. Exit\n\n\tEnter your choice = ";
		cin >> opt;
		cout << endl;

		switch (opt)
		{
			default:
			cout << "Invalid input";
			break;

			case 1:
				add_new();
				break;

			case 2:
				find_relation();
				break;

			case 3:
				display_relation();
				break;

			case 4:
				destroy();
				break;

			case 5:
				display();
				break;

			case 6:
				ansestor();
				break;

			case 7:
				return 0;
		}
		cout << "\n\nPress any key to continue.....";
		cin >> c;	
	}
}













