#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cstring>
using namespace std;



class List
{
public:
    string data;
    List *next;
    List *back;
};




class MyLinkedList
{
public:
    List *head=NULL;
    int number=0;
    int size=0;
    int max=10;
    List *tail=NULL;
    List *center=NULL;
    List *delelem=NULL;
    string Name;
    bool LorR;


    /*void expansion()
    {
        max*=2;
        List **Copy=new List*[max];
        for(int i=0;i<size;i++)
           Copy[i]=ArrList[i];
        delete []ArrList;
        ArrList=Copy;
    }*/


    void add(string elem)
    {
        if(head==NULL)
        {
            head=new List();
            head->data=elem;
            head->next=NULL;
            head->back=NULL;
            tail=head;
            center=head;
            size++;
        }
        else
        {
            tail->next=new List();
            tail->next->data=elem;
            tail->next->next=NULL;
            tail->next->back=tail;
            tail=tail->next;
            size ++;
            if(size%2!=0)
                center=center->next;
        }

    }



    //НОВАЯ ФУНКЦИЯ


    void zdvigcenter()
    {
        if(LorR&&size%2!=0)
            center=center->next;
        if(!LorR&&size%2==0)
            center=center->back;
    }


    bool addd(string elem,int left,int right,bool flip,List *centercopy,bool flag=1)
    {
        int i=0;
        int z=0,a=(right-left)/2;

        if(!flip&&(right-left)%2!=0)
            a+=1;

        List *p=centercopy;

        if(flag)
        {
            while(a!=z)
            {
                z++;
                if(flip)
                    p=p->next;
                else
                    p=p->back;
            }
        }
        centercopy=p;

        if(right-left==1)
        {
            //for(;p->data[i]!=0&&elem[i]!=0&&p->data[i]==elem[i];i++);
            //if(i==strlen(elem.c_str())&&i==strlen(p->data.c_str()))
            //    return false;
            //if(i==strlen(elem.c_str())&&i==strlen(p->back->data.c_str()))
            //    return false;
            if(!flag)
                LorR=1;
            List *r=p->next;
            List *g=new List();
            g->data=elem;
            g->next=r;
            g->back=r->back;
            r->back->next=g;
            r->back=g;
            size ++;
            zdvigcenter();
            return true;
        }

        i=0;
        if(p->data[0]==elem[0])
        {
            for(;p->data[i]!=0&&elem[i]!=0&&p->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(p->data.c_str()))
            {
                delelem=p;
                return false;
            }
            //    return false;
            if((i==strlen(elem.c_str())||p->data[i]>elem[i]))
            {
                if(!flag)
                    LorR=0;
                if(addd(elem,left,(right+left)/2,0,centercopy))
                    return true;
                else
                    return false;
            }
            else
            {
                if(!flag)
                    LorR=1;
                if(addd(elem,(right+left)/2,right,1,centercopy))
                    return true;
                else
                    return false;
            }
        }
        if(p->data[0]>elem[0])
        {
            if(!flag)
                LorR=0;
            if(addd(elem,left,(right+left)/2,0,centercopy))
                return true;
            else
                return false;
        }
        else
        {
            if(!flag)
                LorR=1;
            if(addd(elem,(right+left)/2,right,1,centercopy))
                return true;
            else
                return false;
        }
    }


