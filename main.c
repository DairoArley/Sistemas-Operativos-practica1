#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAXIMA_LONGITUD_CADENA 50

int main (int argc, char *argv[]) {
    if(argc < 2){
      printf("Debe ingresar al menos un parametro\n");
    }else if (argc > 2){
        if(strcmp(argv[1], "-l") == 0 ){
          char pidP[MAXIMA_LONGITUD_CADENA];
          printf("-- Información recolectada!!!");
          for (int i = 2; i < argc; i++ ){
            strcpy(pidP, "/proc/");
            strcat(pidP, argv[i]);
            strcat(pidP, "/status");

            FILE* fichero = fopen(pidP, "r");
            if (!fichero) {
              printf("\nError de apertura del archivo, proceso inexistente %s \n\n", pidP);
            }else{
                char state, name[32];
                int pid;
                fscanf(fichero, "%s %s %d",&state, name, &pid);
                printf("Nombre del proceso: %s \nEstado: %c \nPid: %d \n", name, state, pid);
                fclose(fichero);
            }
            strcpy(pidP, "");
          }
        }else if(strcmp(argv[1], "-r") == 0 ){
          char pidP[MAXIMA_LONGITUD_CADENA];
          FILE* ficheroEscri;
          char nombreArch[30];
          strcpy(nombreArch,"psinfo-report-" );
          strcat(nombreArch, argv[2]);
          strcat(nombreArch, ".info");
          ficheroEscri = fopen(nombreArch,"w");
          for (int i = 2; i < argc; i++ ){
            strcpy(pidP, "/proc/");
            strcat(pidP, argv[i]);
            strcat(pidP, "/status");

            FILE* fichero = fopen(pidP, "r");
            if (!fichero) {
              printf("\nError de apertura del archivo %s \n\n", pidP);
              return 0;
            }else{
                char state, name[32];
                int pid;
                fscanf(fichero, "%s %s %d",&state, name, &pid);
                fprintf(ficheroEscri, "Nombre del proceso: %s \nEstado: %d \nPid: %d \n\n\n", name, state, pid);

                printf("Nombre del proceso: %s \nEstado: %d \nPid: %d \n", name, state, pid);
            }
            fclose(fichero);
            strcpy(pidP, "");
          }
          fclose(ficheroEscri);
          //
        }else printf("\nflags no permitido, piensalo bien\n\n");
    }else{
      char str[MAXIMA_LONGITUD_CADENA];
      strcpy(str, "/proc/");
      strcat(str, argv[1]);
      strcat(str, "/status");
      FILE* fichero = fopen(str, "r");
      if (!fichero) {
        printf("\nError de apertura del archivo, proceso inexistente \n\n");
      }else{
          char state, name[32];
          int VmPeak, VmData, VmStk, VmExe, voluntary_context_switches, nonvoluntary_context_switches;
          fscanf(fichero, "%s %s %d %d %d %d %d %d",&state, name, &VmPeak, &VmData, &VmStk, &VmExe,
           &voluntary_context_switches, &nonvoluntary_context_switches);
           printf("Nombre del proceso: %s \nEstado: %c \nTamaño total de la imagen de memoria: %d \nTamaño de la memoria en la región TEXT: %d \nTamaño de la memoria en la región DATA: %d \nTamaño de la memoria en la región STACK: %d \nNúmero de cambios de contexto realizados (voluntarios - no voluntarios): %d - %d\n", 
           name, state, VmPeak, VmData, VmStk, VmExe, voluntary_context_switches,nonvoluntary_context_switches );
          fclose(fichero);
          return 0;
      }
    }
    return 0;
}
