#pragma once
#include "hc_collections.h"

/// @brief A singly linked list, which contains data and tracks the address of the next element or NULL if the node is at the tail.
/// pData will be NULL only when being used as the list's sentinel node.
typedef struct HC_SinglyLinkedList_t
{
    void *pData;
    struct HC_SinglyLinkedList_t *pNext;
} HC_SinglyLinkedList_t;

/// @brief Creates a new singly linked list sentinel node, which is the root used for tracking the linked list itself.
/// @return New HC_SinglyLinkedList_t sentinel node (root) [HEAP] or NULL if alloc fails.
HC_SinglyLinkedList_t *hc_SLL_create(void);

/// @brief Creates a new node for addition into a singly linked list with pData.
/// @param pData The data actually stored within the newly created node.
/// @return New HC_SinglyLinkedList_t node [HEAP] or NULL if alloc fails or pData is NULL.
HC_SinglyLinkedList_t *hc_SLL_nodeNew(void *pData);

/// @brief Determines if the passed node is considered a sentinel node, which has dummy data is used to track the instance of
/// the linked list itself.
/// @param pNode The node that will be checked for the sentinel pattern.
/// @return If the node is a sentinel or not.
bool hc_SLL_nodeIsSentinel(HC_SinglyLinkedList_t *pNode);

/// @brief Adds the passed pNode to the provided linked list ppSentinel.
/// @param ppSentinel The root node used to track the linked list itself.
/// @param pNode The node to add to the linked list.
/// @return Result of attempting to add the node. True only when a valid node is added to a valid linked list.
bool hc_SLL_nodeAdd(HC_SinglyLinkedList_t **ppSentinel, HC_SinglyLinkedList_t *pNode);

/// @brief Creates a new node with the passed data and adds it to the provided linked list ppSentinel.
/// @param ppSentinel The root node used to track the linked list itself.
/// @param pData The data that will be tracked inside the newly created node that will be added to the linked list.
/// @return Result of attempting to add the data inside a new node. True only when a valid node is added to a valid linked list.
bool hc_SLL_dataAdd(HC_SinglyLinkedList_t **ppSentinel, void *pData);

/// @brief Inserts the pAdd node after the passed pNode in the linked list.
/// @param pNode Node that already exists in the linked list. NOT elligible to be a sentinel node. Use hc_SLL_nodeAdd for that.
/// @param pAdd Node to add into the linked list after pNode.
/// @return Result of attempting to insert the node into the linked list. True only when a valid node is inserted after a valid node.
bool hc_SLL_nodeInsertAfter(HC_SinglyLinkedList_t *pNode, HC_SinglyLinkedList_t *pAdd);

/// @brief Creates a new node with the passed data and adds it after the passed pNode in the linked list.
/// @param pNode Node that already exists in the linked list. NOT elligible to be a sentinel node. Use hc_SLL_dataAdd for that.
/// @param pData The data that will be tracked inside the newly created node that will be added to the linked list.
/// @return Result of attempting to add the data inside a new node. True only when a valid node is added to a valid linked list.
bool hc_SLL_dataInsertAfter(HC_SinglyLinkedList_t *pNode, void *pData);

/// @brief Walks the provided linked list until pData is found. If a data_equality_func is passed, that is used to determine if
/// there is a found match when comparing pDatas. Otherwise, the pointers themselves are compared. The data is not destroyed/owned
/// by this operation.
/// @param ppSentinel The root node used to track the linked list itself.
/// @param pData The data to be removed, if found, from the linked list.
/// @param data_equality_func The function used to determine if pData matches. Ptr comparison if NULL.
/// @return Result of attempting to remove the data from the linked list. True only when a node with matching data is found and
/// that node is successfuly removed from the list.
bool hc_SLL_dataRemove(HC_SinglyLinkedList_t **ppSentinel, void *pData, HC_LeftRightCompare_Func data_equality_func);

/// @brief Walks the provided linked list until a matching pNode address is found. De-links it but does NOT destroy it if so.
/// @param ppSentinel The root node used to track the linked list itself.
/// @param pNode The node to be removed, if found, from the linked list.
/// @return Result of attempting to remove the node from the linked list. True only when a node is found and successfully
/// removed.
bool hc_SLL_nodeRemove(HC_SinglyLinkedList_t **ppSentinel, HC_SinglyLinkedList_t *pNode);

/// @brief Removes the node from the linked list at its current location. The rest of the ordering is perserved.
/// @param ppNode Node to remove.
/// @return Result of attempting to remove the node from the linked list. True only when a node is successfully removed.
bool hc_SLL_nodeDetatch(HC_SinglyLinkedList_t **ppNode);

/// @brief Calls the data_destructor_func on the node's data and frees the node's memory allocation.
/// @param pNode Node to be destroyed.
/// @param data_destructor_func The function used to destroy the data of each pNode. This can be NULL if the data isn't owned
/// by the linked list.
/// @return Result of attempting to destroy the node and its data.
bool hc_SLL_nodeDestroy(HC_SinglyLinkedList_t *pNode, HC_DataDestructor_Func data_destructor_func);

/// @brief Walks the provided linked list and calls the data_destructor_func on each node's data. Frees the linked list
/// once complete.
/// @param ppSentinel The root node used to track the linked list itself.
/// @param data_destructor_func The function used to destroy the data of each pNode. This can be NULL if the data isn't owned
/// by the linked list.
/// @return Result of destroying the linked list. Only true if a valid linked list was provided and successfully destroyed.
bool hc_SLL_destroy(HC_SinglyLinkedList_t **ppSentinel, HC_DataDestructor_Func data_destructor_func);