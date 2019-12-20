#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char board[8][8];
    char castle;
    char ep[2];
    int halfmove;
    int fullmove;
    char side;
} FEN;

FEN fen; 

int is_valid(char c);
void print_fen();
void parse_fen();

int main () {

    parse_fen();
    print_fen();

    return 0;

}

int is_valid(char c) {

    if (c >= '1' && c <= '8') return 1;

    switch (c) {
        case 'p':
            return 1;
        case 'n':
            return 1;
        case 'b':
            return 1;
        case 'r':
            return 1;
        case 'q':
            return 1;
        case 'k':
            return 1;
        case 'P':
            return 1;
        case 'N':
            return 1;
        case 'B':
            return 1;
        case 'R':
            return 1;
        case 'Q':
            return 1;
        case 'K':
            return 1;
        default:
            return 0;
    }
}

void print_fen() {

    int rank, file;

    printf("    ----------------\n");
    for (rank = 7; rank >= 0; rank--) {
        printf("%3d|", rank + 1);
        for (file = 0; file <= 7; file++) {
            printf("%2c", fen.board[rank][file]);
        }
        printf("\n");
    }
    printf("    ----------------\n");
    printf("     A B C D E F G H\n\n");

    if (fen.side == 'w') printf("White to play.\n\n");
    else printf("Black to play.\n\n");

    if (!fen.castle) printf("Neither side has castling rights.\n");
    else {
        if (fen.castle & 8) printf("White can castle kingside.\n");
        if (fen.castle & 4) printf("White can castle queenside.\n");
        if (fen.castle & 2) printf("Black can castle kingside.\n");
        if (fen.castle & 1) printf("Black can castle queenside.\n");
    }
    printf("\n");

    if (fen.ep[0] == '-') 
        printf("There is no current en passant square.\n\n");
    else
        printf("En passant square is %c%c.\n\n", fen.ep[0], fen.ep[1]);

    printf("Halfmove clock is %d.\n\n", fen.halfmove);
    printf("Fullmove number is %d.\n\n", fen.fullmove);

}

void parse_fen() {

    char c;
    int rank, file, i;

    /* parse piece placement string */
    for (rank = 7; rank >= 0; rank--) {
        for (file = 0; file <= 7; file++) {
            if(is_valid(c = getchar())) {
                if (c >= '1' && c <= '8') {
                    for(i = 0; i < c - 48; i++) {
                        fen.board[rank][file++] = '.';
                    }
                    file--;
                } else {
                    fen.board[rank][file] = c; 
                }
            } else {
                fprintf(stderr, "Invalid piece (use [0-8pnbrqkPNBRQK]).\n");
                exit(1);
            }
        }
        if (file != 8) {
            fprintf(stderr, "Too many pieces on rank.\n");
            exit(1);
        }
        if (rank > 0 && getchar() != '/') {
            fprintf(stderr, "Invalid rank seperator (use '/').\n");
            exit(1);
        }
    }

    if (getchar() != ' ') {
        fprintf(stderr, "Expecting space between piece ");
        fprintf(stderr, "placement string and active color.\n");
        exit(1);
    }

    /* parse active color */
    fen.side = getchar();
    if (fen.side != 'w' && fen.side != 'b') {
        fprintf(stderr, "Invalid active color (use [wb]).\n");
        exit(1);
    }

    if (getchar() != ' ') {
        fprintf(stderr, "Expecting space between active ");
        fprintf(stderr, "color and castling rights.\n");
        exit(1);
    }

    /* parse castling availability */
    fen.castle = 0;
    if ((c = getchar()) != '-') {
        do {
            switch (c) {
                case 'K':
                    fen.castle |= 8;
                    break;
                case 'Q':
                    fen.castle |= 4;
                    break;
                case 'k':
                    fen.castle |= 2;
                    break;
                case 'q':
                    fen.castle |= 1;
                    break;
                default:
                    fprintf(stderr, "Invalid castling rights string ");
                    fprintf(stderr, "use '-' or one or more [KQkq]).\n");
                    exit(1);
            }
        } while ((c = getchar()) != ' ');
    }

    /* parse en passant square */
    if ((fen.ep[0] = getchar()) != '-') {
        if (fen.ep[0] < 'a' || fen.ep[0] > 'h') {
            fprintf(stderr, "Invalid en passant file (must be a - h).\n");
            exit(1);
        }

        fen.ep[1] = getchar();

        if (fen.ep[1] < '1' || fen.ep[1] > '8') {
            fprintf(stderr, "Invalid en passant rank (must be 1 - 8).\n");
            exit(1);
        }
    }

    if (getchar() != ' ') {
        fprintf(stderr, "Expecting space between en ");
        fprintf(stderr, "passant square and halfmove clock.\n");
        exit(1);
    }

    /* parse halfmove clock */
    if (scanf("%d", &fen.halfmove) != 1) {
        fprintf(stderr, "Invalid halfmove clock. ");
        fprintf(stderr, "Must be a non-negative integer.\n");
        exit(1);
    }
    
    if (getchar() != ' ') {
        fprintf(stderr, "Expecting space between halfmove clock ");
        fprintf(stderr, "and fullmove number.\n");
        exit(1);
    }


    /* parse fullmove number */
    if (scanf("%d", &fen.fullmove) != 1) {
        fprintf(stderr, "Invalid fullmove number. ");
        fprintf(stderr, "Must be a positive integer.\n");
        exit(1);
    } else {
        if (i < 1) {
            fprintf(stderr, "Invalid fullmove number. ");
            fprintf(stderr, "Must be a positive integer.\n");
            exit(1);
        } 
    }

    getchar(); /* eat newline */
    if (getchar() != EOF) {
        fprintf(stderr, "EOF expected after fullmove number.\n");
        exit(1);
    }

}
