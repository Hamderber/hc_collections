#include "ut.h"
#include "hc_collections/singly_linked_set.h"

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

int hashcode_func(void *pData)
{
    // represents magically turning in some data into a hashCode int
    return *(int *)pData;
}

int main(void)
{
    int fails = 0;
    int dummyData = 5;
    HC_SinglyLinkedSet_t *pSentinel = hc_SLS_create();
    HC_SinglyLinkedSet_t *pBad = NULL;

    fails += ut_assert(hc_SLS_nodeIsSentinel(NULL) == false, "SLS nodeIsSentinel (NULL sentinel)");
    fails += ut_assert(hc_SLS_nodeIsSentinel(pSentinel) == true, "SLS nodeIsSentinel (good sentinel)");
    pSentinel->pData = &dummyData;

    fails += ut_assert(hc_SLS_nodeIsSentinel(pSentinel) == false, "SLS nodeIsSentinel (sentinel w/ dummy data)");
    hc_SLS_destroy(&pSentinel, NULL);

    // HC_SinglyLinkedSet_t *pNode = hc_SLS_nodeNew(&dummyData, hashcode_func);
    // pSentinel = hc_SLS_create();
    // hc_SLS_nodeAdd(&pSentinel, pNode);

    // fails += ut_assert(hc_SLS_nodeDetatch(&pSentinel) == false, "SLS nodeDelink (sentinel)");
    // fails += ut_assert(hc_SLS_nodeDetatch(NULL) == false, "SLS nodeDelink (NULL)");
    // fails += ut_assert(hc_SLS_nodeDetatch(&pBad) == false, "SLS nodeDelink (&NULL)");

    // HC_SinglyLinkedSet_t **ppLink = &pSentinel->pNext;
    // fails += ut_assert(hc_SLS_nodeDetatch(ppLink) == true, "SLS nodeDelink (good node)");
    // fails += ut_assert(pSentinel->pNext == NULL, "SLS nodeDelink (verify updated)");
    // fails += ut_assert(pNode->pNext == NULL, "SLS nodeDelink (verify cleared pNext)");

    // fails += ut_assert(pSentinel != NULL, "SLS sentinelCreate");

    // fails += ut_assert(hc_SLS_destroy(&pSentinel, NULL) == true, "SLS destroy (good sentinel)");
    // fails += ut_assert(hc_SLS_destroy(NULL, NULL) == false, "SLS destroy (NULL sentinel)");
    // fails += ut_assert(hc_SLS_destroy(&pBad, NULL) == false, "SLS destroy (&NULL sentinel)");

    // pSentinel = hc_SLS_create();

    // pNode = hc_SLS_nodeNew(&dummyData, hashcode_func);
    // fails += ut_assert(pNode != NULL, "SLS nodeNew (good data)");
    // fails += ut_assert(hc_SLS_nodeNew(NULL, hashcode_func) == NULL, "SLS nodeNew (NULL data)");
    // fails += ut_assert(*(int *)(pNode->pData) == dummyData, "SLS nodeNew pData assignment");

    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, pNode) == true, "SLS nodeAdd (good node)");
    // fails += ut_assert(hc_SLS_nodeAdd(&pNode, pNode) == false, "SLS nodeAdd (non-sentinel)");
    // fails += ut_assert(hc_SLS_nodeAdd(NULL, pNode) == false, "SLS nodeAdd (NULL sentinel)");
    // fails += ut_assert(hc_SLS_nodeAdd(&pBad, pNode) == false, "SLS nodeAdd (&NULL sentinel)");
    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, NULL) == false, "SLS nodeAdd (NULL node)");
    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, hc_SLS_create()) == false, "SLS nodeAdd (sentinel node)");
    // fails += ut_assert(*(int *)(pSentinel->pNext->pData) == dummyData, "SLS nodeAdd added node data check");

    // fails += ut_assert(hc_SLS_destroy(&pSentinel, NULL) == true, "SLS destroy (good sentinel w/ added node)");

    // pSentinel = hc_SLS_create();

    // pNode = hc_SLS_nodeNew(&dummyData, hashcode_func);

    // fails += ut_assert(hc_SLS_dataAdd(&pSentinel, &dummyData, hashcode_func) == true, "SLS dataAdd (good data)");
    // fails += ut_assert(hc_SLS_dataAdd(&pNode, &dummyData, hashcode_func) == false, "SLS dataAdd (non-sentinel)");
    // fails += ut_assert(hc_SLS_dataAdd(&pSentinel, NULL, hashcode_func) == false, "SLS dataAdd (NULL data)");
    // fails += ut_assert(hc_SLS_dataAdd(&pNode, &dummyData, hashcode_func) == false, "SLS dataAdd (non-sentinel)");
    // fails += ut_assert(hc_SLS_dataAdd(NULL, &dummyData, hashcode_func) == false, "SLS dataAdd (NULL sentinel)");
    // fails += ut_assert(hc_SLS_dataAdd(&pBad, &dummyData, hashcode_func) == false, "SLS dataAdd (&NULL sentinel)");

    // fails += ut_assert(hc_SLS_nodeRemove(&pSentinel, NULL) == false, "SLS nodeRemove (NULL node)");
    // fails += ut_assert(hc_SLS_nodeRemove(NULL, pNode) == false, "SLS nodeRemove (NULL sentinel)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pBad, pNode) == false, "SLS nodeRemove (&NULL sentinel)");

    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, pNode) == true, "SLS nodeAdd (good node)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pNode, pNode) == false, "SLS nodeRemove (non-sentinel)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pSentinel, pNode) == true, "SLS nodeRemove (good node)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pSentinel, pNode) == false, "SLS nodeRemove (non-present node)");

    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, pNode) == true, "SLS nodeAdd (good node duplicate)");
    // fails += ut_assert(hc_SLS_nodeAdd(&pSentinel, pNode) == true, "SLS nodeAdd (good node duplicate)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pSentinel, pNode) == true, "SLS nodeRemove (good node duplicate)");
    // fails += ut_assert(hc_SLS_nodeRemove(&pSentinel, pNode) == true, "SLS nodeRemove (good node duplicate)");

    // fails += ut_assert(hc_SLS_dataRemove(&pSentinel, NULL, NULL) == false, "SLS dataRemove (good sent./NULL data/NULL comp. func.)");
    // fails += ut_assert(hc_SLS_dataRemove(NULL, &dummyData, NULL) == false, "SLS dataRemove (NULL sent./data/NULL comp. func.)");
    // fails += ut_assert(hc_SLS_dataRemove(&pBad, &dummyData, NULL) == false, "SLS dataRemove (&NULL sent./data/NULL comp. func.)");
    // fails += ut_assert(hc_SLS_dataRemove(&pNode, &dummyData, NULL) == false, "SLS dataRemove (non-sentinel)");

    // fails += ut_assert(hc_SLS_dataRemove(&pSentinel, &dummyData, NULL) == true, "SLS dataRemove (good sent./data/NULL comp. func.)");

    // fails += ut_assert(hc_SLS_dataAdd(&pSentinel, &dummyData, hashcode_func) == true, "SLS dataAdd (good data)");
    // fails += ut_assert(hc_SLS_dataRemove(&pSentinel, &dummyData, data_equality_func) == true, "SLS dataRemove (good sent./data/comp. func.)");
    // fails += ut_assert(hc_SLS_dataRemove(&pSentinel, &dummyData, data_equality_func) == false, "SLS dataRemove (data already removed)");

    // hc_SLS_destroy(&pSentinel, NULL);

    // pSentinel = hc_SLS_create();

    // int data1 = 1;
    // int data2 = 2;
    // int data3 = 3;
    // int expectedResult = data1 + data2 + data3;
    // hc_SLS_dataAdd(&pSentinel, &data1, hashcode_func);
    // hc_SLS_dataAdd(&pSentinel, &data2, hashcode_func);
    // hc_SLS_dataAdd(&pSentinel, &data3, hashcode_func);

    // hc_SLS_destroy(&pSentinel, data_destructor_func);

    // fails += ut_assert(dataDestructorCount == expectedResult, "SLS destroy (using data destructor)");
    // dataDestructorCount = 0;

    // pSentinel = hc_SLS_create();

    // int a = 5;
    // int b = 5;

    // hc_SLS_dataAdd(&pSentinel, &a, hashcode_func);
    // hc_SLS_dataAdd(&pSentinel, &b, hashcode_func);

    // hc_SLS_dataRemove(&pSentinel, &a, NULL);

    // hc_SLS_destroy(&pSentinel, data_destructor_func);

    // fails += ut_assert(dataDestructorCount == b, "SLS dataRemove (ptr compare not by value)");

    // hc_SLS_destroy(&pSentinel, NULL);

    // pSentinel = hc_SLS_create();

    // int n1 = 1;
    // int n2 = 4;
    // int n3 = 7;
    // HC_SinglyLinkedSet_t *pNode1 = hc_SLS_nodeNew(&n1, hashcode_func);
    // HC_SinglyLinkedSet_t *pNode2 = hc_SLS_nodeNew(&n2, hashcode_func);
    // HC_SinglyLinkedSet_t *pNode3 = hc_SLS_nodeNew(&n3, hashcode_func);

    // fails += ut_assert(hc_SLS_nodeInsertAfter(pSentinel, pNode1) == false, "SLS nodeInsertAfter (sentinel)");
    // fails += ut_assert(hc_SLS_nodeInsertAfter(NULL, pNode1) == false, "SLS nodeInsertAfter (bad node)");
    // hc_SLS_nodeAdd(&pSentinel, pNode1);
    // fails += ut_assert(hc_SLS_nodeInsertAfter(pNode1, pNode2) == true, "SLS nodeInsertAfter (good node)");
    // int sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 4;
    // fails += ut_assert(sumValidation == expectedResult, "SLS nodeInsertAfter (sumValidation = 4)");

    // fails += ut_assert(hc_SLS_nodeInsertAfter(pNode1, pNode3) == true, "SLS nodeInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 7;
    // fails += ut_assert(sumValidation == expectedResult, "SLS nodeInsertAfter (sumValidation = 7)");

    // hc_SLS_destroy(&pSentinel, NULL);

    // pSentinel = hc_SLS_create();
    // pNode1 = hc_SLS_nodeNew(&n1, hashcode_func);
    // pNode2 = hc_SLS_nodeNew(&n2, hashcode_func);
    // pNode3 = hc_SLS_nodeNew(&n3, hashcode_func);

    // fails += ut_assert(hc_SLS_dataInsertAfter(pSentinel, &n1) == false, "SLS dataInsertAfter (sentinel)");
    // fails += ut_assert(hc_SLS_dataInsertAfter(NULL, &n1) == false, "SLS dataInsertAfter (bad node)");
    // hc_SLS_nodeAdd(&pSentinel, pNode1);
    // fails += ut_assert(hc_SLS_dataInsertAfter(pNode1, NULL) == false, "SLS dataInsertAfter (bad data)");
    // fails += ut_assert(hc_SLS_dataInsertAfter(pNode1, &n2) == true, "SLS dataInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 4;
    // fails += ut_assert(sumValidation == expectedResult, "SLS dataInsertAfter (sumValidation = 4)");

    // fails += ut_assert(hc_SLS_dataInsertAfter(pNode1, &n3) == true, "SLS dataInsertAfter (good node)");
    // sumValidation = *(int *)(pSentinel->pNext->pNext->pData);
    // expectedResult = 7;
    // fails += ut_assert(sumValidation == expectedResult, "SLS dataInsertAfter (sumValidation = 7)");

    // hc_SLS_destroy(&pSentinel, NULL);

    return fails;
}