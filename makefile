chess: ChessMain.o ChessBoard.o piece.o
	g++ -g  ChessMain.o ChessBoard.o piece.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h piece.h
	g++ -Wall -g -c ChessBoard.cpp

piece.o: piece.cpp piece.h
	g++ -Wall -g -c piece.cpp

clean:
	rm -f *.o chess
