#include "LinkedList.h"

using namespace std;

int main()
{
    LinkedList v;
    for(int i = 0;i < 5;i++)
        v.pushBack(i);
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.pushFront(9);
    v.pushBack(9);
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.insert(2,11);
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.insertAfterNode(v.findNode(3),9);
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.removeNextNode(v.findNode(3));
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.removeFront();
    v.removeBack();
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
    v.reverse();
    for(int i =0; i < v.size(); i++)
        cout<<v[i]<<" ";



}