# Genetic-Algorithm
Genetic Algorithm is a search heuristic that is inspired by the process of natural selection and evolution. It is used to solve optimization problems by mimicking the process of natural selection, where the fittest individuals are selected for reproduction to produce the next generation of individuals.

In Genetic Algorithm, the solution to the optimization problem is represented as a chromosome, which is a string of bits or a vector of real numbers. The chromosome is encoded in a way that represents a potential solution to the problem. The fitness of each chromosome is evaluated using a fitness function, which measures how well the chromosome solves the problem.

The Genetic Algorithm works by initializing a population of chromosomes randomly and then applying genetic operators, such as selection, crossover, and mutation, to the population to produce a new generation of chromosomes. The selection operator chooses the fittest individuals from the population to be used for reproduction, while the crossover operator combines the genetic information from two individuals to produce offspring. The mutation operator introduces random changes to the chromosomes to maintain genetic diversity.

The process of selection, crossover, and mutation is repeated for several generations, and each generation is evaluated using the fitness function. The algorithm terminates when a satisfactory solution is found or after a predetermined number of generations.

Genetic Algorithm has been successfully applied to a wide range of optimization problems, such as feature selection, scheduling, and image processing. However, it may not always find the optimal solution and may get stuck in local optima. Therefore, it is important to choose appropriate parameters and to run the algorithm multiple times to increase the chances of finding the global optimum.



This is a C program implementing a genetic algorithm to find the optimal solution to a given problem. The problem is not specified in the code, but it seems to involve finding a set of individuals with certain characteristics, as indicated by the fitness function.

The main function of the program controls the algorithm flow. It starts by calling the getinputparams function to get the required parameters from the user. These include the size of the population, the representation size of individuals, the mutation probability, the maximum fitness level of the optimal solution, the maximum number of iterations, the base size, and the lower and upper bounds.

After initializing the population and evaluating its fitness, the program enters a loop that runs until the maximum number of iterations is reached or the optimal solution is found. In each iteration, it recombines the parents to create children, mutates the children, evaluates their fitness, and creates the next generation of the population.

The recombineparents function performs crossover between pairs of parents to create children. The crossover point is selected randomly from the representation size. The mutatechildren function performs mutation on the children with a given probability. The mutation involves randomly selecting an index in the individual and changing the value at that index to a random value in the allowed range.

The makenextgenpopulation function creates the next generation of the population by selecting the best individuals from both the population and the children. The selection process is based on the fitness of the individuals, with a higher fitness value indicating a higher chance of being selected. The selected individuals replace the worst individuals in the current population.

The solutionfound function checks if the optimal solution has been found by looking for an individual with a fitness equal to the maximum fitness level of the optimal solution. If such an individual is found, the function returns 1, indicating that the optimal solution has been found.

The fitness function calculates the fitness of an individual by counting the number of times a certain value appears in the individual. The value is BASE_SIZE - 1, which is derived from the upper bound entered by the user.

The program prints the data for each generation of the population and the children. It also prints the solution when it is found, including the fitness value and the individual. The program terminates by printing the solution and some parameters of the run.
