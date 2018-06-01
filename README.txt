
General:
This is not an excuse, but due to militarly service (Arie) and work in the Holidy (not only the Chol HaMoed but rather the Holidays themselves) we couldnt design the program properly and each team member did his own part without syncing with the others.
In addition to that in the first two to three weeks of the semester, Arie was also required to apply for two repeated (moed B) tests in courses from the previous semester, which led to a significant delay at the start of the project
Following that, our design is lacking, and therefore there is a huge code duplication, unsed code parts, wrongly used code part and bugs that even the extra week was not sufficent.


Notes:
- If one player place a flag and (optional) none moveable pieces than the game will not start however an output will be created as there is a winner, the output is: All moving PIECEs of the opponent are eaten.
- If both players place a flag and (optional) none moveable pieces than the game will not start however an output will be created as there is a winner, the output is: All moving PIECEs of both players are eaten.
- If the players used a valid positioning file that cause the game to end (due to a tile or a win) it will be loaded and comabts will be made and final conclusion will be done
  meaning if there was a combat after load that caused one player to win, we will not stop until the full first comabats are done. HOWEVER we will not continoe to the move file!! as there is already a winner. 


Bugs:
- Not deleting from the screen properly after a combat.
- Not updating the square properly after a comabat. (not in all cases).
- Show-only-known-info and show-player are not working properly, couldn't finish writing the code due to other bugs. In addition to that, Joker is not threated as it should with these arguments.
- Close of files is not being performed on all cases.
- ifndef i snot verfied and properly set (we are doing includes in CPP).
- Static const is being used in CPP.
- We didn't finialize all the warnings.
- Moving Joker and changing his form (need to review if it is possible)



-------------------------------------------------------------project 2----------------------------------------------------------

1. default delay for console mode set to 50 ms as in excercise 1
2. To check input same location Example: R 5 5 then P 5 5 same player.
