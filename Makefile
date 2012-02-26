CPPFLAGS	= -I/usr/X11R6/include -DX11 -Wall
LDLIBS	= -L/usr/X11R6/lib -lglut -lGLU -lGL -lm
OBJECTS	= $(subst .cpp,.o,$(wildcard *.cpp))
TARGET	= ggsample09

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	-rm -f $(TARGET) *.o *~ core

depend:
	makedepend -- $(CPPFLAGS) -- $(wildcard *.cpp)

# DO NOT DELETE

gg.o: Gg.h /usr/X11R6/include/GL/gl.h /usr/X11R6/include/GL/glext.h
gg.o: /usr/include/stddef.h /usr/include/_types.h /usr/include/sys/_types.h
gg.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
gg.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
gg.o: /usr/include/i386/_types.h /usr/include/inttypes.h
gg.o: /usr/include/stdint.h /usr/X11R6/include/GL/glu.h
gg.o: /usr/X11R6/include/GL/glx.h /usr/X11R6/include/X11/Xlib.h
gg.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
gg.o: /usr/include/machine/types.h /usr/include/i386/types.h
gg.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
gg.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
gg.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/sys/_structs.h
gg.o: /usr/X11R6/include/X11/X.h /usr/X11R6/include/X11/Xfuncproto.h
gg.o: /usr/X11R6/include/X11/Xosdefs.h /usr/X11R6/include/X11/Xutil.h
gg.o: /usr/X11R6/include/X11/keysym.h /usr/X11R6/include/X11/keysymdef.h
gg.o: /usr/X11R6/include/GL/glxext.h /usr/X11R6/include/GL/glut.h
main.o: gg.h /usr/X11R6/include/GL/gl.h /usr/X11R6/include/GL/glext.h
main.o: /usr/include/stddef.h /usr/include/_types.h /usr/include/sys/_types.h
main.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/inttypes.h
main.o: /usr/include/stdint.h /usr/X11R6/include/GL/glu.h
main.o: /usr/X11R6/include/GL/glx.h /usr/X11R6/include/X11/Xlib.h
main.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
main.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/sys/_structs.h
main.o: /usr/X11R6/include/X11/X.h /usr/X11R6/include/X11/Xfuncproto.h
main.o: /usr/X11R6/include/X11/Xosdefs.h /usr/X11R6/include/X11/Xutil.h
main.o: /usr/X11R6/include/X11/keysym.h /usr/X11R6/include/X11/keysymdef.h
main.o: /usr/X11R6/include/GL/glxext.h /usr/X11R6/include/GL/glut.h matrix.h
matrix.o: matrix.h gg.h /usr/X11R6/include/GL/gl.h
matrix.o: /usr/X11R6/include/GL/glext.h /usr/include/stddef.h
matrix.o: /usr/include/_types.h /usr/include/sys/_types.h
matrix.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
matrix.o: /usr/include/sys/_posix_availability.h
matrix.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
matrix.o: /usr/include/inttypes.h /usr/include/stdint.h
matrix.o: /usr/X11R6/include/GL/glu.h /usr/X11R6/include/GL/glx.h
matrix.o: /usr/X11R6/include/X11/Xlib.h /usr/include/sys/types.h
matrix.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
matrix.o: /usr/include/i386/types.h /usr/include/machine/endian.h
matrix.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
matrix.o: /usr/include/libkern/_OSByteOrder.h
matrix.o: /usr/include/libkern/i386/_OSByteOrder.h
matrix.o: /usr/include/sys/_structs.h /usr/X11R6/include/X11/X.h
matrix.o: /usr/X11R6/include/X11/Xfuncproto.h
matrix.o: /usr/X11R6/include/X11/Xosdefs.h /usr/X11R6/include/X11/Xutil.h
matrix.o: /usr/X11R6/include/X11/keysym.h /usr/X11R6/include/X11/keysymdef.h
matrix.o: /usr/X11R6/include/GL/glxext.h /usr/X11R6/include/GL/glut.h
