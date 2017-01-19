//Program to Create a Dictionary using Binary Search Tree

/*
 * Created by Devashish Katoriya on 19-01-2017
 */

#include <iostream>
#include <cstring>

using namespace std;

#define LIMIT 999

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
    node *retRoot()
    {
        return root;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void clr()
    {
        root = NULL;
        count = 0;
    }
    void insert();
    void search();
    void display(node *);
    void remove(char []);
};

node *dictionary::create()
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

void dictionary::insert()
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
            if(temp->word<p->word)
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
            else if (temp->word>p->word)
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

void dictionary::search()
{

}

void dictionary::display(node *s)
{
    if(s!=NULL)
    {
        display(s->left);
        cout<<"\t"<<s->word<<","<<s->meaning;
        display(s->right);
    }
}

void dictionary::remove(char d[])
{
//Locate the element
    bool found = false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    node *curr;
    node *parent=NULL;
    curr = root;
    while(curr != NULL)
    {
        if(strcmp(curr->word,d)==0)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if(d>curr->word)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    if(!found)
    {
        cout<<" Data not found! "<<endl;
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
                strcpy(curr->word,lcurr->word);
                delete lcurr;
                lcurrp->left = NULL;
            }
            else
            {
                node *tmp;
                tmp = curr->right;
                strcpy(curr->word,tmp->word);
                curr->right = tmp->right;
                delete tmp;
            }

        }
        return;
    }
}

int main() {
    dictionary obj;
    int ch,key;
    char choice;
    cout<<"\nProgram to perform Various operation on Binary Search Tree.";
    do
    {
        ch = key = 0;
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 for Insertion";
        cout<<"\n 2 for In order Traversal";
        cout<<"\n 3 for Pre order Traversal";
        cout<<"\n 4 for Post order Traversal";
        cout<<"\n 5 to  Display Root Node";
        cout<<"\n -1 to Clear whole Tree";
        cout<<"\n 0 to  Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1 : obj.construct();
                break;
            case 2 : cout<<"\nIn order Traversal is ";
                obj.inOrder(obj.retRoot());
                break;
            case 3 : cout<<"\nPre order Traversal is ";
                obj.postOrder(obj.retRoot());
                break;
            case 4 : cout<<"\nPost order Traversal is ";
                obj.preOrder(obj.retRoot());
                break;
            case 5 : if(!obj.isEmpty())
                    cout<<"\nRoot Node is "<<obj.retRoot()->data;
                else
                    cout<<"\nEmpty Tree!";
                break;
            case 6 : cout<<"\nNo. of Nodes in Tree are "<<obj.retSize();
                break;
            case 7 : cout<<"\nIn order Interative is ";
                obj.in_itr(obj.retRoot());
                break;
            case 8 : cout<<"\nPre order Interative is ";
                obj.pre_itr(obj.retRoot());
                break;
            case 9 : cout<<"\nPost order Interative is ";
                obj.post_itr(obj.retRoot());
                break;
            case 10 : cout<<"\nEnter the search term : ";
                cin>>key;
                if(obj.search(key))
                    cout<<"\nKey Found!";
                else
                    cout<<"\nKey NOT found.";
                break;
            case 11 : cout<<"\nEnter the term to delete : ";
                cin>>key;
                obj.remove(key);
                break;
            case 14 : cout<<"\nThe height of tree is "<<obj.height(obj.retRoot());
                break;
            case 15 : cout<<"\nTotal No. of Leaves are "<<obj.retLeaves();
                break;
            case 16 : obj.swap(obj.retRoot());
                cout<<"\nNodes Swapped Successfully!";
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
    return 0;
}