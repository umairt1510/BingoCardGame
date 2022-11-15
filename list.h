typedef struct node NodeType;
struct node {
        int ch;
        NodeType *next;
   };
typedef struct {
        int length;
        NodeType *head;
    } List;
void init(int n, List *L) ;
void add(List *L, int c) ;
void print(List L) ;
int found (List L, int num) ;
int length(List L) ;