    bool trueaddpro(string elem)
    {
        List *p=head;
        int i=0;
        if(head==NULL)
        {
            head=new List();
            head->data=elem;
            head->next=NULL;
            head->back=NULL;
            tail=head;
            center=head;
            size ++;
            return true;
        }
        if(head->data[0]>elem[0])
        {
            head=new List();
            head->data=elem;
            head->next=p;
            head->back=NULL;
            p->back=head;
            size ++;
            LorR=0;
            zdvigcenter();
            return true;
        }
        if(tail->data[0]<elem[0])
        {
            p=new List();
            p->data=elem;
            p->next=NULL;
            p->back=tail;
            tail->next=p;
            tail=p;
            size ++;
            LorR=1;
            zdvigcenter();
            return true;
        }
        if(p->data[0]==elem[0])
        {
            for(;p->data[i]!=0&&elem[i]!=0&&p->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(p->data.c_str()))
            {
                delelem=p;
                return false;
            }
                //return false;
            if(i==strlen(elem.c_str())||p->data[i]>elem[i])
            {
                head=new List();
                head->data=elem;
                head->next=p;
                head->back=NULL;
                p->back=head;
                size ++;
                LorR=0;
                zdvigcenter();
                return true;
            }
        }
        if(tail->data[0]==elem[0])
        {
            for(;tail->data[i]!=0&&elem[i]!=0&&tail->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(tail->data.c_str()))
            {
                delelem=p;
                return false;
            }
                //return false;
            if(i==strlen(tail->data.c_str())||tail->data[i]<elem[i])
            {
                p=new List();
                p->data=elem;
                p->next=NULL;
                p->back=tail;
                tail->next=p;
                tail=p;
                size ++;
                LorR=1;
                zdvigcenter();
                return true;
            }
        }
        if(addd(elem,0,size-1,1,center,0))
            return true;
        else
            return false;
    }



    void delall()
    {
        List *p=head;
        while(p!=NULL)
        {
            List *g=p;
            delete g;
            p=p->next;
        }
    }




    bool dopisin(string elem,int left,int right,bool flip,List *centercopy,bool flag=1)
    {
        int i=0;
        int z=0,a=(right-left)/2;

        if(!flip&&(right-left)%2!=0)
            a+=1;

        List *p=centercopy;
        if(flag)
        {
            while(a!=z)
            {
                z++;
                if(flip)
                    p=p->next;
                else
                    p=p->back;
            }
        }
        centercopy=p;

        if(right-left==1)
        {
            return false;
        }

        i=0;
        if(p->data[0]==elem[0])
        {
            for(;p->data[i]!=0&&elem[i]!=0&&p->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(p->data.c_str()))
            {
                delelem=p;
                return true;
            }
            if((i==strlen(elem.c_str())||p->data[i]>elem[i]))
            {
                if(dopisin(elem,left,(right+left)/2,0,centercopy))
                    return true;
                else
                    return false;
            }
            else
            {
                if(dopisin(elem,(right+left)/2,right,1,centercopy))
                    return true;
                else
                    return false;
            }
        }
        if(p->data[0]>elem[0])
        {
            if(dopisin(elem,left,(right+left)/2,0,centercopy))
                return true;
            else
                return false;
        }
        else
        {
            if(dopisin(elem,(right+left)/2,right,1,centercopy))
                return true;
            else
                return false;
        }
    }


    bool newisin(string elem)
    {
        List *p=head;
        int i=0;
        if(head->data[0]>elem[0])
        {
            return false;
        }
        if(tail->data[0]<elem[0])
        {
            return false;
        }
        if(p->data[0]==elem[0])
        {
            for(;p->data[i]!=0&&elem[i]!=0&&p->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(p->data.c_str()))
            {
                delelem=p;
                return true;
            }
            if(i==strlen(p->data.c_str())||p->data[i]<elem[i])
            {
                return false;
            }
        }
        if(tail->data[0]==elem[0])
        {
            for(;tail->data[i]!=0&&elem[i]!=0&&tail->data[i]==elem[i];i++);
            if(i==strlen(elem.c_str())&&i==strlen(tail->data.c_str()))
            {
                delelem=p;
                return true;
            }
            if(i==strlen(tail->data.c_str())||tail->data[i]<elem[i])
            {
                return false;
            }
        }
        if(dopisin(elem,0,size-1,1,center,0))
            return true;
        else
            return false;
    }




