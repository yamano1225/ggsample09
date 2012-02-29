CXXFLAGS	= -I/usr/X11R6/include -DX11 -Wall
LDLIBS	= -L/usr/X11R6/lib -lglut -lGLU -lGL -lm
OBJECTS	= $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET	= ggsample09

.PHONY: clean depend

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	-$(RM) -f $(TARGET) *.o *~ core

depend:
	$(CXX) $(CXXFLAGS) -MM *.cpp > $(TARGET).d

-include $(wildcard *.d)
