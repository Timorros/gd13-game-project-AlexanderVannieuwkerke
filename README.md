<a name="readme-top"></a>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h2 align="center">pallworld pinball garnet and lappis</h2>

  <p align="center">
    This game is just a pinball game using the pokemon IP.
    Although it is just a pinball game, there are many mini games and secrets to unravel.
    Please the pokemon company don't sue me.
    <br />
    <strong>Original game : p0k3m0n pinball ruby and sapphire</strong>
    <a href="https://www.google.be/"><strong>General info »</strong></a>
    ·
    <a href="https://www.google.be/"><strong>Youtube video »<strong></a>
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#my-version">My version</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#how-to-play">How To Play</a></li>
    <li><a href="#class-structure">Class structure</a></li>
    <li><a href="#checklist">Checklist</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Here's why:
TODO: describe why you chose this game 
* I recently discovered this addictive game and fell in love with it.
* I think it is fascinating how you can keep discovering mechanics after dozens of hours in.
* I like the challenge that the physics make.
* It is an original choice, I am pretty sure no one would've thought of this game or even know it.
<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

### The minimum I will most certainly develop:
* The basic pinball mechanics
* all the events for using certain paths e.g: money path, get path, evolve path
* the egg hatching mechanics
* the keckleon mini game
* the groudon mini game
* the slot machine in the middle

### What I will probably make as well:
* the ball that spins when rubbing against the walls
* the shop
* the pause button

### What I plan to create if I have enough time left:
* more mini games
* the pokeball upgrade mechanics
* the board shaking mechanic
* more of the small mechanics listed in the manual

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
In the main branch open the game folder, then open the x64 folder and the debug folder that is in there. Then launch the gd13-game-project-AlexanderVannieuwkerke.exe file.

### Prerequisites
A computer with windows and a copy of the project.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- HOW TO PLAY -->
## How to play
### Controls
* Use A and D to actuate the left and right paddles.
* D is also used to set the ball back in play.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 
Some Classes use composition like my map class ( the one who contains all parts of the map like bumpers) and my catcher class use composition for physics or event purposes.

### Inheritance 
I have a Bumper class used for normall bumpers that don't do anything.
My Pokemon class furtther enherits from the bumper class to incorporate a counter in the CalcPhysics function that will return true when it has been hit 3 times.
The BabyPokemon class then enherits from the pokemon class because a baby pokemon only needs 2 bumps to be cought.

### Polymorphism
Because the BabyPokemon enherits from Pokemon I can use polymorphysm and only use 1 pointer for both catching a pokemon or a babypokemon.
This is possible because you can never try to catch both at the same time.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [x] week 01 topics applied
    - [x] const keyword applied proactively (variables, functions,..)
    - [x] static keyword applied proactively (class variables, static functions,..)
    - [x] object composition (optional)
- [x] week 02 topics applied
- [x] week 03 topics applied
- [x] week 04 topics applied
- [x] week 05 topics applied
- [x] week 06 topics applied
- [x] week 07 topics applied
- [x] week 08 topics applied
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Your Name - alexander.vannieuwkerke@student.howest.be

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. 

* [The spriteSheets I used](https://www.spriters-resource.com/game_boy_advance/pokemonpinballrubysapphire/)
* [This video was usefull to better understand some mechanics](https://www.youtube.com/watch?v=XquiJQEybSs)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

