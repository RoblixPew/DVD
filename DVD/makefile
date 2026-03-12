CXX = g++
# Aggiungiamo -mwindows per evitare che si apra la console nera dietro l'app
CXXFLAGS = `wx-config --cxxflags` -std=c++17
LDFLAGS = `wx-config --libs` -mwindows

# Tool per compilare le risorse di Windows
WINDRES = windres

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
# Aggiungiamo l'oggetto delle risorse
RES_OBJ = resource.o

TARGET = dvdsavescreen.exe

all: $(TARGET)

# 1. Genera il file .rc che include il manifest ufficiale di wxWidgets
resource.rc:
	@echo "Generating resource.rc..."
	@echo '#include "wx/msw/wx.rc"' > resource.rc

# 2. Compila il file .rc in un oggetto binario (.o)
# Nota: wx-config --cppflags serve a windres per trovare i file header di wxWidgets
$(RES_OBJ): resource.rc
	@echo "Compiling resources..."
	$(WINDRES) -i resource.rc -o $(RES_OBJ) `wx-config --cppflags`

# 3. Linka tutto insieme (Sorgenti + Risorse)
$(TARGET): $(OBJ) $(RES_OBJ)
	@echo "Linking $(TARGET)..."
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(RES_OBJ) $(TARGET) resource.rc

.PHONY: all clean
