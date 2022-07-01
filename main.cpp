#include <iostream>
#include <queue>
#define DATANUM 1000  // 实测这里的数据要小于300000，不然跑不出来
#define Base1 10
#define Base2 256
#define Base3 65536
using namespace std;


struct numNode {
	int data;
	struct numNode* next;
};

// 初始化一个单链表，返回头节点，头节点不存储数据
struct numNode* InitList() 
{  
	struct numNode* Head = new struct numNode;
	Head->next = NULL;
	return Head;
}

// 根据传入的最大值和最小值返回他们两之间的随机数 [down, up)
int returnRandInRange(int down, int up)
{
	if (down > up) {
		printf("returnRandInRange() 函数错误：设置获取数字的区间不合理");
	}
	int x = rand() % (up - down) + down;  // 生成随机数
	return x;
}

// 传入未初始化的单链表，为其中增加指定数量数据，头节点中存储的数据是当前节点数
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

// 打印单链表
void printLinkList(struct numNode* Head)
{
	int len = Head->data;
	struct numNode* nodePos = Head;
	for (int i = 0; i < len; i++) {
		nodePos = nodePos->next;
		cout << i + 1 << "\t" << nodePos->data << endl;
	}
}

// 将单链表中的元素复制到数组中
void copyListToArr(struct numNode* Head, int* arr)
{
	int len = Head->data;
	struct numNode* nodePos = Head;
	for (int i = 0; i < len; i++) {
		nodePos = nodePos->next;
		arr[i] = nodePos->data;
	}
}

// 和快速排序一起使用的函数
// 函数作用是：根据传入待划分的数组，对数组内元素进行划分，返回中间点的位置
// 详细的可以看王道数据结构
int Partition(int arr[], int low, int high) {
	int key = arr[low];   // 第一个元素作为枢轴
	while (low < high) {  // 用low、high搜索枢轴的最终位置
		while (low < high && arr[high] >= key)
			high--;
		if (low < high)
			arr[low++] = arr[high];  // 比枢轴小的元素移动到左端
		while (low < high && arr[low] <= key)
			low++;
		if (low < high)
			arr[high--] = arr[low];  // 比枢轴大的元素移动到右端
	}
	arr[low] = key;  // 枢轴元素存放到最终位置
	return low;  // 返回存放枢轴的最终位置
}

// 快速排序，使用递归
void QuickSort(int arr[], int low, int high) {
	if (low < high) {                              // 递归跳出的条件
		int pivotpos = Partition(arr, low, high);  // 划分
		QuickSort(arr, low, pivotpos - 1);         // 划分左子表
		QuickSort(arr, pivotpos + 1, high);        // 划分右子表
	}
}

// 非递归归并排序
void MergeSort(int num[])
{
	int i, j;
	int* sort;
	int L_start = 0, L_end = 0;//初始化左区间的起点、终点下标
	int R_start = 0, R_end = 0;//初始化右区间的起点、终点下标

	sort = (int*)malloc(DATANUM * sizeof(int));//为临时数组分配空间

	for (i = 1; i < DATANUM; i *= 2)//区间长度两倍递增
	{
		for (L_start = 0; L_start < DATANUM - i; L_start = R_end)
		{
			//确定左右区间两边的起点、终点下标		
			L_end = L_start + i;
			R_start = L_start + i;
			R_end = R_start + i;

			if (R_end > DATANUM)//右区间终点不超过数组长度
			{
				R_end = DATANUM;
			}
			j = 0;	//临时数组初始下标

			while (L_start < L_end && R_start < R_end)
			{
				//比较左右起点数据的大小，并将较小的数据依次存入临时数组
				if (num[L_start] < num[R_start])
					sort[j++] = num[L_start++];
				else
					sort[j++] = num[R_start++];
				//同时起点下标递增
			}

			while (L_start < L_end)//将比较完剩余的数据存入临时数组
			{
				sort[j++] = num[L_start++];
			}
			while (j > 0)			//将已排好的临时数组数据录入原数组中
			{
				num[--R_start] = sort[--j];
			}

		}

	}
	free(sort);
}

/*
// 基数排序的辅助函数，求数据的最大位数
int maxbit(int data[])
{
	int maxData = data[0];      // 最大数
	// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
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

// 基数排序，基数为 10
void radixsort(struct numNode* Head, int MaxBit)
{
	queue<int>** arr[Base1];  // 创建一个数组，用来存储其他队列

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
	// 初始化需要的数据
	struct numNode* Head = InitList();
	InitData(Head, DATANUM, 1, DATANUM);

	// 快速排序需要的数据初始化
	int* arr = new int[DATANUM];
	copyListToArr(Head, arr);

	// 计算快速排序时间
	clock_t start_time = clock();
	QuickSort(arr, 0, DATANUM - 1);
	clock_t end_time = clock();
	cout << "QuickSort run time is: " << (double)(end_time - start_time) << "ms" << endl;

	// 非递归排序需要的数据初始化
	copyListToArr(Head, arr);

	// 计算非递归归并排序
	start_time = clock();
	MergeSort(arr);
	end_time = clock();
	cout << "MergeSort run time is: " << (double)(end_time - start_time) << "ms" << endl;

	// 基数排序需要的数据初始化
	/*copyListToArr(Head, arr);
	int Max = maxbit(arr);    // 获取到当前最大的位数

	// 计算基数排序
	start_time = clock();
	radixsort(Head, Max);
	end_time = clock();
	cout << "Radixsort run time is: " << (double)(end_time - start_time) << "ms" << endl;
	*/

	return 0;
}