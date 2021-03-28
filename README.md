# PuzzleSolver

This is a project that tries to find all possible solutions to the following puzzle:
[!ExamplePuzzle]

The task was given for fun by an instructor to attempt to brute force and find all the solutions.

I start by finding all sets of 2.  Then I loop through each set and check if each piece fits together.  If the pieces fit into a 4x4 grid then I save it as a solution.

I wanted to make this more interesting than just writing on screen 'The first piece is number 10 and is rotated 3 times' so I made a dll and used Unity to display the solutions
