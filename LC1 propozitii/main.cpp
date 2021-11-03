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
bool valProp[256],folosit[256];
int i,j;

struct nod                      //creearea tipului de date care va retine fiecare nod al arborelui propozitiei de verificat
{
    nod *a,*b;
    int val=0;                    //se va retine in aceasta valoare daca nodul este folosit. in viitor s-ar putea modifica programul pentru a retine date mai complexe despre fiecare nod.
};

void afis(int pozi, int pozf)       //afisarea tuturor caracterelor dintre 2 pozitii in sirul de caractere citit
{
    for(int ii=pozi; ii<=pozf; ii++)
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
            x->a->val=valProp[c[i-1]];
            if(valProp[0]==1)
            {
                cout<<"Valoarea de adevar a "<<c[i-1]<<": "<<valProp[c[i-1]]<<"\n";
            }
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
            neg=2;
        }
        else if(s1=='|'&&s2=='|')
        {
            x->val=1;
            neg=3;
        }
        else if(s1=='='&&s2=='>')
        {
            x->val=1;
            neg=4;
        }
        else if(s1=='<'&&s2=='>')
        {
            x->val=1;
            neg=5;
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
            x->b->val=valProp[c[i-1]];
            afis(init,i-1);
            cout<<" asteapta o paranteza inchisa.\nPropozitia curenta:";
            afis(0,i-1);
            if(valProp[0]==1)
            {
                cout<<"Valoarea de adevar a "<<c[i-1]<<": "<<valProp[c[i-1]]<<"\n";
            }
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
        if(valProp[0]==1)
        {
            switch(neg)
            {
                case 1:
                {
                    x->val=!x->b->val;
                    break;
                }
                case 2:
                {
                    x->val=x->a->val&&x->b->val;
                    break;
                }
                case 3:
                {
                    x->val=x->a->val||x->b->val;
                    break;
                }
                case 4:
                {
                    x->val=(!x->a->val)||x->b->val;
                    break;
                }
                case 5:
                {
                    x->val=(x->a->val||x->b->val)&&(!(x->val=x->a->val&&x->b->val));
                    break;
                }
            }
            cout<<"Valoarea de adevar a ";
            afis(init,i-1);
            cout<<": "<<x->val<<"\n";
        }
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
    int p,cnt,oke,oke2,q;
    x=new nod;
    bool ok=0;
    char cs[10001];

    in.getline(c,12800);

    i=0;

    cout<<"Doriti sa introduceti o interpretare?(0/1 pentru NU/DA)    ";
    cin>>valProp[0];

    while(i<strlen(c))
    {
        if(c[i]==' ')
            strcpy(c+i,c+i+1);
        else
        {
            if(c[i]<='Z'&&c[i]>='A'&&folosit[c[i]]==0&&valProp[0]==1)
            {
                folosit[c[i]]=1;
                cout<<"Scrieti valoarea de adevar atribuita lui "<<c[i]<<": ";
                cin>>valProp[c[i]];
            }
            i++;
        }
    }
    i=0;



    cout<<c<<"\n"<<"Doriti ca propozitia introdusa sa fie considerata in sintaxa relaxata?(0/1 pentru NU/DA)    ";
    cin>>p;

    if(p)
    {
        i=strlen(c)-1;
        while(i>0)
        {
            oke=0;
            cnt=0;
            if(c[i]=='!'&&c[i+1]=='(')
            {
                for(p=i+1;p<strlen(c);p++)
                {
                    cnt=cnt+(c[p]=='(')-(c[p]==')');
                    if(cnt==0&&c[p+1]==')')
                    {
                        oke=0;
                        break;
                    }
                    if(cnt==0&&c[p+1]!=')')
                    {
                        oke=1;
                        break;
                    }
                }
            }
            if(c[i]=='!'&&(c[i-1]!='('||oke))
            {
                strcpy(cs,c+i);
                strcpy(c+i+1,cs);
                c[i]='(';
                cnt=0;
                for(p=i+2;p<strlen(c);p++)
                {
                    cnt=cnt+(c[p]=='(')-(c[p]==')');
                    if(cnt==0)
                    {
                        strcpy(cs,c+p+1);
                        strcpy(c+p+2,cs);
                        c[p+1]=')';
                        cout<<c<<"\n";
                        break;
                    }
                }
                if(cnt!=0)
                {
                    strcpy(cs,c+p+1);
                    strcpy(c+p+2,cs);
                    c[p+1]=')';
                    cout<<c<<"\n";
                }
            }
            i--;
        }
        if(c[i]=='!')
        {
            strcpy(cs,c+i);
            strcpy(c+i+1,cs);
            c[i]='(';
            cnt=0;
            for(p=i+2;p<strlen(c);p++)
            {
                cnt=cnt+(c[p]=='(')-(c[p]==')');
                if(cnt==0)
                {
                    strcpy(cs,c+p+1);
                    strcpy(c+p+2,cs);
                    c[p+1]=')';
                    cout<<c<<"\n";
                    break;
                }
            }
            if(cnt!=0)
            {
                strcpy(cs,c+p+1);
                strcpy(c+p+2,cs);
                c[p+1]=')';
                cout<<c<<"\n";
            }
        }

        i=strlen(c)-1;
        while(i>1)
        {
            oke=0;
            cnt=0;
            if((c[i]=='|'&&c[i-1]=='|')||(c[i]=='&'&&c[i-1]=='&'))
            {
                if(/*c[i+1]=='('*/true)
                {
                    for(p=i+1;p<strlen(c);p++)
                    {
                        cnt=cnt+(c[p]=='(')-(c[p]==')');
                        if(cnt==0&&c[p+1]==')')
                        {
                            oke=0;
                            break;
                        }
                        if(cnt==0&&c[p+1]!=')')
                        {
                            oke=1;
                            break;
                        }
                    }
                }


                oke2=0;
                cnt=0;
                if(/*c[i-2]==')'*/true)
                {
                    for(q=i-2;q>=0;q--)
                    {
                        cnt=cnt+(c[q]=='(')-(c[q]==')');
                        if(cnt==0&&c[q-1]=='(')
                        {
                            oke2=0;
                            break;
                        }
                        if(cnt==0&&c[q-1]!='(')
                        {
                            oke2=1;
                            break;
                        }
                    }
                }
                if(oke||oke2)
                {
                    strcpy(cs,c+p+1);
                    strcpy(c+p+2,cs);
                    c[p+1]=')';
                    strcpy(cs,c+q);
                    strcpy(c+q+1,cs);
                    c[q]='(';
                    cout<<c<<"\n";
                }
            }
            i--;
        }

        i=strlen(c)-1;
        while(i>1)
        {
            oke=0;
            cnt=0;
            if(c[i]=='>'&&c[i-1]=='=')
            {
                if(/*c[i+1]=='('*/true)
                {
                    for(p=i+1;p<strlen(c);p++)
                    {
                        cnt=cnt+(c[p]=='(')-(c[p]==')');
                        if(cnt==0&&c[p+1]==')')
                        {
                            oke=0;
                            break;
                        }
                        if(cnt==0&&c[p+1]!=')')
                        {
                            oke=1;
                            break;
                        }
                    }
                }


                oke2=0;
                cnt=0;
                if(/*c[i-2]==')'*/true)
                {
                    for(q=i-2;q>=0;q--)
                    {
                        cnt=cnt+(c[q]=='(')-(c[q]==')');
                        if(cnt==0&&c[q-1]=='(')
                        {
                            oke2=0;
                            break;
                        }
                        if(cnt==0&&c[q-1]!='(')
                        {
                            oke2=1;
                            break;
                        }
                    }
                }
                if(oke||oke2)
                {
                    strcpy(cs,c+p+1);
                    strcpy(c+p+2,cs);
                    c[p+1]=')';
                    strcpy(cs,c+q);
                    strcpy(c+q+1,cs);
                    c[q]='(';
                    cout<<c<<"\n";
                }
            }
            i--;
        }

        i=strlen(c)-1;
        while(i>1)
        {
            oke=0;
            cnt=0;
            if(c[i]=='>'&&c[i-1]=='<')
            {
                if(/*c[i+1]=='('*/true)
                {
                    for(p=i+1;p<strlen(c);p++)
                    {
                        cnt=cnt+(c[p]=='(')-(c[p]==')');
                        if(cnt==0&&c[p+1]==')')
                        {
                            oke=0;
                            break;
                        }
                        if(cnt==0&&c[p+1]!=')')
                        {
                            oke=1;
                            break;
                        }
                    }
                }


                oke2=0,q;
                cnt=0;
                if(/*c[i-2]==')'*/true)
                {
                    for(q=i-2;q>=0;q--)
                    {
                        cnt=cnt+(c[q]=='(')-(c[q]==')');
                        if(cnt==0&&c[q-1]=='(')
                        {
                            oke2=0;
                            break;
                        }
                        if(cnt==0&&c[q-1]!='(')
                        {
                            oke2=1;
                            break;
                        }
                    }
                }
                if(oke||oke2)
                {
                    strcpy(cs,c+p+1);
                    strcpy(c+p+2,cs);
                    c[p+1]=')';
                    strcpy(cs,c+q);
                    strcpy(c+q+1,cs);
                    c[q]='(';
                    cout<<c<<"\n";
                }
            }
            i--;
        }
    }

    cout<<"\n"<<c<<"\n\n";
    i=0;
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
            cout<<"\n\nCorect. Programul nu a gasit nicio greseala in scrierea propozitiei logice.\n";

            if(valProp[0]==1)
            {
                cout<<"Valoarea de adevar a expresiei: "<<x->a->val<<"\n";
            }
        }
        else
        {
            cout<<"\n\nGresit, se mai gasesc caractere dupa sfarsitul propozitiei\n\n\n";
        }
            cout<<"\n\n";
    }
    in.close();
    return 0;
}
