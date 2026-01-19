# Santase (66) Card Game

Course Project for Introduction to Programming (Practicum)
Faculty of Mathematics and Informatics, Sofia University
Winter Semester 2025/2026

**Author:** Mladen Stankov
**Faculty Number:** 3MI0600676
**Variant:** 66 (Santase)

## Description

This project is a console-based implementation of the popular card game Santase (66). It supports two players and implements all standard rules including marriages, switching the nine, closing the deck, and score calculation.

## Features

- **Standard 66 Rules:** Includes marriages (20/40 points), switching the trump nine, closing the deck.
- **Save/Load System:** Ability to save the game at any point and load it later.
- **Customizable Settings:** Change target points, marriage points, and display options.
- **Console Interface:** Colorful and interactive command-line interface.

## Compilation

The project can be compiled using GCC or Visual Studio.

### GCC

```bash
g++ *.cpp -o main.exe
```

## How to Run

After compilation, run the executable:

```bash
./main.exe
```

## Commands

- `help`: Show all available commands.
- `start`: Start a new game or round.
- `play <index>`: Play a card from your hand.
- `marriage <suit>`: Announce a marriage.
- `switch-nine`: Switch your nine of trumps with the bottom card.
- `close`: Close the deck.
- `status`: Show current game status.
- `surrender`: Surrender the round.
- `surrender-forever`: Surrender the game.
- `stop`: Stop the round.
- `hand`: Show your hand.
- `save <name>`: Save game to file.
- `load <name>`: Load game from file.
- `rules`: Display game rules.
