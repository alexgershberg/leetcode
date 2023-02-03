//
// Created by alexgershberg on 03/02/23.
//

//https://leetcode.com/problems/merge-k-sorted-lists/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct LinkedList
{
    ListNode* head;
    ListNode* tail;
    std::size_t size;
    LinkedList() : head(nullptr), tail(nullptr), size(0) {};

    void append(ListNode* node)
    {
        if (size == 0)
        {
            head = node;
            tail = node;
            size++;
            return;
        }

        tail->next = node;
        tail = node;
        size++;
    }

    void append(int val)
    {
        this->append(new ListNode(val));
    }
};

class Solution
{
public:
    static ListNode* mergeTwo(ListNode* first, ListNode* second)
    {
        LinkedList output;

        while (first != nullptr && second != nullptr)
        {
            auto val1 = first->val;
            auto val2 = second->val;

            if (val1 <= val2)
            {
                output.append(new ListNode(val1));
                first = first->next;
            }
            else
            {
                output.append(new ListNode(val2));
                second = second->next;
            }
        }

        while (first != nullptr)
        {
            output.append(new ListNode(first->val));
            first = first->next;
        }

        while (second != nullptr)
        {
            output.append(new ListNode(second->val));
            second = second->next;
        }

        return output.head;

    }

    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        if (lists.empty())
            return nullptr;

        if (lists.size() == 1)
            return lists.at(0);

        if (lists.size() == 2)
        {
            auto first = lists.at(0);
            auto second = lists.at(1);
            return mergeTwo(first, second);
        }

        auto size = static_cast<long double>(lists.size());
        auto midpoint  = static_cast<long>(floorl(size / 2L));

        auto left = std::vector<ListNode*>(lists.begin(), lists.begin() + midpoint);
        auto left_result = mergeKLists(left);

        auto right = std::vector<ListNode*>(lists.begin() + midpoint, lists.end());
        auto right_result = mergeKLists(right);

        return mergeTwo(left_result, right_result);
    }
};

void printRes(ListNode* node)
{
    if (node == nullptr)
    {
        std::cout << "empty" << std::endl;
        return;
    }

    while (node != nullptr)
    {
        auto val = node->val;
        std::cout << val << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

int main()
{
    LinkedList list1;
    list1.append(1);
    list1.append(4);
    list1.append(5);

    LinkedList list2;
    list2.append(1);
    list2.append(3);
    list2.append(4);

    LinkedList list3;
    list3.append(2);
    list3.append(6);

    std::vector<ListNode*> lists;
    lists.push_back(list1.head);
    lists.push_back(list2.head);
    lists.push_back(list3.head);

    Solution sol;

    auto res = sol.mergeKLists(lists);
    printRes(res);
}
