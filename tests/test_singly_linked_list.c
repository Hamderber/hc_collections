#include "ut.h"
#include "hc_collections/singly_linked_list.h"

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
    int dummyData = 5;
    HC_SinglyLinkedList_t *pSentinel = hc_SLL_create();
    HC_SinglyLinkedList_t *pBad = NULL;

    fails += ut_assert(hc_SLL_nodeIsSentinel(NULL) == false, "SLL nodeIsSentinel (NULL sentinel)");
    fails += ut_assert(hc_SLL_nodeIsSentinel(pSentinel) == true, "SLL nodeIsSentinel (good sentinel)");
    pSentinel->pData = &dummyData;

    fails += ut_assert(hc_SLL_nodeIsSentinel(pSentinel) == false, "SLL nodeIsSentinel (sentinel w/ dummy data)");
    hc_SLL_destroy(&pSentinel, NULL);

    HC_SinglyLinkedList_t *pNode = hc_SLL_nodeNew(&dummyData);
    pSentinel = hc_SLL_create();
    hc_SLL_nodeAdd(&pSentinel, pNode);

    fails += ut_assert(hc_SLL_nodeDetatch(&pSentinel) == false, "SLL nodeDelink (sentinel)");
    fails += ut_assert(hc_SLL_nodeDetatch(NULL) == false, "SLL nodeDelink (NULL)");
    fails += ut_assert(hc_SLL_nodeDetatch(&pBad) == false, "SLL nodeDelink (&NULL)");

    HC_SinglyLinkedList_t **ppLink = &pSentinel->pNext;
    fails += ut_assert(hc_SLL_nodeDetatch(ppLink) == true, "SLL nodeDelink (good node)");
    fails += ut_assert(pSentinel->pNext == NULL, "SLL nodeDelink (verify updated)");
    fails += ut_assert(pNode->pNext == NULL, "SLL nodeDelink (verify cleared pNext)");

    fails += ut_assert(pSentinel != NULL, "SLL sentinelCreate");

    fails += ut_assert(hc_SLL_destroy(&pSentinel, NULL) == true, "SLL destroy (good sentinel)");
    fails += ut_assert(hc_SLL_destroy(NULL, NULL) == false, "SLL destroy (NULL sentinel)");
    fails += ut_assert(hc_SLL_destroy(&pBad, NULL) == false, "SLL destroy (&NULL sentinel)");

    pSentinel = hc_SLL_create();

    pNode = hc_SLL_nodeNew(&dummyData);
    fails += ut_assert(pNode != NULL, "SLL nodeNew (good data)");
    fails += ut_assert(hc_SLL_nodeNew(NULL) == NULL, "SLL nodeNew (NULL data)");
    fails += ut_assert(*(int *)(pNode->pData) == dummyData, "SLL nodeNew pData assignment");

    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, pNode) == true, "SLL nodeAdd (good node)");
    fails += ut_assert(hc_SLL_nodeAdd(&pNode, pNode) == false, "SLL nodeAdd (non-sentinel)");
    fails += ut_assert(hc_SLL_nodeAdd(NULL, pNode) == false, "SLL nodeAdd (NULL sentinel)");
    fails += ut_assert(hc_SLL_nodeAdd(&pBad, pNode) == false, "SLL nodeAdd (&NULL sentinel)");
    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, NULL) == false, "SLL nodeAdd (NULL node)");
    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, hc_SLL_create()) == false, "SLL nodeAdd (sentinel node)");
    fails += ut_assert(*(int *)(pSentinel->pNext->pData) == dummyData, "SLL nodeAdd added node data check");

    fails += ut_assert(hc_SLL_destroy(&pSentinel, NULL) == true, "SLL destroy (good sentinel w/ added node)");

    pSentinel = hc_SLL_create();

    pNode = hc_SLL_nodeNew(&dummyData);

    fails += ut_assert(hc_SLL_dataAdd(&pSentinel, &dummyData) == true, "SLL dataAdd (good data)");
    fails += ut_assert(hc_SLL_dataAdd(&pNode, &dummyData) == false, "SLL dataAdd (non-sentinel)");
    fails += ut_assert(hc_SLL_dataAdd(&pSentinel, NULL) == false, "SLL dataAdd (NULL data)");
    fails += ut_assert(hc_SLL_dataAdd(&pNode, &dummyData) == false, "SLL dataAdd (non-sentinel)");
    fails += ut_assert(hc_SLL_dataAdd(NULL, &dummyData) == false, "SLL dataAdd (NULL sentinel)");
    fails += ut_assert(hc_SLL_dataAdd(&pBad, &dummyData) == false, "SLL dataAdd (&NULL sentinel)");

    fails += ut_assert(hc_SLL_nodeRemove(&pSentinel, NULL) == false, "SLL nodeRemove (NULL node)");
    fails += ut_assert(hc_SLL_nodeRemove(NULL, pNode) == false, "SLL nodeRemove (NULL sentinel)");
    fails += ut_assert(hc_SLL_nodeRemove(&pBad, pNode) == false, "SLL nodeRemove (&NULL sentinel)");

    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, pNode) == true, "SLL nodeAdd (good node)");
    fails += ut_assert(hc_SLL_nodeRemove(&pNode, pNode) == false, "SLL nodeRemove (non-sentinel)");
    fails += ut_assert(hc_SLL_nodeRemove(&pSentinel, pNode) == true, "SLL nodeRemove (good node)");
    fails += ut_assert(hc_SLL_nodeRemove(&pSentinel, pNode) == false, "SLL nodeRemove (non-present node)");

    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, pNode) == true, "SLL nodeAdd (good node duplicate)");
    fails += ut_assert(hc_SLL_nodeAdd(&pSentinel, pNode) == true, "SLL nodeAdd (good node duplicate)");
    fails += ut_assert(hc_SLL_nodeRemove(&pSentinel, pNode) == true, "SLL nodeRemove (good node duplicate)");
    fails += ut_assert(hc_SLL_nodeRemove(&pSentinel, pNode) == true, "SLL nodeRemove (good node duplicate)");

    fails += ut_assert(hc_SLL_dataRemove(&pSentinel, NULL, NULL) == false, "SLL dataRemove (good sent./NULL data/NULL comp. func.)");
    fails += ut_assert(hc_SLL_dataRemove(NULL, &dummyData, NULL) == false, "SLL dataRemove (NULL sent./data/NULL comp. func.)");
    fails += ut_assert(hc_SLL_dataRemove(&pBad, &dummyData, NULL) == false, "SLL dataRemove (&NULL sent./data/NULL comp. func.)");
    fails += ut_assert(hc_SLL_dataRemove(&pNode, &dummyData, NULL) == false, "SLL dataRemove (non-sentinel)");

    fails += ut_assert(hc_SLL_dataRemove(&pSentinel, &dummyData, NULL) == true, "SLL dataRemove (good sent./data/NULL comp. func.)");

    fails += ut_assert(hc_SLL_dataAdd(&pSentinel, &dummyData) == true, "SLL dataAdd (good data)");
    fails += ut_assert(hc_SLL_dataRemove(&pSentinel, &dummyData, data_equality_func) == true, "SLL dataRemove (good sent./data/comp. func.)");
    fails += ut_assert(hc_SLL_dataRemove(&pSentinel, &dummyData, data_equality_func) == false, "SLL dataRemove (data already removed)");

    hc_SLL_destroy(&pSentinel, NULL);

    pSentinel = hc_SLL_create();

    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int expectedResult = data1 + data2 + data3;
    hc_SLL_dataAdd(&pSentinel, &data1);
    hc_SLL_dataAdd(&pSentinel, &data2);
    hc_SLL_dataAdd(&pSentinel, &data3);

    hc_SLL_destroy(&pSentinel, data_destructor_func);

    fails += ut_assert(dataDestructorCount == expectedResult, "SLL destroy (using data destructor)");
    dataDestructorCount = 0;

    pSentinel = hc_SLL_create();

    int a = 5;
    int b = 5;

    hc_SLL_dataAdd(&pSentinel, &a);
    hc_SLL_dataAdd(&pSentinel, &b);

    hc_SLL_dataRemove(&pSentinel, &a, NULL);

    hc_SLL_destroy(&pSentinel, data_destructor_func);

    fails += ut_assert(dataDestructorCount == b, "SLL dataRemove (ptr compare not by value)");

    hc_SLL_destroy(&pSentinel, NULL);

    pSentinel = hc_SLL_create();

    int n1 = 1;
    int n2 = 4;
    int n3 = 7;
    HC_SinglyLinkedList_t *pNode1 = hc_SLL_nodeNew(&n1);
    HC_SinglyLinkedList_t *pNode2 = hc_SLL_nodeNew(&n2);
    HC_SinglyLinkedList_t *pNode3 = hc_SLL_nodeNew(&n3);

    fails += ut_assert(hc_SLL_nodeInsertAfter(pSentinel, pNode1) == false, "SLL nodeInsertAfter (sentinel)");
    fails += ut_assert(hc_SLL_nodeInsertAfter(NULL, pNode1) == false, "SLL nodeInsertAfter (bad node)");
    hc_SLL_nodeAdd(&pSentinel, pNode1);
    fails += ut_assert(hc_SLL_nodeInsertAfter(pNode1, pNode2) == true, "SLL nodeInsertAfter (good node)");
    int sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    expectedResult = 4;
    fails += ut_assert(sumValidation == expectedResult, "SSL nodeInsertAfter (sumValidation = 4)");

    fails += ut_assert(hc_SLL_nodeInsertAfter(pNode1, pNode3) == true, "SLL nodeInsertAfter (good node)");
    sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    expectedResult = 7;
    fails += ut_assert(sumValidation == expectedResult, "SSL nodeInsertAfter (sumValidation = 7)");

    hc_SLL_destroy(&pSentinel, NULL);

    pSentinel = hc_SLL_create();
    pNode1 = hc_SLL_nodeNew(&n1);
    pNode2 = hc_SLL_nodeNew(&n2);
    pNode3 = hc_SLL_nodeNew(&n3);

    fails += ut_assert(hc_SLL_dataInsertAfter(pSentinel, &n1) == false, "SLL dataInsertAfter (sentinel)");
    fails += ut_assert(hc_SLL_dataInsertAfter(NULL, &n1) == false, "SLL dataInsertAfter (bad node)");
    hc_SLL_nodeAdd(&pSentinel, pNode1);
    fails += ut_assert(hc_SLL_dataInsertAfter(pNode1, NULL) == false, "SLL dataInsertAfter (bad data)");
    fails += ut_assert(hc_SLL_dataInsertAfter(pNode1, &n2) == true, "SLL dataInsertAfter (good node)");
    sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    expectedResult = 4;
    fails += ut_assert(sumValidation == expectedResult, "SSL dataInsertAfter (sumValidation = 4)");

    fails += ut_assert(hc_SLL_dataInsertAfter(pNode1, &n3) == true, "SLL dataInsertAfter (good node)");
    sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    expectedResult = 7;
    fails += ut_assert(sumValidation == expectedResult, "SSL dataInsertAfter (sumValidation = 7)");

    hc_SLL_destroy(&pSentinel, NULL);

    return fails;
}