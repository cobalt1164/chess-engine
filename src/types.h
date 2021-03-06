#ifndef TYPES_H
#define TYPES_H

typedef unsigned long long U64;

#define NAME "Engine"
#define BOARD_NUM 120

#define MAX_MOVES 2000

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


enum { EMPTY, WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING, 
    BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING };

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { WHITE, BLACK, BOTH };

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    SQ_NONE
};

// Castling permissions are a 4 bit value, white king castling = 0001, 
// white queen castling = 0010, and so on
enum { WHITE_KING_CASTLING = 1, WHITE_QUEEN_CASTLING = 2,
    BLACK_KING_CASTLING = 4, BLACK_QUEEN_CASTLING = 8 };

enum { FALSE, TRUE };

typedef struct {
    int move;
    int castlingPerms;
    int enPassant;
    int fiftyMoveRule;
    U64 position;


} HISTORY_STRUCT;

typedef struct {

    int pieces[BOARD_NUM];
    U64 pawns[3];

    int kingSquares[2];
    int side;
    int enPassant;
    int fiftyMoveRule;
    int ply;
    int plyHistory;
    int castlePerms;
    U64 positionKey;

    // There are 13 indexes in the piece enum
    int numPieces[13];
    
    // Anything not a pawn
    int bigPieces[2];

    // Rook and queen
    int majorPieces[2];

    // Bishop and knight
    int minorPieces[2];

    // Value of material score for black/white
    int material[2];

    HISTORY_STRUCT history[MAX_MOVES];
    
    // One dimension for each piece type, another dimension for the multiples
    // of each piece. The maximum number of a single piece possible is 10
    // pieceList[WHITE_PAWN][3] gets the square of the 4th multiple
    int pieceList[13][10];

} BOARD_STRUCT;

#define fileRankTo120(file,rank) ( (21 + file) + (10 * rank) )
#define fileRankTo64(file,rank) board120To64[fileRankTo120(file,rank)]
#define setBit(board,square) board |= SetMask[square]
#define clearBit(board,square) board &= ClearMask[square]

extern int board120To64[BOARD_NUM];
extern int board64To120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 pieceKeys[13][64];
extern U64 sideKey;
extern U64 castleKeys[16];

extern char pieceChars[];
extern char sideChars[];
extern char rankChars[];
extern char fileChars[];

extern int bigPiece[13];
extern int majorPiece[13];
extern int minorPiece[13];
extern int pieceValue[13];
extern int pieceColor[13];

extern void initAll();
extern void printBitBoard(U64 board);
extern int popBit(U64 *bb);
extern int countBits(U64 bb);
extern U64 genPositionKey(const BOARD_STRUCT *position);
extern void printBoard(const BOARD_STRUCT *board);
extern void resetBoard(BOARD_STRUCT *board);
extern int parseFen(char *fen, BOARD_STRUCT *board);
extern void updatePieceLists(BOARD_STRUCT *board);
#endif
