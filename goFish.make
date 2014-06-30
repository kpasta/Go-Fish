goFish.out: final.o player.o deck.o game.o 
	g++ -o goFish.out final.o player.o deck.o game.o 
final.o: final.cpp game.cpp game.h
	g++ -c final.cpp
player.o: player.cpp player.h
	g++ -c player.cpp
deck.o: deck.cpp deck.h
	g++ -c deck.cpp
game.o: game.cpp game.h
	g++ -c game.cpp
clean:
	rm *.out goFish
