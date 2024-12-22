#include <SDL2/SDL.h>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Paddle dimensions
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;

// Ball dimensions
const int BALL_SIZE = 20;

// Movement speed
const int PADDLE_SPEED = 8;
const int BALL_SPEED = 5;

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create SDL Window
    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game variables
    SDL_Rect leftPaddle = {30, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_Rect rightPaddle = {SCREEN_WIDTH - 50, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_Rect ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE};

    int ballVelX = BALL_SPEED, ballVelY = BALL_SPEED;
    int leftPaddleVel = 0, rightPaddleVel = 0;

    bool quit = false;
    SDL_Event event;

    // Game loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        leftPaddleVel = -PADDLE_SPEED;
                        break;
                    case SDLK_s:
                        leftPaddleVel = PADDLE_SPEED;
                        break;
                    case SDLK_UP:
                        rightPaddleVel = -PADDLE_SPEED;
                        break;
                    case SDLK_DOWN:
                        rightPaddleVel = PADDLE_SPEED;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_s:
                        leftPaddleVel = 0;
                        break;
                    case SDLK_UP:
                    case SDLK_DOWN:
                        rightPaddleVel = 0;
                        break;
                }
            }
        }

        // Update paddles
        leftPaddle.y += leftPaddleVel;
        rightPaddle.y += rightPaddleVel;

        // Prevent paddles from moving off-screen
        if (leftPaddle.y < 0) leftPaddle.y = 0;
        if (leftPaddle.y + PADDLE_HEIGHT > SCREEN_HEIGHT) leftPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
        if (rightPaddle.y < 0) rightPaddle.y = 0;
        if (rightPaddle.y + PADDLE_HEIGHT > SCREEN_HEIGHT) rightPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;

        // Update ball
        ball.x += ballVelX;
        ball.y += ballVelY;

        // Ball collision with top and bottom walls
        if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
            ballVelY = -ballVelY;
        }

        // Ball collision with paddles
        if (SDL_HasIntersection(&ball, &leftPaddle) || SDL_HasIntersection(&ball, &rightPaddle)) {
            ballVelX = -ballVelX;
        }

        // Ball goes out of bounds (reset position)
        if (ball.x <= 0 || ball.x + BALL_SIZE >= SCREEN_WIDTH) {
            ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
            ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
            ballVelX = BALL_SPEED * (ballVelX > 0 ? -1 : 1); // Change direction
            ballVelY = BALL_SPEED;
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &leftPaddle);
        SDL_RenderFillRect(renderer, &rightPaddle);
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
