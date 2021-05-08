#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <stack>
#include <memory>
#include <string>
#include <functional>
#include <ratio>
#include <future>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
using namespace std;

int arr[8] = { 4, 3, 5, 4, 3, 3, 6, 7 };
int arrStack[7] = { 3, 4, 1, 5, 6, 2, 7 };
int arrStackMulti[9] = { 3, 1, 3, 4, 3, 5, 3, 3, 2 };
int arrHeight[] = { 2, 4, 5, 4, 3, 6 };
deque<int> g_deque;
stack<int> g_stack;
stack<vector<int>> g_stackMulti;

void findMax(int nw)
{
	int nSize = 8 - nw + 1;
	int index = 0;
	int *out = new int[nSize];
	for (int i = 0; i < 8; ++i)
	{
		while (!g_deque.empty() && arr[g_deque.front()] <= arr[i])
		{
			g_deque.pop_back();
		}
		g_deque.push_back(i);
		if (g_deque.front() == i - nw)
		{
			g_deque.pop_front();
		}
		if (i >= nw - 1)
		{
			out[index++] = arr[g_deque.front()];
		}
	}
	delete out;
}

//单调栈
void stackMin()
{
	int nIndex = 0;
	int nleft = -1;
	int nright = -1;
	for (int i = 0; i < 7; ++i)
	{
		int nPos = -1;
		while (!g_stack.empty() && arrStack[g_stack.top()] > arrStack[i])
		{
			nPos = g_stack.top();
			g_stack.pop();
			nleft = g_stack.empty() ? -1 : g_stack.top();
			nright = i;
			cout << nPos << " : " << nleft << "," << nright << endl;
		}
		g_stack.push(i);
	}
	nright = -1;
	while (!g_stack.empty())
	{
		int nPos = g_stack.top();
		g_stack.pop();
		nleft = g_stack.empty() ? -1 : g_stack.top();
		cout << nPos << " : " << nleft << "," << nright << endl;
	}
}

void stackMulti()
{
	for (int i = 0; i < 9; ++i)
	{
		while (!g_stackMulti.empty() && arrStackMulti[g_stackMulti.top()[0]] > arrStackMulti[i])
		{
			vector<int> vec = g_stackMulti.top();
			g_stackMulti.pop();
			int left = g_stackMulti.empty() ? -1 : g_stackMulti.top().at(g_stackMulti.top().size() - 1);
			for (auto & pos : vec)
			{
				cout << pos << " : " << left << "," << i << endl;
			}
		}
		if (!g_stackMulti.empty() && arrStackMulti[g_stackMulti.top()[0]] == arrStackMulti[i])
		{
			g_stackMulti.top().push_back(i);
		}
		else
		{
			vector<int> vec;
			vec.push_back(i);
			g_stackMulti.push(vec);
		}
	}
	while (!g_stackMulti.empty())
	{
		auto vec = g_stackMulti.top();
		g_stackMulti.pop();
		int left = g_stackMulti.empty() ? -1 : g_stackMulti.top().at(g_stackMulti.top().size() - 1);
		for (auto & pos : vec)
		{
			cout << pos << " : " << left << "," << -1 << endl;
		}
	}
}

int partition(vector<int> & nums, int low, int hight)
{
	int pivot = nums[low];
	while (low < hight)
	{
		while (low < hight && nums[hight] >= pivot)
		{
			--hight;
		}
		if (low < hight)
		{
			nums[low] = nums[hight];
		}
		while (low < hight && nums[low] <= pivot)
		{
			++low;
		}
		if (low < hight)
		{
			nums[hight] = nums[low];
		}
	}
	nums[low] = pivot;
	return low;
}

void quickSort(vector<int> & nums, int low, int hight)
{
	if (low < hight)
	{
		int index = partition(nums, low, hight);
		quickSort(nums, low, index - 1);
		quickSort(nums, index + 1, hight);
	}
}

int quick_sort(vector<int> & s, int l, int r, int n)
{
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		int th = r - i + 1;
		if (th == n)
		{
			return s[i];
		}
		else if (th > n)
		{
			return quick_sort(s, i+1, r, n); // 递归调用 
		}
		else
		{
			return quick_sort(s, l, i - 1, n - th);
		}
	}
	return 0;
}

void bubbleSort(vector<int> & num)
{
	int nSize = num.size() - 1;
	bool bFlag = true;
	while (nSize >= 0 && bFlag)
	{
		bFlag = false;
		for (int j = 0; j < nSize; ++j)
		{
			if (num[j] > num[j + 1])
			{
				bFlag = true;
				int t = num[j];
				num[j] = num[j + 1];
				num[j + 1] = t;
			}
		}
		--nSize;
	}
}

void selectSort(vector<int> & num)
{
	int nSize = num.size();
	for (int i = 0; i < nSize - 1; ++i)
	{
		int k = i;
		for (int j = i + 1; j < nSize; ++j)
		{
			if (num[k] > num[j])
			{
				k = j;
			}
		}
		if (k != i)
		{
			int t = num[k];
			num[k] = num[i];
			num[i] = t;
		}
	}
}

