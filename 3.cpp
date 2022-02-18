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
	void addChild(node*,node*);
	void addSib(node*,node*);
	node *traverseDown(node *, char[]); // Search functions
	node *traverseRight(node *, char[]);
	void show(node *);	  // Function to show details of particular person

};
void familyTree::show(node *ptr)
{
	char gender[10];
	strcpy(gender, "Female");
	if (ptr->g)
		strcpy(gender, "Male");
	cout << "\n\nName: " << ptr->name << endl;
	cout << "Age: " << ptr->age << endl;
	cout << "Gender: " << gender << endl;
}
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
		char name1[50];
		cin >> name1;
		cout << "\n1. Mom\n2. Dad\n\n"
			 << temp->name << " is ____ to " << name1 << " : ";
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1:
			addChild(search(name1), temp);
			break;
		case 2:
			addSib(search(name1), temp);
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


node *familyTree::traverseDown(node *ptr, char s[50])// ye mai tb use karunga tb muje node as a whole chalana hai 
{
	// Searches all the children

	ptr = ptr->left;

	while (ptr != NULL)
	{
		if (strcmp(ptr->name, s) == 0)
			return ptr;
		else if (traverseRight(ptr, s) != NULL)
			return traverseRight(ptr, s);
		else
			ptr = ptr->left;
	}
	return NULL;
}

node *familyTree::traverseRight(node *ptr, char s[50])
{

	//  Searches all the sibilings

	ptr = ptr->right;

	while (ptr != NULL)
	{
		if (strcmp(ptr->name, s) == 0)
			return ptr;
		else if (traverseDown(ptr, s) != NULL)
			return traverseDown(ptr, s);
		else
			ptr = ptr->right;
	}
	return NULL;
}


void familyTree::addChild(node *a, node *b)
{

	// b is added as child as a (or) b is added as sibiling to last child of a

	if (a->left == NULL)
		a->left = b;
	else
		addSib(a->left, b);

	b->x = a->x + 1;
}
void familyTree::addSib(node *a, node *b)// ye func tb jb muje node me data add karna hai 
{
	// b is added as sibling of a

	while (a->right != NULL)
		a = a->right;
	a->right = b;

	b->x = a->x;
}


int main()
{
	familyTree f;
	int z=1,opt,c;
	while(z==1)
	{
		cout<<"\n\n\t1. addNew\n\t2. show\n\t7. exit"<<endl;
		cout<<"Enter no";
		cin>>opt;
		switch(opt)
		{
			case 1:
				f.addNew();
				break;
			case 2:
				char name2[50];
				cout<<"Enter name of person to show info: ";
				cin>>name2;
				f.show(f.search(name2));
				break;

			case 7:
				z=0;
				return 0;

		}
		cout << "\n\nPress any key to continue.....";
		cin >> c;
	}

}	


// bool findPath(Node *root, vector<string> &path,string per)
// {
//     // base case
//     if (root == NULL) return false;
 
//     // Store this node in path vector. The node will be removed if not in path from root to person
//     path.push_back(root->data);
 
//     // See if the person's name is same as root's name
//     if ((root->data).equals(per))
//         return true;
 
//     // Check if data is found in left or right sub-tree
//     if ( (root->left && findPath(root->left,path,per)) ||(root->right && findPath(root->right,path,per)) )
//         return true;
 
//     // If not present in subtree rooted with root, remove root from
//     // path[] and return false
//     path.pop_back();
//     return false;
// }

// // Returns LCA if person per1,per2 are present in the given binary tree,otherwise return -1

// string findLCSuccessor(Node *root,string per1,string per2)
// {
//     // to store paths to per1 and per2 from the root
//     vector<string> path1, path2;
 
//     // Find paths from root to per1 and root to per2.If either per1 or per2 is not present, return -1
//     if ( !findPath(root, path1,per1) || !findPath(root, path2,per2))
//           return -1;
 
//     /* Compare the paths to get the first different value */
//     int i;
//     for (i = 0; i < path1.size() && i < path2.size() ; i++)
//         if (path1[i] != path2[i])
//             break;
//     return path1[i-1];
// }
// [12:15 AM, 2/19/2022] Siddhesh Bits: bool printSuccessors(struct node *root,string per)
// {
  
//   if (root == NULL) //base case
//      return false;
 
//   if ((root->data).equals(per))
//      return true;
 
//   //If person is present in either left or right subtree of this node,then print this node
//   if (printSuccessors(root->left,per)||printSuccessors(root->right,per))
//   {
//     cout<<root->data<< " ";
//     return true;
//   }
// //else it will return false
//   return false;
// }






