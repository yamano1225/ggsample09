CPPFLAGS	= -I/usr/X11R6/include -DX11 -Wall
LDLIBS	= -L/usr/X11R6/lib -lglut -lGLU -lGL -lm
OBJECTS	= $(subst .cpp,.o,$(wildcard *.cpp))
TARGET	= ggsample09

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	-rm -f $(TARGET) *.o *~ core

main.o:	gg.h matrix.h
gg.o: gg.h
matrix.o: gg.h matrix.h
