# WormSim
This project simulates life of unspecified worms. They are placed in a closed space, where they can move, eat, grow, breed and die. The ground is self-replenishing food source. The parameters that are considered in simulation:
    - amount of worms that are hatched from one egg,
    - hunger of worms - for how long (in ticks) they can walk on tiles that don't have food on them,
    - rate of food regeneration,
    - max size of worms,
    - average productivity time - for how long (in ticks) is worm able to lay an egg, range equals +- 10% of it's value,
    - average lifespan - for how long (in ticks) worm can live, range equals +- 10% of it's value.

Legend:
    - red square - food that replenishes 1 food unit when eaten,
    - orange square - food that replenishes 2 food units when eaten,
    - green square - food that replenishes 4 food units when eaten,
    - white square - worm's head and body segments,
    - pink square - worm egg.