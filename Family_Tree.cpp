#include <bits/stdc++.h>
using namespace std;

struct node //node structure
{
    string name;// for the name of the person
    int age;//for the age of the person
    int g;// g for gender

    node *left;
    node *right;
    node();
    void getData();
};
node::node() 
{
    left = right = NULL;
    g = 0;
    name = "";
    age=0;

}
class familyTree
{

public:
    node *start;
                                        //r
    familyTree();                   // m     d
    node *search(string);
    void addNew();
    void addMother(node *, node *);
    void addFather(node *, node *);
    node *traverseDown(node *, string);
    node *traverseRight(node *, string);
    void destroy(node *);
    void show(node *);
    void printKDistant(node *, int);
    string findLCSuccessor(node *, string, string);
    void print2DUtil(node *, int);
    void parentofnode(string);
    node *findparent(struct node *, string);
    node *findpartner(string);
};
void familyTree::print2DUtil(node *root, int space) //to print the whole family tree in 2D using reverse inorder traversal
{
    int count = 5; //using count for space 
    // Base case
    if (root == NULL)
        return;

    space += count;

    print2DUtil(root->right, space);

    cout << endl;
    for (int i = count; i < space; i++)
        cout << " ";
    cout << root->name << "\n";

    print2DUtil(root->left, space);
}
node *familyTree::findparent(struct node *ptr, string str) //to find the parents of a particular node
{
    if (ptr == NULL || ptr->name == str)
    {
        return NULL;
    }
    if ((ptr->left != NULL && ptr->left->name == str) || (ptr->right != NULL && ptr->right->name == str))
    {
        return ptr;
    }
    node *l = findparent(ptr->left, str);
    if (l != NULL)
    {                                         
        return l;                             
    }                                         
    l = findparent(ptr->right, str);

    return l;
}
node *familyTree::findpartner(string str)
{
    node *ptr = start;
    node *lf, *rf;
    node *l = findparent(ptr, str); 
    lf = l->left;
    if (lf != NULL && lf->name == str)
    {
        return l->right;
    }
    rf = l->right;
    if (rf != NULL && rf->name == str)
    {
        return l->left;
    }
    return ptr;
}
bool findPath(node *start, vector<string> &path, string per)
{

    if (start == NULL)
        return false;

    path.push_back(start->name);

    if (start->name == per)
        return true;

    if ((start->left && findPath(start->left, path, per)) || (start->right && findPath(start->right, path, per)))
        return true;

    path.pop_back();
    return false;
}

string familyTree::findLCSuccessor(node *start, string per1, string per2)
{

    vector<string> path1, path2;

    if (!findPath(start, path1, per1) || !findPath(start, path2, per2))
        return NULL;

    int i;
    for (i = 0; i < path1.size() && i < path2.size(); i++)
    {
        if (path1[i] != path2[i])//r d dd
        {                       //r d dm
            break;
        }
    }
    return path1[i - 1];
}
void familyTree::printKDistant(node *start, int k) // to print the people of a particular generation
{                                               // generation in terms of binary tree not family tree 
    if (start == NULL || k < 0)
        return;
    if (k == 0)//base case
    {
        cout << endl;                   
        cout << start->name << " ";
        return;
    }

    printKDistant(start->left, k - 1);
    printKDistant(start->right, k - 1);
}
void familyTree::destroy(node *ptr)// to delete the whole family tree
{
    node *temp = ptr;

    if (ptr == NULL)
        return;

    while (ptr != NULL) //to delete each and every node
    {
        destroy(ptr->left);
        temp = ptr;
        ptr = ptr->right;
        delete temp;
    }   

    start = NULL;
}
void familyTree::show(node *ptr) // to show the information of a particular person
{
    string gender;
    gender = "Female";
    if (ptr->g)
        gender = "Male";
    cout << "\n\nName: " << ptr->name << endl;
    cout << "Age: " << ptr->age << endl;
    cout << "Gender: " << gender << endl;
}
familyTree::familyTree() //---->const
{
    start = NULL;
}
void node::getData()// to input data for a new person
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

