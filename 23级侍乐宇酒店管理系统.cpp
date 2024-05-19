  //�����ں�ʵ��

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//����������Ϊ����Ƕ���ںϺ���������Ҫ�����뺯���ڶ����뺯����Ҫ�����������Ϸ�����������Ҫ���������·� 
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








// ���ô���ʵ�����Ϊ�е��ҿ��������¸���ר�ſ�������� 
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
    
    printf(" %d:%d:%d\n", (8+p->tm_hour), p->tm_min, p->tm_sec);//�й���������������ʱ����8Сʱ
    
}

//�����û������������뿪̨����裻 



 

//�����µ��������������ֵ��޸ģ�����Ӧ�ö�һ����
//��һ�������ļ����޸�
//Ȼ����������һ����Կ���û�д������������ļ���
//���һ���ǽ��û�ϵͳ�ںϵ��ն�ʵ�飻




struct drinks
{
     char name[20];//���� 
     float price;//�۸� 
     int num;//���� 

};




struct Node//���� 
{
    struct drinks data;
	struct Node* next;//����ṹ��ָ��ȥ���������еĽڵ㣬�ڵ�������ǽṹ�����ʽ
	 
	 
};
struct Node* list = NULL;





//��һ��ͷ�ڵ�, �ṹ����� 
struct Node *createhead()
{
	//���붯̬�ڴ�
	 struct Node*headNode = (struct Node*)malloc(sizeof(struct Node));
	 headNode->next = NULL;
	 return headNode;
	
}


//�ڵ㣬���ݴ������ɽڵ� 
struct Node *createNode(struct drinks data) //�ṹ��ָ�뺯�� ���������ָ����ʽ 
{
	struct Node*newNode = (struct Node*)malloc(sizeof(struct Node));//�ڵ�Ľṹ��ָ�뱣��ڵ�Ĵ�С 
	newNode->data = data;//���ݸ������� 
	newNode->next = NULL;//ָ����Ϊ�� 
	return newNode;
	
	
}

//��һ������Ľڵ���룬��������ͷ���뷨 
void addNodeByHead(struct Node *headNode,struct drinks data) 
{
//   struct Node* createNode;
  
   //��һ����ȥ������ת��Ϊһ���ṹ�� ���ο�����ĺ��� 
    struct Node *newNode = createNode(data);
   //����ڵ��ұ߽ڵ��ָ����ԭ����ͷ����ָ���� 
    newNode->next = headNode->next;
   //�½ڵ��������ĵ�ַ����ͷ����ָ���� 
    headNode->next = newNode;

}

//����Ĳ��� 
struct Node* searchByName(struct Node* headNode,char* drinksName)
{
	struct Node* posNode = headNode->next;
	while(posNode!=NULL&&strcmp(posNode->data.name,drinksName))
	{
		posNode = posNode->next;	
	}
	return posNode;
}



//����һ���ƶ�ָ��ӵڶ����ڵ㿪ʼ�ƶ�,��ӡ����
void printfList(struct Node* headNode) 
{
	struct Node* pMove = headNode->next;//ָ��ͷ�ڵ��ָ����
	printf("���� �۸� ����\n"); 
	while(pMove!=NULL)
	{
		printf("%s %.1f %d\n ",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
	
	
}


//������޸� 
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
	printf("�޴�����");
	return;
	}
	else 
	{
		printf("%s %f %d\n",posNode->data.name,posNode->data.price,posNode->data.num);
		printf("�������µ���Ϣ");
		printf("1�޸����� 2�޸ļ۸� 3�޸�����");
        scanf("%d",&m);
switch(m)
{
	case 1: printf("�����µ�����");
	        scanf("%s",posNode->data.name);
	        break;
	case 2: printf("�����µļ۸�");
	        scanf("%f",&posNode->data.price);
	        break;       
	case 3: printf("�����µ�����");
	        scanf("%d",&posNode->data.num);
	        break;        
	
}
		printf("�޸ĳɹ�"); 
	}	
	
	
}

//ϵͳ��¼���鿴�ʵ� 

void kkk()
{
	
	int i = 0,p=0;
	//�����������ַ���
	char password[20] = "0",ch;
	for (p = 0;p < 3;p++)
	{
		printf("���������룺");
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
			printf("��¼�ɹ�\n");
			system("cls");
	        manager();
	        break;		
        }
		
	       
		else
		{
			printf("�����������������\n");
			
		}
	}
	if (p == 3)
	{
		printf("����������������\n");
	}
	
}




