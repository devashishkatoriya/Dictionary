//Program to Create a Dictionary using Binary Search Tree

/*
 * Created by Devashish Katoriya on 19-01-2017
 */

#include <iostream>

using namespace std;

#define LIMIT 9999

//Function Prototypes
int stringCompare(char [],char []);
void stringCopy(char [],char []);

//Class Definitions
class node                                                              //Node Class
{
public :
    char word[LIMIT],meaning[LIMIT];
    node *left,*right;
};

class dictionary                                                        //Dictionary Class
{
    int count;
    node *root;
    node *create();
public :
    dictionary()
    {
        root = NULL;
        count = 0;
    }
    inline node *retRoot()
    {
        return root;
    }
    inline bool isEmpty()
    {
        return root == NULL;
    }
    inline int retCount()
    {
        return count;
    }
    void clr()
    {
        root = NULL;
        count = 0;
    }
    void insert();
    void search(char []);
    void display(node *);
    void remove(char []);
    void update(char []);
};

node *dictionary::create()                                                  //Creates a word
{
    node *temp;
    temp = new node;

    cout<<"\nEnter word \t: ";
    cin>>temp->word;
    cout<<"Enter meaning : ";
    cin>>temp->meaning;
    temp->left = NULL;
    temp->right = NULL;

    count++;
    return temp;
}

void dictionary::insert()                                                  //Inserts the word
{
    node *temp,*p;
    temp = create();
    if(isEmpty())
    {
        root = temp;
        cout<<"\nRoot word Inserted!";
    }
    else
    {
        p = root;
        while(p!=NULL)
        {
            if(stringCompare(temp->word,p->word)==-1)
            {
                if(p->left==NULL)
                {
                    p->left = temp;
                    cout<<"\nWord Inserted!";
                    break;
                }
                else
                {
                    p = p->left;
                }
            }
            else if (stringCompare(temp->word,p->word)==1)
            {
                if(p->right==NULL)
                {
                    p->right = temp;
                    cout<<"\nWord Inserted!";
                    break;
                }
                else
                {
                    p = p->right;
                }
            }
            else
            {
                cout<<"\nEntry already Exist";
                count--;
                break;
            }
        }
    }
}

void dictionary::search(char key[])                                                //Search a word
{
    node *p;
    if(isEmpty())
    {
        cout<<"\nEmpty tree!";

    }
    else
    {
        p = root;
        while(p!=NULL)
        {
            if(stringCompare(key,p->word)==-1)
            {
                if(p->left==NULL)
                {
                    cout<<"\nWord NOT Found!";
                    return;
                }
                else
                {
                    p = p->left;
                }
            }
            else if (stringCompare(key,p->word)==1)
            {
                if(p->right==NULL)
                {
                    cout<<"\nWord NOT Found!";
                    return;
                }
                else
                {
                    p = p->right;
                }
            }
            else
            {
                cout<<"\nMeaning of "<<p->word<<" is "<<p->meaning;
                return;
            }
        }
    }
}

void dictionary::update(char key[])                                                //Update a word
{
    node *p;
    if(isEmpty())
    {
        cout<<"\nEmpty tree!";
    }
    else
    {
        p = root;
        while(p!=NULL)
        {
            if(stringCompare(key,p->word)==-1)
            {
                if(p->left==NULL)
                {
                    cout<<"\nWord NOT Found!";
                    return;
                }
                else
                {
                    p = p->left;
                }
            }
            else if (stringCompare(key,p->word)==1)
            {
                if(p->right==NULL)
                {
                    cout<<"\nWord NOT Found!";
                    return;
                }
                else
                {
                    p = p->right;
                }
            }
            else
            {
                cout<<"\nEnter new Meaning of "<<p->word<<" : ";
                cin>>p->meaning;
                cout<<"\nWord Updated Successfully!";
                return;
            }
        }
    }
}

void dictionary::display(node *s)                                           //Display Dictionary
{
    if(s!=NULL)
    {
        display(s->left);
        cout<<"\t"<<s->word<<"="<<s->meaning<<",";
        display(s->right);
    }
}

