#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int blocksize = 1024;  //cada bloque tiene un tamaño de 1024 bytes

typedef struct
{
    int blocks; // (4)----- cantidad de bloques totales del archivo.
    int blocks_fe;  // (4) ------ bloques dedicados para los file entries
    int blocks_te; // (4) ------- bloques dedicados para los tag entries
}header; //(12)

typedef struct
{
    int pointer;	// (4)
    char filename[60];
}FE; //(64)

typedef struct
{
    char tag[28];
    int pointer;	// (4)
}TE;	//(32)

typedef struct
{
    int size_bytes;	//(4)
    int num_bloques;	//(4)
    unsigned int pointer_dir[12];	//(48)
    unsigned int pointer_indir;	//(4)
    unsigned int pointer_indir_dob;	//(4)
    unsigned int file_entry;	//(4)
    char tags_song[128];	//(128)
    char tags[250];	//(250)
}inodo; //(446)

void set_lista(int *lista)
{
    int i;
    for(i=0 ; i<256 ; i++)
        lista[i] = 0;
}

void remover_tag(char *tag, FILE *archivo, int pos, int fin, int pointer_inodo)
{
    fseek(archivo,pos,0);
    TE temp;
    int lista[256]={0};
    int i,j;


    for(i=0 ; i<fin ; i++)
    {
        fread(&temp,sizeof(TE),1,archivo);
        //printf("tag par: %s tag temp:%s\n",tag,temp.tag);
        if(strcmp(tag,temp.tag)==0)
        {
            fseek(archivo,temp.pointer,0);
            fread(&lista,blocksize,1,archivo);
            for(j=0 ; j<256 ; j++)
            {
                if(lista[j]==pointer_inodo)
                {
                    lista[j] = 0;
                    fseek(archivo,ftell(archivo)-blocksize,0);
                    fwrite(&lista,blocksize,1,archivo);
                    j=256;
                    i=fin;
                }
            }
        }
    }
}


//antes era int, ahora es void
void buscar_espacio_libre(int &pos_bit, int &pos_byte, int size_mapa_bits, unsigned char *mapa_bits)
{
    int j,k;
    for(j=pos_byte; j<size_mapa_bits; j++)
    {
        for(k=pos_bit; k<8; k++)
        {
            int valordelbit = mapa_bits[j] & (1<< (7-k));
            if(valordelbit == 0)
            {
                pos_byte = j;
                pos_bit = k;
                j=size_mapa_bits;
                k=8;
                mapa_bits[pos_byte] = mapa_bits[pos_byte] | (1 << (7-pos_bit));
            }
        }
        if(k==8)
            pos_bit=0;
    }
    //return (pos_bit + pos_byte*8)*blocksize;
}

void liberar_bloque(unsigned char *mapa_bits, int pos_pointer)
{
    int pos_byte = (pos_pointer/1024)/8;
    int pos_bit = (pos_pointer/1024)%8;

    mapa_bits[pos_byte] = mapa_bits[pos_byte] & ~(1 << (7-pos_bit));
}

