#include<iostream>
#include"Arr.cpp"
#include"LL.cpp"
using namespace std;
class dishStackInfo
{
public:
    int k,t,s;
    bool continued;
    dishStackInfo() {}
    dishStackInfo(int k, int t, int s,bool c)
    {
        this->k=k;
        this->t=t;
        this->s=s;
        continued=c;
    }
};
void printList(LStack<int>& ob)
{
    int top=ob.length();
    int a[top];

    for(int i=0; i<top; i++)
    {
        a[i]=ob.pop();
    }
    for(int i=top-2; i>=0; i--)
        cout<<a[i]<<",";
    cout<<"\b";
    cout<<" ";
    cout<<'\n';
    ob.clear();
    for(int i=top-1; i>=0; i--)
    {
        ob.push(a[i]);
    }
}
void printList(AStack<int>& ob)
{
    int top=ob.length();
    int a[top];

    for(int i=0; i<top; i++)
    {
        a[i]=ob.pop();
    }
    for(int i=top-2; i>=0; i--)
        cout<<a[i]<<",";
    cout<<"\b";
    cout<<" ";
    cout<<'\n';
    ob.clear();
    for(int i=top-1; i>=0; i--)
    {
        ob.push(a[i]);
    }
}
int main()
{
//    LStack<dishStackInfo> dirty,clean;

    dishStackInfo* arr=new dishStackInfo[DEFAULT_SIZE];
    AStack<dishStackInfo> dirty(arr,1),clean(arr,-1);

    int inviteeNo,dishNo;
    cin>>inviteeNo>>dishNo;
    int timeForEach[dishNo];
    for(int i=0; i<dishNo; i++)
        cin>>timeForEach[i];
    int invitee=-1,timePushed,course;
    int j=inviteeNo,freetime;

//    LStack<int> endTime;

    int* timeArr=new int[DEFAULT_SIZE];
    AStack<int> endTime(timeArr);

    endTime.push(-1);
    int fullCourseCount[2][inviteeNo];
    for(int j=0; j<2; j++)
        for(int i=0; i<inviteeNo; i++)
            fullCourseCount[j][i]=0;
    dirty.push(dishStackInfo(-1,-1,-1,false));
    while(true)
    {
        if(invitee!=0)
        {
            cin>>invitee>>timePushed>>course;

            fullCourseCount[0][invitee-1]++;
            if(fullCourseCount[0][invitee-1]==3)
            {
                fullCourseCount[1][invitee-1]=j--;
            }

            if(timePushed<endTime.topValue()){
                dirty.push(dishStackInfo(invitee,timePushed,course,true));
            }
            else if(timePushed>endTime.topValue())
            {
                while(dirty.topValue().continued)
                {
                    endTime.push(endTime.topValue()+timeForEach[dirty.topValue().s-1]);
                    clean.push(dirty.pop());
                }
                dirty.push(dishStackInfo(invitee,timePushed,course,false));
                clean.push(dirty.pop());
                endTime.push(timePushed+timeForEach[course-1]-1);
            }
            else if(timePushed==endTime.topValue())
            {
                dirty.push(dishStackInfo(invitee,timePushed,course,false));
                clean.push(dirty.pop());
                endTime.push(timePushed+timeForEach[course-1]);
                while(dirty.topValue().continued)
                {
                    endTime.push(endTime.topValue()+timeForEach[dirty.topValue().s-1]);
                    clean.push(dirty.pop());
                }
            }
            if(!invitee)
                break;
        }
    }
    cout<<endTime.topValue()<<'\n';
    printList(endTime);
    bool flag=true;
    for(int i=0; i<inviteeNo; i++)
    {
        if(fullCourseCount[0][i]!=dishNo)
        {
            flag=false;
            break;
        }
    }
    cout<<(flag?"Y":"N")<<'\n';
    for(int i=1; i<=inviteeNo; i++)
    {
        for(int j=0;j<inviteeNo;j++){
            if(fullCourseCount[1][j]==i)
                cout<<j+1<<" ";
        }
    }
    cout<<'\n';

    delete[] arr;

    delete[] timeArr;
}

