  //代码融合实验

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//做声明段因为我内嵌套融合函数但他需要在密码函数内而密码函数需要在主交互的上方，副链表需要在主链表下方 
struct Node* createhead();
struct Node *createNode();
void addNodeByHead();
struct Node* searchByName();
void printfList();
void xiugai();
void kkk();
void deleteNodeByName();
void menu();
void saveInfoToFile();
void readInfoFromFile();
void bubblesort();
void bubblesortB();
struct NodeT* createheadT();
struct NodeT *createNodeT();
void addNodeByHeadT();
void printfListT();
void yonghu();
void saveInfoToFileT();
void readInfoFromFileT();
void jiaohuB(); 
void jiaohu();
void jiaohuC();
void ronghe();
void manager(); 








// 外置代码彩蛋段因为有的我看不懂害怕搞错就专门开此区存放 
const int max_iterations = 128;
const float stop_threshold = 0.01f;
const float grad_step = 0.01f;
const float clip_far = 10.0f;

const float PI = 3.14159265359f;
const float PI2 = 6.28318530718f;
const float DEG_TO_RAD = 3.14159265359f / 180.0f;

typedef struct { float x, y; } vec2;
typedef struct { float x, y, z; } vec3;
typedef struct { float m[9]; } mat3;

const vec3 light_pos = { 20.0f, 50.0f, 20.0f };

