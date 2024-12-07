#ifndef RANDOMIZEDQSORT_H
#define RANDOMIZEDQSORT_H
namespace RQSORT
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
template <typename E>
void swap(E arr[], int l, int r)
{
    arr[l]=arr[l]+arr[r]-(arr[r]=arr[l]);
}
template <typename E>
inline int findpivot(E* A,int i,int j)
{
    srand(time(NULL));
    int r=i+rand()%(j-i);
    return r;
}
template <typename E>
inline int partition(E A[], int l, int r, E& pivot)
{
    do
    {
        while (prior<E>(A[++l], pivot));
        while ((l < r) && prior<E>(pivot, A[--r]));
        swap(A, l, r);
    }
    while (l < r);
    return l;
}

}
template <typename E>
void rqsort(E A[], int i, int j)
{
    if (j <= i)
        return;
    int pivotindex = RQSORT::findpivot(A,i, j);
    RQSORT::swap(A, pivotindex, j);
    int k = RQSORT::partition<E>(A, i-1, j, A[j]);
    RQSORT::swap(A, k, j);
    qsort<E>(A, i, k-1);
    qsort<E>(A, k+1, j);
}
#endif//RANDOMIZEDQSORT_H
