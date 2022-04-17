/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {   //노드를 표현하기 위한 구조체
    int key;            //필드값
    struct Node* link;  //node를 가리키는 변수
} listNode;

typedef struct Head {   //헤더노드를 표현하기 위한 구조체
    struct Node* first; 
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);      //초기화하는 함수 
int freeList(headNode* h);              //링크드리스트를 메모리해제하는 함수

int insertFirst(headNode* h, int key);  //첫 노드에 삽입하는 함수
int insertNode(headNode* h, int key);   //입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입하는 함수
int insertLast(headNode* h, int key);   //마지막에 노드를 삽입하는 함수

int deleteFirst(headNode* h);           //첫 노드를 삭제하는 함수
int deleteNode(headNode* h, int key);   //입력한 key와 같은 노드를 삭제하는 함수
int deleteLast(headNode* h);            //마지막 노드를 삭제하는 함수
int invertList(headNode* h);            //링크드리스트를 역순으로 배치하는 함수

void printList(headNode* h);            //리스트를 출력하는 함수

int main()
{
    char command;   
    int key;
    headNode* headnode=NULL;

    printf("[----- [Cho Joon Hee] [2017038076] -----]\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");   //사용자로부터 커맨드를 입력받음
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            headnode = initialize(headnode);    //연결리스트 초기화
            break;
        case 'p': case 'P':
            printList(headnode);                //연결리스트 출력
            break;
        case 'i': case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);          //입력된 key값을 key값 보다 큰 노드 앞에 삽입
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);          //입력한 key와 같은 노드 삭제
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);          //연결리스트 마지막에 key값의 노드 삽입
            break;
        case 'e': case 'E':
            deleteLast(headnode);               //마지막노드삭제
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);         //노드의 처음에 삽입
            break;
        case 't': case 'T':
            deleteFirst(headnode);              //첫번째 노드 삭제
            break;
        case 'r': case 'R':
            invertList(headnode);               //연결리스트 역순으로 배치
            break;
        case 'q': case 'Q':
            freeList(headnode);                 //프로그램 종료 전 할당된 메모리 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

headNode* initialize(headNode* h) { //초기화하는 함수
   /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
   if(h != NULL)      //h가 할당받은 것이 있다면
      freeList(h);   //할당된 메모리 모두 해제

   /* headNode에 대한 메모리를 할당하여 리턴 */
   headNode* temp = (headNode*)malloc(sizeof(headNode));   //temp에 headNode사이즈만큼 메모리 할당받음
   temp->first = NULL;                              //현재는 헤더노드가 없음
   return temp;                                     //temp주소 리턴
}