    void zdvigcenter2()
    {
        if(LorR&&size%2==0)
            center=center->back;
        if(!LorR&&size%2!=0)
            center=center->next;
    }


    bool del(string elem)
    {
        if(head==NULL)
        {
            cout<<"Пустое множество"<<endl;
            return true;
        }
        if(elem==head->data)
        {
            if(head->next!=NULL)
            {
                head=head->next;
                head->back=NULL;
                size--;
                LorR=0;
                zdvigcenter2();
                return true;
            }
            else
            {
                head=NULL;
                center=NULL;
                size--;
                return true;
            }
        }
        if(elem==tail->data)
        {
            tail->back->next=NULL;
            tail=tail->back;
            size--;
            LorR=1;
            zdvigcenter2();
            return true;
        }
        else
        {
            if(newisin(elem))
            {
                delelem->back->next=delelem->next;
                delelem->next->back=delelem->back;
                delete delelem;
                size--;
                zdvigcenter2();
                return true;
            }
            else
            {
                return false;
            }
        }
    }


    bool isin(string elem)
    {cout<<"isin"<<endl;
        List *p = head;
        while(p!=NULL)
        {
            if(elem[0]<p->data[0])
                return false;
            if(strcmp(p->data.c_str(),elem.c_str())==0)
                return true;
            p = p->next;
        }
        return false;
    }


    MyLinkedList* intersect(MyLinkedList *list)
    {
        MyLinkedList *result=new MyLinkedList();
        List *p=head;
        while(p!=NULL)
        {
            if(list->newisin(p->data))
            {
                result->add(p->data);
            }
            p=p->next;
        }
        return result;
    }


    string print()
    {
        List *p = head;
        string s = "[\"";
        while(p->next != NULL)
        {
            s = s + p->data + "\",\"";
            p = p->next;
        }
        s = s + p->data + "\"]";
        return s;
    }


    MyLinkedList* diff(MyLinkedList *list)
    {
        MyLinkedList *result=new MyLinkedList();
        List *p=head;
        while(p!=NULL)
        {
            if(!list->newisin(p->data))
            {
                result->add(p->data);
            }
            p=p->next;
        }
        return result;
    }


    MyLinkedList* simmdiff(MyLinkedList *list)
    {
        MyLinkedList *result=new MyLinkedList();
        List *p = head;
        while(p!=NULL)
        {
            if(!list->newisin(p->data))
            {
                result->add(p->data);
            }
            p=p->next;
        }

        p=list->head;
        while(p != NULL)
        {
            if(!this->newisin(p->data))
            {
                result->trueaddpro(p->data);
            }
            p=p->next;
        }
        return result;
    }


};




MyLinkedList **ArrSet=new MyLinkedList*[0];
int n=0;





int existSet(string namelist)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(ArrSet[i]->Name==namelist)
            return i;
    }
    return i=-1;
}




