//
// Created by alexgershberg on 02/02/23.
//

//https://leetcode.com/problems/add-two-numbers/description/

#include <cstddef>
#include <iostream>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr)
    {
    }
    explicit ListNode(int x) : val(x), next(nullptr)
    {
    }
    ListNode(int x, ListNode* next) : val(x), next(next)
    {
    }
};

struct LinkedList
{
    ListNode* head;
    ListNode* tail;
    std::size_t size;
    LinkedList(): head(nullptr), tail(nullptr), size(0){};


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
};
class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        LinkedList output;

        int carry = 0;
        while(l1 != nullptr && l2 != nullptr)
        {
            auto first= l1->val;
            auto second = l2->val;
            auto result = first + second + carry;
            carry = 0;

            if (result > 9)
            {
                result = result % 10;
                carry++;
            }
            output.append(new ListNode(result));

            l1 = l1->next;
            l2 = l2->next;
        }

        while(l1 != nullptr)
        {
            auto first= l1->val;
            auto result = first + 0 + carry;
            carry = 0;

            if (result > 9)
            {
                result = result % 10;
                carry++;
            }
            output.append(new ListNode(result));

            l1 = l1->next;

        }

        while(l2 != nullptr)
        {
            auto second = l2->val;
            auto result = 0 + second + carry;
            carry = 0;

            if (result > 9)
            {
                result = result % 10;
                carry++;
            }
            output.append(new ListNode(result));

            l2 = l2->next;
        }

        if (carry != 0)
        {
            output.append(new ListNode(carry));
            carry = 0;
        }

        return output.head;
    }
};

void printRes(ListNode* node)
{
    while(node != nullptr)
    {
        int v = node->val;
        std::cout << v << " ";
        node = node->next;
    }

    std::cout << std::endl;
}

int main()
{
    /*
    ListNode c1(3);
    ListNode b1(4, &c1);
    ListNode a1(2, &b1);

    ListNode c2(4);
    ListNode b2(6, &c2);
    ListNode a2(5, &b2);
    */

    /*
    ListNode g3(9);
    ListNode f3(9, &g3);
    ListNode e3(9, &f3);
    ListNode d3(9, &e3);
    ListNode c3(9, &d3);
    ListNode b3(9, &c3);
    ListNode a3(9, &b3);

    ListNode d4(9);
    ListNode c4(9, &d4);
    ListNode b4(9, &c4);
    ListNode a4(9, &b4);

    */

    ListNode c5(9);
    ListNode b5(4,&c5);
    ListNode a5(2, &b5);

    ListNode d6(9);
    ListNode c6(4, &d6);
    ListNode b6(6, &c6);
    ListNode a6(5, &b6);

    Solution sol;
    auto* res = sol.addTwoNumbers(&a5, &a6);
    printRes(res);
}