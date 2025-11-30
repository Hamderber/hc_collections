#include "hc_collections.h"
#include "hc_collections/singly_linked_list.h"

HC_SinglyLinkedList_t *hc_SLL_create(void)
{
    HC_SinglyLinkedList_t *pNode = calloc(1, sizeof(HC_SinglyLinkedList_t));
    if (!pNode)
        return NULL;

    return pNode;
}

HC_SinglyLinkedList_t *hc_SLL_nodeNew(void *pData)
{
    if (!pData)
        return NULL;

    HC_SinglyLinkedList_t *pNode = malloc(sizeof(HC_SinglyLinkedList_t));
    if (!pNode)
        return NULL;

    pNode->pData = pData;
    pNode->pNext = NULL;

    return pNode;
}

static inline bool hc_SLL_nodeIsSentinel(HC_SinglyLinkedList_t *pNode)
{
    // Sentinel nodes will always have no data
    return pNode && !pNode->pData;
}

bool hc_SLL_nodeAdd(HC_SinglyLinkedList_t **ppSentinel, HC_SinglyLinkedList_t *pNode)
{
    if (!ppSentinel || !*ppSentinel || !hc_SLL_nodeIsSentinel(*ppSentinel) || !pNode || hc_SLL_nodeIsSentinel(pNode))
        return false;

    HC_SinglyLinkedList_t *pCurrent = *ppSentinel;
    while (pCurrent && pCurrent->pNext != NULL)
        pCurrent = pCurrent->pNext;

    pCurrent->pNext = pNode;

    return true;
}

bool hc_SLL_dataAdd(HC_SinglyLinkedList_t **ppSentinel, void *pData)
{
    if (!ppSentinel || !*ppSentinel || !pData)
        return false;

    HC_SinglyLinkedList_t *pNode = hc_SLL_nodeNew(pData);
    if (!pNode)
        return false;

    return hc_SLL_nodeAdd(ppSentinel, pNode);
}

static inline bool hc_SLL_nodeDelink(HC_SinglyLinkedList_t **ppNode)
{
    if (!ppNode || !*ppNode || hc_SLL_nodeIsSentinel(*ppNode))
        return false;

    HC_SinglyLinkedList_t *pRemove = *ppNode;
    *ppNode = pRemove->pNext;
    pRemove->pNext = NULL;

    return true;
}

bool hc_SLL_nodeRemove(HC_SinglyLinkedList_t **ppSentinel, HC_SinglyLinkedList_t *pNode)
{
    if (!ppSentinel || !*ppSentinel || !hc_SLL_nodeIsSentinel(*ppSentinel) || !pNode || hc_SLL_nodeIsSentinel(pNode))
        return false;

    HC_SinglyLinkedList_t **ppCurrent = &(*ppSentinel)->pNext;
    while (*ppCurrent && *ppCurrent != pNode)
        ppCurrent = &(*ppCurrent)->pNext;

    if (!*ppCurrent)
        return false;

    return hc_SLL_nodeDelink(ppCurrent);
}

bool hc_SLL_dataRemove(HC_SinglyLinkedList_t **ppSentinel, void *pData, HC_LeftRightCompare_Func data_equality_func)
{
    if (!ppSentinel || !*ppSentinel || !hc_SLL_nodeIsSentinel(*ppSentinel) || !pData)
        return false;

    HC_SinglyLinkedList_t **ppCurrent = &(*ppSentinel)->pNext;

    while (*ppCurrent && (*ppCurrent)->pData != NULL)
    {
        void *pCurrentData = (*ppCurrent)->pData;

        if ((data_equality_func && data_equality_func(pCurrentData, pData)) || pCurrentData == pData)
            break;

        ppCurrent = &(*ppCurrent)->pNext;
    }

    if (!*ppCurrent)
        return false;

    return hc_SLL_nodeDelink(ppCurrent);
}

bool hc_SLL_destroy(HC_SinglyLinkedList_t **ppSentinel, HC_DataDestructor data_destructor_func)
{
    if (!ppSentinel || !*ppSentinel)
        return false;

    if (!hc_SLL_nodeIsSentinel(*ppSentinel))
        return false;

    HC_SinglyLinkedList_t *pNode = *ppSentinel;
    while (pNode)
    {
        HC_SinglyLinkedList_t *pNext = pNode->pNext;

        if (data_destructor_func && pNode->pData)
            data_destructor_func(pNode->pData);

        free(pNode);
        pNode = pNext;
    }

    *ppSentinel = NULL;

    return true;
}

#include "../tests/ut.h"
int hc_SLLINTERNALUT(void)
{
    HC_SinglyLinkedList_t *pBad = NULL;
    int fails = 0;
    int dummyData = 5;

    HC_SinglyLinkedList_t *pSentinel = hc_SLL_create();
    fails += ut_assert(hc_SLL_nodeIsSentinel(NULL) == false, "SLL nodeIsSentinel (NULL sentinel)");
    fails += ut_assert(hc_SLL_nodeIsSentinel(pSentinel) == true, "SLL nodeIsSentinel (good sentinel)");
    pSentinel->pData = &dummyData;

    fails += ut_assert(hc_SLL_nodeIsSentinel(pSentinel) == false, "SLL nodeIsSentinel (sentinel w/ dummy data)");
    hc_SLL_destroy(&pSentinel, NULL);

    HC_SinglyLinkedList_t *pNode = hc_SLL_nodeNew(&dummyData);
    pSentinel = hc_SLL_create();
    hc_SLL_nodeAdd(&pSentinel, pNode);

    fails += ut_assert(hc_SLL_nodeDelink(&pSentinel) == false, "SLL nodeDelink (sentinel)");
    fails += ut_assert(hc_SLL_nodeDelink(NULL) == false, "SLL nodeDelink (NULL)");
    fails += ut_assert(hc_SLL_nodeDelink(&pBad) == false, "SLL nodeDelink (&NULL)");

    HC_SinglyLinkedList_t **ppLink = &pSentinel->pNext;
    fails += ut_assert(hc_SLL_nodeDelink(ppLink) == true, "SLL nodeDelink (good node)");
    fails += ut_assert(pSentinel->pNext == NULL, "SLL nodeDelink (verify updated)");
    fails += ut_assert(pNode->pNext == NULL, "SLL nodeDelink (verify cleared pNext)");

    return fails;
}