void familyTree::addNew() // to add a new member to the family
{
    struct node *temp = new struct node;
    temp->getData();
    if (start == NULL)
    {
        cout << "First member added to the family!" << endl;
        start = temp;
    }
    else
    {
        cout << "New member added to the family!" << endl;
        cout << "\nEnter the name of the person he/she is a parent to: ";
        string name1;
        cin >> name1;
        cout << "\nEnter 1 if the new person entered is Mother,2 for Father, of the relative mentioned \n 1.Mother \n2.Father\n\n"
             << "Specify what " << temp->name << " is to " << name1 << " : ";
        int opt;
        cin >> opt;
        switch (opt)
        {
        case 1:
            addMother(search(name1), temp);
            break;
        case 2:
            addFather(search(name1), temp);
            break;
        }
    }
    cout << "\nPerson sucessfully added.\n";
}

void familyTree::addMother(node *a, node *b) // to add b as the mother of a
{

    if (a->left == NULL)
        a->left = b;
    else
        addMother(a->left, b);
}
void familyTree::addFather(node *a, node *b)// to add b as the father of a
{

    while (a->right != NULL)
        a = a->right;

    a->right = b;

}

node *familyTree::search(string s) // to search for a particular person in the family
{

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
        cout << "*Sorry,no person found with the given name*";
    }
}

node *familyTree::traverseDown(node *ptr, string s) 
{

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
    ptr = search(a);
    cout << "Enter the option below to print the name of one of the parent:" << endl;
    cout << "1.Mother\n2.Father" << endl;
    int opt;
    cout << "Enter 1 or 2:";
    cin >> opt;
    switch (opt)
    {
    case 1:
        ptr = ptr->left;
        cout << ptr->name << endl;
        break;
    case 2:
        ptr = ptr->right;
        cout << ptr->name << endl;
        break;
    }
}

int main()
{
    familyTree f;
    char c;
    int z = 1, opt, k;
    string s1, s2;
    string temp, str, nameofperson, nameofperson1;
    cout << "Welcome to FAMILY TREE PROJECT!!";
    while (z == 1)
    {
        cout << "\n\n\t1.Add new member to the family\n\t2.Show the information for a particular person\n\t3.Delete the whole family tree\n\t4.Print the names of all the people in the same generation\n\t5.To find the least common successor\n\t6.Print the whole family tree!\n\t7.To find the parents of a particular person\n\t8.To find the spouse of a particular person\n\t9.To find the child of a particular person\n\t10.Exit " << endl;
        cout << "Enter the option no:";
        cin >> opt;
        switch (opt)
        {
        case 1:
            f.addNew();
            break;
        case 2:
            cout << "Enter name of person to show information: ";
            cin >> temp;
            f.show(f.search(temp));
            break;
        case 3:
            f.destroy(f.start);
            break;
        case 4:
            cout << "Enter the generation no. of whom the names are to be displayed:";
            cin >> k;
            f.printKDistant(f.start, k);
            break;
        case 5:
            cout << "Enter name 1:";
            cin >> s1;
            cout << endl;
            cout << "Enter name 2:";
            cin >> s2;
            cout << f.findLCSuccessor(f.start, s1, s2);

            break;
        case 6:
            f.print2DUtil(f.start,0);
            break;
        case 7:
            cout << "Enter name of person:";
            cin >> str;
            f.parentofnode(str);
            break;
        case 8:
        {
            cin >> nameofperson1;
            node *partner = f.findpartner(nameofperson1);
            if (partner != NULL)
            {
                cout << partner->name;
                break;
            }
            else
            {
                cout << "Partner does not exists.";
                break;
            }
        }

        case 9:
        {
            cout << "Enter name of person whose child you want to find: ";
            cin >> nameofperson;
            node *parent = f.findparent(f.start, nameofperson);
            if (parent != NULL)
            {
                cout << parent->name;
                break;
            }
            else
            {
                cout << "There is no child";
                break;
            }
        }
        case 10:
            z = 0;
            return 0;
        }
        cout << "\n\nPress any key to continue.....";
        cin >> c;
    }
    return 0;
}