void areaStack()
{
	int nMaxArea = 0;
	for (int i = 0; i < 6; ++i)
	{
		while (!g_stack.empty() && arrHeight[i] <= arrHeight[g_stack.top()])
		{
			int nPosJ = g_stack.top();
			g_stack.pop();
			int nPosK = g_stack.empty() ? -1 : g_stack.top();
			int nCurArea = (i - nPosK - 1) * arrHeight[nPosJ];
			nMaxArea = nMaxArea > nCurArea ? nMaxArea : nCurArea;
		}
		g_stack.push(i);
	}
	while (!g_stack.empty())
	{
		int j = g_stack.top();
		g_stack.pop();
		int k = g_stack.empty() ? -1 : g_stack.top();
		int nCurArea = (6 - k - 1) * arrHeight[j];
		nMaxArea = nMaxArea > nCurArea ? nMaxArea : nCurArea;
	}
	cout << nMaxArea << endl;
}

int add(int num1, int num2)
{
	int sum = 0;
	int carry = 0;
	do
	{
		sum = num1 ^ num2;
		carry = (num1 & num2) << 1;
		num1 = sum;
		num2 = carry;

	} while (carry != 0);
	return sum;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	int nS = m + n - 1;
	int i = m - 1;
	int j = n - 1;
	while (i >= 0 && j >= 0)
	{
		if (nums1[i] <= nums2[j])
		{
			nums1[nS] = nums2[j];
			--j;
			--nS;
		}
		else
		{
			nums1[nS] = nums1[i];
			--i;
			--nS;
		}
	}
	for (int i = 0; i <= j; ++i)
	{
		nums1[i] = nums2[i];
	}
}

void heapAdjust(vector<int> & nums, int nLen, int parent)
{
	int nTmp = nums[parent];
	int child = 2 * parent + 1;
	while (child < nLen)
	{
		if (child + 1 < nLen && nums[child + 1] > nums[child])
		{
			child++;
		}
		if (nTmp > nums[child])
		{
			break;
		}
		nums[parent] = nums[child];
		parent = child;
		child = 2 * parent + 1;
	}
	nums[parent] = nTmp;
}

void heapSort(vector<int> & nums)
{
	int nLen = nums.size();
	for (int i = nLen / 2; i >= 0; --i)
	{
		heapAdjust(nums, nLen, i);
	}
	for (int i = nLen - 1; i > 0; --i)
	{
		int tmp = nums[0];
		nums[0] = nums[i];
		nums[i] = tmp;
		heapAdjust(nums, i, 0);
	}
}

typedef struct Tree
{
	int nData;
	struct Tree *lchild;
	struct Tree *rchild;
}TreeNode;

typedef struct ListNode
{
	int nData;
	struct ListNode *next;
}List;

typedef struct List2Node
{
	int nData;
	struct List2Node *pre;
	struct List2Node *next;
}List2;

void LDR(TreeNode * node)
{
	if (node)
	{
		TreeNode * pTmp = node->lchild;
		node->lchild = node->rchild;
		node->rchild = pTmp;
		LDR(node->lchild);
		cout << node->nData << endl;
		LDR(node->rchild);
	}
}

bool isSymmetric(TreeNode * left, TreeNode * right)
{
	if (!left && !right)
	{
		return true;
	}
	if ((!left && right) || (left && !right))
	{
		return false;
	}
	if (left->nData != right->nData)
	{
		return false;
	}
	return isSymmetric(left->lchild, right->rchild) && isSymmetric(left->rchild, right->lchild);
}

bool isSymmetric(TreeNode * root)
{
	if (!root)
	{
		return true;
	}
	return isSymmetric(root->lchild, root->rchild);
}

bool LDRStack(TreeNode *node)
{
	if (!node)
	{
		return true;
	}
	stack<TreeNode*> st1, st2;
	st1.push(node->lchild);
	st2.push(node->rchild);
	while (!st1.empty() && !st2.empty())
	{
		TreeNode * pNode1 = st1.top();
		TreeNode * pNode2 = st2.top();
		st1.pop();
		st2.pop();
		if ((pNode1 && !pNode2) || (!pNode1 && pNode2))
		{
			return false;
		}
		if (pNode1)
		{
			if (pNode1->nData != pNode2->nData)
			{
				return false;
			}
			st1.push(pNode1->lchild);
			st1.push(pNode1->rchild);
			st2.push(pNode2->rchild);
			st2.push(pNode2->lchild);
		}
	}
	return true;
}

class MinStack {
public:
	/** initialize your data structure here. */
	stack<int> m_stack;
	int m_nMin;
	MinStack() {
		m_nMin = INT_MAX;
	}

	void push(int val) {
		if (val <= m_nMin)
		{
			m_stack.push(m_nMin);
			m_nMin = val;
		}
		m_stack.push(val);
	}

	void pop() {
		if (m_nMin == m_stack.top())
		{
			m_stack.pop();
			m_nMin = m_stack.top();
			m_stack.pop();
		}
		m_stack.pop();
	}

