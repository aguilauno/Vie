# Makefile para aplicacion "MiCuento"
CC	= gcc
OBJS	= MiCuento.o funciones.o
GDB	= -ggdb

MiCuento:	$(OBJS)
		$(CC) $(OBJS) -o $@ 

MiCuento.o:		MiCuento.c funciones.h Makefile
		$(CC) $(GDB) -c MiCuento.c

funciones.o:	funciones.c funciones.h Makefile
		$(CC) $(GDB) -c funciones.c

clean:
		/bin/rm *.o MiCuento	