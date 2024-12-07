#ifndef QUICKSORT_H
#define QUICKSORT_H
namespace QUICKSORT
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
inline int partition(E A[], int l, int r, E& pivot)
{
    do
    {
        while (prior<E>(A[++l], pivot));//smaller than pivot
        while ((l < r) && prior<E>(pivot, A[--r]));//larger than pivot
        swap(A, l, r);//swapping to get them right
    }
    while (l < r);
    return l;//elements larger than pivot stat here
}

}
template <typename E>
void qsort(E A[], int i, int j)
{
    if (j <= i)//only 0 or 1 element
        return;
    int k = QUICKSORT::partition<E>(A, i-1, j, A[j]);
    QUICKSORT::swap(A, k, j);
    qsort<E>(A, i, k-1);
    qsort<E>(A, k+1, j);
}
#endif//QUICKSORT_H
