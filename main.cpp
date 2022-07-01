#include <iostream>
#include <queue>
#define DATANUM 1000  // ʵ�����������ҪС��300000����Ȼ�ܲ�����
#define Base1 10
#define Base2 256
#define Base3 65536
using namespace std;


struct numNode {
	int data;
	struct numNode* next;
};

// ��ʼ��һ������������ͷ�ڵ㣬ͷ�ڵ㲻�洢����
struct numNode* InitList() 
{  
	struct numNode* Head = new struct numNode;
	Head->next = NULL;
	return Head;
}

// ���ݴ�������ֵ����Сֵ����������֮�������� [down, up)
int returnRandInRange(int down, int up)
{
	if (down > up) {
		printf("returnRandInRange() �����������û�ȡ���ֵ����䲻����");
	}
	int x = rand() % (up - down) + down;  // ���������
	return x;
}

// ����δ��ʼ���ĵ�����Ϊ��������ָ���������ݣ�ͷ�ڵ��д洢�������ǵ�ǰ�ڵ���
void InitData(struct numNode* Head, int len, int down, int up)
{
	Head->data = len;
	struct numNode* newNode;

	for (int i = 0; i < len; i++) {
		newNode = new struct numNode;
		newNode->data = returnRandInRange(down, up);
		newNode->next = Head->next;
		Head->next = newNode;
	}
}

// ��ӡ������
void printLinkList(struct numNode* Head)
{
	int len = Head->data;
	struct numNode* nodePos = Head;
	for (int i = 0; i < len; i++) {
		nodePos = nodePos->next;
		cout << i + 1 << "\t" << nodePos->data << endl;
	}
}

// ���������е�Ԫ�ظ��Ƶ�������
void copyListToArr(struct numNode* Head, int* arr)
{
	int len = Head->data;
	struct numNode* nodePos = Head;
	for (int i = 0; i < len; i++) {
		nodePos = nodePos->next;
		arr[i] = nodePos->data;
	}
}

// �Ϳ�������һ��ʹ�õĺ���
// ���������ǣ����ݴ�������ֵ����飬��������Ԫ�ؽ��л��֣������м���λ��
// ��ϸ�Ŀ��Կ��������ݽṹ
int Partition(int arr[], int low, int high) {
	int key = arr[low];   // ��һ��Ԫ����Ϊ����
	while (low < high) {  // ��low��high�������������λ��
		while (low < high && arr[high] >= key)
			high--;
		if (low < high)
			arr[low++] = arr[high];  // ������С��Ԫ���ƶ������
		while (low < high && arr[low] <= key)
			low++;
		if (low < high)
			arr[high--] = arr[low];  // ��������Ԫ���ƶ����Ҷ�
	}
	arr[low] = key;  // ����Ԫ�ش�ŵ�����λ��
	return low;  // ���ش�����������λ��
}

// ��������ʹ�õݹ�
void QuickSort(int arr[], int low, int high) {
	if (low < high) {                              // �ݹ�����������
		int pivotpos = Partition(arr, low, high);  // ����
		QuickSort(arr, low, pivotpos - 1);         // �������ӱ�
		QuickSort(arr, pivotpos + 1, high);        // �������ӱ�
	}
}

// �ǵݹ�鲢����
void MergeSort(int num[])
{
	int i, j;
	int* sort;
	int L_start = 0, L_end = 0;//��ʼ�����������㡢�յ��±�
	int R_start = 0, R_end = 0;//��ʼ�����������㡢�յ��±�

	sort = (int*)malloc(DATANUM * sizeof(int));//Ϊ��ʱ�������ռ�

	for (i = 1; i < DATANUM; i *= 2)//���䳤����������
	{
		for (L_start = 0; L_start < DATANUM - i; L_start = R_end)
		{
			//ȷ�������������ߵ���㡢�յ��±�		
			L_end = L_start + i;
			R_start = L_start + i;
			R_end = R_start + i;

			if (R_end > DATANUM)//�������յ㲻�������鳤��
			{
				R_end = DATANUM;
			}
			j = 0;	//��ʱ�����ʼ�±�

			while (L_start < L_end && R_start < R_end)
			{
				//�Ƚ�����������ݵĴ�С��������С���������δ�����ʱ����
				if (num[L_start] < num[R_start])
					sort[j++] = num[L_start++];
				else
					sort[j++] = num[R_start++];
				//ͬʱ����±����
			}

			while (L_start < L_end)//���Ƚ���ʣ������ݴ�����ʱ����
			{
				sort[j++] = num[L_start++];
			}
			while (j > 0)			//�����źõ���ʱ��������¼��ԭ������
			{
				num[--R_start] = sort[--j];
			}

		}

	}
	free(sort);
}

/*
// ��������ĸ��������������ݵ����λ��
int maxbit(int data[])
{
	int maxData = data[0];      // �����
	// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
	for (int i = 1; i < DATANUM; ++i)
	{
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;
}

// �������򣬻���Ϊ 10
void radixsort(struct numNode* Head, int MaxBit)
{
	queue<int>** arr[Base1];  // ����һ�����飬�����洢��������

	queue<int>* q;
	for (int i = 0; i < Base1; i++) {
		q = new queue<int>;
		arr[i] = &q;
	}

	struct numNode* NodePos;
	int Bit;
	int num;
	for (int j = 0; j < MaxBit; j++) {
		Bit = pow(Base1, j + 1);
		NodePos = Head;
		for (int i = 0; i < Head->data; i++) {
			NodePos = NodePos->next;
			arr[NodePos->data % Bit]->push(NodePos->data);
		}
	}
}
*/

int main(void)
{
	// ��ʼ����Ҫ������
	struct numNode* Head = InitList();
	InitData(Head, DATANUM, 1, DATANUM);

	// ����������Ҫ�����ݳ�ʼ��
	int* arr = new int[DATANUM];
	copyListToArr(Head, arr);

	// �����������ʱ��
	clock_t start_time = clock();
	QuickSort(arr, 0, DATANUM - 1);
	clock_t end_time = clock();
	cout << "QuickSort run time is: " << (double)(end_time - start_time) << "ms" << endl;

	// �ǵݹ�������Ҫ�����ݳ�ʼ��
	copyListToArr(Head, arr);

	// ����ǵݹ�鲢����
	start_time = clock();
	MergeSort(arr);
	end_time = clock();
	cout << "MergeSort run time is: " << (double)(end_time - start_time) << "ms" << endl;

	// ����������Ҫ�����ݳ�ʼ��
	/*copyListToArr(Head, arr);
	int Max = maxbit(arr);    // ��ȡ����ǰ����λ��

	// �����������
	start_time = clock();
	radixsort(Head, Max);
	end_time = clock();
	cout << "Radixsort run time is: " << (double)(end_time - start_time) << "ms" << endl;
	*/

	return 0;
}