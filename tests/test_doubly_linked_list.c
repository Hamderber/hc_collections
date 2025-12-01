#include "ut.h"
#include "hc_collections/doubly_linked_list.h"

static int dataDestructorCount = 0;

void data_destructor_func(void *pData)
{
    dataDestructorCount += *(int *)pData;
}

bool data_equality_func(void *pDataLeft, void *pDataRight)
{
    printf("%p <> %p, %d <> %d\n", pDataLeft, pDataRight, *(int *)pDataLeft, *(int *)pDataRight);
    return *(int *)pDataLeft == *(int *)pDataRight;
}

int main(void)
{
    int fails = 0;

    fails += test();

    return fails;
}