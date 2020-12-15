chess: ChessMain.o ChessBoard.o ChessPiece.o PiecePawn.o PieceKing.o PieceQueen.o PieceRook.o PieceBishop.o PieceKnight.o
	g++ -g  ChessMain.o ChessBoard.o ChessPiece.o PiecePawn.o PieceKing.o PieceQueen.o PieceRook.o PieceBishop.o PieceKnight.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h ChessPiece.h PiecePawn.h PieceKing.h PieceQueen.h PieceRook.h PieceBishop.h PieceKnight.h
	g++ -Wall -g -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp

PiecePawn.o: PiecePawn.cpp PiecePawn.h ChessPiece.h
	g++ -Wall -g -c PiecePawn.cpp

PieceKing.o: PieceKing.cpp PieceKing.h ChessPiece.h
	g++ -Wall -g -c PieceKing.cpp

PieceQueen.o: PieceQueen.cpp PieceQueen.h ChessPiece.h
	g++ -Wall -g -c PieceQueen.cpp

PieceRook.o: PieceRook.cpp PieceRook.h ChessPiece.h
	g++ -Wall -g -c PieceRook.cpp

PieceBishop.o: PieceBishop.cpp PieceBishop.h ChessPiece.h
	g++ -Wall -g -c PieceBishop.cpp

PieceKnight.o: PieceKnight.cpp PieceKnight.h ChessPiece.h
	g++ -Wall -g -c PieceKnight.cpp

clean:
	rm -f *.o chess
