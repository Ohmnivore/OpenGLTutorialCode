# What?
This is the source code from Jamie King's excellent (modern) OpenGL tutorial at
https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY

# Why?
10 years later, I don't want to have to re-listen to the 103 videos in the playlist to remember how to use OpenGL.
Don't be mistaken, the videos are a joy to watch, but the whole playlist is rather long. It's the same
motivation I have for writing my book notes: https://github.com/Ohmnivore/Notes

# Which commit corresponds to which episode?
Check out the past commits. You will find that commits don't happen every episode, and are rather rare. That's because
the videos in the code are cumulative and don't start from scratch everytime. I only made new commits when I thought
that the code base would be significantly altered.

# Which parts of the code have I changed?
I changed as little as possible, but I couldn't stand Qt. I love Qt for GUIs, but I'm learning OpenGL in the context
of video games, so using SDL2 made much more sense. It's also a lot more light-weight, and it's a game framework
after all.
