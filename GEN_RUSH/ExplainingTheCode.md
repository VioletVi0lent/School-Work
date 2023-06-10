# What is this?
This is a short explanation for all the weird code in my game.

There will be jokes spliced between my explanations, but know that this is my first time ever coding a game outside of using Scratch.

We'll be going down the code sections at a time, just to lower the amount of time it will take to write all of this.

## Preset Variables
The two lines that include Circuit Playground and Async Delay are there for a library background. Without it, this code would be an even bigger unhinged mess.

The integers and the bools are there to keep the flags and score systems in check, along with setting controls and making sure some functions only play once.
This also includes how the scoring will work, plus how the player will move, and how fast the game will be played.

## The Setup
Very simple stuff. A serial monitor is used to keep score, and to check whether the difficulty has changed or not.
Fortunately, the serial monitor will no longer be constantly flooded now that I have the ability to only print out the score when you hit or miss in the game.

The setup also has the Interrupt Pins in place for the game to function properly.
This includes only the A button and B button, used for interactions and difficulty selection respectively.

## The Preamble
Over everything in the code is a simple IF statement, asking if the goal of the game has been reached yet.
Once the game is over, it skips everything and turns the entire board white, indicating that the game is over, and to restart.

Yes, this is based on completing a generator in Dead by Daylight. This entire game is based on the generator minigame from Dead by Daylight.

Past the first line of code is a set of code that functions with the B button, only going up one value, and back down to 0 with each press.
There were going to be more than two difficulties, but I didn't have time to code that in.
Instead, there are now only two modes, one for easy/normal, and another for hard.

This is indicated by a change in color and speed, accelerating your character while turning the highlighted zones red instead of green.

## The Game Time Code
Within this statement is another IF statement, which prevents the delay flag from playing out its function if the game is already going on.
This is to prevent the game from playing over itself, which doesn't really happen, since the flag is 5 seconds long, and the game itself lasts for about 2.

Still, better safe than sorry.

Once the flag expires, however, a special function will play that predetermines the LEDs to light up, directly opposite of where the player spawns.
When this happens, the LEDs will turn into the color determined by the difficulty, and start the game, resetting the flags back to "Game Time."

So while the game is playing, it will constantly check for the A button using the Interrupt function set by a simple IF statement.
While that's happening, just below that chuck of code, is the code that moves the player forward constantly. You will move depending on the difficulty.
Much like the README.md says, your job is to land your dot in the zone marked by the brighter lights for points.

This point system is built into the actions, or inaction, of the player.
If you don't do anything, letting the blue dot reach the end of the board, you lose points. If you miss your mark, you also lose points.
In order to win points, you must time your dot so it reaches into the zone at the right time.

There's a strange bug where if an LED is at the very end of the board, the blue LED will continue moving past it and count as a loss.
I have no idea how to fix that specific bug, but if you let the player reach the end, and only hit that last LED, I'm choking it up as a Skill Issue.

## Past That Point
Beyond the loop of the code is where all the background functions lay dormant until called.

This includes the ISRs for the Interrupt Flags, both for A and B buttons, and the special "Start Engine" function, used by the Preamble.

Start Engine allows the zones to be preset every time the Delay Flag expires, changing it up with a random seed generator that randomizes the location of the zone.
This function really only exists to lessen the load of how much is on screen at once; Especially effective for me, since I have bad eye sight.
I would've done this for most of the other functions in the game, but I didn't want to constantly go back and forth on the comments for that reason.

So that's how the game functions. I hope this serves you well.

- Maximilian Throgmorton