bool enter(string Vvod)
{
    string word;
    string word1=word;


    MyLinkedList *commanda = new MyLinkedList();
    commanda->Name="commanda";
    for(int i=0;;i++)
    {
        if(Vvod[i]==' '||Vvod[i]=='\0')
        {
            commanda->add(word);
            word=word1;
            if(Vvod[i]=='\0')
                break;
        }
        else
            word+=Vvod[i];
    }



    if(commanda->head->data=="new")
    {
        if(existSet(commanda->head->next->data)==-1)
        {
            ArrSet[n]=new MyLinkedList();
            ArrSet[n]->Name=commanda->head->next->data;
            n++;
        }
        else
            cout<<"Такое множество уже существует"<<endl;
    }


    if(commanda->head->data=="add")
    {
        if(existSet(commanda->head->next->data)>-1)
        {
            if(commanda->head->next->next!=NULL)
            {
                if(!ArrSet[existSet(commanda->head->next->data)]->trueaddpro(commanda->head->next->next->data));
                    //cout<<"Такой элемент уже существует"<<endl;
            }
            else
                cout<<"Вы не ввели элемент"<<endl;
        }
        else
            cout<<"Такого множества не существует"<<endl;
    }


    if(commanda->head->data=="del")
    {
        if(existSet(commanda->head->next->data)>-1)
        {
            if(commanda->head->next->next!=NULL)
            {
                if(!ArrSet[existSet(commanda->head->next->data)]->del(commanda->head->next->next->data))
                    cout<<"Такого элемента не существует"<<endl;
            }
            else
            {
                ArrSet[existSet(commanda->head->next->data)]->delall();
                delete ArrSet[existSet(commanda->head->next->data)];
                for(int i=existSet(commanda->head->next->data);i<n-1;i++)
                    ArrSet[i]=ArrSet[i+1];
                n--;
            }
        }
        else
            cout<<"Такого множества не существует"<<endl;
    }


    if(commanda->head->data=="exit")
    {
        return false;
    }


    if(commanda->head->data=="show")
    {
        if(existSet(commanda->head->next->data)>-1)
        {
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL)
            {
                cout<<ArrSet[existSet(commanda->head->next->data)]->print()<<endl;
            }
            else
                cout<<"Пустое множество"<<endl;
        }
        else
            cout<<"Такого множества не существует"<<endl;
    }


    if(commanda->head->data=="Showall")
    {
        for(int i=0;i<n;i++)
        {
            if(ArrSet[i]->head!=NULL)
            {
                cout<<ArrSet[i]->print()<<endl;
            }
            else
                cout<<"Пустое множество"<<endl;
        }
        if(n==0)
            cout<<"Нету ни одного множества"<<endl;
    }


    if(commanda->head->data=="isin")
    {
        if(existSet(commanda->head->next->next->data)>-1)
        {
            if(ArrSet[existSet(commanda->head->next->next->data)]->newisin(commanda->head->next->data))
                cout<<"Да"<<endl;
            else
                cout<<"Нет"<<endl;
        }
        else
            cout<<"Такого множества не существует"<<endl;
    }


    if(commanda->head->data=="exist")
    {
        if(existSet(commanda->head->next->data)>-1)
            cout<<"Да"<<endl;
        else
            cout<<"Нет"<<endl;
    }


    if(commanda->head->data=="cls")
    {
        system("cls");
    }


    if(commanda->head->data=="intersect")
    {
        if(existSet(commanda->head->next->data)>-1||existSet(commanda->head->next->next->data)>-1)
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL||ArrSet[existSet(commanda->head->next->data)]->head!=NULL)
            {
                if(commanda->head->next->next->next!=NULL)
                {
                    ArrSet[n]=ArrSet[existSet(commanda->head->next->data)]->intersect(ArrSet[existSet(commanda->head->next->next->data)]);
                    ArrSet[n]->Name=commanda->head->next->next->next->data;
                    n++;
                }
                else
                {
                    cout<<ArrSet[existSet(commanda->head->next->data)]->intersect(ArrSet[existSet(commanda->head->next->next->data)])->print()<<endl;
                }
            }
            else
                cout<<"Множество/а пустое/ые"<<endl;
        else
            cout<<"Введены не существующее/ие множества"<<endl;
    }


    if(commanda->head->data=="union")
    {
        if(existSet(commanda->head->next->data)>-1&&existSet(commanda->head->next->next->data)>-1)
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL&&ArrSet[existSet(commanda->head->next->data)]->head!=NULL)
            {
                ArrSet[n]=new MyLinkedList();
                ArrSet[n]->Name="result";
                n++;
                List *p=ArrSet[existSet(commanda->head->next->data)]->head;
                while(p!=NULL)
                {
                    ArrSet[n-1]->add(p->data);
                    p=p->next;
                }
                p=ArrSet[existSet(commanda->head->next->next->data)]->head;
                while(p!=NULL)
                {
                    ArrSet[n-1]->trueaddpro(p->data);
                    p=p->next;
                }
                cout<<"dno"<<endl;
                if(commanda->head->next->next->next!=NULL)
                    ArrSet[n-1]->Name=commanda->head->next->next->next->data;
                else
                {
                    cout<<ArrSet[n-1]->print()<<endl;
                    ArrSet[n-1]->delall();
                    delete ArrSet[n-1];
                    for(int i=existSet(commanda->head->next->data);i<n-1;i++)
                    ArrSet[i]=ArrSet[i+1];
                    n--;
                }
            }
            else
                cout<<"Множество/а пустое/ые"<<endl;
        else
            cout<<"Введены не существующее/ие множества"<<endl;
    }


    if(commanda->head->data=="diff")
    {
       if(existSet(commanda->head->next->data)>-1||existSet(commanda->head->next->next->data)>-1)
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL||ArrSet[existSet(commanda->head->next->data)]->head!=NULL)
            {
                if(commanda->head->next->next->next!=NULL)
                {
                    ArrSet[n]=ArrSet[existSet(commanda->head->next->data)]->diff(ArrSet[existSet(commanda->head->next->next->data)]);
                    ArrSet[n]->Name=commanda->head->next->next->next->data;
                    n++;
                }
                else
                {
                    cout<<ArrSet[existSet(commanda->head->next->data)]->diff(ArrSet[existSet(commanda->head->next->next->data)])->print()<<endl;
                }
            }
            else
                cout<<"Множество/а пустое/ые"<<endl;
        else
            cout<<"Введены не существующее/ие множества"<<endl;
    }


    if(commanda->head->data=="simmdiff")
    {
       if(existSet(commanda->head->next->data)>-1||existSet(commanda->head->next->next->data)>-1)
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL||ArrSet[existSet(commanda->head->next->data)]->head!=NULL)
        {
                if(commanda->head->next->next->next!=NULL){
                    ArrSet[n]=ArrSet[existSet(commanda->head->next->data)]->simmdiff(ArrSet[existSet(commanda->head->next->next->data)]);
                    ArrSet[n]->Name=commanda->head->next->next->next->data;
                    n++;
                }
                else
                {
                    cout<<ArrSet[existSet(commanda->head->next->data)]->simmdiff(ArrSet[existSet(commanda->head->next->next->data)])->print()<<endl;
                }
       }
            else
                cout<<"Множество/а пустое/ые"<<endl;


        else
            cout<<"Введены не существующее/ие множества"<<endl;
    }


    if(commanda->head->data=="Isin")
    {
        if(existSet(commanda->head->next->data)>-1||existSet(commanda->head->next->next->data)>-1)
        {
            if(ArrSet[existSet(commanda->head->next->data)]->head!=NULL||ArrSet[existSet(commanda->head->next->data)]->head!=NULL){
                if(ArrSet[existSet(commanda->head->next->data)]->intersect(ArrSet[existSet(commanda->head->next->next->data)])->size==ArrSet[existSet(commanda->head->next->data)]->size)
                    cout<<"Да"<<endl;
                else
                    cout<<"Нет"<<endl;
            }
            else
                cout<<"Множество/а пустое/ые"<<endl;
        }
        else
            cout<<"Введены не существующее/ие множества"<<endl;
    }


    return true;
}


int main()
{
    setlocale(LC_ALL, "");

    string Vvod;
    char Buff[50];
    int kod;

    cout<<"1-Консольный ввод"<<endl<<"2-Скрипт"<<endl;

    kod=getch();
    system("cls");
    switch(kod)
    {
        case 49:
        do
        {
            getline(cin, Vvod);
        }while(enter(Vvod));
        break;

        case 50:
        ifstream file("script.txt");
        if (!file.is_open())
        cout<<"Файл не может быть открыт!"<<endl;
        do
        {
            file.getline(Buff, 50);
        }while(enter(Buff));
        file.close();
        break;
    }


    return 0;
}
