=========================
PACMAN GAME
=========================

TO COMPILE AND RUN (OSX/Linux)
> git clone <repo>; cd <dir>/pacman; make; ./pacman.x

CONTROLS
P - pause game
N - new game (reset)
Q - quit game
Arrow keys - to move left,right,up and down

FEATURES
Animated characters - pacman and ghost figures
Non-geometric primitives (pixel maps) - pacman and ghost figures
AI - the ghosts each have a different personality

MECHANICS
1 - The game starts with Pacman (with 3 lives excluding current) and 4 ghosts
2 - Every Pacman gets eaten by a ghost he loses a life
3 - When Pacman has no more lives left he dies
4 - Every Food pellet eaten by Pacman earns him 10 points
5 - For every 100 points, Pacman gets a new life
6 - During random intervals in the game, Pacman is allowed to chase ghosts (watch for prompt) and gets a random bonus life/score
