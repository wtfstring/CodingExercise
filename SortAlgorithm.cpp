////////////////////////////////////冒泡排序
class BubbleSort {
public:
    int* bubbleSort(int* A, int n) {
        // write code here
        int i,j;
        for(i = n - 1; i >= 0; i--){
            for(j = 0; j < i; j++)
                if(A[j] > A[j + 1])
                    swap(A[j],A[j + 1]);
        }
        return A;
    }
};
////////////////////////////////////选择排序
class SelectionSort {
public:
    int* selectionSort(int* A, int n) {
        // write code here
        int i,j,temp;
        for(i = 0; i < n; i++){
            temp = i;
            for(j = i + 1; j < n; j++)
                if(A[j] < A[temp])
                    temp = j;
            swap(A[i],A[temp]);
        }
        return A;
    }
};
////////////////////////////////////插入排序
class InsertionSort {
public:
    int* insertionSort(int* A, int n) {
        // write code here
        int i,j,temp;
        for(i = 1; i < n; i++){
            temp = A[i];
            for(j = i; j > 0 && temp < A[j - 1]; j--)
                A[j] = A[j - 1];
            A[j] = temp;
        }
        return A;
    }
};
////////////////////////////////////归并排序
class MergeSort {
public:
    int* mergeSort(int* A, int n) {
        // write code here
        if(n <= 0 || A == NULL)
            return A;
        Msort(A,0,n-1);
        return A;
    }
    void Msort(int *A,int left,int right){
        if(left == right)
            return ;
        else{
            int mid = (left + right) / 2;
            Msort(A,left,mid);
            Msort(A,mid + 1,right);
            Merge(A,left,mid,right);
        }
    }
    void Merge(int *A,int left,int mid,int right){
        int leftStart = left,leftEnd = mid,rightStart = mid + 1,rightEnd = right;
        int i = 0;
        int *tempA = new int[right - left + 1];
        while(leftStart <= leftEnd && rightStart <= rightEnd){
            if(A[leftStart] <= A[rightStart])
                tempA[i++] = A[leftStart++];
            else
                tempA[i++] = A[rightStart++];
        }
        while(leftStart <= leftEnd)
            tempA[i++] = A[leftStart++];
        while(rightStart <= rightEnd)
            tempA[i++] = A[rightStart++];
        for(int j = left,i = 0; j <= right; i++) //注意把tempA中元素拷贝到A中，下标从left到right
            A[j++] = tempA[i];
        delete []tempA;
        tempA = NULL; //释放空间后将指针置空，防止产生野指针
      
    }
};
////////////////////////////////////快速排序
class QuickSort {
public:
    int* quickSort(int* A, int n) {
        // write code here
        if(A == NULL || n <= 0)
            return A;
        else
            Q_sort(A,0,n - 1);
        return A;
    }
    void Q_sort(int *A,int left,int right){
        if(left >= right)
            return;
        int mid = (left + right) / 2;
        int i,last = left;
        swap(A[left],A[mid]);
        for(i = left + 1; i <= right; i++){
            if(A[i] < A[left])
                swap(A[i],A[++last]);
        }
        swap(A[left],A[last]);
        Q_sort(A,left,last - 1);
        Q_sort(A,last + 1,right);
    }
};
////////////////////////////////////堆排序
class HeapSort {
public:
    int* heapSort(int* A, int n) {
        // write code here
        int i;
        for(i = n / 2 - 1; i >= 0; i--)
            PercDown(A,i,n);
        for(i = n - 1; i > 0; i--){
            swap(A[0],A[i]);
            PercDown(A,0,i);
        }
        return A;
    }
    void PercDown(int *A,int p,int n){
        int parent,child,temp = A[p];
        for(parent = p; parent * 2 + 1 < n; parent = child){
            child = parent * 2 + 1;
            if(child + 1 != n && A[child] < A[child + 1])
                child++;
            if(A[child] <= temp)  //注意是建立大顶堆
                break;
            else
                A[parent] = A[child];
        }
        A[parent] = temp;
    }
};
//////////////////////////////////// 希尔排序
class ShellSort {
public:
    int* shellSort(int* A, int n) {
        // write code here
        if(A == NULL || n <= 0)
            return A;
        int step,i,j,temp;
        for(step = n / 2; step > 0; step /= 2){
            for(i = step; i < n; i++){
                temp = A[i];
                for(j = i; j >= step && temp < A[j - step]; j -= step)
                    A[j] = A[j - step];
                A[j] = temp;
            }
        }
        return A;
    }
};
////////////////////////////////////计数排序
class CountingSort {
public:
    int* countingSort(int* A, int n) {
        // write code here
        if(A == NULL || n <= 0)
            return A;
        int max = 0;
        int min = A[0];
        for(int i = 0; i < n; i++){  //求大值，代表桶的最大数目
            if(A[i] > max)
                max = A[i];
            if(A[i] < min)
                min = A[i];
        }
        int *tempA = new int[max + 1]();  //new申请内存空间，并初始化为0
        for(int i = 0; i < n; i++)
            tempA[A[i]]++;
        int index = 0;
        for(int i =min,j; i <= max; i++){
            for(j = 0; j < tempA[i]; j++)
                A[index++] = i;
        }
        delete []tempA;
        tempA = NULL;
        return A;
         
    }
};
////////////////////////////////////基数排序
class RadixSort {
public:
    int* radixSort(int* A, int n) {
        // write code here
        if(A== NULL || n <= 1)
            return A;
        vector<vector<int>> res(10); //创建10个桶
        int max = 0;
        for(int i = 0; i < n; i++)
            if(A[i] > max)
            	max = A[i];
        int count = 0;
        while(max){  //找出最大的位数，以确定外循环的次数
            count++;
            max /= 10;
        }
        
        for(int i = 0; i < count; i++){
            for(int j = 0; j < n; j++){
                int num = A[j] % (int)pow(10,i + 1) / (int)pow(10,i);  //num代表个、十、百、千位上的数字
                res[num].push_back(A[j]);
            }
            int index = 0;
            for(auto iter1 = res.begin(); iter1 != res.end(); iter1++){
                for(auto iter2 = iter1->begin(); iter2 != iter1->end(); iter2++)
                    A[index++] = *iter2;
            }
            for(int i = 0; i < 10; i++)
                res[i].clear();
        }
        return A;
    }
};
*/