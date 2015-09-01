# Author: Daniel Cotter

DESTDIR 	=	/usr
LIBDIR 		=	$(DESTDIR)/lib
INCLUDEDIR	= 	$(DESTDIR)/include/libserver
OBJSDIR 	=	src
HEADERSDIR	=	headers
OBJS 		=	$(patsubst %.cpp,%.o,$(wildcard $(OBJSDIR)/**/*.cpp))
HEADERDIRS	=	$(addprefix -I, $(sort $(dir $(wildcard $(OBJSDIR)/**/$(HEADERSDIR)/*.h))))

CXX 		=	g++
CXXFLAGS 	=	$(HEADERDIRS) -std=c++0x -O3 -Wall
LDFLAGS 	=	-pthread

TARGET 		=	libserver.a

$(TARGET):	$(OBJS)
	ar crf $(TARGET) $(OBJS)
	ranlib $(TARGET)
	
all:
	$(TARGET)
	
install:
	mkdir -p $(INCLUDEDIR)
	cp $(TARGET) $(LIBDIR)
	cp -R include/* $(INCLUDEDIR)
	
uninstall:
	rm -rf $(INCLUDEDIR)
	rm -f $(LIBDIR)/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)