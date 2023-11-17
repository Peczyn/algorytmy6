#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "/Users/marcin/CLionProjects/algorytmy5/main.cpp"

int czas()
{
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);
    return ti->tm_sec;
}

void ladowanie(BST* root, int x)
{
    if(!root)
    {
        root = BST::Insert(root,x);
        return;
    }

    if(root->val == x)
    {
        cout << "zly termin";
        return;
    }
    else if(root->val > x)
    {
        if(!root->left)
        {
            if(root->val - x > 2)
            {
                root = BST::Insert(root,x);
                cout << "Rezerwacja dokonana\n";
                return;
            }
            else
            {
                cout << "Zly termin rezerwacji\n";
                return;
            }
        }
        else
        {
            if(root->val - x > 2 && x - root->left->val > 2)
            {
                root = BST::Insert(root,x);
                cout << "Rezerwacja dokonana\n";
                return;
            }
            else
            {
                cout << "Zly termin rezerwacji\n";
                return;
            }
        }
    }
    else
    {
        if(root->right)
        {
            ladowanie(root->right,x);
            return;
        }
        else
        {
            if(x - root->val > 2)
            {
                root = BST::Insert(root,x);
                cout << "Rezerwacja dokonana\n";
                return;
            }
            else
            {
                cout << "Zly termin rezerwacji\n";
                return;
            }
        }
    }
}

void timecheck(BST* root)
{
    int sekundy = czas();
    cout << "\nCzas: "<< sekundy << endl;
}

using namespace std;
int main() {

    BST* root = nullptr;
    root = BST::Insert(root,21);
    root = BST::Insert(root,30);
    root = BST::Insert(root,27);
    root = BST::Insert(root,38);

    int l;
//    int sekundy = 19;
    for(;;)
    {

        cout << "Podaj czas ladowania: ";
        cin >> l;

        ladowanie(root,l);
        BST::printTreeInOrder(root);
        timecheck(root);

    }



}
