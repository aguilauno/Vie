# Makefile para aplicacion "MiCuento"
CFLAGS	=
CC	= gcc
OBJS	= MiCuento.o funciones.o
GDB	= -ggdb

MiCuento:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@ 

MiCuento.o:		MiCuento.c funciones.h Makefile
		$(CC) $(CFLAGS) $(GDB) -c MiCuento.c

funciones.o:	funciones.c funciones.h Makefile
		$(CC) $(CFLAGS) $(GDB) -c funciones.c

clean:
		/bin/rm *.o MiCuento	