void dictionary::remove(char d[])                                           //Delete a word
{
    //Locate the element
    bool found = false;
    if(isEmpty())
    {
        cout<<"\nThe tree is Empty! "<<endl;
        return;
    }
    node *curr;
    node *parent=NULL;
    curr = root;
    while(curr != NULL)
    {
        if(stringCompare(curr->word,d)==0)
        {
            found = true;
            count--;
            break;
        }
        else
        {
            parent = curr;
            if(stringCompare(d,curr->word)==1)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    if(!found)
    {
        cout<<"\nWord NOT found! "<<endl;
        return;
    }


    // 3 cases :
    // 1. We're removing a leaf node
    // 2. We're removing a node with a single child
    // 3. we're removing a node with 2 children

    // Node with single child
    if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL && curr->right == NULL))
    {
        if(curr->left == NULL && curr->right != NULL)
        {
            if(parent->left == curr)
            {
                parent->left = curr->right;
                delete curr;
            }
            else
            {
                parent->right = curr->right;
                delete curr;
            }
        }
        else // left child present, no right child
        {
            if(parent->left == curr)
            {
                parent->left = curr->left;
                delete curr;
            }
            else
            {
                parent->right = curr->left;
                delete curr;
            }
        }
        return;
    }

    //We're looking at a leaf node
    if( curr->left == NULL && curr->right == NULL)
    {
        if(parent->left == curr) parent->left = NULL;
        else parent->right = NULL;
        delete curr;
        return;
    }


    //Node with 2 children
    // replace node with smallest value in right subtree
    if (curr->left != NULL && curr->right != NULL)
    {
        node *chkr;
        chkr = curr->right;
        if((chkr->left == NULL) && (chkr->right == NULL))
        {
            curr = chkr;
            delete chkr;
            curr->right = NULL;
        }
        else // right child has children
        {
            //if the node's right child has a left child
            // Move all the way down left to locate smallest element

            if((curr->right)->left != NULL)
            {
                node *lcurr;
                node *lcurrp;
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while(lcurr->left != NULL)
                {
                    lcurrp = lcurr;
                    lcurr = lcurr->left;
                }
                stringCopy(curr->word,lcurr->word);
                delete lcurr;
                lcurrp->left = NULL;
            }
            else
            {
                node *tmp;
                tmp = curr->right;
                stringCopy(curr->word,tmp->word);
                curr->right = tmp->right;
                delete tmp;
            }

        }
        return;
    }
}


//main()
int main()                                                                          //main()
{
    dictionary obj;
    int ch;
    char key[LIMIT];
    char choice;
    cout<<"\nProgram to perform Various operation on Binary Search Tree.";
    do
    {
        ch = 0;
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 to  Insert a word";
        cout<<"\n 2 to  Display Dictionary";
        cout<<"\n 3 to  Search a word";
        cout<<"\n 4 to  Remove a word";
        cout<<"\n 5 to  Update the word";
        cout<<"\n 6 for Word Count";
        cout<<"\n -1 to Clear whole Tree";
        cout<<"\n 0 to  Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1 : obj.insert();
                break;
            case 2 : cout<<"\nWords included are \n";
                obj.display(obj.retRoot());
                break;
            case 3 : cout<<"\nEnter the Search term : ";
                cin>>key;
                obj.search(key);
                break;
            case 4 : cout<<"\nEnter the word to Delete : ";
                cin>>key;
                obj.remove(key);
                break;
            case 5 : cout<<"\nEnter the word to Update : ";
                cin>>key;
                obj.update(key);
                break;
            case 6 : cout<<"\nTotal No. of Words are "<<obj.retCount();
                break;
            case -1: cout<<"\nAre you sure you want to clear tree (y/n) ? ";
                cin>>choice;
                if(choice=='y'||choice=='Y')
                {
                    obj.clr();
                    cout<<"\nTree Cleared Successfully!";
                }
                else
                    cout<<"\nCancelled!";
            case 0 : break;
            default : cout<<"\nInvalid Option!";
        }

        /*
        if(ch!=0)
        {
            cout<<"\n\n\n\n\n\n\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
        */
    }while(ch!=0);

    cout<<"\nThank you for using this program :) \n\n";
    return 0;
}

//Various Functions
int stringCompare(char a[],char b[])                                        //Compares two strings
{
    int i,len=0,len2=0;
    for(i=0;a[i]!='\0';i++)
        len++;
    for(i=0;b[i]!='\0';i++)
        len2++;
    if(len!=len2)
        return 1;
    for(i=0;i<len;i++)
    {
        if(a[i]<b[i])
        {
            return -1;          //a<b
        }
        else if(a[i]>b[i])
        {
            return 1;           //a>b
        }
    }
    return 0;                   //a==b
}

void stringCopy(char a[],char b[])                                          //Copies one string to another
{
    for(int i=0;b[i]!='\0';i++)
    {
        a[i] = b[i];
    }
}