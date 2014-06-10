# Makefile gry #TITLE
# 	data: 13.04.2014
#	autor: Pawel Kaczynski
# 
# Każdy nowy plik z rozszerzeniem .cpp trzeba dołączyć do zmiennej OBJECTS z rozszerzeniem .o

OBJECTS=classes/Animated.o \
classes/Animation.o \
classes/Dynamic.o \
classes/Effectable.o \
classes/GameObject.o \
classes/Effect.o \
creature/Creature.o \
creature/CreatureController.o \
interface/KeyboardInterface.o \
interface/MouseInterface.o \
interface/EntityFactory.o \
interface/Game.o \
interface/Logger.o \
interface/Console.o \
interface/CommandQueue.o \
interface/ContactListener.o \
interface/Utility.o \
interface/states/GameState.o \
interface/states/PauseState.o \
interface/states/LoadState.o \
interface/states/MenuState.o \
interface/states/State.o \
interface/states/StateStack.o \
interface/states/TitleState.o \
item/Item.o \
item/ItemController.o \
item/Plant.o \
map/Chunk.o \
map/ChunkView.o \
map/PoissonDiskSampling.o \
map/PerlinNoise.o \
map/WorldMap.o \
map/WorldMapView.o \
options/GraphicsOptions.o \
player/Player.o \
player/PlayerController.o \
MapTile.o \
MapGenerator.o \
MapController.o \
RandomNoise.o \
Source.o

CXX=g++ -std=c++11
CFLAGS=-Wall -pedantic
LFLAGS=-lsfml-system -lsfml-graphics -lsfml-window -lBox2D
EXEC=Project.o

# Finalny projekt wykonywalny
$(EXEC): $(OBJECTS)
	$(CXX) -o $(EXEC) $(OBJECTS) $(LFLAGS) 

%.o: %.c
	$(CXX) -c -o $@ $< $(CFLAGS)

# Traktuje ponizsze wyrazy jaki instrukcje, nie nazwy plikow
.PHONY: clean del

# Czysci wszystkie pliki posrednie
clean:
	rm -rf $(OBJECTS)

# Usuwa wykonywalny plik projektu
del:
	rm -rf $(EXEC)