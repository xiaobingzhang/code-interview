# cracking-the-coding-interview-5e


##5. Bit Manipulation

* 5.3 Given a positive integer, print the next smallest and the next largest number that have the `same` number of `1` bits in their `binary` representation.

**next smallest**
```cpp
TODO//P244 E版本
```



**next largest 非常巧妙的做法**
```cpp
typedef unsigned int uint_t;
int theSameOneBitsInBinaryNext(uint_t x){
    //x = 156 = 10011100
	uint_t rightOne;
	uint_t nextHighOneBit;
	uint_t rightOnePattern;
	uint_t next = 0;
	if (x)
	{
		// right most set bit
		rightOne = x &(-(signed)x);//00000100
		cout << hex << "rightOne" << rightOne << endl;
		// reset the pattern and set next higher bit
		// left part of x will be here
		nextHighOneBit = x + rightOne;//10100000

		// nextHigherOneBit is now part [D] of the above explanation.
		// isolate the pattern

		rightOnePattern  = x^nextHighOneBit; //00111100
		// right adjust pattern
		rightOnePattern = (rightOnePattern) / rightOne;//00001111
		// correction factor
		cout << hex << "rightOnePattern" << rightOnePattern << endl;
		rightOnePattern >>= 2;//00000011

		// rightOnesPattern is now part [A] of the above explanation.
		cout << hex << "rightOnePattern"<<rightOnePattern << endl;
		// integrate new pattern (Add [D] and [A])
		next = nextHighOneBit | rightOnePattern;//10100011
	}
	return next;
}
```


*  5.6 Write a program to `swap odd and even bits` in an integer with as few instructions as
possible (e.g., bit 0 and bit! are swapped, bit 2 and bit 3 are swapped, and so on).
```cpp
int swapOddEvenBits(int x){
    //先清空奇数或者偶数位，然后移位 进行或操作
    int ret = ((x & 0xaaaaaaaa) >> 1)|((x & 0x55555555) << 1)
}

```
*  5.7 An array A contains all the integers from 0 through n, except for one number which is missing. In this problem, we cannot access an entire integer in A with a single operation.The elements of A are represented in `binary`, and the only operation we can use to access them is "`fetch` the `j` th bit of `A[i]`," which takes `constant` time. Write code to find the missing integer. Can you do it in `0(n)` time?

```cpp
int findMissing(vector<BitInt> vec){
    return findMissing(vec,0);
}
int findMissing(vector<BitInt> vec,int bit){
    if (bit < 0){
        return 0;
    }
    vector<BitInt> oneBits(vec.size()/2);
    vector<BitInt> zeroBits(vec.size()/2);
    for(BitInt t :vector<BitInt> vec){
        if(t.fetch(bit) == 0){
            zeroBits.push_back(t);
        }else{
            oneBits.push_back(t);
        }
    }
    
    if(zeroBits.size() <= oneBits.size()){
        int v = findMissing(zeroBits,bit+1);
        return (v << 1)|0;
    }else{
        int v = findMissing(oneBits,bit+1);
        return (v << 1)|1;
    }
}
```
O(n)的解决方案


##6. Brain Teasers

* 6.5 There is a building of `1OO` floors. I fan egg drops from the Nth floor or above, it will
break. If it's dropped from any floor below, it will not break. You're given `two` eggs.
Find `N`, while `minimizing the number of drops for the worst case`0.