	int top() {
		return m_stack.top();
	}

	int getMin() {
		return m_nMin;
	}
};

void getdp(vector<int> & arr, vector<int> & dp)
{
	int nLen = arr.size();
	for (int i = 0; i < nLen; ++i)
	{
		dp.push_back(1);
		for (int j = 0; j < i; ++j)
		{
			if (arr[i] > arr[j])
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
}

std::unique_ptr<vector<int>> generateLIS(vector<int> & nums, const vector<int> & dp)
{
	int ndpLen = dp.size();
	int nSubLen = 0;
	int nIndex = 0;
	for (int i = 0; i < ndpLen; ++i)
	{
		if (dp[i] > nSubLen)
		{
			nSubLen = dp[i];
			nIndex = i;
		}
	}
	std::unique_ptr<vector<int>> vec = std::make_unique<vector<int>>(nSubLen);
	(*vec)[--nSubLen] = nums[nIndex];
	for (int i = nIndex; i >= 0; --i)
	{
		if (nums[i] < nums[nIndex] && dp[i] == dp[nIndex] - 1)
		{
			(*vec)[--nSubLen] = nums[i];
			nIndex = i;
		}
	}
	return vec;
}

int generateLISDyn(vector<int> & nums, vector<int> & lis)
{
	int nLen = nums.size();
	lis.resize(nLen);
	int res = 0;
	lis[0] = 1;
	vector<int> ends(nLen);
	ends[0] = nums[0];
	int right = 0;
	int l = 0;
	int r = 0;
	int m = 0;
	for (int i = 0; i < nLen; ++i)
	{
		l = 0;
		r = right;
		while (l <= r)
		{
			m = (l + r) / 2;
			if (nums[i] > ends[m])
			{
				l = m + 1;
			}
			else
			{
				r = m - 1;
			}
		}
		right = max(right, l);
		ends[l] = nums[i];
		lis[i] = l + 1;
	}
	return res;
}

List * delNList(List * head, int k)
{
	List *slow = head;
	List *fast = head;
	List * pre = nullptr;
	int i = 1;
	while (fast)
	{
		if (i > k)
		{
			fast = fast->next;
			pre = slow;
			slow = slow->next;
		}
		else
		{
			fast = fast->next;
		}
		++i;
	}
	if (pre)
	{
		pre->next = pre->next->next;
	}
	else
	{
		head = head->next;
	}
	return head;
}

List* removeListbyValue(List* head, int values)
{
	while (head)
	{
		if (head->nData != values)
		{
			break;
		}
		head = head->next;
	}
	List *pre = head;
	List *cur = head;
	while (cur)
	{
		if (cur->nData == values)
		{
			pre->next = cur->next;
		}
		else
		{
			pre = cur;
		}
		cur = cur->next;
	}
	return head;
}

void readFile()
{
	ifstream redfile;
	redfile.open("C:/Users/WinT/Desktop/CPU/log/LGRecog-14340.log", ios::in);
	ofstream wrtfile;
	wrtfile.open("C:/Users/WinT/Desktop/CPU/log/LGRecog.csv", ios::out);
	while (!redfile.eof())
	{
		char buf[256] = { 0 };
		redfile >> buf;
		size_t len = strlen(buf);
		if (len > 0)
		{
			buf[len - 1] = '\0';
			wrtfile << buf << endl;
		}
	}
	redfile.close();
	wrtfile.close();
}

void llDR(TreeNode *head, deque<TreeNode*> & trDeque)
{
	if (head)
	{
		llDR(head->lchild, trDeque);
		trDeque.push_back(head);
		llDR(head->rchild, trDeque);
	}
}

List2* bst2list(TreeNode *head)
{
	deque<TreeNode*> trDeque;
	llDR(head, trDeque);
	if (trDeque.empty())
	{
		return nullptr;
	}
	List2 *lhead = new List2;
	List2 *p1 = lhead;
	p1->pre = nullptr;
	TreeNode *t = trDeque.front();
	trDeque.pop_front();
	p1->nData = t->nData;
	List2 *pre = p1;
	List2 *cur = nullptr;
	while (!trDeque.empty())
	{
		TreeNode *tmp = trDeque.front();
		trDeque.pop_front();
		cur = new List2;
		cur->nData = tmp->nData;
		pre->next = cur;
		cur->pre = pre;
		pre = cur;
	}
	cur->next = nullptr;
}

int main()
{
	TreeNode n1;
	n1.lchild = nullptr;
	n1.rchild = nullptr;
	n1.nData = 1;
	TreeNode n3;
	n3.lchild = nullptr;
	n3.rchild = nullptr;
	n3.nData = 3;
	TreeNode n2;
	n2.lchild = &n1;
	n2.rchild = &n3;
	n2.nData = 2;
	TreeNode n5;
	n5.lchild = nullptr;
	n5.rchild = nullptr;
	n5.nData = 5;
	TreeNode n4;
	n4.lchild = &n2;
	n4.rchild = &n5;
	n4.nData = 4;

	bst2list(&n4);

	system("pause");
	return 0;
}