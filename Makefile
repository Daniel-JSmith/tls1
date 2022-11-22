cflags := -g -O2
lflags := -g -O2 -lglfw3 -lgdi32
includeDirs := include
libDirs:= lib

sources := $(wildcard source/*.cpp)
objects := $(patsubst source/%.cpp,build/%.o,$(sources))

$(shell mkdir build)

out.exe: $(objects)
	g++ -I $(includeDirs) -L $(libDirs) $(objects) -o build/out.exe $(lflags)

build/%.o : source/%.cpp
	g++ -c -I $(includeDirs) -L $(libDirs) $< -o $@ $(cflags)
