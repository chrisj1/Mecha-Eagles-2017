struct node {
   int data;
   int key;
   struct node *next;
};

typedef struct linkedlist {
	struct node *head;
	struct node *current;
} linkedlist;



void insertFirst(linkedlist* list, int key, int data) {
   struct node link;
   struct node* = &link;

   link->key = key;
   link->data = data;

   link->next = head;

   list->head = link;
}

struct node* deleteFirst(linkedlist* list) {
   struct node *tempLink = head;

   list->head = head->next;

   return tempLink;
}

bool isEmpty(linkedlist* list) {
   return list->head == NULL;
}

int length(linkedlist* list) {
   int length = 0;
   struct node *current;

   for(current = list->head; current != NULL; current = current->next) {
      length++;
   }

   return length;
}

struct node* find(linkedlist* list, int key) {

   struct node* current = list->head;

   if(head == NULL) {
      return NULL;
   }

   while(current->key != key) {
      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }
   return current;
}

struct node* delete(linkedlist* list, int key) {
   struct node* current = list->head;
   struct node* previous = NULL;

   if(list->head == NULL) {
      return NULL;
   }

   while(current->key != key) {
      if(current->next == NULL) {
         return NULL;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if(current == list->head) {
      list->head = head->next;
   } else {
      list->previous->next = current->next;
   }

   return current;
}
