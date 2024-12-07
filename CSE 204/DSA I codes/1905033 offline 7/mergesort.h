#ifndef MERGESORT_H
#define MERGESORT_H
namespace MERGESORT
{
template<typename E>
bool prior(E it1, E it2)
{
    if(it1<it2)
    {
        return true;
    }
    return false;
}
}
using namespace MERGESORT;
template <typename E>
int mergesort(E A[], E temp[], int left, int right)
{
    if (left == right)//only 1 element
        return 0;
    int mid = (left+right)/2;
    int c=0;
    mergesort<E>(A, temp, left, mid);
    mergesort<E>(A, temp, mid+1, right);
    for (int i=left; i<=right; i++)
        temp[i] = A[i];
    int i1 = left;
    int i2 = mid + 1;
    for (int curr=left; curr<=right; curr++)
    {
        if (i1 == mid+1)//if left one is empty
            A[curr] = temp[i2++];
        else if (i2 > right)//if right one is empty
            A[curr] = temp[i1++];
        else if (prior<E>(temp[i1], temp[i2]))
        {//place the smallest one
            A[curr] = temp[i1++];
            c+=mid-i1;
        }
        else
            A[curr] = temp[i2++];//same
    }
    return c;
}
#endif//MERGESORT_H
