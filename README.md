# Computer Graphics Assignment 1

### Pooja Desur

### 2019101112

---

## Compiling and Running

In the 2019101112 directory, the source files and CMakeLists.txt are present.
In order to run the code, create a build folder and compile using cmake.

```python
mkdir build && cd build && cmake ..
```
```python
make && ./AmongUs
```

---

## Game Play
You are a crewmate who is dropped into a randomly generated maze. An imposter is chasing you to murder you from a random part of the maze. 
There are two buttons in the maze that help you win
* Green Button - this releases coins that help you gain health, but also bombs that damage you when you collide with them.
* Red Button - this blows up the imposter and stops their murder spree

In order to win, you have to complete your tasks by finding both the buttons and collecting all the 4 coins scattered throughout the maze.

Be careful, there's a timelimit of 120 seconds. If you fail to complete your tasks within this time, you lose.
You also lose when the imposter kills you before you kill them. He always takes the shortest path to kill you, so don't take him for granted!

You start off with a health of 100. You can view your health, time left and the tasks youve completed in the Heads Up Display at the top left corner.


---

## Keyboard Controls

Use the keyboard arrow keys to move up,down, left and right. 
You cannot pass through walls of a maze.