float min(float a, float b) { return a < b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }
float clamp(float f, float a, float b) { return max(min(f, b), a); }
vec2 make2(float x, float y) { vec2 r = { x, y }; return r; }
vec2 add2(vec2 a, vec2 b) { vec2 r = { a.x + b.x, a.y + b.y }; return r; }
vec2 sub2(vec2 a, vec2 b) { vec2 r = { a.x - b.x, a.y - b.y }; return r; }
float dot2(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
float length2(vec2 v) { return sqrt(dot2(v, v)); }
vec3 make3(float x, float y, float z) { vec3 r = { x, y, z }; return r; }
vec3 add3(vec3 a, vec3 b) { vec3 r = { a.x + b.x, a.y + b.y, a.z + b.z }; return r; }
vec3 sub3(vec3 a, vec3 b) { vec3 r = { a.x - b.x, a.y - b.y, a.z - b.z }; return r; }
vec3 mul3(vec3 a, vec3 b) { vec3 r = { a.x * b.x, a.y * b.y, a.z * b.z }; return r; }
vec3 scale3(vec3 v, float s) { vec3 r = { v.x * s, v.y * s, v.z * s }; return r; }
float dot3(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float length3(vec3 v) { return sqrt(dot3(v, v)); }
vec3 normalize3(vec3 v) { return scale3(v, 1.0f / length3(v)); }
vec3 mul(mat3 m, vec3 v) {
    return make3(
        m.m[0] * v.x + m.m[3] * v.y + m.m[6] * v.z,
        m.m[1] * v.x + m.m[4] * v.y + m.m[7] * v.z,
        m.m[2] * v.x + m.m[5] * v.y + m.m[8] * v.z);
}

mat3 rotationXY(float x, float y) {
    vec2 c = { cos(x), cos(y) }, s = { sin(x), sin(y) };
    mat3 m = {
        c.y      , 0.0f, -s.y,
        s.y * s.x,  c.x,  c.y * s.x,
        s.y * c.x, -s.x,  c.y * c.x
    };
    return m;
}

float opI(float d1, float d2) { return max(d1, d2); }
float opU(float d1, float d2) { return min(d1, d2); }
float opS(float d1, float d2) { return max(-d1, d2); }

float sdPetal(vec3 p, float s) {
    p = add3(mul3(p, make3(0.8f, 1.5f, 0.8f)), make3(0.1f, 0.0f, 0.0f));
    vec2 q = make2(length2(make2(p.x, p.z)), p.y);

    float lower = length2(q) - 1.0f;
    lower = opS(length2(q) - 0.97f, lower);
    lower = opI(lower, q.y);

    float upper = length2(sub2(q, make2(s, 0.0f))) + 1.0f - s;
    upper = opS(upper, length2(sub2(q, make2(s, 0.0f))) + 0.97f - s);
    upper = opI(upper, -q.y);
    upper = opI(upper, q.x - 2.0f);

    float region = length3(sub3(p, make3(1.0f, 0.0f, 0.0f))) - 1.0f;
    return opI(opU(upper, lower), region);
}

float map(vec3 p) {
    float d = 1000.0f, s = 2.0f;
    mat3 r = rotationXY(0.1f, PI2 * 0.618034f);
    r.m[0] *= 1.08f;  r.m[1] *= 1.08f;  r.m[2] *= 1.08f;
    r.m[3] *= 0.995f; r.m[4] *= 0.995f; r.m[5] *= 0.995f;
    r.m[6] *= 1.08f;  r.m[7] *= 1.08f;  r.m[8] *= 1.08f;
    for (int i = 0; i < 21; i++) {
        d = opU(d, sdPetal(p, s));
        p = mul(r, p);
        p = add3(p, make3(0.0, -0.02, 0.0));
        s *= 1.05f;
    }
    return d;
}

vec3 gradient(vec3 pos) {
    const vec3 dx = { grad_step, 0.0, 0.0 };
    const vec3 dy = { 0.0, grad_step, 0.0 };
    const vec3 dz = { 0.0, 0.0, grad_step };
    return normalize3(make3(
        map(add3(pos, dx)) - map(sub3(pos, dx)),
        map(add3(pos, dy)) - map(sub3(pos, dy)),
        map(add3(pos, dz)) - map(sub3(pos, dz))));
}

float ray_marching(vec3 origin, vec3 dir, float start, float end) {
    float depth = start;
    for (int i = 0; i < max_iterations; i++) {
        float dist = map(add3(origin, scale3(dir, depth)));
        if (dist < stop_threshold)
            return depth;
        depth += dist * 0.3;
        if (depth >= end)
            return end;
    }
    return end;
}

float shading(vec3 v, vec3 n, vec3 eye) {
    vec3 ev = normalize3(sub3(v, eye));
    vec3 vl = normalize3(sub3(light_pos, v));
    float diffuse = dot3(vl, n) * 0.5f + 0.5f;
    vec3 h = normalize3(sub3(vl, ev));
    float rim = pow(1.0f - max(-dot3(n, ev), 0.0f), 2.0f) * 0.15f;
    float ao = clamp(v.y * 0.5f + 0.5f, 0.0f, 1.0f);
    return (diffuse + rim) * ao;
}

vec3 ray_dir(float fov, vec2 pos) {
    vec3 r = { pos.x, pos.y, -tan((90.0f - fov * 0.5f) * DEG_TO_RAD) };
    return normalize3(r);
}

float f(vec2 fragCoord) {
    vec3 dir = ray_dir(45.0f, fragCoord);
    vec3 eye = { 0.0f, 0.0f, 4.5f };
    mat3 rot = rotationXY(-1.0f, 1.0f);

    dir = mul(rot, dir);
    eye = mul(rot, eye);

    float depth = ray_marching(eye, dir, 0.0f, clip_far);
    vec3 pos = add3(eye, scale3(dir, depth));
    if (depth >= clip_far)
        return 0.0f;
    else
        return shading(pos, gradient(pos), eye);
}


void time(void)
{
    time_t timep;
    
    time(&timep);
    
    struct tm *p = gmtime(&timep);
    
    printf("%d/%d/%d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    
    printf(" %d:%d:%d\n", (8+p->tm_hour), p->tm_min, p->tm_sec);//中国东八区，比世界时间早8小时
    
}

//建立用户界面完成买酒与开台，点歌； 



 

//创建新的链表首先是名字的修改，函数应该都一样；
//下一步再做文件的修改
//然后是两个在一起测试看有没有创建新链表与文件；
//最后一步是将用户系统融合到终端实验；




struct drinks
{
     char name[20];//名字 
     float price;//价格 
     int num;//数量 

};




struct Node//容器 
{
    struct drinks data;
	struct Node* next;//这个结构体指针去访问链表中的节点，节点的数据是结构体的形式
	 
	 
};
struct Node* list = NULL;





//建一个头节点, 结构体变量 
struct Node *createhead()
{
	//申请动态内存
	 struct Node*headNode = (struct Node*)malloc(sizeof(struct Node));
	 headNode->next = NULL;
	 return headNode;
	
}


//节点，数据处理，生成节点 
struct Node *createNode(struct drinks data) //结构体指针函数 最后函数返回指针形式 
{
	struct Node*newNode = (struct Node*)malloc(sizeof(struct Node));//节点的结构体指针保存节点的大小 
	newNode->data = data;//数据给数据域 
	newNode->next = NULL;//指针域为空 
	return newNode;
	
	
}

//做一个链表的节点插入，函数，表头插入法 
void addNodeByHead(struct Node *headNode,struct drinks data) 
{
//   struct Node* createNode;
  
   //这一步是去把数据转化为一个结构体 ，参考上面的函数 
    struct Node *newNode = createNode(data);
   //插入节点右边节点的指针域原来在头结点的指针域 
    newNode->next = headNode->next;
   //新节点的数据域的地址赋给头结点的指针域 
    headNode->next = newNode;

}

//链表的查找 
struct Node* searchByName(struct Node* headNode,char* drinksName)
{
	struct Node* posNode = headNode->next;
	while(posNode!=NULL&&strcmp(posNode->data.name,drinksName))
	{
		posNode = posNode->next;	
	}
	return posNode;
}



//建立一个移动指针从第二个节点开始移动,打印链表
void printfList(struct Node* headNode) 
{
	struct Node* pMove = headNode->next;//指向头节点的指针域
	printf("酒名 价格 数量\n"); 
	while(pMove!=NULL)
	{
		printf("%s %.1f %d\n ",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
	
	
}


//链表的修改 
void xiugai(struct Node* headNode,char *drinksName)
{
	int m;
    struct Node*posNode = headNode;
	while(posNode != NULL&&strcmp(posNode->data.name,drinksName))	
	{
		posNode = posNode->next;
	}
	if(posNode==NULL)
	{
	printf("无此内容");
	return;
	}
	else 
	{
		printf("%s %f %d\n",posNode->data.name,posNode->data.price,posNode->data.num);
		printf("请输入新的信息");
		printf("1修改名字 2修改价格 3修改数量");
        scanf("%d",&m);
switch(m)
{
	case 1: printf("输入新的名字");
	        scanf("%s",posNode->data.name);
	        break;
	case 2: printf("输入新的价格");
	        scanf("%f",&posNode->data.price);
	        break;       
	case 3: printf("输入新的数量");
	        scanf("%d",&posNode->data.num);
	        break;        
	
}
		printf("修改成功"); 
	}	
	
	
}

//系统登录并查看彩蛋 

void kkk()
{
	
	int i = 0,p=0;
	//假设密码是字符串
	char password[20] = "0",ch;
	for (p = 0;p < 3;p++)
	{
		printf("请输入密码：");
	while(1)
	{
		ch=getch();
		if(ch=='\r')
		{
		break;
		}
		password[i++]=ch;
		printf("*"); 
		
	}
	password[i]='\0';
		
		if (strcmp(password, "sss123") == 0)
		{
			printf("登录成功\n");
			system("cls");
	        manager();
	        break;		
        }
		
	       
		else
		{
			printf("密码错误，请重新输入\n");
			
		}
	}
	if (p == 3)
	{
		printf("三次密码均输入错误\n");
	}
	
}




//指定删除
void deleteNodeByName(struct Node* headNode,char *drinksName) //传入头节点的指针，传入要删除的数据 
{
	struct Node* posLeftNode = headNode;//因为要遍历，所以从最初开始 
	struct Node* posNode = headNode->next;
	//字符串比较函数
	 
	while (posNode != NULL && strcmp(posNode->data.name,drinksName)) //被删除的目标数据不等于此时数据域 
	{
		posLeftNode = posNode;
		posNode = posLeftNode->next;//使左边节点与目标节点同时向右边遍历 
		
	}
	
	//讨论遍历查找的结果
	 if(posNode == NULL) //查找到表尾无结果 
	      return;
	else//查找到目标 
	{
		printf("删除成功");
		posLeftNode->next = posNode->next;//这是一个链接操作，将目标右边节点的地址赋值给目标左边的指针域，然后释放目标节点 
		free(posNode);
		posNode = NULL;//架空，防止数据泄露 
		
	}
	
}



 
void menu()//做个页面 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               酒吧管理系统                 \n");
	time();
	printf("               0.退出系统\n");
	printf("               1.登记酒水\n");
	printf("               2.浏览库存\n");
	printf("               3.修改酒水信息\n");
	printf("               4.酒水排序\n");
	printf("               5.删除酒水\n");
	printf("               6.查找酒水\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	
	
}
//对list做文件操作 

//存文件 
void saveInfoToFile(const char* fileName, struct Node* headNode)
{
	FILE* fp = fopen(fileName,"w");// 以写的方式打开文件 
	struct Node* pMove = headNode->next;
	while(pMove != NULL	)
	{
		fprintf(fp,"%s %.1f %d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
	fclose(fp);
}



//读文件 
void readInfoFromFile(const char* fileName,struct Node* headNode)
{
	FILE* fp = fopen(fileName,"r");//以读的方式打开文件，但是第一次开文件是不存在的 
	if(fp==NULL)
	{
		fp = fopen(fileName,"w+");//以可读可写的方式创建文件 
	}
	struct drinks tempData;//创建临时结构体变量去存放我向文件输入的内容 ，可以理解为我代码不能直接传进来需要一个假体 
	while(fscanf(fp,"%s %f %d",tempData.name,&tempData.price,&tempData.num) != EOF)
	{
		addNodeByHead(list,tempData);//添加节点创建链表，也就是在文件中创建链表 
		
	}
	
	fclose(fp);
}

//对链表进行冒泡排序
void bubbleSortList(struct Node* headNode){
	struct Node* p;
	struct Node* q;
	struct Node* r;
	struct Node* t;
	int flag = 1;
	while(flag){
		p = headNode;
		q = headNode->next;
		flag = 0;
		while(q != NULL){
			r = q->next;
			if(r == NULL){
				break;
			}else if(q->data.price < r->data.price){
				t = r->next;
				q->next = t;
				r->next = q;
				p->next = r;
				p = r;
				q = p->next;
				r = q->next;
				flag = 1;
			}else{
				p = q;
				q = p->next;
			}
		}
	}
	printfList(list);
}


//对链表进行冒泡排序第二种方式，我认为再交互中用IF选择可以解决此问题，没想到真行 
void bubbleSortListB(struct Node* headNode){
	struct Node* p;
	struct Node* q;
	struct Node* r;
	struct Node* t;
	int flag = 1;
	while(flag){
		p = headNode;
		q = headNode->next;
		flag = 0;
		while(q != NULL){
			r = q->next;
			if(r == NULL){
				break;
			}else if(q->data.num < r->data.num){
				t = r->next;
				q->next = t;
				r->next = q;
				p->next = r;
				p = r;
				q = p->next;
				r = q->next;
				flag = 1;
			}else{
				p = q;
				q = p->next;
			}
		}
	}
	printfList(list);
}





// 现在我们要去做新的链表，新的文件

struct tai
{
     char name[20];//用户名字 
     int num;//数量 
};




struct NodeT//容器 
{
    struct tai data;
	struct NodeT* next;//这个结构体指针去访问链表中的节点，节点的数据是结构体的形式
	 
	 
};
struct NodeT* listT = NULL;





//建一个头节点, 结构体变量 
struct NodeT* createheadT() //指针函数最后返回一个指针类型 
{
	
	
	struct NodeT*headNodeT = (struct NodeT*)malloc(sizeof(struct NodeT));//动态内存 ,结构体指针去指向结构体内存 // 这个HEADNODE是头指针存放头结点的地址 
	//变量使用.初始化 
	 headNodeT->next = NULL;//初始化头节点的指针，头节点的数据是空 
	 return headNodeT;//返回出头结点的地址便于后续调用 也就是头结点的指针 
	
}


//节点，数据处理，生成节点 
struct NodeT *createNodeT(struct tai data) //结构体指针函数 最后函数返回指针形式 
{
	struct NodeT*newNodeT = (struct NodeT*)malloc(sizeof(struct NodeT));//节点的结构体指针保存节点的大小 
	newNodeT->data = data;//数据给数据域 
	newNodeT->next = NULL;//指针域为空 
	return newNodeT;
	
	
}

//做一个链表的节点插入，函数，表头插入法 
void addNodeByHeadT(struct NodeT *headNodeT,struct tai data) 
{
//   struct Node* createNode;
   struct NodeT* newNodeT = createNodeT(data);//这一步是去把数据转化为一个结构体 ，参考上面的函数 
   newNodeT->next = headNodeT->next;//插入节点右边节点的指针域原来在头结点的指针域 
   headNodeT->next = newNodeT;//新节点的数据域的地址赋给头结点的指针域 


}



//建立一个移动指针从第二个节点开始移动,打印链表
void printfListT(struct NodeT* headNodeT) 
{
	struct NodeT* pMoveT = headNodeT->next;//指向头节点的指针域
	printf("用户名 台号\n"); 
	while(pMoveT!=NULL)
	{
		printf("%s %d\n ",pMoveT->data.name,pMoveT->data.num);
		pMoveT = pMoveT->next;
	}
	
	
}

//指定删除 




//建立用户界面完成买酒与开台，点歌； 
void yonghu()
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$                  欢迎进入用户系统                            $\n");
	time();
    printf("$                 1# 发起订单                                  $\n");
	printf("$                 2#  开座位                                   $\n");
	printf("$                 3#  查看座位                                 $\n");
	printf("$                 4#  查看彩蛋                                 $\n");
	printf("$                 0#  回到页面                                 $\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	
}






//对list做文件操作 

//存文件 
void saveInfoToFileT(const char* fileName, struct NodeT* headNodeT)
{
	FILE* fp = fopen(fileName,"w");// 以写的方式打开文件 
	struct NodeT* pMoveT = headNodeT->next;
	while(pMoveT != NULL)
	{
		fprintf(fp,"%s %d\n",pMoveT->data.name,pMoveT->data.num);
		pMoveT = pMoveT->next;
	}
	fclose(fp);
}



//读文件 
void readInfoFromFileT(const char* fileName,struct NodeT* headNodeT)
{
	FILE* fp = fopen(fileName,"r");//以读的方式打开文件，但是第一次开文件是不存在的 
	if(fp==NULL)
	{
		fp = fopen(fileName,"w+");//以可读可写的方式创建文件 
	}
	struct tai tempDataT;//创建临时结构体变量去存放我向文件输入的内容 ，可以理解为我代码不能直接传进来需要一个假体 
	while(fscanf(fp,"%s %d",tempDataT.name,&tempDataT.num) != EOF)
	{
		addNodeByHeadT(listT,tempDataT);//添加节点创建链表，也就是在文件中创建链表 
		
	}
	
	fclose(fp);
}


 //关于台数建立新的链表 这个一会做
 //先做交互 


struct drinks tempdrinks;//建立临时的酒水信息

struct Node* result = NULL;//建立临时指针结果去存放函数用于查找函数结果的判定 




//做交互 
void jiaohuB(); 
void jiaohu()
{
	int a,key = 0;
	struct Node* result = NULL;//建立临时指针结果去存放函数用于查找函数结果的判定 
	
	scanf("%d",&key);
	switch(key){
			case 1: printf("登记\n");
			        printf("输入酒水的信息(name,price,num):");
					scanf("%s %f %d",tempdrinks.name,&tempdrinks.price,&tempdrinks.num); 
					addNodeByHead(list,tempdrinks);
					saveInfoToFile("drinksinfo.txt",list);
			        break;
			case 2: printf("浏览\n");
			        printfList(list);
			        break;
			case 3: printf("修改\n"); 
			        printf("请输入要修改的酒水"); 
			        scanf("%s",tempdrinks.name);
			        xiugai(list,tempdrinks.name);
				    saveInfoToFile("drinksinfo.txt",list);// 数据的修改要同步到文件 
			        break;	      
			case 4: printf("价格排序1  数量排序2\n"); 
                    scanf("%d",&a);
                    if(a==1){bubbleSortList(list);
					}
			        else if(a==2){bubbleSortListB(list);
					}
			        break;
			case 5: printf("删除\n");
			        printf("请输入删除的名字");
			        scanf("%s",tempdrinks.name);
			        deleteNodeByName(list,tempdrinks.name);
			        saveInfoToFile("drinksinfo.txt",list);// 数据的修改要同步到文件 
			        break;
			case 6: printf("查找\n");
			        printf("请输入名字："); 
			        scanf("%s",tempdrinks.name);
			        result = searchByName(list,tempdrinks.name);
			        if(result == NULL)
					{
			        	printf("未找到相关信息\n");
					}
					else
					{
						printf("名字 价格 数量\n");
						printf("%s %.1f %d\n",result->data.name,result->data.price ,result->data.num);
				    }
			        break;
			case 0: printf("感谢使用\n"); 
			exit(0);//退出 
			default: 
			printf("您的输入有误，重新输入");
			break; 
			 
		}
	
	
}

struct tai temptai;//建立临时的台信息
void jiaohu();
void jiaohuB() 
{
	int op=0;
	scanf("%d",&op);
//	struct tai temptai;//建立临时的台信息
	struct Node* resultT = NULL;//建立临时指针结果去存放函数用于查找函数结果的判定 
	switch(op)
	{
		case 1:
	          printf("购买\n");
	          printfList(list);
	          printf("请输入购买的名字：");
	          scanf("%s",tempdrinks.name);
	           resultT = searchByName(list,tempdrinks.name);
	         if(resultT==NULL)
	         {
	             printf("没有该商品信息\n");	
	         }
          	else
         	{
	     	if (resultT->data.num>0)
	    	{
			resultT->data.num--;
			printf("购买成功\n");
	    	}
	     	else
	    	{
			printf("当前目标无库存，换个别的\n");
		    }
	        }
	        saveInfoToFile("drinksinfo.txt",list);// 数据的修改要同步到文件
        	break;
		case 2: printf("开座位\n");
			    printf("输入座位的信息(name,num):");
				scanf("%s %d",temptai.name,&temptai.num); 
				addNodeByHeadT(listT,temptai); 
				saveInfoToFileT("taiinfo.txt",listT);// 数据的修改要同步到文件
		break;
		case 3:printf("浏览\n");
			        printfListT(listT);
			        break;
		case 4:printf("彩蛋\n");
		   puts("\033[91m");
           for (int y = 0; y < 80; y++) {
           for (int x = 0; x < 160; x++)
            putchar("  .,-:;+=*#@"[(int)(f(make2((x / 160.0f - 0.5f) * 2.0f, (y / 80.0f - 0.5f) * -2.0f)) * 12.0f)]);
        putchar('\n');
        }
			        
		case 0: printf("感谢使用\n"); 
			    exit(0);//退出 
		default: 
			printf("您的输入有误，重新输入");
	    break; 
		
	}
} 
 
 
void ronghe()
{
	
	listT = createheadT();
	readInfoFromFileT("taiinfo.txt",listT);
	
	while(1)
	{
		yonghu();
		jiaohuB();
		system("pause");//防止闪屏
		system("cls");//清屏 
		
	}
		
		system("pause");
        
	
}





//管理员系统的函数 
void manager() 
{
	list = createhead();
	readInfoFromFile("drinksinfo.txt",list);
	while(1)
	{
		menu();
		jiaohu();
		system("pause");//防止闪屏
		system("cls");//清屏 
		
		
	}
		
		system("pause");
	
}

//KKK登陆成功后调用管理员系统 



//页面 
void page()
{
  	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); 
	printf("@          进入用户系统扣1    @\n");
	time();
	printf("@   进入管理员系统扣2，并登录 @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	
}
//做新的交互 

void jiaohuC()
{
	
	
	int key=0;
    scanf("%d",&key);
    switch(key)
	{
		case 1: ronghe();//用户系统 
		break;
		case 2: kkk();//登录并进入管理 
		break;
		
		
	}
	
}


int main()
{
	    list = createhead();
	    readInfoFromFileT("taiinfo.txt",listT);
	    readInfoFromFile("drinksinfo.txt",list);
		page();
		jiaohuC();
		return 0;
}








