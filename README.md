2-Player Yahtzee!

This was originally a school project but with slight modifications to make it playable with 2 people.

/--How to run:

Download C++ file
  1. Make sure you have a C++ compiler on your PC or whatever machine you're running. --- https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/
  2. Compile file. --- https://www.tutorialspoint.com/How-to-compile-and-run-the-Cplusplus-program
  3. Run exe file
  4. Grab a buddy and have fun!

/--How to play:

  This game is turn based, each turn ends when a player selects a combo to play.

  Per turn, you will be prompted:

    'Keep dice (s to stop rolling)'
  
  You will see your hand of 5 dices. Each number represeting the Die.

    'Hand: 1 2 3 4 5'
    
  You can choose which Dices to keep (not roll) by entering the order of which they appear.

    'Hand: 1 1 3 2 6'
    'Select a combination to play: 125'
    
  If I wanted to keep both '1's and the '6', enter in '125' since 1 and 2 are the first 2, and 5 is the last. If you wanted to keep rolling without keeping any dices, just enter in anything that isn't 12345 so like 'f' or '-2'. If you want to stop rolling to select a combo, enter in 's'.

  To select a combo, enter in the number corresponding to the numbered combo.

    '13. Yhatzee'
    
  so I enter in '13'. You cannot enter in combos that are already played. Meaning you can only play combos with '-' listed to the right.

/--Here are the general rules for Yhatzee: 'https://www.dicegamedepot.com/yahtzee-rules/'
