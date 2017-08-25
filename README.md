# Nueral-Evolution-Simulator
2D simulation of evolution using neural networks. 
REFACTOR IN PROGRESS!

Simulation creates 10 animals. Each brain of animal has four inputs( is food: up,down,left,right).
2 hidden layers. 2 output neurons telling how fast to move vertically and horizontally.

Scoring of fitness: More food animal eats higher the score, plus how much time it spent close to food.

DNA: It is their brains weights, vector of floats, the size.

Evolution: After scoring, 2 best brains continue to next generation, 7 are created by crossover with the best.
Plus one is always reinitialized.

Requirements:
-SFML graphic library
-C++11


