//////////////////////////////////////////////////////////////////////
//                                                                  //
//                    Manual de utilizare                           //
//                                                                  //
//  Se vor folosi urmatoarele simboluri pentru conectorii logici:   //
//      '!'  - Negatie     (NU)                                     //
//      '&&' - Conjunctie  (SI)                                     //
//      '||' - Disjunctie  (SAU)                                    //
//      '=>' - Implicatia  (DACA... ATUNCI...)                      //
//      '<>' - Echivalenta (DACA SI NUMAI DACA)                     //
//                                                                  //
//  Pentru paranteze vor fi folosite simbolurile '(' si ')'         //
//                                                                  //
//  Variabilele propozitionale in acest stadiu al dezvoltarii sunt  //
//  notate cu litere mari ale alfabetului latin.                    //
//                                                                  //
//  Spatiile vor fi complet ignorate.                               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

char c[12801];
int i,j;

struct nod                      //creearea tipului de date care va retine fiecare nod al arborelui propozitiei de verificat
{
    nod *a,*b;
    int val=0;                    //se va retine in aceasta valoare daca nodul este folosit. in viitor s-ar putea modifica programul pentru a retine date mai complexe despre fiecare nod.
};

void afis(int pozi, int pozf)       //afisarea tuturor caracterelor dintre 2 pozitii in sirul de caractere citit
{
    for(int ii=pozi;ii<=pozf;ii++)
    {
        cout<<c[ii];
    }
}

bool rezolv(nod *x)             // daca subprogramul va returna 0, atunci o eroare in scrierea propozitiei a fost gasita. daca valoarea returnata este 1, atunci nu sunt erori in portiunea veriicata de apel.
{
    int neg=0,init;
    char A,s1,s2,B;
    init=i-1;
        afis(init,i-1);
        cout<<" asteapta o paranteza deschisa, o variabila propozitionala sau '!'.\nPropozitia curenta:";
        afis(0,i-1);
        cout<<"\n\n";
    {
        A=c[i++];
        if(A=='(')
        {
            cout<<j++<<". "<<c[i-1]<<" vrea sa fie o propozitie complexa.\n";
            x->a=new nod;
            if(rezolv(x->a)==0)      // daca o propozitie are in componenta sa o propozitie atomica gresita, atunci e clar ca intreaga propozitie nu e corecta.
            {
                cout<<"S-a gasit o eroare in ";
                afis(init,i);
                cout<<", se iese din executie...\n";

                return 0;
            }
        }
        else if(A<='Z'&&A>='A')
        {
            cout<<j++<<". "<<c[i-1]<<"\n";
            x->a=new nod;
            x->a->val=1;
        }
        else if(A=='!')
        {
            cout<<j++<<". "<<c[i-1]<<" vrea sa fie o propozitie negativa.\n";
            neg=1;
        }
        else
        {
            cout<<j++<<". "<<c[i-1]<<"\n";
            cout<<"S-a gasit un caracter neasteptat dupa ";
            afis(init,i-1);
            cout<<", caracterele asteptate erau: '(', '!', sau o variabila propozitionala. Se iese din executie...\n";
            return 0;
        }
    }



    if(neg==0)      //daca nu suntem in cazul negatiei, vom astepta un alt operator logic (&&, ||, =>, <>)
    {
        afis(init,i-1);
        cout<<" asteapta \"&&\", \"||\", \"=>\", \"<>\".\nPropozitia curenta:";
        afis(0,i-1);
        cout<<"\n\n";
        s1=c[i++];
        s2=c[i++];
        cout<<j++<<". "<<c[i-2]<<c[i-1]<<"\n";
        if(s1=='&'&&s2=='&')
        {
            x->val=1;
        }
        else if(s1=='|'&&s2=='|')
        {
            x->val=1;
        }
        else if(s1=='='&&s2=='>')
        {
            x->val=1;
        }
        else if(s1=='<'&&s2=='>')
        {
            x->val=1;
        }
        else
        {
            cout<<"S-a gasit un caracter neasteptat dupa ";
            afis(init,i-2);
            cout<<", seturile de caracterele asteptate erau: \"&&\", \"||\", \"=>\", \"<>\". Se iese din executie...\n";
            return 0;
        }
    }


        afis(init,i-1);
        cout<<" asteapta o paranteza deschisa sau o variabila propozitionala.\nPropozitia curenta:";
        afis(0,i-1);
        cout<<"\n\n";

    {
        B=c[i++];
        if(B=='(')
        {
            cout<<j++<<". "<<c[i-1]<<" vrea sa fie o propozitie complexa.\n";
            x->b=new nod;
            if(rezolv(x->b)==0)
            {
                cout<<"S-a gasit un caracter neasteptat dupa ";
                afis(init,i-1);
                cout<<", caracterele asteptate erau: (, !, sau o variabila propozitionala. Se iese din executie...\n";
                return 0;
            }
            else
            {
                cout<<"\n";
            }
        }
        else if(B<='Z'&&B>='A')
        {
            cout<<j++<<". "<<c[i-1]<<"\n";
            x->b=new nod;
            x->b->val=1;
            afis(init,i-1);
            cout<<" asteapta o paranteza inchisa.\nPropozitia curenta:";
            afis(0,i-1);
            cout<<"\n\n";
        }
        else
        {
            cout<<j++<<". "<<c[i-1]<<"\n";
            cout<<"S-a gasit un caracter neasteptat dupa ";
            afis(init,i-1);
            cout<<", caracterele asteptate erau: '(' sau o variabila propozitionala. Se iese din executie...\n";
            return 0;
        }
    }

    if(c[i++]==')')
    {
        cout<<j++<<". "<<c[i-1]<<" vrea sa inchida propozitia complexa.\n";
        cout<<"Nu s-a gasit nicio greseala in";
        afis(init,i-1);
        cout<<". Se continua executia...\n";
        return 1;
    }


            cout<<j++<<". "<<c[i-1]<<"\n";
            cout<<"S-a gasit un caracter neasteptat dupa ";
            afis(init,i-1);
            cout<<", caracterul asteptat era: ')'. Se iese din executie...\n";
    return 0;
}


int main()
{
    ifstream in("date.in");
    nod *x;
    x=new nod;
    bool ok=0;

    in.getline(c,12800);

    i=0;
    while(i<strlen(c))
    {
        if(c[i]==' ')
            strcpy(c+i,c+i+1);
        else
            i++;
    }
    i=0;

    cout<<c<<"\n\n";


    if(c[i]=='(')
{
        cout<<j++<<". "<<c[i]<<" vrea sa fie o propozitie complexa.\n";
        i++;
        x->a=new nod;
        if(rezolv(x->a)==0)
        {
            cout<<"\n\nGresit, s-a gasit o eroare de scriere in propozitie.\n\n\n";
            ok=1;
        }
    }
    if(ok==0)
    {
        if(!(c[i]<='Z'||c[i]>='A'))
        {
            cout<<"\n\nGresit, programul a intampinat un caracter neasteptat la finalul codului\n\n\n";
        }
        else if(i==strlen(c))
        {
            cout<<"\n\nCorect. Programul nu a gasit nicio greseala in scrierea propozitiei logice.\n\n\n";
        }
        else
        {
            cout<<"\n\nGresit, se mai gasesc caractere dupa sfarsitul propozitiei\n\n\n";
        }
    }
    in.close();
    return 0;
}
