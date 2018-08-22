bool hasCircle(ListNode *pHead)
{
	ListNode *pFast = pHead;
	ListNode *pSlow = pHead;
	while (pFast != NULL && pFast->next != NULL)
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
		if (pFast == pSlow)
			return true;
	}
	return false;
}
