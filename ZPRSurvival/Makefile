# Makefile gry #TITLE
# 	data: 13.04.2014
#	autor: Pawel Kaczynski
#
# W przypadku nowych plików, należy dodać je do zmiennej OBJECTS z 
# zmienionym rozszerzeniem z .cpp na .o (+ sciezka wzgledna).
#
# Następnie należy dodać regułę wg schematu:
# NazwaPliku.o: NazwaPliku.cpp
# <TAB>	$(CXX) $(CFLAGS) NazwaPliku.cpp 
#
# (Oczywiscie NazwaPliku.cpp wraz z ewent. sciezka wzgledna).

OBJECTS=animated/AnimatedObjectView.o \
animated/AnimatedObjectController.o \
animated/AnimatedObject.o \
creature/CreatureView.o \
creature/CreatureController.o \
creature/Creature.o \
interface/KeyboardInterface.o \
interface/Interface.o \
interface/MouseInterface.o \
interface/Game.o \
interface/Logger.o \
interface/Console.o \
player/Player.o \
player/PlayerController.o \
player/PlayerView.o \
survival/SurvivalObjectView.o \
survival/SurvivalObject.o \
survival/SurvivalObjectController.o \
PerlinNoise.o  \
MidpointDisplacementNoise.o \
MapTile.o \
MapGenerator.o \
MapView.o \
MapController.o \
Map.o \
Source.o

CXX=g++ -std=c++11
CFLAGS=-c -Wall -pedantic
LFLAGS=-lsfml-system -lsfml-graphics -lsfml-window
EXEC=ProjectSurvival.o

# Finalny projekt wykonywalny
$(EXEC): $(OBJECTS)
	$(CXX) -o $(EXEC) $(OBJECTS) $(LFLAGS) 

# Folder animated
AnimatedObjectController.o: animated/AnimatedObjectController.cpp
	$(CXX) $(CFLAGS) animated/AnimatedObjectView.cpp 

AnimatedObject.o: animated/AnimatedObject.cpp 
	$(CXX) $(CFLAGS) animated/AnimatedObject.cpp 

AnimatedObjectView.o: animated/AnimatedObjectView.cpp
	$(CXX) $(CFLAGS) animated/AnimatedObjectView.cpp 

# Folder creature
CreatureController.o: creature/CreatureView.cpp
	$(CXX) $(CFLAGS) creature/CreatureController.cpp 

Creature.o: creature/Creature.cpp
	$(CXX) $(CFLAGS) creature/Creature.cpp 

CreatureView.o: creature/CreatureView.cpp
	$(CXX) $(CFLAGS) creature/CreatureView.cpp 

#Folder player
PlayerController.o: player/PlayerView.cpp
	$(CXX) $(CFLAGS) player/PlayerController.cpp 

Player.o: player/Player.cpp
	$(CXX) $(CFLAGS) player/Player.cpp 

PlayerView.o: player/PlayerView.cpp 
	$(CXX) $(CFLAGS) player/PlayerView.cpp 

# Folder interface
Game.o: interface/Game.cpp 
	$(CXX) $(CFLAGS) interface/Game.cpp 

Console.o: interface/Console.cpp
	$(CXX) $(CFLAGS) interface/Console.cpp 

Logger.o: interface/Logger.cpp
	$(CXX) $(CFLAGS) interface/Logger.cpp 

MouseInterface.o: interface/MouseInterface.cpp
	$(CXX) $(CFLAGS) interface/MouseInterface.cpp 

KeyboardInterface.o: interface/KeyboardInterface.cpp 
	$(CXX) $(CFLAGS) interface/KeyboardInterface.cpp 

Interface.o: interface/Interface.cpp
	$(CXX) $(CFLAGS) interface/Interface.cpp 

# Folder glowny
Source.o: Source.cpp 
	$(CXX) $(CFLAGS) Source.cpp 

MapGenerator.o: MapGenerator.cpp
	$(CXX) $(CFLAGS) MapGenerator.cpp 

MapTile.o: MapTile.cpp
	$(CXX) $(CFLAGS) MapTile.cpp 

MidpointDisplacementNoise.o: MidpointDisplacementNoise.cpp
	$(CXX) $(CFLAGS) MidpointDisplacementNoise.cpp 

PerlinNoise.o: PerlinNoise.cpp
	$(CXX) $(CFLAGS) PerlinNoise.cpp 

Map.o: Map.cpp MapView.cpp MapController.cpp
	$(CXX) $(CFLAGS) Map.cpp 

MapController.o: MapController.cpp
	$(CXX) $(CFLAGS) MapController.cpp 

MapView.o: MapView.cpp
	$(CXX) $(CFLAGS) MapView.cpp 

# Traktuje ponizsze wyrazy jaki instrukcje, nie nazwy plikow
.PHONY: clean del

# Czysci wszystkie pliki posrednie
clean:
	rm -rf $(OBJECTS)

# Usuwa wykonywalny plik projektu
del:
	rm -rf $(EXEC)

# Kompilacja jednym poleceniem (caly projekt na raz)
# Oczywiscie nalezy dopisac brakujace pliki, jesli pojawia sie nowe
#
# g++ -std=c++11 survival/SurvivalObjectView.cpp survival/SurvivalObject.cpp survival/SurvivalObjectController.cpp Source.cpp player/Player.cpp PerlinNoise.cpp  MidpointDisplacementNoise.cpp MapTile.cpp MapGenerator.cpp interface/MouseInterface.cpp interface/KeyboardInterface.cpp interface/Interface.cpp interface/Game.cpp creature/Creature.cpp player/PlayerController.cpp player/PlayerView.cpp MapView.cpp MapController.cpp Map.cpp interface/Logger.cpp interface/Console.cpp creature/CreatureView.cpp creature/CreatureController.cpp animated/AnimatedObjectView.cpp animated/AnimatedObjectController.cpp animated/AnimatedObject.cpp -Wall -pedantic -o ProjectSurvival -lsfml-graphics -lsfml-window -lsfml-system