# 1. Nombre del programa resultante
TARGET := programa_compilado

# 2. Compilador y Flags
CXX      := g++
CXXFLAGS := -std=c++98 -Wall -Wextra

# 3. Detección automática (Busca en la carpeta actual)
# Busca todos los .cpp, .cxx o .cc
SOURCES  := $(wildcard *.cpp *.cxx *.cc)
# Crea los nombres de los archivos .o (objetos)
OBJECTS  := $(SOURCES:.cpp=.o)
OBJECTS  := $(OBJECTS:.cxx=.o)
OBJECTS  := $(OBJECTS:.cc=.o)

# 4. Reglas de compilación
.PHONY: all clean run

all: $(TARGET)

# Crea el ejecutable final
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "--------------------------------------------"
	@echo "Listo! Ejecutable creado como: ./$(TARGET)"
	@echo "--------------------------------------------"

# Regla para compilar cualquier .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 5. Utilidades rápidas
run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
	@echo "Archivos temporales eliminados."
