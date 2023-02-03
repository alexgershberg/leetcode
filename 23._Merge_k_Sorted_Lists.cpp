#include <iostream>
#include <vector>

//https://leetcode.com/problems/merge-k-sorted-lists/

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


class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        if (lists.size() == 0)
        {
            return nullptr;
        }

        if (lists.size() == 1)
        {
            return lists.at(0);
        }

        if (lists.size() == 2)
        {
            auto list1 = lists.at(0);
            auto list2 = lists.at(1);
            return mergeTwo(list1, list2);
        }

        auto list1 = lists.back();
        lists.pop_back();

        auto list2 = lists.back();
        lists.pop_back();

        auto result = mergeTwo(list1, list2);

        auto remaining = mergeKLists(lists);

        auto final = mergeTwo(result, remaining);

        return final;


    }

    ListNode* mergeTwo(ListNode* list1, ListNode* list2)
    {
        LinkedList output;

        while (list1 != nullptr && list2 != nullptr)
        {
            auto val1 = list1->val;
            auto val2 = list2->val;

            if (val1 <= val2)
            {
                output.append(new ListNode(val1));
                list1 = list1->next;
            }
            else
            {
                output.append(new ListNode(val2));
                list2 = list2->next;
            }
        }

        while (list1 != nullptr)
        {
            output.append(new ListNode(list1->val));
            list1 = list1->next;
        }

        while (list2 != nullptr)
        {
            output.append(new ListNode(list2->val));
            list2 = list2->next;
        }

        return output.head;
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