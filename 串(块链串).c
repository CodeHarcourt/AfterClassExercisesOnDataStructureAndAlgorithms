#define BLOCK_SIZE 4
typedef struct Block{
    char ch[BLOCK_SIZE];
    struct Block* next;
}Block;
typedef struct{
    Block* head;
    Block * tail;
    int len;
}BLString;
//结点大小：结点的数据域data中存放字符的个数。
//链域大小：结点的指针域next占用字符的个数。
//存储密度 = 串值占用的存储位/实际为串分配的存储位