[Promble of Two Eggs Solutions ](http://ppwwyyxx.com/2013/Problem-of-Two-Eggs/)
**数学方式解答**:

第一次测试的时候，第一个鸡蛋不能放置的楼层太高了，否则，如果第一个鸡蛋破碎，第二个鸡蛋可能不能在k次测试后得到结果。但是也不能放置的矮了，因为如果放置的矮了，第一个鸡蛋破碎了还好说，如果没破，我们浪费了一次测试机会，也不能说是完全浪费了，不过至少是让效用没有最大化。所以，第一次测试的时候必须让第一个鸡蛋放置的不高不矮。

不高不矮是多高？高到如果第一个鸡蛋破碎后第二个鸡蛋刚好能完成k次测试得到结果这个目标。由此可知，第一次测试所在的楼层高度为k. 如果第一次测试第一枚鸡蛋破碎，则向下还有k-1层楼和k-1次机会， 一层一层的试，k次一定能完成目标寻找目标。

如果第一次测试，第一枚鸡蛋没有破碎，则我们现在只有k-1次测试机会了，而且知道k楼及其以下都是安全的了。我们消耗了一次测试机会，但是一次就测试了k层楼。
然后只有k-1次机会了，第二次测试，我们可以在k层的基础上再增加k-1层了，注意，这个时候由于我们只有k-1次机会，所以这次只能再增加k-1层，以保证测试的时候第一枚鸡蛋破碎的情况下仍然能完成任务。

重复上述过程，直到最后一次机会，我们总共测试的楼层数为：

$$ k + (k - 1) + \cdots + 1 = \frac{k(k + 1)}{2} = 100  \Rightarrow k \approx 14 $$
```
k + k -1 + k -2 + ... + 1 = (k+1)*k/2 = 100  => k = 14
```
**程序解决方式**

\begin{eqnarray}
f(0, m) & = & 0, (m >= 1)\\
f(n, 1) & = & n, (n >= 1)\\
f(n, m) & = & \min_{1 \le i \le n} \{ \max\{ f(i - 1, m - 1), f(n - i, m)\}\} + 1 \\
\end{eqnarray}

```
f(0,m) = 0,(m >= 1)
f(n,1) = n,(n >= 1)
f(n,m) = min{max{f(i-1,m-1),f(n-i,m)}} + 1
        (1=<i<=n)
```

```python
import functools
@functools.lru_cache(maxsize=None)
def f(n, m):
    if n == 0:
        return 0
    if m == 1:
        return n
    ans = min([max([f(i - 1, m - 1), f(n - i, m)]) for i in range(1, n + 1)]) + 1
    return ans
print(f(100, 2))	# 14
print(f(200, 2))	# 20
```
* 6.6 There are 100 closed lockers in a hallway. A man begins by opening all `100` lockers.
Next, he closes every second locker. Then, on his third pass, he toggles every third
locker (`closes it if it is open or opens it if it is closed`). This process continues for / 00
passes, such that on each pass i, the man toggles every ith locker. After his 100th
pass in the hallway, in which he toggles only locker #100, how many lockers are
`open`?

**SOLUTION**
We can tackle this problem by thinking through what it means for a door to be toggled. This will help us deduce which doors at the very end will be left opened.
**Question: For which rounds is a door toggled (open or closed)?**
A door n is toggled once for each factor of n, including itself and 1. That is, door 15 is toggled on rounds 1,3,5, and 15.
**Question: When would a door be left open?**
A door is left open if the number of factors (which we will call x) is `odd`. You can think about this by pairing factors off as an open and a close. If there's one remaining, the door will be open.
**Question: When would x be odd?**
The value x is odd if n is a perfect square. Here's why: pair n's factors by their complements.For example, if n is 36, the factors are `(1,36)`, `(2,18)`, `(3,12)`, `(4,9)`, `(6,6)`. Note that `{6,6)` only contributes one factor, thus giving nan odd number of factors.
**Question: How many perfect squares are there?**
There are `10` perfect squares. You could count them `(1,4,9,16,25,36,49,64,81,100)`, or you could simply realize that you can take the numbers 1 through 10 and square them: 1*1, 2*2, 3*3, ..., 10*10 Therefore, there are 10 lockers open at the end of this process.

##Mathematics and Probability

* 7.4 Write methods to implement the `multiply`, `subtract`, and `divide` operations for integers.Use `only` the add operator
**subtration**
```cpp
//negtive function
int negative(int n){
    int neg = 0;
    int d = n < 0 ? 1 : -1;
    while(n != 0){
        neg += d;
        n += d;
    }
    return neg;
}
int subtration(int a,int b){
    return a + negative(b);
}
```


**multiplication**

```cpp
    int multiply(int a,int b){
        if(abs(a) < abs(b)){//小优化
            multiply(b,a);
        }
        int sum = 0;
        for(int i = abs(b);i > 0; i--){
            sum += a;
        }
        if(b < 0){
            sum = negative(sum);
        }
        return sum;
    }
    int abs(int n){
        if(n < 0){
            return negative(n);
        }else{
            return n;
        }
    }
```

**Division**
```cpp
int divide(int a,int b){
    int absa = abs(a);
	int absb = abs(b);
	int product = 0;
	int x = 0;
	while (product + absb <= absa){
		product += absb;
		x++;
	}
	if ((a < 0 && b < 0) || (a > 0 && b > 0)){
		return x;
	}
	else{
		return negative(x);
	}
}
}
```
*  7.6 Given a two-dimensional graph with points on it, find a line which passes the most number of points.

[A very clean answer in Yang's Blog](http://www.cnblogs.com/Antech/p/3756825.html)
```Java
/*这道题目的时间复杂度最多就是O（n^2）
*因为要取任何两个点的组合求出斜率
*利用HashMap来存储Line ,slop的映射
*/
```,难点之一就是斜率是double类型不能用==比较
*/
//所以统一精度使得可以用 == 进行比较

```
```java
public Line findBestLine(Point[] points){
    Line bestLine = null;
    int bestCount = 0;
    Map<Line,Integer> lineCounts = new HashMap<Line,Integer>();
    for(int i = 0;i < point.length;i++){
        for(int j = i+1; j < points.length;j++){
            Line line = new Line(points[i],points[j]);
            int currentCount;
            if(lineCounts.containsKey(line)){
                currentCount = lineCounts.get(line) + 1;
            }else{
                currentCount = 1;
            }
            lineCounts.put(line,currentCount);
            if(currentCount > bestCount){
                bestCount = currentCount;
                bestLine = line;
            }
        }
    }
    return bestLine;
}
class Point{
    double x;
    double y;
}
class Line{
    double slope = 0;
    double intersect;
    public static final eps = 0.0001;
    boolean infinite_slop = false;
    public Line(Point p1,Point p2){
        if(Math.abs(p1.x -p2.x) < eps){
            infinite_slop = true;
            intersect = p1.x;
        }else{
            slope = (p1.y-p2.y)/(p1.x-p2.x);
            intersect = p1.y - slope*p1.x ;
        }
        slope = floor(slope);
        intersect = floor(intersect);
    }
    

    private floor(double val){
            return esp*((int)(val/esp));
        }
    @override
    public int hashCode(){
        if(infinite_slop){
            return (int) intersect; 
        }else{
            return (int)(slope+intersect)
        }
    }
    
    @override
    public boolean equal(Object obj){
        if(this == obj){
            return true;
        }
        if(obj == null || getClass != obj.getClass()){
            return false;
        }
        Line other = (Line)obj;
        if(this.infinite_slope == other.infinite_slope 
        && this.slope == other.slope 
        && this.intersect = that.intersect){
            return true;
        }
        return false;
    }
}

```

* 7.7 Design an algorithm to find the kth number such that the only prime factors are 3,
5, and 7.

**这本书的答案看着真的很不爽。。。。**

**其实这个答案通用性很强的，这个题目为3.5.7的倍数**

**有一个题目是计算丑数ugly number 2.3.5的倍数**

**或者更加通用的方法是有几个数字开几个队列是不是有点傻逼。。。。**

**谁有更好的方法可以告诉我**
```cpp
int kthNum(int k){
	queue<int> q3, q5, q7;
	int ret = 1;
	for (int i = 1; i < k; i++){
		q3.push(ret * 2);
		q5.push(ret * 3);
		q7.push(ret * 5);
		ret = min(q3.front(), min(q5.front(), q7.front()));
		if (ret == q3.front()){
			q3.pop();
		}
		if (ret == q5.front()){
			q5.pop();
		}
		if (ret == q7.front()){
			q7.pop();
		}
	}
	return ret;
}
```

##8. Object-Oriented Design
* 8.2  Imagine you have a call center with three levels of employees: `respondent`, `manager`,and `director`. An incoming telephone call must be first allocated to a respondent who is `free`. If the respondent `can't handle` the call, he or she must escalate the call to a` manager`. If the manager is not free or notable to handle it, then the call should be escalated to a director. Design the classes and data structures for this problem. Implement a method dispatchCall () which assigns a call to the first available employee.

    **这道题目Mircosoft面试被问到了，答的很不好，为啥没早一点看到这本书啊**

    **关注3个部分**
    
    **1 CallHandler中心角色负责任务分配和资源调度**
    **2 Call本身**
    **3 3类角色有一个抽象的父类**
    **类似与一个集群，在具体的内容就是临场发挥了，这3个点应该是重点**


##9. Recursion and Dynamic Programming

* 9.4 Write a method to return all subsets of a set.

```cpp
vector<vector<int>> subset(vector<int> &S){
    sort(S.begin(),S.end());
    int count = S.size();
    vector<vector<int>> ret;
    for(int i = 0; i < (1<<count);i++){
        vector<int> tmp;
        for(int j = 0;j < count;j++){
            if((i>>j)&1){
                tmp.push_back(S[j]);
            }
        }
        ret.push_back(tmp);
    }
    return ret;
}
```
* 9.5 Write a method to compute all permutations of array v

```cpp
//能够排除掉相同的序列

bool isSwap(const vector<int> &v,int begin,int end){
    for(int i = begin; i < end;i++){
        if(v[i] == v[end]){
            return false;
        }
    }
    return true;
}

void allPermutation(vector<int> &v,int l){
    if(l == v.size()){
        //print resutlt in the v;
    }else{
        for(int i = l;i < v.size();i++){
            if(isSwap(v,l,i)){//不需要去重直接去掉即可
                swap(v[l],v[i]);
                allPermutation(v,l+1);
                swap(v[l],v[i]);
            }
        }
    }
}
```

* 9.3  A magic index in an array A[l.. .n-l] is defined to be an index such that A[i] = i. Given a sorted array of distinct integers, write a method to find a magic index, if one exists, in array A.

FOLLOW UP
What if the values are not distinct?
```cpp
//第一问是就是二分一模一样的没啥说的

//第二问 //如果A[mid] < mid的时候结果可能在左边，因此两本都搜索
int search(vector<int> v,int l,int r){
    if(r < l || l < 0 || r >= v.size()){
        return -1;
    }
    int mid = (r - l) / 2 + l;
    if(v[mid] == mid){
        return mid;
    }
    
    int leftIndex = min(mid-1,v[mid]);
    int left = search(v,l,leftIndex);
    if(left >= 0){
        return left;
    }
    int rightIndex = max(mid+1,v[mid]);
    int right = search(v,rightIndex,r);
    
    return right;
    
}
```

* 9.6 Implement an algorithm to print all valid (i.e., properly opened and closed) combinations ofn-pairs of parentheses.
[Generate Parentheses ](https://leetcode.com/problems/generate-parentheses/)

```cpp
class Solution {
public:
    void generateParenthesis(int l, int r,const string &item, vector<string> &ret){
    	if (r < l){
    		return;
    	}
    	if (l == 0 && r == 0){
    		ret.push_back(item);
    	}
    	if (l > 0){
    		generateParenthesis(l - 1, r, item + "(", ret);
    	}
    	if (r > 0){
    		generateParenthesis(l, r - 1, item + ")", ret);
    	}
    }
    vector<string> generateParenthesis(int n) {
    	vector<string> ret;
    	if (n < 0){
    		return ret;
    	}
    	string item = "";
    	generateParenthesis(n, n, item, ret);
    	return ret;
    }

};

```

* 9.8 Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent), write code to calculate the number of ways of representing n cents.

```cpp
//a good solution to slove it
int makeChange(int n,int denom){
    int next_denom = 0;
    switch(denom){
        case 25:
            next_denom = 10;
            break;
        case 10:
            next_denom = 5;
            break;
        case 5:
            next_denom = 5;
            break;
        case 1:
            return 1;
    }
    int ways = 0;
    for(int i = 0; i * denom <= n;i++){
        ways += makeChange(n - i*denom,next_denom);
    }
    return ways;
}
```

* 9.9 八皇后问题

```cpp
bool check(int row, vector<int> &columnForRow){
	for (int i = 0; i < row;i++){
		if (columnForRow[row] == columnForRow[i]|| (row - i) == abs(columnForRow[row] - columnForRow[i])){
			return false;
		}
	}
	return true;
}
void totalNQuees(int row, int n, vector<int> &columnForRow, int &count){
	if (row == n){
		count++;
		for (int i = 0; i < n;i++){
			for (int j = 0; j < n;j++){
				if (columnForRow[j] == i){
					cout << "*";
				}
				else{
					cout << "_ ";
				}
			}
			cout << endl;
		}
		cout << endl;
		return;
	}
	for (int i = 0; i < n;i++){
		columnForRow[row] = i;
		if (check(row,columnForRow)){
			totalNQuees(row+1,n,columnForRow,count);
		}
	}
}

int totalNQuees(int n){
	vector<int> columnForRow(n,0);
	int count = 0;
	helper(0,n,columnForRow,count);
	return count;
}
```
* 9.10 You have a stack of n boxes, with widths , heights and depths. The boxes
cannot be rotated and can only be stacked on top of one another if each box in the
stack is strictly larger than the box above it in width, height, and depth. Implement
a method to build the tallest stack possible, where the heigh t of a stack is the sum of the heights of each box.
```java
public List<Box> createStackR(Box[] boxes,Box bottom){
    ArrayList<Box> max_stack = null;
    int max_height = 0;
    for(int i = 0;i < boxes.length;i++){
        if(boxes[i].canBeAbove(bottom)){
            ArrayList<Box> new_stack = createStackR(boxes, boxes[i]);
            int new_height = stackHeight(new_stack);
            if(new_height > max_height){
                max_stack = new_stack;
                max_height = new_height;
            }
        }
    }
    if(max_stack == null){
        max_stack = new ArrayList<Box>();
    }
    if(bottom != null){
        max_stack.add(0,bottom);
    }
    return max_stack;
}
/*
The problem in this code is that it gets very inefficient. We try to find the best solution that looks like {b3, ba, ...} even though we may have already found the best solution with b4 at the bottom. Instead of generating these solutions from scratch, we can cache these results using dynamic programming.
*/
public List<Box> createStackDP(Box[] boxes,Box bottom,HashMap<Box,ArrayList<Box>> stack_map){
    /////////////////////////////////////add
    if (bottom != null && stack_map.containsKey(bottom)) {
        return stack_map.get(bottom);
    }
    /////////////////////////
    ArrayList<Box> max_stack = null;
    int max_height = 0;
    for(int i = 0;i < boxes.length;i++){
        if(boxes[i].canBeAbove(bottom)){
            ArrayList<Box> new_stack = createStackDP(boxes, boxes[i],stack_map);
            int new_height = stackHeight(new_stack);
            if(new_height > max_height){
                max_stack = new_stack;
                max_height = new_height;
            }
        }
    }
    if(max_stack == null){
        max_stack = new ArrayList<Box>();
    }
    if(bottom != null){
        max_stack.add(0,bottom);
    }
    ////////////////////////////////////////////////add
    stack_map.put(bottom,max_stack);
    ///////////////////////////////////////////////
    return (ArrayList<Box>)max_stack.clone();
}
```

