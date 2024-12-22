ChatGPTGame

ChatGPTGame is an interactive and minimalist game project powered by SDL2 and C++. The repository contains a playable version of the classic Pong game, written to showcase the fundamentals of game development using SDL2.

Features

🎮 Core Gameplay

Pong Game Mechanics: Play a two-player Pong game with paddle and ball interactions.

Simple Controls:

Player 1: W (Up) and S (Down).

Player 2: Arrow keys ↑ (Up) and ↓ (Down).

⚡ Optimized Rendering

SDL2 accelerated rendering for smooth gameplay.

🛠️ Customizable Code

The code is modular and easy to extend with features like scoring, sound effects, or advanced AI for single-player modes.

Prerequisites

SDL2 Library

Install SDL2 on your system. For macOS users:

brew install sdl2

For Windows or Linux, refer to the SDL2 installation guide.

Compiler

A modern C++ compiler (e.g., clang++ or g++).

Git (optional, for cloning the repository)

Install Git from git-scm.com.

Getting Started

Clone the Repository

git clone https://github.com/catsanzsh/ChatGPTGame.git
cd ChatGPTGame

Build the Game

macOS

Compile using clang++:

clang++ -o pong pong.cpp \
-I/opt/homebrew/Cellar/sdl2/2.30.9/include/SDL2 \
-L/opt/homebrew/Cellar/sdl2/2.30.9/lib -lSDL2

Run the game:

./pong

Linux

Compile using g++:

g++ -o pong pong.cpp -lSDL2

Run the game:

./pong

Windows

Use an IDE like Visual Studio or Code::Blocks to set up your project with SDL2.

Add pong.cpp to the project.

Link SDL2 libraries in your project settings.

Build and run the game.

Repository Structure

ChatGPTGame/
├── pong.cpp          # Source code for the Pong game
├── README.md        # Documentation
└── LICENSE          # License file

Future Plans

🏆 Add a scoring system.

🤖 Introduce an AI for single-player mode.

🎵 Add sound effects and background music.

🌟 Improve visuals with better graphics and animations.

Contributing

Contributions are welcome! To contribute:

Fork the repository.

Create a new branch for your feature or bugfix.

Commit and push your changes.

Open a pull request.

License

This project is licensed under the MIT License.

Acknowledgments

Built using SDL2.

Inspired by the classic Pong game.

# ChatGPTGame
1.0
