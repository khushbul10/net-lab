#include <stdio.h>
 
int n, h;
 
void oneEat(int hungry[]) {
   printf("Allow one philosopher to eat at a time\n");
   for (int i = 0; i < h; i++) {
       printf("P%d is eating\n", hungry[i]);
       for (int j = 0; j < h; j++)
           if (i != j) printf("P%d is waiting\n", hungry[j]);
   }
}
 
void twoEat(int hungry[]) {
   printf("Allow two philosophers to eat at the same time\n");
   for (int i = 0; i < h; i++)
       for (int j = i + 1; j < h; j++) {
           printf("P%d and P%d are eating\n", hungry[i], hungry[j]);
           for (int k = 0; k < h; k++)
               if (k != i && k != j) printf("P%d is waiting\n", hungry[k]);
       }
}
 
int main() {
   int choice;
   printf("Dining Philosophers Problem\n");
   printf("Total philosophers: ");
   scanf("%d", &n);
   printf("Number hungry: ");
   scanf("%d", &h);
 
   int hungry[h];
   for (int i = 0; i < h; i++) {
       printf("Enter P%d position: ", i + 1);
       scanf("%d", &hungry[i]);
   }
 
   do {
       printf("\n1. One eat\n2. Two eat\n3. Exit\nChoice: ");
       scanf("%d", &choice);
       if (choice == 1) oneEat(hungry);
       else if (choice == 2) twoEat(hungry);
       else if (choice == 3) printf("Exiting...\n");
       else printf("Invalid choice!\n");
   } while (choice != 3);
 
   return 0;
}
