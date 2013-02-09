SRCDIR = src
INCDIR = include
LIBDIR = lib
CPP = g++
UPX = upx -qq

#CFLAGS = -O2 -s -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod
#CFLAGS = -O2 -s -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -DDEV
CFLAGS = -O0 -g -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -DDEV

# Determine if operating system is 32-bit or 64-bit
ifeq ($(shell uname -m),x86_64)

	# These are the definitions specific to 64-bit systems
	LFLAGS = -L$(LIBDIR)/x86_64 -ltcod -ltcodxx -lm -Wl,-rpath=$(LIBDIR)/x86_64

else

	# These are the definitions specific to 32-bit systems
	LFLAGS = -L$(LIBDIR)/i386 -ltcod -ltcodxx -lm -Wl,-rpath=$(LIBDIR)/i386

endif

.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

HEADERS = $(wildcard $(INCDIR)/tsc/*.hpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: tsc

tsc: $(HEADERS) $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $@ $(LFLAGS)
	rm -f $(OBJECTS)
#	$(UPX) $@

clean:
	rm -f $(OBJECTS)
	rm -f tsc
