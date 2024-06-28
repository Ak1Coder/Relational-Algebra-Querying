CXX=g++
LD=g++

CXXFLAGS=-Wall -pedantic -Wextra -std=c++17
LDFLAGS=-fsanitize=address 

TARGET=lapundav

SRCDIR = src
DOCDIR = doc
BUILDDIR = build

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(SRCDIR)/*.h)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: compile doc

compile: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)/* $(TARGET) $(DOCDIR)/* Makefile.d

run: $(TARGET)
	./$(TARGET)

doc: doc/index.html

doc/index.html: $(HEADERS) $(SOURCES) Doxyfile
	doxygen Doxyfile

-include Makefile.d

Makefile.d: $(SOURCES) $(HEADERS)
	$(CXX) -MM $(SOURCES) > Makefile.d
	