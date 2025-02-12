# Brick Breaker Game

## Description
This is a basic 2D Brick Breaker game implemented in C++ using OpenGL. The game features a paddle, a ball, and a grid of bricks. The objective is to break all the bricks by bouncing the ball off the paddle. The game includes various power-ups and challenges to enhance the gameplay experience.

## Features
- **Paddle Control**: Move the paddle left and right using the mouse to keep the ball in play.
- **Ball Physics**: The ball bounces off the paddle, walls, and bricks with realistic physics.
- **Brick Types**: Different colored bricks with varying hit points.
- **Power-Ups**: Special power-ups that can double the paddle size, halve the paddle size, and more.
- **Score System**: Keep track of your score as you break bricks.
- **High Scores**: Save and display the top three high scores.
- **Game States**: Start, resume, and exit the game with a main menu.

## Controls
- **Mouse**: Move the paddle left and right.
- **Spacebar**: Launch the ball at the start of the game or after losing a life.
- **Arrow Keys**: Navigate the main menu.
- **Enter**: Select an option in the main menu.
- **S**: Start a new game.
- **Esc**: Return to the main menu.

## Installation
To compile and run the game, you need to have OpenGL and GLUT installed on your system.

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/brick-breaker-game.git
    cd brick-breaker-game
    ```

2. **Compile the game**:
    ```bash
    g++ -o brickbreaker main.cpp -lGL -lGLU -lglut
    ```

3. **Run the game**:
    ```bash
    ./brickbreaker
    ```

## Code Structure
- **main.cpp**: Contains the main game logic, including the `Game` class and its methods.
- **util.h**: Utility functions for drawing shapes and handling colors.
- **game_objects.h**: Definitions for game objects like `Ball`, `Paddle`, and `Bricks`.

## Dependencies
- OpenGL
- GLUT (OpenGL Utility Toolkit)

## Author
- **Shilok Kumar**
- **Roll No**: 23I-2502

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- This game was developed as a project for learning OpenGL and game development in C++.
- Special thanks to the OpenGL community for providing valuable resources and tutorials.

## Screenshots
![Main Menu](screenshots/main_menu.png)
![Gameplay](screenshots/gameplay.png)
![High Scores](screenshots/high_scores.png)

## Future Improvements
- Add more levels with increasing difficulty.
- Introduce new power-ups and obstacles.
- Improve graphics and animations.
- Add sound effects and background music.

## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes.

## Issues
If you encounter any issues or have suggestions for improvements, please open an issue on the GitHub repository.
