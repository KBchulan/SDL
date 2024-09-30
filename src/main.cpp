#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 15
#define CELL_SIZE 40
#define WIN_CONDITION 5

int board[BOARD_SIZE][BOARD_SIZE] = {0}; // 0为空，1为黑棋，2为白棋
int currentPlayer = 1;

void drawBoard(SDL_Renderer *renderer) {
    // 绘制棋盘
    SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255); // 棋盘颜色
    SDL_RenderClear(renderer); // 清空渲染器
    for (int i = 0; i <= BOARD_SIZE; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, BOARD_SIZE * CELL_SIZE, i * CELL_SIZE);
    }
}

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // 横向偏差
            int dy = radius - h; // 纵向偏差
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void drawPieces(SDL_Renderer *renderer) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == 1) {
                // 绘制黑棋
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                drawCircle(renderer, x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE / 2 - 2);
            } else if (board[x][y] == 2) {
                // 绘制白棋
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                drawCircle(renderer, x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE / 2 - 2);
            }
        }
    }
}

bool checkWin(int player) {
    // 检查胜利条件（此处省略实现）
    return false;
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("五子棋", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x / CELL_SIZE;
                int y = event.button.y / CELL_SIZE;

                if (x < BOARD_SIZE && y < BOARD_SIZE && board[x][y] == 0) {
                    board[x][y] = currentPlayer;
                    if (checkWin(currentPlayer)) {
                        printf("玩家 %d 胜利！\n", currentPlayer);
                    }
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }
            }
        }

        SDL_RenderClear(renderer);
        drawBoard(renderer);
        drawPieces(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
