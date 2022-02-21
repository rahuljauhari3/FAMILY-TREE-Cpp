#include <bits/stdc++.h>
using namespace std;

struct node{
	string name;
	int age,x;
	int g;

	node* left;
	node* right;
	node();
	void getData();
};
node::node()
{
	left = right = NULL;
	g = 0;
	name = "";
	age = x = 0;
}
class 	familyTree//---->class
{

public:
	node *start;

	familyTree();//--->class declare func prototype
	node *search(string);
	void addNew();
	void addChild(node*,node*);
	void addSib(node*,node*);
	node *traverseDown(node *, string); // Search functions
	node *traverseRight(node *, string);
	void destroy(node *); // Function to destroy full tree
	void show(node *);	  // Function to show details of particular person
	void printKDistant(node * , int );
	string findLCSuccessor(node*,string,string);
	void print2DUtil(node*, int);
	void print2D(node *);
	void parentofnode(string);

};
void familyTree::print2DUtil(node *root, int space)
{
    int count=5;
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space +=count;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i =count; i < space; i++)
        cout<<" ";
    cout<<root->name<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void familyTree::print2D(node *start)
{
    // Pass initial space count as 0
    print2DUtil(start, 0);
}
bool findPath(node *start, vector<string> &path,string per)
{
    // base case
    if (start == NULL) 
    	return false;
 
    // Store this node in path vector. The node will be removed if not in path from start to person
    path.push_back(start->name);
 
    // See if the person's name is same as start's name
    if ((start->name).compare(per)==0)
        return true;
 
    // Check if Data is found in left or right sub-tree
    if ( (start->left && findPath(start->left,path,per)) ||(start->right && findPath(start->right,path,per)) )
        return true;
 
    // If not present in subtree started with start, remove start from
    // path and return false
    path.pop_back();
    return false;
}

// Returns lcsuccessor if person per1,per2 are present in the given binary tree,otherwise return -1

