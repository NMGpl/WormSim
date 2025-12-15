# WormSim
This project simulates life of unspecified worms. They are placed in a closed space, where they can move, eat, grow, breed and die. The ground is self-replenishing food source. The parameters that are considered in simulation:
    \n- amount of worms that are hatched from one egg,
    - **worm hunger** - for how long (in ticks) they can walk on tiles that don't have food on them,
    - **food regeneration rate**,
    - **worm max size**,
    - **average productivity time** - for how long (in ticks) is worm able to lay an egg, range equals +- 10% of it's value,
    - **average lifespan** - for how long (in ticks) worm can live, range equals +- 10% of it's value.

###Legend:
    - `rgb(230, 41, 55)`**red** square - food that replenishes 1 food unit when eaten,
    - `rgb(255, 161, 0)`**orange** square - food that replenishes 2 food units when eaten,
    - `rgb(0, 228, 48)`**green** square - food that replenishes 4 food units when eaten,
    - `rgb(255, 255, 255)`**white** square - worm's head and body segments,
    - `rgb(255, 109, 194)`**pink** square - worm egg.