//ָ��ɾ��
void deleteNodeByName(struct Node* headNode,char *drinksName) //����ͷ�ڵ��ָ�룬����Ҫɾ�������� 
{
	struct Node* posLeftNode = headNode;//��ΪҪ���������Դ������ʼ 
	struct Node* posNode = headNode->next;
	//�ַ����ȽϺ���
	 
	while (posNode != NULL && strcmp(posNode->data.name,drinksName)) //��ɾ����Ŀ�����ݲ����ڴ�ʱ������ 
	{
		posLeftNode = posNode;
		posNode = posLeftNode->next;//ʹ��߽ڵ���Ŀ��ڵ�ͬʱ���ұ߱��� 
		
	}
	
	//���۱������ҵĽ��
	 if(posNode == NULL) //���ҵ���β�޽�� 
	      return;
	else//���ҵ�Ŀ�� 
	{
		printf("ɾ���ɹ�");
		posLeftNode->next = posNode->next;//����һ�����Ӳ�������Ŀ���ұ߽ڵ�ĵ�ַ��ֵ��Ŀ����ߵ�ָ����Ȼ���ͷ�Ŀ��ڵ� 
		free(posNode);
		posNode = NULL;//�ܿգ���ֹ����й¶ 
		
	}
	
}



 
void menu()//����ҳ�� 
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("               �ưɹ���ϵͳ                 \n");
	time();
	printf("               0.�˳�ϵͳ\n");
	printf("               1.�ǼǾ�ˮ\n");
	printf("               2.������\n");
	printf("               3.�޸ľ�ˮ��Ϣ\n");
	printf("               4.��ˮ����\n");
	printf("               5.ɾ����ˮ\n");
	printf("               6.���Ҿ�ˮ\n");
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	
	
}
//��list���ļ����� 

