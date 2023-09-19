# Nome do executável
EXECUTABLE = rpg_loja

# Compiladores
CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++
CXX = $(CXX_LINUX)

# Flags de compilação
CFLAGS = -std=c++20 -Wall -pthread
LDFLAGS = 

# Diretórios
SOURCE_FOLDER = .
DIALOG_FOLDER = Dialog
LOJA_FOLDER = Loja

# Fontes
SOURCES = $(wildcard $(SOURCE_FOLDER)/*.cpp $(SOURCE_FOLDER)/$(DIALOG_FOLDER)/*.cpp $(SOURCE_FOLDER)/$(LOJA_FOLDER)/*.cpp)
DIALOG_SOURCES_LINUX = $(wildcard $(DIALOG_FOLDER)/Linux/*.cpp)
DIALOG_SOURCES_WINDOWS = $(wildcard $(DIALOG_FOLDER)/Windows/*.cpp)

# Objetos
DIALOG_OBJECTS_LINUX = $(DIALOG_SOURCES_LINUX:.cpp=.o)
DIALOG_OBJECTS_WINDOWS = $(DIALOG_SOURCES_WINDOWS:.cpp=.o)
OTHER_OBJECTS = $(SOURCES:.cpp=.o)

# Objetos específicos para cada ambiente
OBJECTS_LINUX = $(DIALOG_OBJECTS_LINUX) $(OTHER_OBJECTS)
OBJECTS_WINDOWS = $(DIALOG_OBJECTS_WINDOWS) $(OTHER_OBJECTS)

# Regra de compilação para objetos
%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# Regra de compilação padrão
all: $(EXECUTABLE)

# Regra de construção do executável
$(EXECUTABLE): $(OBJECTS_LINUX)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS_LINUX) $(LDFLAGS)

# Regra de compilação para o ambiente Windows
windows: CXX = $(CXX_WINDOWS)
windows: CFLAGS += -static-libgcc -static-libstdc++ # -static
windows: LDFLAGS += -Wl,-Bstatic -lpthread -Wl,-Bdynamic -lstdc++fs -lmingw32
windows: $(EXECUTABLE).exe

# Regra de construção do executável para o ambiente Windows
$(EXECUTABLE).exe: $(OBJECTS_WINDOWS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS_WINDOWS) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE).exe $(OBJECTS_LINUX) $(OBJECTS_WINDOWS)

.PHONY: all windows clean
