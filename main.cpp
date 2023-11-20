#include <iostream>
#include <ctime>
#include "lab5.cpp"
using namespace std;


class zegar{
public:
    int val; //licznik zmieniajacy sie co sekunde
    int lasttime; //ostatni odczytany czas
    //etc
    zegar();

    void czas(); //metoda ktora zmienia licznik
};

zegar::zegar() {
        time_t tt;
        struct tm* ti;
        time(&tt);
        ti = localtime(&tt); //to wszystko sluzy do pobierania czasu

        lasttime = ti->tm_sec + 60*ti->tm_min; //ostatni odczytany czas
        val=0; //licznik = 0
    }

void zegar::czas() {
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt); //to potrzebne do odczytania czasu

    int currtime = ti->tm_sec+ 60*ti->tm_min; //odczytujemy aktualny czas

    if(lasttime != currtime) //jezeli aktualny czas == poprzedni czas to nic
    {
        val+=currtime - lasttime; // w innym przypadku zmieniamy licznik o tyle sekund ile minelo od ostatniego odczytu
        lasttime=currtime; //a lasttime == obecnyczas
    }
}


void ladowanie(BST* root, int x, zegar zeg)
{
   if(x < zeg.val + 2 || x == root->val) //jezeli termin jest starszy niz obecnyczas lub zajety
   {
       cout << "Zly termin rezerwacji!\n";
       return;
   }

   if(root->val - x > 2) //jezeli wartosc rezerwacji jest o 2 mniejsza od wartosci roota
   {
       if(root->left) //to sprawdzamy lewe dziecko roota
       {
           ladowanie(root->left, x, zeg); //jezeli istnieje to rekurencja
           return;
       }
       root->left = new BST(x); //jezeli nie to tworzymy nowe dziecko o wartosci x
   }
   else if(x - root->val > 2) //jezeli wartosc rezerwacji jest o 2 wieksza od wartosci roota
   {
       if(root->right) //to sprawdzamy prawe dziecko roota
       {
           ladowanie(root->right, x, zeg); //jezeli istnieje to rekurencja
           return;
       }
       root->right = new BST(x); //jezeli nie to tworzymy dziecko o wartosci x
   }
   else //jezeli wartosc x nie jest ani o min 2 wieksza ani o min 2 mniejsza
   {
       cout << "Zly termin rezerwacji!\n";
       return;
   }
}


void UsunRezerwacjeSprzedCzasu(BST* &root, zegar czas)
{
    while(czas.val > BST::min(root)->val) //dopoki minimialna wartosc w drzewie jest mniejsza od czasu
    {
        BST::Delete(root,BST::min(root)->val); //usun minimalna wartosc w drzewie
    }
}





int main() {
    BST* root = nullptr;
    root = BST::Insert(root,50);
    root = BST::Insert(root,60);
    root = BST::Insert(root,57);
    root = BST::Insert(root,66); //tutaj jakies losowe rezerwacje zeby mozna bylo sprawdzic czy program dziala


    zegar x = zegar();
    BST::printTreeInOrder(root);
    cout << "Czas: "<< x.val << endl;

    int l;
    while(true) //robimy ile chcemy bez ograniczen
    {
        cout << "Podaj czas ladowania: ";
        cin >> l; //pytamy o termin ladowania

        x.czas(); //update licznika czasu
        UsunRezerwacjeSprzedCzasu(root,x); //usuwamy rezerwacje ktore juz sie odbyly
        ladowanie(root,l,x); //jezeli podany termin byl poprawny to dodajemy go do drzewka


        BST::printTreeInOrder(root); //wypisujemy wszystkie rezerwacje dla ulatwienia odczytu
        cout << "Czas: "<< x.val << endl << endl; //dodatkowo wypisuje czas dla wygody odczytu
    }
    return 0;
}
