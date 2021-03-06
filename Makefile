LIB = lib$(LIBNAME).a
OBJECTS = $(SOURCES:.c=.o)

LIBNAME = emret
INC_SUBDIR = include

.PHONY: all clean

include sources.mk

all: $(LIB)

clean:
	-rm $(OBJECTS) $(LIB)

COMBINED_CFLAGS= $(CPPFLAGS) $(CFLAGS)
AUG_CFLAGS = $(COMBINED_CFLAGS) -I $(INC_SUBDIR) -I .

.c.o:
	$(CC) $(AUG_CFLAGS) -c $<

$(LIB): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

include dependencies.mk

# Rules not required for just building the application.
include lib_maintainer.mk