string familyTree::findLCSuccessor(node *start,string per1,string per2)
{
    // to store paths to per1 and per2 from the start
    vector<string> path1, path2;
 
    // Find paths from start to per1 and start to per2.If either per1 or per2 is not present, return -1
    if ( !findPath(start, path1,per1) || !findPath(start, path2,per2))
          return NULL;
 
    /* Compare the paths to get the first different value */
      int flag=0,i=0;
    for ( i = 0; i < path1.size(); i++)
    {
    	for (int j=0; j < path2.size() ;j++)
    	{
        	if (path1[i] != path2[j])
            	{
            		flag=1;
            		break;
            	}
    	}
    	if (flag==1){
    		break;
    	}
    }
    return path1[i-1];
}
void familyTree::printKDistant(node *start , int k)
{
    if(start == NULL|| k < 0 )
        return;
    if( k == 0 )
    {
        cout << start->name << " ";
         return;
    }
     
        printKDistant( start->left, k - 1 ) ;
        printKDistant( start->right, k - 1 ) ;
     
}
void familyTree::destroy(node *ptr)
{
	node *temp = ptr;

	if (ptr == NULL)
		return;

	while (ptr != NULL)
	{
		destroy(ptr->left);
		temp = ptr;
		ptr = ptr->right;
		delete temp;
	}

	start = NULL;
}
void familyTree::show(node *ptr)
{
	string gender;
	gender= "Female";
	if (ptr->g)
		gender= "Male";
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
		cout<<"start"<<endl;
		start = temp;
		temp->x = 0;
	}
	else
	{
		cout<<"NOT A start"<<endl;
		cout << "\nEnter any relation's name: ";
		string name1;
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
node *familyTree::search(string s)
{
	/*
		Searches for the given name from start
		Returns the pointer of node where the name is present
	*/

	node *ptr = start;

	if ((ptr->name).compare(s) == 0)
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


node *familyTree::traverseDown(node *ptr, string s)// ye mai tb use karunga tb muje node as a whole chalana hai 
{
	// Searches all the children

	ptr = ptr->left;

	while (ptr != NULL)
	{
		if ((ptr->name).compare(s) == 0)
			return ptr;
		else if (traverseRight(ptr, s) != NULL)
			return traverseRight(ptr, s);
		else
			ptr = ptr->left;
	}
	return NULL;
}

node *familyTree::traverseRight(node *ptr, string s)
{

	//  Searches all the sibilings

	ptr = ptr->right;

	while (ptr != NULL)
	{
		if ((ptr->name).compare(s) == 0)
			return ptr;
		else if (traverseDown(ptr, s) != NULL)
			return traverseDown(ptr, s);
		else
			ptr = ptr->right;
	}
	return NULL;
}
void familyTree::parentofnode(string a)
{
	node *ptr;
	ptr=search(a);
	cout<<"Print mom or dad"<<endl;
	cout<<"1. Mom\n2.dad"<<endl;
	int opt;
	cout<<"Enter 1 or 2";
	cin>>opt;
	switch(opt){
		case 1:
		ptr=ptr->left;
		cout<<ptr->name<<endl;
		break;
		case 2:
		ptr=ptr->right;
		cout<<ptr->name<<endl;
		break;
	}
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
void familyTree::addSib(node *a, node *b)// ye func tb jb muje node me Data add karna hai 
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
	char c;
	int z=1,opt,k;
	string s1,s2;
	string temp,str;

	while(z==1)
	{
		cout<<"\n\n\t1. addNew\n\t2. show\n\t3. delete\n\t4. print all ppl in kth gen\n\t5.findLCSuccessor\n\t6.\n\t7. parentofnode\n\t8. exit"<<endl;
		cout<<"Enter no";
		cin>>opt;
		switch(opt)
		{
			case 1:
				f.addNew();
				break;
			case 2:
				cout<<"Enter name of person to show info: ";
				cin>>temp;
				f.show(f.search(temp));
				break;
			case 3:
				f.destroy(f.start);
				break;
			case 4:
				cout<<"Konsi gen ka info chaiye";
				cin>>k;
				f.printKDistant(f.start,k);
				break;
			case 5:
				cout<<"Enter name 1";
				cin>>s1;
				cout<<endl;
				cout<<"Enter name 2";
				cin>>s2;
				f.findLCSuccessor(f.start,s1,s2);
				break;
			case 6:
				f.print2D(f.start);
				break;
			case 7:
				cout<<"Enter name of person";
				cin>>str;
				f.parentofnode(str);
				break;
			case 8:
				z=0;
				return 0;

		}
		cout << "\n\nPress any key to continue.....";
		cin >> c;
	}

}	


// bool findPath(node *start, vector<string> &path,string per)
// {
//     // base case
//     if (start == NULL) return false;
 
//     // Store this node in path vector. The node will be removed if not in path from start to person
//     path.push_back(start->Data);
 
//     // See if the person's name is same as start's name
//     if ((start->Data).equals(per))
//         return true;
 
//     // Check if Data is found in left or right sub-tree
//     if ( (start->left && findPath(start->left,path,per)) ||(start->right && findPath(start->right,path,per)) )
//         return true;
 
//     // If not present in subtree started with start, remove start from
//     // path and return false
//     path.pop_back();
//     return false;
// }

// // Returns lcsuccessor if person per1,per2 are present in the given binary tree,otherwise return -1

// string findLCSuccessor(node *start,string per1,string per2)
// {
//     // to store paths to per1 and per2 from the start
//     vector<string> path1, path2;
 
//     // Find paths from start to per1 and start to per2.If either per1 or per2 is not present, return -1
//     if ( !findPath(start, path1,per1) || !findPath(start, path2,per2))
//           return -1;
 
//     /* Compare the paths to get the first different value */
//     int i;
//     for (i = 0; i < path1.size() && i < path2.size() ; i++)
//         if (path1[i] != path2[i])
//             break;
//     return path1[i-1];
// }
//  bool printSuccessors(struct node *start,string per)
// {
  
//   if (start == NULL) //base case
//      return false;
 
//   if ((start->Data).equals(per))
//      return true;
 
//   //If person is present in either left or right subtree of this node,then print this node
//   if (printSuccessors(start->left,per)||printSuccessors(start->right,per))
//   {
//     cout<<start->Data<< " ";
//     return true;
//   }
// //else it will return false
//   return false;
// }


// void printKDistant(node *start , int k)
// {
//     if(start == NULL|| k < 0 )
//         return;
//     if( k == 0 )
//     {
//         cout << start->Data << " ";
//          return;
//     }
     
//         printKDistant( start->left, k - 1 ) ;
//         printKDistant( start->right, k - 1 ) ;
     
// }



