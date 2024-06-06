//Bayron Sebastian Jojoa Rosero 2242917
//Alejandro Muñoz Guerrero 2242951

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

typedef struct {
   int id;
} Rango;

int inicio;
int fin;
int numH = 4;


// Función para verificar si un número es primo
int es_primo(int num) {
   if (num <= 1) return 0;
   if (num == 2) return 1;
   if (num % 2 == 0) return 0;
   for (int i = 3; i <= sqrt(num); i += 2) {
       if (num % i == 0) return 0;
   }
   return 1;
}


// Función del hilo para verificar números primos en un rango dado
void* verificar_primo(void* arg) {
   Rango* rango = (Rango*)arg;
   int counter = 0;
   clock_t inicio_tiempo = clock();

   for (int i = inicio + rango->id; i <= fin; i += numH) {
       if (es_primo(i)) {
           counter++;
       }
   }

   clock_t fin_tiempo = clock();
   double tiempo_total = (double)(fin_tiempo - inicio_tiempo) / CLOCKS_PER_SEC;

  printf("Hilo %d encontró %d primos en %f segundos.\n", rango->id, counter, tiempo_total);   return NULL;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
       inicio = atoi(argv[1]);
       fin = atoi(argv[2]);
       numH = atoi(argv[3]);
   }

   pthread_t hilos[numH];
   Rango rangos[numH];


   // Crear hilos
   for (int i = 0; i < numH; i++) {
       rangos[i].id = i;
       if (pthread_create(&hilos[i], NULL, verificar_primo, &rangos[i]) != 0) {
           perror("Error al crear el hilo");
           return 1;
       }
   }
   // Unir hilos
   for (int i = 0; i < numH; i++) {
       pthread_join(hilos[i], NULL);
   }
   return 0;
}