//���ļ� 
void saveInfoToFile(const char* fileName, struct Node* headNode)
{
	FILE* fp = fopen(fileName,"w");// ��д�ķ�ʽ���ļ� 
	struct Node* pMove = headNode->next;
	while(pMove != NULL	)
	{
		fprintf(fp,"%s %.1f %d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
	fclose(fp);
}



//���ļ� 
void readInfoFromFile(const char* fileName,struct Node* headNode)
{
	FILE* fp = fopen(fileName,"r");//�Զ��ķ�ʽ���ļ������ǵ�һ�ο��ļ��ǲ����ڵ� 
	if(fp==NULL)
	{
		fp = fopen(fileName,"w+");//�Կɶ���д�ķ�ʽ�����ļ� 
	}
	struct drinks tempData;//������ʱ�ṹ�����ȥ��������ļ���������� ���������Ϊ�Ҵ��벻��ֱ�Ӵ�������Ҫһ������ 
	while(fscanf(fp,"%s %f %d",tempData.name,&tempData.price,&tempData.num) != EOF)
	{
		addNodeByHead(list,tempData);//��ӽڵ㴴������Ҳ�������ļ��д������� 
		
	}
	
	fclose(fp);
}

//���������ð������
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


//���������ð������ڶ��ַ�ʽ������Ϊ�ٽ�������IFѡ����Խ�������⣬û�뵽���� 
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





// ��������Ҫȥ���µ������µ��ļ�

struct tai
{
     char name[20];//�û����� 
     int num;//���� 
};




struct NodeT//���� 
{
    struct tai data;
	struct NodeT* next;//����ṹ��ָ��ȥ���������еĽڵ㣬�ڵ�������ǽṹ�����ʽ
	 
	 
};
struct NodeT* listT = NULL;





//��һ��ͷ�ڵ�, �ṹ����� 
struct NodeT* createheadT() //ָ�뺯����󷵻�һ��ָ������ 
{
	
	
	struct NodeT*headNodeT = (struct NodeT*)malloc(sizeof(struct NodeT));//��̬�ڴ� ,�ṹ��ָ��ȥָ��ṹ���ڴ� // ���HEADNODE��ͷָ����ͷ���ĵ�ַ 
	//����ʹ��.��ʼ�� 
	 headNodeT->next = NULL;//��ʼ��ͷ�ڵ��ָ�룬ͷ�ڵ�������ǿ� 
	 return headNodeT;//���س�ͷ���ĵ�ַ���ں������� Ҳ����ͷ����ָ�� 
	
}


//�ڵ㣬���ݴ������ɽڵ� 
struct NodeT *createNodeT(struct tai data) //�ṹ��ָ�뺯�� ���������ָ����ʽ 
{
	struct NodeT*newNodeT = (struct NodeT*)malloc(sizeof(struct NodeT));//�ڵ�Ľṹ��ָ�뱣��ڵ�Ĵ�С 
	newNodeT->data = data;//���ݸ������� 
	newNodeT->next = NULL;//ָ����Ϊ�� 
	return newNodeT;
	
	
}

//��һ������Ľڵ���룬��������ͷ���뷨 
void addNodeByHeadT(struct NodeT *headNodeT,struct tai data) 
{
//   struct Node* createNode;
   struct NodeT* newNodeT = createNodeT(data);//��һ����ȥ������ת��Ϊһ���ṹ�� ���ο�����ĺ��� 
   newNodeT->next = headNodeT->next;//����ڵ��ұ߽ڵ��ָ����ԭ����ͷ����ָ���� 
   headNodeT->next = newNodeT;//�½ڵ��������ĵ�ַ����ͷ����ָ���� 


}



//����һ���ƶ�ָ��ӵڶ����ڵ㿪ʼ�ƶ�,��ӡ����
void printfListT(struct NodeT* headNodeT) 
{
	struct NodeT* pMoveT = headNodeT->next;//ָ��ͷ�ڵ��ָ����
	printf("�û��� ̨��\n"); 
	while(pMoveT!=NULL)
	{
		printf("%s %d\n ",pMoveT->data.name,pMoveT->data.num);
		pMoveT = pMoveT->next;
	}
	
	
}

//ָ��ɾ�� 




//�����û������������뿪̨����裻 
void yonghu()
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$                  ��ӭ�����û�ϵͳ                            $\n");
	time();
    printf("$                 1# ���𶩵�                                  $\n");
	printf("$                 2#  ����λ                                   $\n");
	printf("$                 3#  �鿴��λ                                 $\n");
	printf("$                 4#  �鿴�ʵ�                                 $\n");
	printf("$                 0#  �ص�ҳ��                                 $\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	
}






//��list���ļ����� 

//���ļ� 
void saveInfoToFileT(const char* fileName, struct NodeT* headNodeT)
{
	FILE* fp = fopen(fileName,"w");// ��д�ķ�ʽ���ļ� 
	struct NodeT* pMoveT = headNodeT->next;
	while(pMoveT != NULL)
	{
		fprintf(fp,"%s %d\n",pMoveT->data.name,pMoveT->data.num);
		pMoveT = pMoveT->next;
	}
	fclose(fp);
}



//���ļ� 
void readInfoFromFileT(const char* fileName,struct NodeT* headNodeT)
{
	FILE* fp = fopen(fileName,"r");//�Զ��ķ�ʽ���ļ������ǵ�һ�ο��ļ��ǲ����ڵ� 
	if(fp==NULL)
	{
		fp = fopen(fileName,"w+");//�Կɶ���д�ķ�ʽ�����ļ� 
	}
	struct tai tempDataT;//������ʱ�ṹ�����ȥ��������ļ���������� ���������Ϊ�Ҵ��벻��ֱ�Ӵ�������Ҫһ������ 
	while(fscanf(fp,"%s %d",tempDataT.name,&tempDataT.num) != EOF)
	{
		addNodeByHeadT(listT,tempDataT);//��ӽڵ㴴������Ҳ�������ļ��д������� 
		
	}
	
	fclose(fp);
}


 //����̨�������µ����� ���һ����
 //�������� 


struct drinks tempdrinks;//������ʱ�ľ�ˮ��Ϣ

struct Node* result = NULL;//������ʱָ����ȥ��ź������ڲ��Һ���������ж� 




//������ 
void jiaohuB(); 
void jiaohu()
{
	int a,key = 0;
	struct Node* result = NULL;//������ʱָ����ȥ��ź������ڲ��Һ���������ж� 
	
	scanf("%d",&key);
	switch(key){
			case 1: printf("�Ǽ�\n");
			        printf("�����ˮ����Ϣ(name,price,num):");
					scanf("%s %f %d",tempdrinks.name,&tempdrinks.price,&tempdrinks.num); 
					addNodeByHead(list,tempdrinks);
					saveInfoToFile("drinksinfo.txt",list);
			        break;
			case 2: printf("���\n");
			        printfList(list);
			        break;
			case 3: printf("�޸�\n"); 
			        printf("������Ҫ�޸ĵľ�ˮ"); 
			        scanf("%s",tempdrinks.name);
			        xiugai(list,tempdrinks.name);
				    saveInfoToFile("drinksinfo.txt",list);// ���ݵ��޸�Ҫͬ�����ļ� 
			        break;	      
			case 4: printf("�۸�����1  ��������2\n"); 
                    scanf("%d",&a);
                    if(a==1){bubbleSortList(list);
					}
			        else if(a==2){bubbleSortListB(list);
					}
			        break;
			case 5: printf("ɾ��\n");
			        printf("������ɾ��������");
			        scanf("%s",tempdrinks.name);
			        deleteNodeByName(list,tempdrinks.name);
			        saveInfoToFile("drinksinfo.txt",list);// ���ݵ��޸�Ҫͬ�����ļ� 
			        break;
			case 6: printf("����\n");
			        printf("���������֣�"); 
			        scanf("%s",tempdrinks.name);
			        result = searchByName(list,tempdrinks.name);
			        if(result == NULL)
					{
			        	printf("δ�ҵ������Ϣ\n");
					}
					else
					{
						printf("���� �۸� ����\n");
						printf("%s %.1f %d\n",result->data.name,result->data.price ,result->data.num);
				    }
			        break;
			case 0: printf("��лʹ��\n"); 
			exit(0);//�˳� 
			default: 
			printf("��������������������");
			break; 
			 
		}
	
	
}

struct tai temptai;//������ʱ��̨��Ϣ
void jiaohu();
void jiaohuB() 
{
	int op=0;
	scanf("%d",&op);
//	struct tai temptai;//������ʱ��̨��Ϣ
	struct Node* resultT = NULL;//������ʱָ����ȥ��ź������ڲ��Һ���������ж� 
	switch(op)
	{
		case 1:
	          printf("����\n");
	          printfList(list);
	          printf("�����빺������֣�");
	          scanf("%s",tempdrinks.name);
	           resultT = searchByName(list,tempdrinks.name);
	         if(resultT==NULL)
	         {
	             printf("û�и���Ʒ��Ϣ\n");	
	         }
          	else
         	{
	     	if (resultT->data.num>0)
	    	{
			resultT->data.num--;
			printf("����ɹ�\n");
	    	}
	     	else
	    	{
			printf("��ǰĿ���޿�棬�������\n");
		    }
	        }
	        saveInfoToFile("drinksinfo.txt",list);// ���ݵ��޸�Ҫͬ�����ļ�
        	break;
		case 2: printf("����λ\n");
			    printf("������λ����Ϣ(name,num):");
				scanf("%s %d",temptai.name,&temptai.num); 
				addNodeByHeadT(listT,temptai); 
				saveInfoToFileT("taiinfo.txt",listT);// ���ݵ��޸�Ҫͬ�����ļ�
		break;
		case 3:printf("���\n");
			        printfListT(listT);
			        break;
		case 4:printf("�ʵ�\n");
		   puts("\033[91m");
           for (int y = 0; y < 80; y++) {
           for (int x = 0; x < 160; x++)
            putchar("  .,-:;+=*#@"[(int)(f(make2((x / 160.0f - 0.5f) * 2.0f, (y / 80.0f - 0.5f) * -2.0f)) * 12.0f)]);
        putchar('\n');
        }
			        
		case 0: printf("��лʹ��\n"); 
			    exit(0);//�˳� 
		default: 
			printf("��������������������");
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
		system("pause");//��ֹ����
		system("cls");//���� 
		
	}
		
		system("pause");
        
	
}





//����Աϵͳ�ĺ��� 
void manager() 
{
	list = createhead();
	readInfoFromFile("drinksinfo.txt",list);
	while(1)
	{
		menu();
		jiaohu();
		system("pause");//��ֹ����
		system("cls");//���� 
		
		
	}
		
		system("pause");
	
}

//KKK��½�ɹ�����ù���Աϵͳ 



//ҳ�� 
void page()
{
  	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); 
	printf("@          �����û�ϵͳ��1    @\n");
	time();
	printf("@   �������Աϵͳ��2������¼ @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	
}
//���µĽ��� 

void jiaohuC()
{
	
	
	int key=0;
    scanf("%d",&key);
    switch(key)
	{
		case 1: ronghe();//�û�ϵͳ 
		break;
		case 2: kkk();//��¼��������� 
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








