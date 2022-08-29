# C Compiler
CC= gcc

# Check if Unix or Windows
ifeq (OS, Windows_NT)
	CLEAN=rm -f *.o *.d *~ $(TARGET)
else
	CLEAN=del *.o *.d *~ $(TARGET).exe 
endif

# Header Directory
#	 Example 1 : If Makefile resides in ..Project and header files reside in ..Project, then value here would be left empty
#	 Example 2 : If Makefile resides in ..Project and header files reside in ..Project/headers, then value here would be "-Iheaders" without quotes
#	 Example 3 : If Makefile resides in ..Project/src and header files reside in ..Project/headers, then value here would be "-I../headers" without quotes
HDIR= -I../headers

# Source Directory
#	 Example 1 : If Makefile resides in ..Project and source files reside in ..Project/src, then value here would be "-Isrc" without quotes
#	 Example 2 : If Makefile resides in ..Project/src and source files reside in ..Project/src, then value here would be left empty
SRCDIR=

# Link Libraries
#	 -lm       : Link with libm
#	 -lpthread : Link with libpthread
#	 -lrt      : Link with librt
LINKLIBS=

# Compiler Flags
#	 -g      : adds debugging information to the executable file
#	 -Wall   : turns on most, but not all, compiler warnings
#	 -Wextra : turns on some, but not all, compiler warnings not controlled by -Wall
#	 -Werror : makes all warnings into errors
CFLAGS= -g -Wall  ${HDIR} ${SRCDIR}

# Name of Build Target
TARGET= main

# C Files
CFILES= main.c bitops.c

# Object Files
OBJS= ${CFILES:.c=.o}

# The first target entry in this file to be invoked when typing "make". Convention is to use "all" or "default" here
all: $(TARGET)

# To create the executable, we need all object files
$(TARGET): ${OBJS}
	$(CC) $(CFLAGS) -o $(TARGET) ${OBJS} ${LINKLIBS}

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(CLEAN)