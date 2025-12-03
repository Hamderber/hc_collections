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
    int dummyData = 5;
    HC_DoublyLinkedList_t *pSentinel = hc_DLL_create();
    HC_DoublyLinkedList_t *pBad = NULL;

    HC_DoublyLinkedList_t *pNonNullPrev = hc_DLL_create();
    pNonNullPrev->pPrev = pSentinel;
    fails += ut_assert(hc_DLL_nodeIsSentinel(NULL) == false, "DLL nodeIsSentinel (NULL sentinel)");
    fails += ut_assert(hc_DLL_nodeIsSentinel(pNonNullPrev) == false, "DLL nodeIsSentinel (non-null pPrev)");
    fails += ut_assert(hc_DLL_nodeIsSentinel(pSentinel) == true, "DLL nodeIsSentinel (good sentinel)");
    pSentinel->pData = &dummyData;

    pNonNullPrev->pPrev = NULL;
    hc_DLL_destroy(&pNonNullPrev, NULL);

    fails += ut_assert(hc_DLL_nodeIsSentinel(pSentinel) == false, "DLL nodeIsSentinel (sentinel w/ dummy data)");
    hc_DLL_destroy(&pSentinel, NULL);

    HC_DoublyLinkedList_t *pNode = hc_DLL_nodeNew(&dummyData);
    pSentinel = hc_DLL_create();
    hc_DLL_nodeAdd(&pSentinel, pNode);

    fails += ut_assert(hc_DLL_nodeDetatch(&pSentinel) == false, "DLL nodeDelink (sentinel)");
    fails += ut_assert(hc_DLL_nodeDetatch(NULL) == false, "DLL nodeDelink (NULL)");
    fails += ut_assert(hc_DLL_nodeDetatch(&pBad) == false, "DLL nodeDelink (&NULL)");

    HC_DoublyLinkedList_t **ppLink = &pSentinel->pNext;
    fails += ut_assert(hc_DLL_nodeDetatch(ppLink) == true, "DLL nodeDelink (good node)");
    // fails += ut_assert(pSentinel->pNext == NULL, "DLL nodeDelink (verify updated)");
    // fails += ut_assert(pNode->pNext == NULL, "DLL nodeDelink (verify cleared pNext)");
    // fails += ut_assert(pNode->pPrev == NULL, "DLL nodeDelink (verify cleared pNext)");

    // fails += ut_assert(pSentinel != NULL, "DLL sentinelCreate");

    // fails += ut_assert(hc_DLL_destroy(&pSentinel, NULL) == true, "DLL destroy (good sentinel)");
    // fails += ut_assert(hc_DLL_destroy(NULL, NULL) == false, "DLL destroy (NULL sentinel)");
    // fails += ut_assert(hc_DLL_destroy(&pBad, NULL) == false, "DLL destroy (&NULL sentinel)");

    // pSentinel = hc_DLL_create();

    // pNode = hc_DLL_nodeNew(&dummyData);
    // fails += ut_assert(pNode != NULL, "DLL nodeNew (good data)");
    // fails += ut_assert(hc_DLL_nodeNew(NULL) == NULL, "DLL nodeNew (NULL data)");
    // fails += ut_assert(*(int *)(pNode->pData) == dummyData, "DLL nodeNew pData assignment");

    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, pNode) == true, "DLL nodeAdd (good node)");
    // fails += ut_assert(hc_DLL_nodeAdd(&pNode, pNode) == false, "DLL nodeAdd (non-sentinel)");
    // fails += ut_assert(hc_DLL_nodeAdd(NULL, pNode) == false, "DLL nodeAdd (NULL sentinel)");
    // fails += ut_assert(hc_DLL_nodeAdd(&pBad, pNode) == false, "DLL nodeAdd (&NULL sentinel)");
    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, NULL) == false, "DLL nodeAdd (NULL node)");
    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, hc_DLL_create()) == false, "DLL nodeAdd (sentinel node)");
    // fails += ut_assert(*(int *)(pSentinel->pNext->pData) == dummyData, "DLL nodeAdd added node data check");

    // fails += ut_assert(hc_DLL_destroy(&pSentinel, NULL) == true, "DLL destroy (good sentinel w/ added node)");

    // pSentinel = hc_DLL_create();

    // pNode = hc_DLL_nodeNew(&dummyData);

    // fails += ut_assert(hc_DLL_dataAdd(&pSentinel, &dummyData) == true, "DLL dataAdd (good data)");
    // fails += ut_assert(hc_DLL_dataAdd(&pNode, &dummyData) == false, "DLL dataAdd (non-sentinel)");
    // fails += ut_assert(hc_DLL_dataAdd(&pSentinel, NULL) == false, "DLL dataAdd (NULL data)");
    // fails += ut_assert(hc_DLL_dataAdd(&pNode, &dummyData) == false, "DLL dataAdd (non-sentinel)");
    // fails += ut_assert(hc_DLL_dataAdd(NULL, &dummyData) == false, "DLL dataAdd (NULL sentinel)");
    // fails += ut_assert(hc_DLL_dataAdd(&pBad, &dummyData) == false, "DLL dataAdd (&NULL sentinel)");

    // fails += ut_assert(hc_DLL_nodeRemove(&pSentinel, NULL) == false, "DLL nodeRemove (NULL node)");
    // fails += ut_assert(hc_DLL_nodeRemove(NULL, pNode) == false, "DLL nodeRemove (NULL sentinel)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pBad, pNode) == false, "DLL nodeRemove (&NULL sentinel)");

    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, pNode) == true, "DLL nodeAdd (good node)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pNode, pNode) == false, "DLL nodeRemove (non-sentinel)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pSentinel, pNode) == true, "DLL nodeRemove (good node)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pSentinel, pNode) == false, "DLL nodeRemove (non-present node)");

    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, pNode) == true, "DLL nodeAdd (good node duplicate)");
    // fails += ut_assert(hc_DLL_nodeAdd(&pSentinel, pNode) == true, "DLL nodeAdd (good node duplicate)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pSentinel, pNode) == true, "DLL nodeRemove (good node duplicate)");
    // fails += ut_assert(hc_DLL_nodeRemove(&pSentinel, pNode) == true, "DLL nodeRemove (good node duplicate)");

    // fails += ut_assert(hc_DLL_dataRemove(&pSentinel, NULL, NULL) == false, "DLL dataRemove (good sent./NULL data/NULL comp. func.)");
    // fails += ut_assert(hc_DLL_dataRemove(NULL, &dummyData, NULL) == false, "DLL dataRemove (NULL sent./data/NULL comp. func.)");
    // fails += ut_assert(hc_DLL_dataRemove(&pBad, &dummyData, NULL) == false, "DLL dataRemove (&NULL sent./data/NULL comp. func.)");
    // fails += ut_assert(hc_DLL_dataRemove(&pNode, &dummyData, NULL) == false, "DLL dataRemove (non-sentinel)");

    // fails += ut_assert(hc_DLL_dataRemove(&pSentinel, &dummyData, NULL) == true, "DLL dataRemove (good sent./data/NULL comp. func.)");

    // fails += ut_assert(hc_DLL_dataAdd(&pSentinel, &dummyData) == true, "DLL dataAdd (good data)");
    // fails += ut_assert(hc_DLL_dataRemove(&pSentinel, &dummyData, data_equality_func) == true, "DLL dataRemove (good sent./data/comp. func.)");
    // fails += ut_assert(hc_DLL_dataRemove(&pSentinel, &dummyData, data_equality_func) == false, "DLL dataRemove (data already removed)");

    // hc_DLL_destroy(&pSentinel, NULL);

    // pSentinel = hc_DLL_create();

    // int data1 = 1;
    // int data2 = 2;
    // int data3 = 3;
    // int expectedResult = data1 + data2 + data3;
    // hc_DLL_dataAdd(&pSentinel, &data1);
    // hc_DLL_dataAdd(&pSentinel, &data2);
    // hc_DLL_dataAdd(&pSentinel, &data3);

    // hc_DLL_destroy(&pSentinel, data_destructor_func);

    // fails += ut_assert(dataDestructorCount == expectedResult, "DLL destroy (using data destructor)");
    // dataDestructorCount = 0;

    // pSentinel = hc_DLL_create();

    // int a = 5;
    // int b = 5;

    // hc_DLL_dataAdd(&pSentinel, &a);
    // hc_DLL_dataAdd(&pSentinel, &b);

    // hc_DLL_dataRemove(&pSentinel, &a, NULL);

    // hc_DLL_destroy(&pSentinel, data_destructor_func);

    // fails += ut_assert(dataDestructorCount == b, "DLL dataRemove (ptr compare not by value)");

    // hc_DLL_destroy(&pSentinel, NULL);

    // pSentinel = hc_DLL_create();

    // int n1 = 1;
    // int n2 = 4;
    // int n3 = 7;
    // HC_DoublyLinkedList_t *pNode1 = hc_DLL_nodeNew(&n1);
    // HC_DoublyLinkedList_t *pNode2 = hc_DLL_nodeNew(&n2);
    // HC_DoublyLinkedList_t *pNode3 = hc_DLL_nodeNew(&n3);

    // fails += ut_assert(hc_DLL_nodeInsertAfter(pSentinel, pNode1) == false, "DLL nodeInsertAfter (sentinel)");
    // fails += ut_assert(hc_DLL_nodeInsertAfter(NULL, pNode1) == false, "DLL nodeInsertAfter (bad node)");
    // hc_DLL_nodeAdd(&pSentinel, pNode1);
    // fails += ut_assert(hc_DLL_nodeInsertAfter(pNode1, pNode2) == true, "DLL nodeInsertAfter (good node)");
    // int sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 4;
    // fails += ut_assert(sumValidation == expectedResult, "DLL nodeInsertAfter (sumValidation = 4)");

    // fails += ut_assert(hc_DLL_nodeInsertAfter(pNode1, pNode3) == true, "DLL nodeInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 7;
    // fails += ut_assert(sumValidation == expectedResult, "DLL nodeInsertAfter (sumValidation = 7)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pNext->pPrev->pData);
    // expectedResult = 4;
    // fails += ut_assert(sumValidation == expectedResult, "DLL nodeInsertAfter (sumValidation = 4 (pPrev))");
    // printf("%d\n%d\n%d\n",
    //        *(int *)(pSentinel->pNext->pData),
    //        *(int *)(pSentinel->pNext->pNext->pData),
    //        *(int *)(pSentinel->pNext->pNext->pNext->pData));

    // hc_DLL_destroy(&pSentinel, NULL);

    // pSentinel = hc_DLL_create();
    // pNode1 = hc_DLL_nodeNew(&n1);
    // pNode2 = hc_DLL_nodeNew(&n2);
    // pNode3 = hc_DLL_nodeNew(&n3);

    // fails += ut_assert(hc_DLL_dataInsertAfter(pSentinel, &n1) == false, "DLL dataInsertAfter (sentinel)");
    // fails += ut_assert(hc_DLL_dataInsertAfter(NULL, &n1) == false, "DLL dataInsertAfter (bad node)");
    // hc_DLL_nodeAdd(&pSentinel, pNode1);
    // fails += ut_assert(hc_DLL_dataInsertAfter(pNode1, NULL) == false, "DLL dataInsertAfter (bad data)");
    // fails += ut_assert(hc_DLL_dataInsertAfter(pNode1, &n2) == true, "DLL dataInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 4;
    // fails += ut_assert(sumValidation == expectedResult, "DLL dataInsertAfter (sumValidation = 4)");

    // fails += ut_assert(hc_DLL_dataInsertAfter(pNode1, &n3) == true, "DLL dataInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 7;
    // fails += ut_assert(sumValidation == expectedResult, "DLL dataInsertAfter (sumValidation = 7)");

    // hc_DLL_destroy(&pSentinel, NULL);

    return fails;
}