#include <stdio.h>
#include <stdlib.h>

// Maszyna turinga dodajaca wielocyfrowe liczby binarne
// Najpierw nalezy podac ilosc cyfr a nastepnie wprowadzic liczbe
// Cyfry nalezy oddzielić spacjami 
// @author Michal Musial

//Tablica przejść i wyjść
static int transitions [8][3][3] = {
   {{1, 4, -1}, {0, 1, -1}, {-1, 7, 0}},
   {{0, 2, -1}, {1, 2, -1}, {-1, 7, 0}},
   {{0, 3, -1}, {1, 3, -1}, {0, 3, -1}},
   {{1, 6, -1}, {0, 3, -1}, {1, 6, -1}},
   {{1, 5, -1}, {0, 2, -1}, {-1, 7, 0}},
   {{1, 6, -1}, {0, 3, -1}, {1, 6, -1}},
   {{0, 6, -1}, {1, 6, -1}, {-1, -1, 0}},
   {{-1, 7, 0}, {-1, 7, 0}, {-1, -1, 0}},
}; 

void printNumbersReverse(int *arr, int len){
   for(int i = len - 1; i >= 0; i--){
      printf("%d ", *(arr + i));
   }
}

void printNumbers(int *arr, int len){
   for(int i = 0; i<len; i++){
      printf("%d", *(arr + i));
   }
}

void printNumbersToM1(int *arr){
   for(int i = 0; *(arr + i) != -1; i++){
      printf("%d ", *(arr + i));
   }
}

void machine(int *tape, int state, int position){
    if(state == 7){
         printf("/n Stan bledu. To nie jest liczba wielocyfrowa! Koncze prace");
         return;
    }
   int currentValue = *(tape + position);
   int* output = transitions[state][currentValue];
   *(tape + position) = output[0];
   int nextState =  output[1];
   printf("\nObecny stan to q%d, obecna wartość pod głowicą: %d, położenie głowicy na taśmie: %d, zapisana wartość: %d", state, currentValue, position, output[0]);
   if(nextState == -1){
      printf("\nKoniec taśmy!");
      if(state == 6){
          printf("\nMaszyna zakonczyla dzialanie w stanie akceptujacym.");
      }
      return;
   }
   int nextPosition =  position - output[2];
   machine(tape, nextState, nextPosition);
}

void reverseArray(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}   

int main() {
   int n;
   int *numbers;
   printf("Podaj liczbę cyfr:");
   scanf("%d", &n);
   //Rezerwacja pamięci na taśmę
   //Rezeruje dodatkowe 2 miejsca na przeniesienia oraz 1 miejsce na znak konca tasmy
   numbers = malloc((n + 3) * sizeof(*numbers));
   printf("Podaj liczbę przedzieloną spacjami:");
   for (int i=0; i<n; i++){
      scanf("%d", &numbers[i]);
   }
   printf("\nNormalne\n");
   printNumbers(numbers, n + 3);
   //Odwracam tablicę, maszyna czyta taśmę od prawej strony
   reverseArray(numbers, 0, n - 1);
   printf("\nOdwrocone\n");
   printNumbers(numbers, n + 3);
   //Symbol theta - koniec liczby
   numbers[n + 2] = 2;
   printf("\nTheta\n");
   printNumbers(numbers, n + 3);
   //Początkowe położenie głowicy
   int position = 0;
   printf("\nUruchamiam maszynę\n");
   printNumbers(numbers, n + 3);
   machine(numbers, 0, position);
   reverseArray(numbers, 0, n + 1);
   printf("\nWynik to ");
   printNumbersToM1(numbers);
   return 0;
}




