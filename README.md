# Dungeon Smash - Ubisoft Mentorship Project
This project was developed during the **2023 Ubisoft Mentorship Program**. This README explains what the project is about, what were the tasks made, the lessons learned and the following steps 
to improve the project if wanted.

## Game Design
It is a **single player top-down game** where the players will need to kill as many enemies as they can in a given time. To do so, an item (or a scythe) in the ground must be first picked up
so it can be used to attack and kill the enemies. It has support for both **keyboard and gamepad**, the movement can be made in **four directions** and the actions of picking up the item and
using it are **activated with the same button**.

## Development Process
The first stage of the development process consisted in several steps:
- I separated the Ubisoft API code from my own code into **two independent projects (UbiAPI and CrowdedSpace)**.
  The code in CrowdedSpace is compiled as a library which is then used by the UbiAPI. This approach was really useful because it allowed me to ensure a clear and independent project structure.
  - Additionally, I placed the **Assets** folder at the same level of the main projects in order to maintain the independence between code and assets.
  - *Note*: The Ubisoft API code is not included due to confidentiality issues.
- I implemented an **automatic build system**. Each time a compilation in Release mode is made, a .bat file is executed, which stores the results of the compilation in a folder with the current
  date and time and is automatically uploaded to a Dropbox shared folder.
  - *Note*: A build of the game can be found in the Release section of this repository.

In the second stage:
- I created the **game architecture**, opting for an approach similar to the one used by Unreal Engine. I designed and developed the relationship between **Worlds, Actors, and Components**,
  where the world handles the creation, update, render, and destruction of its actors. In the same way, each actor is responsible for its components.

The third stage was all about actually creating the functionality of the videogame.
- This involved the creation of essential components such as **SpriteRendererComponent, MovementComponent, and AnimationComponent**, as well as the implementation of **Effect, Item, and ItemData**
  to manage the application of effects to actors.
- I also implemented a **ColliderComponent** to check collisions between actors and created specific classes like **Pawn, Character, PlayerCharacter and EnemyCharacter**, along with their respective **Controllers**,
  to manage the player and the enemy functionality.
- I introduced a **PickComponent** to pick up items, a **HealthComponent** to manage character life and **VFX and SFXComponent** to handle visual and sound effects.
- I also created **Managers** to control game pause and resume, the time left and the spawn of enemies.
- I implemented a HUD system as well, with **HUD, Widgets and HUDComponents** that work in the same way as Worlds, Actors and Components do and is owned by each player controller.
- Finally, several helper classes were also implemented, like for example:
  - An **Assets** class for the definition of the assets used in the game.
  - **Delegates** or callback functions.
  - A a **GameplayStatics** with functions to retrieve the current world or a specific player controller, and to check collisions between different types of ColliderComponents.

## Learnings
During the development of this project, I learned some valuable things, for example: 
- I learned to automatize builds.
- I learned to define the architecture of a videogame.
- I learned to manage the lifecycle of the classes in a videogame.
- I learned to create callback functions or delegates.
- I learned to use templated functions with multiple arguments.
- I strengthened my knowledge of Unreal Engine architecture.
- I reinforced my skills in project management, estimations and scope handling.

## Following Steps
There are several things we could do to improve this project, so some of the following tasks to be performed next if the videogame were to be further developed would be:
- Create an AI that follows the player, attacks him and decreases its health.
- Implement a widget that shows the player’s current health and other one to indicate when the player has lost (only when enemies can inflict damage to the player).
- Create new items and effects.
- Enhance the current game feel by improving the aesthetics of the HUD, adding a background to the scene, and incorporating a soundtrack.
- Implement more types of enemies or complex maps.
