# Hex (position analyzer)
The project was done as a part of my university study. Its main objective was to exercise implementing graphs and DFS algorithm.
The program itself accepts ASCII drawn hex board (see [Examples](#Examples)) of different sizes (from 1x1 to 11x11), analyzes it and produces output based on query provided "below" the board.

# Input
A sequence of test cases, each starting with a drawing of the board's contents followed by a series of queries. The size of the board can vary from 1 to 11. The presence of a red (starting player) pawn is denoted by the letter "r", and a blue pawn by the letter "b". Sample boards may look like this: 

<details>

<summary>Boards</summary>

```
 ---
< r >
 ---
```
```
          ---
       --<   >--
    --< b >-<   >--
 --< r >-<   >-<   >--
< b >-< b >-<   >-< r >
 --<   >-< r >-< b >--
    --<   >-< r >--
       --<   >--
          ---
```
```
                               ---
                            --<   >--
                         --<   >-< b >--
                      --<   >-<   >-<   >--
                   --<   >-<   >-<   >-<   >--
                --<   >-<   >-<   >-< b >-< r >--
             --<   >-<   >-<   >-<   >-<   >-< r >--
          --<   >-<   >-<   >-<   >-< r >-<   >-<   >--
       --< b >-< r >-< r >-<   >-<   >-< b >-<   >-< b >--
    --<   >-<   >-<   >-<   >-< r >-<   >-<   >-< b >-<   >--
 --<   >-< b >-< r >-< r >-< r >-< b >-<   >-<   >-<   >-< r >--
< b >-<   >-<   >-<   >-<   >-<   >-< b >-<   >-<   >-<   >-< r >
 --< r >-<   >-< b >-< b >-< b >-<   >-<   >-<   >-< b >-< r >--
    --<   >-< r >-< r >-<   >-< b >-< r >-<   >-<   >-<   >--
       --< r >-< b >-<   >-< r >-<   >-<   >-<   >-<   >--
          --<   >-< r >-<   >-<   >-<   >-<   >-<   >--
             --<   >-< r >-< b >-<   >-< r >-< b >--
                --< r >-< r >-<   >-<   >-< r >--
                   --<   >-<   >-<   >-< b >--
                      --<   >-<   >-<   >--
                         --<   >-<   >--
                            --< b >--
                               ---
```
</details>

<details>
<summary>Queries</summary>

- BOARD_SIZE - a number from the range <1;11> indicating the size of the board.
- PAWNS_NUMBER - a number from the range <0;121> indicating the number of pawns of both players on the board.
- IS_BOARD_CORRECT - a YES/NO response indicating whether the state of the board is correct, in other words, whether the number of pawns of one player is appropriate relative to the number of pawns of the other player.
- IS_GAME_OVER - a YES RED/YES BLUE/NO response indicating whether (and if so, which) player has ended the game, i.e., whether they have connected two edges of the board with an uninterrupted path of their color.
- IS_BOARD_POSSIBLE - a YES/NO response indicating whether the state of  the board is possible. This means that the board is correct and that  achieving such a state did not result in overlooking an earlier win by  one of the players. 
- **(not implemented)** CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT (...) - a YES/NO response  indicating whether one of the players can end the game in N (where N  belongs to <1;2>) moves when playing against a naive opponent  (making the worst possible moves for themselves). The number of moves N  indicates the number of moves by the player for whom we are considering  victory. Victory must occur in the Nth move, which means that the player  must have the ability to make such a number of moves.  
- **(not implemented)** CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT (...) - analogous case to  the previous one, with the difference that the player checks whether  they can end the game playing against a perfect opponent (making the  best possible moves for themselves) in N (where N belongs to  <1;2>) moves.

</details>

# Output
A sequence of responses, at least one for each test case, separated by whitespace. Possible responses for each test case are [above](#Input) (queries).

# Examples

<details>
<summary>In</summary>

```

 ---
<   >
 ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

          ---
       --< b >--
    --< r >-< b >--
 --< r >-< r >-< b >--
< b >-< b >-< r >-< b >
 --< r >-< b >-< b >--
    --< r >-< r >--
       --< r >--
          ---

BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

                               ---
                            --<   >--
                         --<   >-<   >--
                      --<   >-<   >-<   >--
                   --< r >-<   >-<   >-< b >--
                --<   >-<   >-<   >-<   >-<   >--
             --<   >-< r >-<   >-<   >-< b >-<   >--
          --<   >-<   >-< r >-<   >-< b >-<   >-<   >--
       --<   >-<   >-<   >-< r >-< b >-<   >-<   >-<   >--
    --<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >--
 --<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >--
<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >
 --<   >-<   >-<   >-<   >-< b >-< r >-<   >-<   >-<   >-<   >--
    --<   >-<   >-<   >-< b >-<   >-<   >-<   >-<   >-<   >--
       --<   >-<   >-<   >-<   >-< r >-<   >-<   >-<   >--
          --<   >-<   >-< b >-<   >-< r >-<   >-<   >--
             --<   >-<   >-<   >-<   >-<   >-<   >--
                --<   >-< b >-<   >-< r >-<   >--
                   --< b >-<   >-<   >-< r >--
                      --<   >-<   >-<   >--
                         --<   >-<   >--
                            --<   >--
                               ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

```
</details>

<details>
  <summary>Out</summary>
  
```
1

0

YES

NO

YES

YES
NO
NO
NO

YES
NO
NO
NO

4

16

YES

YES RED

NO

NO
NO
NO
NO

NO
NO
NO
NO

11

18

YES

NO

YES

NO
NO
YES
YES

NO
NO
YES
NO
```
</details>

# Credits
The author of the requirements is Tomasz G***. The full name is withheld for confidentiality reasons.

 
