#ifndef INSSORT_H
#define INSSORT_H
namespace INSSORT
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
}
template <typename E>
void inssort(E A[], int n)
{
    for (int i=1; i<n; i++)
    {
        for (int j=i; (j>0) && (INSSORT::prior(A[j], A[j-1])); j--)
            INSSORT::swap(A, j, j-1);
    }
}
#endif//INSSORT_H
