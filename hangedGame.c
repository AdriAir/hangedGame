#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <locale.h>

main()
{
    //Declaracion de variables
    FILE *file;              //Contendrá el archivo con las palabras ocultas.
    int i = 0;               //Iterador/contador.
    int length = 0;          //Cantidad de letras de la cadena.
    int remainingChars = 0;  //Cuenta los caracteres que faltan para adivinar la palabra.
    int lifes = 8;           //Vidas del jugador (empieza con 8).
    int lineJump = 0;        //Contador de saltos de linea.
    int wordLine = 0;        //Almacena la linea en la que leer la palabra a ocultar de dentro del archivo.
    int wasCorrect = 0;      //Dice si el carcater introducido por el usuario es correcto o no.
    int charHistoryCont = 0; //Guarda la posición de los caracteres del historial.
    int isInHistory = 0;     //Dice si la letra introducida está o no dentro del historial de caracteres.
    char lowBars[500];        //Barrabajas del colgado a mostrar en pantalla.
    char charReading;        //Guarda el caracter que se está leyendo del archivo.
    char word[500];          //Almacena la palabra a ocultar
    char userChar;           //Guarda el caracter introducido por el usuario.
    char charHistory[100];   //Almacena los caracteres ya usados.

    //Generación de aleatorios y adaptación de lenguaje y simbología.
    setlocale(LC_CTYPE, "Spanish"); //Idioma y simbología Española.
    srand(time(NULL));              //Generación de lista de numeros aleatorios en función del tiempo.

    //Obteción de palabra dentro de un archivo ".txt".
    if ((file = (fopen("words.txt", "r"))) == NULL) //Asignamos el archivo "colgado.txt" en file y lo abrimos como lectura.
    {
        printf("ERROR: No se ha encontrado el archivo...\n"); //Si no se encuentra el archivo, muestra ERROR.
        system("pause>nul");                                  //El usuario debe pulsar una tecla para continuar.
        return 0;                                             //Salir del programa si da error.
    }
    else
    {
        while (!feof(file)) //Mientras no se acabe el archivo...
        {
            charReading = fgetc(file); //Almacena el carcater que se está leyendo.
            if (charReading == '\n')   //Si el caracter almacenado es un salto de linea...
            {
                lineJump++; //Suma un salto de linea a lineJump.
            }
        }
        fclose(file); //Cerramos el archivo para poder reiniciar el lector a 0.
    }
    if ((file = (fopen("words.txt", "r"))) == NULL) //Abrimos el archivo dentro de "file" como lectura.
    {
        printf("ERROR 2: No se ha encontrado el archivo...\n"); //Si no se encuentra el archivo, muestra ERROR.
        system("pause>nul");                                    //El usuario debe pulsar una tecla para continuar.
        return 0;                                               //Salir del programa si da error.
    }
    else
    {
        rand() % lineJump;                //Generamos un número random dentro de 0 y lineJump y no lo usamos, pues el primer valor de la lista siempre se repite.
        wordLine = rand() % lineJump;     //Asignamos el número random para saber que linea del archivo leer.
        for (i = 0; i <= wordLine; i = i) //Mientras i no llegue a la linea wordLine...
        {
            charReading = fgetc(file); //Almacena el carcater que se está leyendo.
            if (charReading == '\n')   //Si es un salto de linea...
            {
                i++; //Suma 1 a i.
            }
        }
        i = 0; //Inicializamos i a 0.
        do
        {
            charReading = fgetc(file); //Almacena el carcater que se está leyendo.
            word[i] = charReading;     //Almacena el caracter en word[i].
            i++;                       //Suma 1 a i.
        } while (charReading != '\n'); //Mientras no se llegue al siguiente salto de linea, el programa guarda letra a letra la palabra oculta.
        strtok(word, "\n");            //Eliminamos el salto final de linea a word.
        fclose(file);                  //Cerramos el archivo.
    }

    //Comienzo del juego:
    length = strlen(word);       //Largaria de word.
    for (i = 0; i < length; i++) //Mientras i sea menos a lenght, i suma 1 y hace...
    {
        if (word[i] != ' ') //Si word[i] NO es un espacio...
        {
            lowBars[i] = '_'; //...lowBars[i] guarda una barra baja.
        }
        else //...Si no...
        {
            lowBars[i] = '\t'; //Al ser un espacio, se guarda una tabulación en lowBars[i].
        }
    }
    do
    {
        remainingChars = 0;          //Inicializamos los caracteres restantes a 0.
        system("cls");               //Limpieza de pantalla.
        for (i = 0; i < length; i++) //Mientras i sea menos a lenght, i suma 1 y hace...
        {
            if (lowBars[i] == '_') //Si lowBars[i] es una barrabaja, osea, contiene una letra...
            {
                remainingChars++; //Cuenta cuantos caracteres quedan en la palabra (igual que length, pero tendremos que modificarla mas adelante).
            }
        }
        if (remainingChars == 0) //Si no quedan caracteres por adivinar...
        {
            system("cls");            //Limpieza de pantalla.
            printf("¡Has ganado!\n"); //Muestra al jugador que ha ganado.
            printf("Pulsa una tecla para salir del juego...\n");
            system("pause>nul"); //Pausa.
            return 0;            //Sale del juego.
        }
        for (i = 0; i < length; i++) //Mientras i sea menos a lenght, i suma 1 y hace...
        {
            printf("%c ", lowBars[i]); //Imprime las barrabajas en pantalla.
        }
        printf("\n\nTienes %d vidas.\n", lifes); //Muestra al jugador cuantas vidas le quedan.
//        for (i = 0; i <= charHistoryCont; i++)
//        {
//            printf("%c, ", charHistory[i]); //Muestra los caracteres ya utilizados anteriormente.
//        }
        printf("Escribe una letra (Quedan %d): ", remainingChars); //Muetra al jugador cuantos caracteres le quedan por adivinar y le pide que introduzca un caracter.
        scanf("%c", &userChar);                                    //Almacena el caracter introducido por el usuario.
        fflush(stdin);                                             //Limpieza de la entrada de teclado (eliminación de conflictos a nivel de bit).
        wasCorrect = 0;                                            //Fijamos el valor wasCorrect en 0.
        for (i = 0; i < lowBars[i]; i++)                           //Mientras i sea menos a lenght, i suma 1 y hace...
        {
            if (word[i] == userChar) //Si el caracter del usuario coincide con algun caracter de la palabra oculta...
            {
                wasCorrect = 1;        //Decimos que es correcta.
                remainingChars--;      //Restamos un caracter a los que quedan.
                lowBars[i] = userChar; //Cambiamos lowBars[i]
            }
            if (charHistory[i] == userChar) //Si el historial contiene la letra del usuario...
            {
                isInHistory = 1; //Decimos que está en el historial.
            }
        }
        if (isInHistory == 1)
        {
            charHistory[charHistoryCont] = userChar;    //Guarda en charHistory[charHistoryCont] el caracter del usuario.
            charHistoryCont++; //Sumamos uno a la posición para el próximo caracter a añadir.
            isInHistory = 0;   //Volvemos a inicializar a 0 isInHistory.
        }
        else{
            isInHistory = 0;   //Inicializamos isInHistory a 0 por si acaso.
        }
        if (wasCorrect == 0) //Si wasCorrect es igual a 0...
        {
            lifes--; //Restamos una vida, pues significa que no hemos acertado ninguna.
        }
    } while (lifes > 0);                     //Mientras tengas vidas repite lo anterior.
    system("cls");                           //Limpieza de pantalla.
    printf("Te has quedado sin vidas...\n"); //Muestra al usuario que se ha quedado sin vidas.
    printf("La palabra era %s\n", word);     //Muesta al usuario cual era la palabra oculta.
    printf("Pulsa una tecla para salir...\n");
    system("pause>nul"); //Pausa.
}