int freeList(headNode* h){  //링크드리스트 메모리해제하는 함수
   /* h와 연결된 listNode 메모리 해제
    * headNode도 해제되어야 함.
    */
   listNode* p = h->first;   //p에 첫번째 노드를 가리키도록 설정

   listNode* prev = NULL;   //삭제하고자하는 노드
   while(p != NULL) {       //리스트가 존재한다면
      prev = p;             //prev가 p를 가리키도록함
      p = p->link;          //p는 p의 다음 노드를 가리키도록함
      free(prev);           //prev가 가리키는 노드 메모리 반납
   }
   free(h);            //마지막으로 헤드노드 메모리 반납
   return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { //첫 노드에 삽입하는 함수

   listNode* node = (listNode*)malloc(sizeof(listNode));   //노드를 추가하기위한 공간을 할당받음
   node->key = key;      //node의 key에 사용자가 입력한 값 할당

   node->link = h->first;   //생성한 노드가 첫번째 노드를 가리키도록함(추가한 노드가 제일 첫번째 노드로 설정을 위함)
   h->first = node;      //헤더가 노드의 첫번째를 가리키도록함

   return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = NULL;      //헤더노드를 받을 노드
    listNode* temp = (listNode*)malloc(sizeof(listNode));   //삽입할 노드
    listNode* previous = NULL;  //이전 노드
    temp->key = key;        //사용자가 입력한 키주고
    temp->link = NULL;      //link필드는 NULL로 초기화
    node = h->first;        //node가 첫번째노드를 가리키도록함
    int count = 0;          //노드가 첫번째 노드인지 판별하기 위한 변수

    for(; node; previous=node, node=node->link){    //node가 비어있지 않다면
        if(node->key >= key){                       //node의 key필드와 사용자가 입력한 key를 비교해서 크거나 같을 경우
            if(count == 0){                         //만일 첫번째 노드였다면
                temp->link = node;                  //삽입할 노드가 첫번째 노드를 가리키도록하고(제일처음 삽입)
                h->first = temp;                    //헤더노드가 temp를 삽입한 노드를 가리키도록함
                return 0;
            }
            else{       //첫번째 노드가 아닐시
                temp->link = node;       //삽입할 노드가 해당노드를 가리키도록하고(큰 값이 나오는 노드 바로 앞에 삽입)
                previous->link = temp;   //이전노드가 삽입한노드를 가리키도록함  
                return 0;
            }
        }
        count++;
    }

    previous->link = temp;  //만일 입력key값이 제일 클 경우 이전노드(제일 마지막노드)가 삽입할 노드를 가리키도록함
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {  //마지막에 노드를 삽입하는 함수
    listNode *temp = (listNode*)malloc(sizeof(listNode));   //삽입할 노드를 할당받음
    listNode *node;         //헤더노드를 받을 포인터
    temp->key = key;        //사용자가 입력한 값 할당
    temp->link = NULL;
    
    node = h->first;        //node가 제일처음을 가리키도록함

    for(; node->link != NULL; node=node->link); //node가 아무것도 가리키지않을때까지 반복(마지막노드까지)
	node->link = temp;      //마지막노드에 삽입
    
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {  //첫 노드를 삭제하는 함수
    listNode *node = h->first;         //헤더노드를 받을 포인터

    if(h->first == NULL) {      //만일 리스트가 비어있다면
      printf("The linked list is empty\n");
      return 0;
   }
    
    h->first = node->link;  //헤더노드가 node의 다음노드를 가리키도록하고
    free(node);             //해당 node 메모리반납

    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {  //입력한 key와 같은 노드를 삭제하는 함수
    listNode *node = h->first;      //node가 헤더노드를 가리키도록함
    listNode *previous = NULL;  //이전노드
    int count = 0;              //노드가 첫번째 노드인지 분별하기 위한 변수

    if(h->first == NULL) {      //만일 리스트가 비어있다면
      printf("The linked list is empty\n");
      return 0;
   }

    for(; node; previous = node, node=node->link) { //node가 마지막노드일때까지 반복
        if(node->key == key){       //node의 key와 입력한 key가 같다면
            if(count == 0){         //해당 노드가 첫번째 노드일시
                h->first = node->link;  //헤더가 다음 노드를 가리키도록하고
                free(node);         //해당 노드 메모리반납
                return 0;
            }
            else{                   //해당 노드가 첫번째가 아니라면
                previous->link = node->link;    //이전노드가 삭제할 노드가 가리키는 노드를 가리키도록하고
                free(node);          //해당노드 메모리반납
                return 0;
            }
        }
        count++;
    }

    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {   //마지막 노드를 삭제하는 함수
    listNode *node = h->first;  //node가 헤더노드를 가리키도록함
    listNode *previous = NULL;  //이전노드
    int count = 0;              //노드가 첫번째인지 구분하기 위한 변수

    if(h->first == NULL) {      //만일 리스트가 비어있다면
      printf("The linked list is empty\n");
      return 0;
   }

    for(; node->link != NULL; previous=node, node = node->link)count++; //node가 마지막 노드일때까지 반복, 반복문을 돌면 카운트증가

    if(count == 0){         //노드가 하나밖에 없다면
        h->first = NULL;    //헤더가 아무것도 가리키지 않도록하고
        free(node);         //해당 노드 메모리반납
        return 0;
    }
    else{                   //노드가 하나가 아니라면
        previous->link = NULL;  //이전노드가 아무것도 가리키지 않도록하고(마지막 노드로 만듦)
        free(node);         //마지막노드 삭제
        return 0;
    }

    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {   //링크드리스트를 역순으로 배치하는 함수
    listNode *node = h->first;  //node가 헤더노드를 가리키도록함
    listNode *trail = NULL;  //이전노드
    listNode *middle = NULL; //중간노드
    
    if(h->first == NULL) {      //만일 리스트가 비어있다면
      printf("The linked list is empty\n");
      return 0;
   }

    while(node){    //node가 마지막 노드일때까지 반복
        trail=middle;   //trail이 middle을 가리키도록하고
        middle = node;  //middle이 node를 가리키도록함
        node = node->link;  //노드는 다음 노드를 가리키도록함
        middle -> link = trail; //middle의 노드가 이전 노드를 가리키도록 함으로써 역순으로 배치
    }

    h->first = middle;  //역순으로 배치가 끝났으니 헤더가 첫번째 노드(node는 null이고 middle이 마지막노드)를 가리키도록함

    return 0;
}


void printList(headNode* h) {   //링크드리스트를 출력하는 함수
   int i = 0;       //리스트의 인덱스
   listNode* p;     //헤더노드를 가리킬 변수

   printf("\n---PRINT\n");

   if(h == NULL) {      //만일 리스트가 비어있다면
      printf("Nothing to print....\n");
      return;
   }

   p = h->first;        //p가 헤더노드를 가리키도록함

   while(p != NULL) {   //p가 마지막노드일때까지 출력
      printf("[ [%d]=%d ] ", i, p->key);    
      p = p->link;
      i++;
   }

   printf("  items = %d\n", i);
}