int main(int argc, char *argv[])
{
    FILE *archivo;
    if(argc<3 || argc>6){
        printf("Error en parametros!!!");
        exit(1);
    }






    if(strcmp(argv[1],"-c")==0)
    {
        if((archivo = fopen(argv[5],"wb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        unsigned char *mapa_bits;
        FE file_entry;
        TE tag_entry;
        int i, fin; //i es para los ciclos for, fin se usa masa abajo en los ciclos for

        encabezado.blocks = atoi(argv[2]);
        encabezado.blocks_fe = atoi(argv[3]);
        encabezado.blocks_te = atoi(argv[4]);

        mapa_bits = (unsigned char *)malloc(encabezado.blocks/8);
        memset(mapa_bits,0,encabezado.blocks/8);


        //aqui se setea los 1 en el mapa de bits, o sea, el header, mapa de bits, FEs, y TEs
        fin = encabezado.blocks_fe + encabezado.blocks_te + 1 + (encabezado.blocks/8)/1024;
        for(i=0 ; i<(fin/8) ; i++)
        {
            mapa_bits[i] = 255;
        }
        if(fin%8 != 0)
        {
            int j, cual = fin%8 - 1;
            for(j=0 ; j<fin%8; j++)
            {
                mapa_bits[i] = mapa_bits[i] | (1 << (7-cual%8));
                cual--;
            }
        }

        //memset(file_entry.filename,' ',60);
        strcpy(file_entry.filename,"");
        file_entry.pointer = 0;

        //memset(tag_entry.tag,' ',28);
        strcpy(tag_entry.tag,"");
        tag_entry.pointer = 0;

        char *resto; //este sirve para escribir el resto de la data
        int size_resto = (encabezado.blocks-encabezado.blocks_fe-encabezado.blocks_te)*1024-(blocksize + encabezado.blocks/8);
        resto=(char *)malloc(size_resto);

        fwrite(&encabezado, sizeof(header), 1, archivo);
        fseek(archivo,blocksize,0);
        fwrite(mapa_bits,(encabezado.blocks/8),1,archivo);

        for(i=0;i<encabezado.blocks_fe*16;i++)
            fwrite(&file_entry,sizeof(FE),1,archivo);
        for(i=0;i<encabezado.blocks_te*32;i++)
            fwrite(&tag_entry,sizeof(TE),1,archivo);

        fwrite(resto,size_resto,1,archivo);

        fclose(archivo);
        free(resto);
        free(mapa_bits);
    }






else







    if(strcmp(argv[1],"-a")==0)
    {
        FILE *mp3;
        if((archivo = fopen(argv[3],"rb+"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }
        if((mp3 = fopen(argv[2],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo de musica.\n");
            exit(3);
        }
        fseek(mp3,0,2);	//colocar el cursor al final del archivo

        if(ftell(mp3)>67383296) //El archivo no puede ser mas grande que 64.26....  Mb
        {
            printf("Archivo demasiado grande.\n");
            exit(4);
        }
        inodo mimp3;
        mimp3.size_bytes = (int)ftell(mp3);
        mimp3.num_bloques = (mimp3.size_bytes%1024 == 0) ? mimp3.size_bytes/1024 : mimp3.size_bytes/1024 + 1;

        //printf("bloques %d\nsize %d\n",mimp3.num_bloques,mimp3.size_bytes);

        header encabezado;
        unsigned char *mapa_bits;
        FE file_entry;
        int i=0, j=0, encontro=0, pos_fe;
        int lista[256] = {0};
        int lista_indir[256] = {0};

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize,0);
        mapa_bits = (unsigned char *)malloc(encabezado.blocks/8);
        fread(mapa_bits,(encabezado.blocks/8),1,archivo);

        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(file_entry.pointer==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro==0)	//SI NO encontró file_entries disponibles, que termine el programa
        {
            printf("No hay mas entradas disponibles.");
            exit(5);
        }

        pos_fe = (int)ftell(archivo) - sizeof(FE);
        strcpy(file_entry.filename,argv[2]);	//copiar el nombre del archivo al file_entry
        //fseek(archivo,pos_fe,0);
        //fwrite(&file_entry,sizeof(FE),1,archivo);

        //AHORA: comenzar a copiar los bloques de datos en el disco.dat, utilizando el Mapa de Bits para saber donde copiar

        //primero crear el bloque que nos va a servir para copiar los datos
        unsigned char *copiar;
        copiar = (unsigned char*)malloc(blocksize);

        //despues, ubicarse en el mapa de bits en la posicion que representa el fin de los TEs
        int pos_byte = (1 + encabezado.blocks_te + encabezado.blocks_fe + (encabezado.blocks/8)/1024)/8;	//posicion del byte
        int pos_bit = (1 + encabezado.blocks_te + encabezado.blocks_fe + (encabezado.blocks/8)/1024)%8;	//posicion del bit
        if(pos_bit!=0)
                pos_bit--;

        buscar_espacio_libre(pos_bit,pos_byte,encabezado.blocks/8,mapa_bits);
        //espacio reservado para el inodo
        fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
        file_entry.pointer = (int)ftell(archivo);
        //fwrite(&mimp3,sizeof(inodo),1,archivo);

        fseek(mp3,0,0);
        int cont=0;

        for(i=0 ; i<mimp3.num_bloques ; i++)
        {
            buscar_espacio_libre(pos_bit,pos_byte,encabezado.blocks/8,mapa_bits);

            fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);


            if(i<12)
            {
                mimp3.pointer_dir[i] = (pos_bit+(pos_byte*8)) * blocksize;
                //printf("Pointer_dir %d\n",mimp3.pointer_dir[i]);
                fread(copiar, blocksize, 1, mp3);
                fwrite(copiar, blocksize, 1, archivo);
            }
            if(i>=12 && i<=268)
            {
                if(i==12)
                {
                    mimp3.pointer_indir = (int)ftell(archivo);
                    fwrite(&lista, blocksize, 1, archivo);

                    buscar_espacio_libre(pos_bit,pos_byte,encabezado.blocks/8,mapa_bits);
                    fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
                 }
                 lista[i-12] = (int)ftell(archivo);
                 fread(copiar, blocksize, 1, mp3);
                 fwrite(copiar, blocksize, 1, archivo);

             }
             if(i>=268)
             {
                if(i==268)
                {
                    mimp3.pointer_indir_dob = (int)ftell(archivo);
                    fwrite(&lista_indir,blocksize,1,archivo);

                    fseek(archivo,mimp3.pointer_indir,0);
                    fwrite(&lista, blocksize, 1, archivo);
                    set_lista(lista);

                    buscar_espacio_libre(pos_bit,pos_byte, encabezado.blocks/8,mapa_bits);
                    fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
                    lista_indir[cont] = (int)ftell(archivo);
                    fwrite(&lista,blocksize,1,archivo);
                    cont++;

                    buscar_espacio_libre(pos_bit,pos_byte, encabezado.blocks/8,mapa_bits);
                    fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
                }
                else
                    if((i-12)%256==0)
                    {
                        fseek(archivo,lista_indir[cont-1],0);
                        fwrite(&lista,blocksize,1,archivo);
                        set_lista(lista);

                        buscar_espacio_libre(pos_bit,pos_byte, encabezado.blocks/8,mapa_bits);
                        fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
                        lista_indir[cont] = (int)ftell(archivo);
                        fwrite(&lista,blocksize,1,archivo);
                        cont ++;

                        buscar_espacio_libre(pos_bit,pos_byte, encabezado.blocks/8,mapa_bits);
                        fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);

                    }

                lista[i - 12 - (i/256)*256] = (int)ftell(archivo);
                fread(copiar, blocksize, 1, mp3);
                fwrite(copiar, blocksize, 1, archivo);
            }

             pos_bit++;

            if(pos_bit==8){
                pos_byte++;
                pos_bit = 0;
            }
        }

        //Ya para terminar, hay que actualizar todo (mapa de bits, listas, inodo, etc...)

        //escribir mapa de bits
        fseek(archivo,blocksize,0);
        fwrite(mapa_bits,encabezado.blocks/8,1,archivo);

        //actualizar la ultima lista de apuntadores
        fseek(archivo,lista_indir[cont-1],0);
        fwrite(&lista,blocksize,1,archivo);

        //acualizar lalista doble indirecta
        fseek(archivo,mimp3.pointer_indir_dob,0);
        fwrite(&lista_indir,blocksize,1,archivo);

        //NOTA: me hizo falta agregar la info del mp3 al inodo
        fseek(mp3,-128,2);
        fread(&mimp3.tags_song,sizeof(char)*128,1,mp3);
        strcpy(mimp3.tags,"");

        //escribir el inodo
        fseek(archivo,file_entry.pointer,0);
        fwrite(&mimp3,sizeof(inodo),1,archivo);

        //escribit file entry
        fseek(archivo,pos_fe,0);
        fwrite(&file_entry,sizeof(FE),1,archivo);

       // printf("Pointer_indir %d\nPointer doble %d\n",mimp3.pointer_indir,mimp3.pointer_indir_dob);
        //printf("Pointer del inodo %d\n",file_entry.pointer);

        fclose(archivo);
        fclose(mp3);
        free(copiar);
        free(mapa_bits);

    }





else




    if(strcmp(argv[1],"-e")==0)
    {

        if((archivo = fopen(argv[4],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        FILE *mp3;
        int i=0, j=0, encontro=0;
        inodo imp3;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8, 0);

        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                //printf("Nombre %s   Pointer %d\n",file_entry.filename,file_entry.pointer);
                if(strcmp(argv[2],file_entry.filename)==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro==0)	//SI NO encontró file_entries disponibles, que termine el programa
        {
            printf("No se encontro ese el archivo mp3 en el disco\n");
            //system("pause");
            exit(6);
        }

        int lista[256] = {0};
        int lista_indir[256] = {0};
        fseek(archivo,file_entry.pointer,0);
        fread(&imp3,sizeof(inodo),1,archivo);


        if((mp3 = fopen(argv[3],"wb"))==NULL)
        {
            printf("No se pudo abrir el archivo destino.\n");
            exit(2);
        }

        unsigned char *copiar;
        copiar = (unsigned char*)malloc(blocksize);

        int cont = 0;

        //printf("Pointer_indir %d\nPointer doble %d\n",imp3.pointer_indir,imp3.pointer_indir_dob);
        //printf("Pointer del inodo %d\n",file_entry.pointer);
        //printf("Numero de bloques %d\n",imp3.num_bloques);
        for(i=0 ; i<imp3.num_bloques-1 ; i++)
        {
            if(i<12)
            {
                fseek(archivo,imp3.pointer_dir[i],0);
                fread(copiar,blocksize,1,archivo);
                fwrite(copiar,blocksize,1,mp3);
            }

            if(i>=12 && i<268)
            {
                if(i==12)
                {
                    fseek(archivo,imp3.pointer_indir,0);
                    fread(&lista,blocksize,1,archivo);
                }

                fseek(archivo, lista[i-12],0);
                fread(copiar,blocksize,1,archivo);
                fwrite(copiar,blocksize,1,mp3);
            }
            if(i>=268)
            {
                if(i==268)
                {
                    fseek(archivo,imp3.pointer_indir_dob,0);
                    fread(&lista_indir,blocksize,1,archivo);
                }
                if((i-12)%256 == 0)
                {
                    fseek(archivo, lista_indir[cont], 0);
                    fread(&lista,blocksize,1,archivo);
                    cont++;
                }
                fseek(archivo,lista[i-12-(i/256)*256],0);
                fread(copiar,blocksize,1,archivo);
                fwrite(copiar,blocksize,1,mp3);
            }
        }


        unsigned char *resto;
        int iresto = imp3.size_bytes - (i)*blocksize;
        resto = (unsigned char*)malloc( iresto);
        fread(copiar,iresto,1,archivo);
        fwrite(copiar,iresto,1,mp3);

        fclose(archivo);
        fclose(mp3);
        free(resto);
        free(copiar);


    }


else



    if(strcmp(argv[1],"-q")==0)
    {
        if((archivo = fopen(argv[3],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        int i=0, j=0;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8, 0);

        for(i=0 ; i<encabezado.blocks_fe; i++)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(strcmp(argv[2],file_entry.filename)==0)
                {
                    printf("-q:%d",file_entry.pointer);
                    fclose(archivo);
                    return 0;
                }
            }
        }
    }




else


    //OPCIONAL: Validar si ya no caben tags en el tags_song[250]
    if(strcmp(argv[1],"-t")==0)
    {
        if((archivo = fopen(argv[4],"rb+"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        TE tag_entry;
        inodo imp3;
        unsigned char *mapa_bits;
        int i=0, j=0, encontro=0, termino=0, pos_bit, pos_byte;
        int lista[256] = {0};

        fread(&encabezado,sizeof(header),1,archivo);

        mapa_bits = (unsigned char*)malloc(encabezado.blocks/8);
        fseek(archivo,blocksize,0);
        fread(mapa_bits,encabezado.blocks/8,1,archivo);

        //buscar si el archivo existe
        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(strcmp(argv[3],file_entry.filename)==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro==0)	//SI NO encontró file_entries disponibles, que termine el programa
        {
            printf("No se encontro ese el archivo mp3 en el disco\n");
            exit(6);
        }

        i=0; encontro=0;
        fseek(archivo, blocksize + (encabezado.blocks/8) + (blocksize*encabezado.blocks_fe),0);

        //buscar si el tag YA existe
        while(encontro==0 && i<encabezado.blocks_te)
        {
            for(j=0; j<32 ; j++)
            {
                fread(&tag_entry, sizeof(TE),1,archivo);
                if(strcmp(argv[2],tag_entry.tag)==0)
                {
                    encontro=1;
                    j=32;
                }
            }
            i++;
        }

        int pos_te;
        pos_byte = (1 + encabezado.blocks_te + encabezado.blocks_fe + (encabezado.blocks/8)/1024)/8;
        pos_bit = (1 + encabezado.blocks_te + encabezado.blocks_fe + (encabezado.blocks/8)/1024)%8;

        if(encontro==0)
        {
            //como no lo encontro, buscar el primer TE disponible
            fseek(archivo, blocksize + (encabezado.blocks/8) + (blocksize * encabezado.blocks_fe),0);
            i=0;
            while(encontro==0 && i<encabezado.blocks_te)
            {
                for(j=0; j<32 ; j++)
                {
                    fread(&tag_entry, sizeof(TE),1,archivo);
                    if(tag_entry.pointer==0)
                    {
                        encontro=1;
                        j=32;
                    }
                }
                i++;
            }

            pos_te = (int) ftell(archivo)-sizeof(TE);

            buscar_espacio_libre(pos_bit,pos_byte,encabezado.blocks/8,mapa_bits);
            fseek(archivo,(pos_bit+(pos_byte*8)) * blocksize,0);
            //printf("La lista de pointers se escribio en: %d\n",ftell(archivo));

            strcpy(tag_entry.tag,argv[2]);
            tag_entry.pointer = (int)ftell(archivo);

            lista[0] = file_entry.pointer;
            fwrite(&lista,blocksize,1,archivo);
            termino=1;

        }
        else
        {
            pos_te = (int)ftell(archivo)-sizeof(TE);
            fseek(archivo,tag_entry.pointer,0);
            fread(&lista,blocksize,1,archivo);
            for(i=0 ; i<256; i++)
            {
                if(lista[i]==0)
                {
                    termino=1;
                    lista[i]=file_entry.pointer;
                    fseek(archivo,tag_entry.pointer,0);
                    fwrite(&lista,blocksize,1,archivo);
                    i=255;
                }
            }
            if(termino==0)
            {
                printf("Ya no se puede tagear mas canciones con este Tag\n");
                exit(7);
            }
        }

        //si escribio bien el tag
        if(termino==1)
        {
            fseek(archivo,blocksize,0);
            fwrite(mapa_bits,encabezado.blocks/8,1,archivo);

            fseek(archivo,file_entry.pointer,0);
            fread(&imp3,sizeof(inodo),1,archivo);

            char tag[128];
            strcpy(tag,tag_entry.tag);
            strcat(tag,",");

            strcat(imp3.tags,tag);

            fseek(archivo,file_entry.pointer,0);
            fwrite(&imp3,sizeof(inodo),1,archivo);
        }

        fseek(archivo,pos_te,0);
        fwrite(&tag_entry,sizeof(TE),1,archivo);

        fclose(archivo);
        free(mapa_bits);



    }


else


    //Aqui hay un error bien raro en Linux :S




    if(strcmp(argv[1],"-it")==0)
    {

        if((archivo = fopen(argv[3],"rb+"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        inodo imp3;
        int i=0, j=0, encontro=0;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8,0);

        //buscar si el archivo existe
        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(strcmp(argv[2],file_entry.filename)==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro==0)	//SI NO encontró file_entries disponibles, que termine el programa
        {
            printf("No se encontro ese el archivo mp3 en el disco\n");
            exit(6);
        }

        fseek(archivo,file_entry.pointer,0);
        fread(&imp3,sizeof(imp3),1,archivo);

        printf("-it:%s\n",imp3.tags_song);

        fclose(archivo);
    }




else




    if(strcmp(argv[1],"-s")==0)
    {
        if((archivo = fopen(argv[3],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        int i=0, j=0, encontro=0, lista[256];
        TE tag_entry;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + (encabezado.blocks/8) + (encabezado.blocks_fe*blocksize),0);

        while(encontro==0 && i<encabezado.blocks_te)
        {
            for(j=0; j<32 ; j++)
            {
                fread(&tag_entry, sizeof(TE),1,archivo);
                if(strcmp(argv[2],tag_entry.tag)==0)
                {
                    encontro=1;
                    j=32;
                }
            }
            i++;
        }


        if(encontro == 0)
        {
            printf("NO se encontre el tag!");
            exit(7);
        }

        fseek(archivo,tag_entry.pointer,0);
        fread(&lista,blocksize,1, archivo);

        printf("-s:");
        for(i=0 ; i<256 ; i++)
        {
            if(lista[i]!=0)
                printf("%d,",lista[i]);
        }
        printf("\n");

        fclose(archivo);

    }



else




    // mfs -qa cancion.mp3 disco.dat
    //revisar
    if(strcmp(argv[1],"-qa")==0)
    {
        if((archivo = fopen(argv[3],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        inodo imp3;
        int i=0, j=0, encontro=0;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8,0);

        //buscar si el archivo existe
        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(strcmp(argv[2],file_entry.filename)==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro == 0)
        {
            printf("NO se encontre el tag!");
            exit(7);
        }

        fseek(archivo,file_entry.pointer,0);
        fread(&imp3,sizeof(inodo),1,archivo);

        printf("-qa:%s\n",imp3.tags_song);

        fclose(archivo);


    }



else




    //TODO

    //se utilizo burbuja, revisar
    if(strcmp(argv[1],"-l")==0)
    {

        if((archivo = fopen(argv[2],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        int i=0, j=0, cont=0, encontro=0;

        fread(&encabezado,sizeof(header),1,archivo);
        TE temp;
        TE arreglo[encabezado.blocks_te*32];

        fseek(archivo,blocksize + encabezado.blocks/8 + (encabezado.blocks_fe*blocksize),0);

        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<32 ; j++)
            {
                fread(&temp, sizeof(TE),1,archivo);
                if(temp.pointer==0)
                {
                    encontro=1;
                    j=32;
                }
                else
                {
                    arreglo[cont]=temp;
                }
                cont++;
            }
            i++;
        }

        for(i=0 ; i<cont-2 ; i++)
        {
            for(j=i+1 ; j<cont-1 ; j++)
            {
                if(strcmp(arreglo[i].tag,arreglo[j].tag)==1)
                {
                    TE temp = arreglo[j];
                    arreglo[j]=arreglo[i];
                    arreglo[i]=temp;
                }
            }
        }

        /*for(i=0 ; i<cont-1 ; i++)
        {
            for(j=i+1 ; j<cont ; j++)
            {
                if(strcmp(arreglo[j].tag,arreglo[i].tag)==-1)
                {
                    TE temp = arreglo[i];
                    arreglo[i]=arreglo[j];
                    arreglo[j]=temp;
                }
            }
        }*/

        printf("-l:");
        for(i=0 ; i<cont-1 ; i++)
            printf("%s,",arreglo[i].tag);

        printf("\n");
        fclose(archivo);

    }


else


    if(strcmp(argv[1],"-lf")==0)
    {
        if((archivo = fopen(argv[2],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        int i=0, j=0;
        FE file_entry;
        //char *out="";

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8, 0);

        printf("-lf:");
        while(i<encabezado.blocks_fe)
        {
            for(j=0 ; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(file_entry.pointer!=0)
                {
                    printf("%s,",file_entry.filename);
                    //strcat(out,file_entry.filename);
                    //strcat(out,",");
                }
            }
            i++;
        }

        printf("\n");
        //printf("%s",out);
        fclose(archivo);
    }


else



    if(strcmp(argv[1],"-d")==0)
    {
        if((archivo = fopen(argv[3],"rb+"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        unsigned char *mapa_bits;
        FE file_entry;
        inodo imp3;
        int i=0, j=0;
        int encontro=0, pos_fe=0, cont=0;
        int lista[256] = {0};
        int lista_indirecta[256] = {0};


        fread(&encabezado,sizeof(header),1,archivo);
        mapa_bits = (unsigned char*)malloc(encabezado.blocks/8);
        fseek(archivo,blocksize,0);
        fread(mapa_bits,encabezado.blocks/8,1,archivo);

        //buscar si el archivo existe
        while(encontro==0 && i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(strcmp(argv[2],file_entry.filename)==0)
                {
                    encontro=1;
                    j=16;
                }
            }
            i++;
        }

        if(encontro == 0)
        {
            printf("NO se encontre el FE!");
            exit(7);
        }

        pos_fe = (int) ftell(archivo) - sizeof(FE);

        fseek(archivo,file_entry.pointer,0);
        //printf("Pointer del inodo %d\n",file_entry.pointer);
        fread(&imp3,sizeof(inodo),1,archivo);
        liberar_bloque(mapa_bits,file_entry.pointer);


        for(i=0 ; i<imp3.num_bloques ; i++)
        {
            if(i<12)
            {
                liberar_bloque(mapa_bits,imp3.pointer_dir[i]);
                //printf("Pointer_dir %d\n",imp3.pointer_dir[i]);
            }

            if(i==12)
            {
                fseek(archivo,imp3.pointer_indir,0);
                fread(&lista,blocksize,1,archivo);
                //printf("Pointer_indir %d\nPointer doble %d\n",imp3.pointer_indir,imp3.pointer_indir_dob);
                liberar_bloque(mapa_bits,imp3.pointer_indir);
            }

            if(i>=12 && i<268)
                liberar_bloque(mapa_bits,lista[i-12]);

            if(i==268)
            {
                fseek(archivo,imp3.pointer_indir_dob,0);
                fread(&lista_indirecta,blocksize,1,archivo);
                liberar_bloque(mapa_bits,imp3.pointer_indir_dob);
            }

            if(i>268)
            {
                if((i-12)%256 == 0)
                {
                    fseek(archivo,lista_indirecta[cont],0);
                    fread(&lista,blocksize,1,archivo);
                    liberar_bloque(mapa_bits,lista_indirecta[cont]);
                    cont++;
                }
                liberar_bloque(mapa_bits,lista[i - 12 - ((i/256)*256)]);
            }
        }

        //actualizar mapa de bits
        fseek(archivo,blocksize,0);
        fwrite(mapa_bits,encabezado.blocks/8,1,archivo);

        //actualizar tags
        char lista_tags[128];
        strcpy(lista_tags,imp3.tags);

        char *tag;
        int pos_TE = blocksize + (encabezado.blocks/8) + (encabezado.blocks_fe)*blocksize;
        tag = strtok(lista_tags,",");

        while(tag!=NULL)
        {
            remover_tag(tag,archivo,pos_TE,encabezado.blocks_te*32,file_entry.pointer);
            tag = strtok(NULL,",");
        }

        //actualizar tags
        memset(file_entry.filename,' ',60);
        file_entry.pointer = 0;

        fseek(archivo,pos_fe,0);
        fwrite(&file_entry,sizeof(FE),1,archivo);

        fclose(archivo);
        free(mapa_bits);


    }


else


    if(strcmp(argv[1],"-ss")==0)
    {
        if((archivo = fopen(argv[3],"rb"))==NULL)
        {
            printf("No se pudo abrir el archivo origen.\n");
            exit(2);
        }

        header encabezado;
        FE file_entry;
        int i=0, j=0;

        fread(&encabezado,sizeof(header),1,archivo);
        fseek(archivo,blocksize + encabezado.blocks/8, 0);

        while(i<encabezado.blocks_fe)
        {
            for(j=0; j<16 ; j++)
            {
                fread(&file_entry, sizeof(FE),1,archivo);
                if(file_entry.pointer == atoi(argv[2]))
                {
                    i=encabezado.blocks_fe;
                    j=16;
                    printf("-ss:%s",file_entry.filename);
                }
            }
            i++;
        }
        printf("\n");
        fclose(archivo);
    }




else
{

    printf("Comando Incorrecto\n");
    return 9;
}

  //  system("pause");

    return 0;
}
