# FUNDOX - Group 2

## GROUP MEMBERS:
- Carolina Mendes Catarino Cerveira Albuquerque
- Maria Eduarda Loureiro Caldeira
- Mariana de Sousa Gandra

## ADDITIONAL SPECIFICATIONS:
- The user should have a text file named "CONFIG.txt" saved in the same directory as the program (a warning is shown if "CONFIG.txt" isn't properly saved in the user's 
computer). This file should present as follows: 

    > WINNER POINTS: numPts\
    VALID WORDS: wordFile\
    LETTERS:\
    let1 occ1\
    let2 occ2\
    ...\
    letn occn

where numPts is the number that specifies the amount of points required to win the game, wordFile is the name of the text file that stores the list of valid words 
(this text file should also be saved in the same directory as the program), leti is a letter and occi is a number that specifies the amount of times that leti appears
on the game. 
- If a player inserts a word that isn't part of the given list of valid words, a warning is shown and the player has the opportunity to try another word. If the player
inserts 3 consecutive non valid words, they lose their turn.
- When a player gives up, their score is removed from the board. The letters they add keep the players' color until they are stollen by someone that is still playing.

## PROGRAM'S STATE OF DEVELOPMENT:
- The developed program achieves all of the proposed goals.
- Improvements done:
    - [x] If a player doesn't insert their name, they are given a name by default (PlayerX, being X the number of the player)
    - [x] As stated before, if a player inserts 3 consecutive non valid words, they lose their turn. Besides, it is considered that the player passed their turn, to prevent
	the game from being endless if a player refuses to pass their turn.

## MAIN DIFFICULTIES:
- Verification of the validity of all the new words formed perpendicularly to a new word placed on the board (when a new word is placed side by side with an old one, the
program makes sure that the adjacent letters of the old word form complete words with the letters of the new word).
- It would be convenient to find a more efficient way to search for the word in the list of valid words (because the list is being searched from top to bottom until a 
correspondence is found, which is particularly costful if the searched word starts by "Z"). Splitting the word list in smaller parts could be a solution but that would 
require the presence of some repetitive parts of code. **(It would be necessary to save all the words of the dictionary on a vector, which would be very costly memory wise).** 