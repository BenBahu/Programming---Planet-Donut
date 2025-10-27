# OOP Project — Robot Simulation (GTKmm)

Authors: Matthieu Lavoix and Benjamin Bahurel

This project implements an object-oriented simulation of bases and robots (communication, prospecting, drilling, transport) with a GTKmm graphical interface. The goal is to maximize base survival and resource extraction by optimizing the strategy for creating/maintaining robots and the communication network.

## Glossary

- 4G: planet-wide communication network built by communication robots
- R: resources
- combo: one drilling robot + one transport robot

## Concept and key constants

- 49 communication robots are enough to cover the whole planet (cost: 49 × 1 R = 49 R)
- A transport robot without a drilling robot (and vice versa) is useless; a combo costs 200 R (2 × 100 R)
- Repairing is cheaper than producing a new robot
- Prospecting: ~20,000 km costs 15 R (sending two robots: ~20 R)
- Draining a deposit yields 250 R
- Guiding principle: “One single transport return is enough to fund 4G and to start draining another deposit”

## Robot modes: remote vs autonomous

Only the prospecting robot behaves fundamentally differently between the two modes.

- Prospecting
  - Remote: checks for deposits at every move; goal can be redefined randomly; can return for maintenance
  - Autonomous: checks only upon arriving at its goal, then returns to base
- Communication: moves only toward its goal, no redefinition of the goal (same in both modes)
- Drilling: moves toward the goal; extracts deltaR if a transport overlaps with it, then sends the transport back; goal is not redefined
- Transport
  - Remote: moves to a drilling robot not yet being served whose deposit is not empty
  - Autonomous: moves to a drilling robot, and returns on order if drilling is possible; on its first return, the 4G is set up, then the behavior follows the remote case

Internal limits: at most 49 communication robots and 4 prospecting robots at the same time. Combos are created on each discovery of an interesting deposit, when it makes sense.

## High-level strategy

- Set up the 4G network as quickly as possible to maximize search area
- As soon as a deposit is found and a transport robot returns at least once, the base “survives” (net +250 R)

Decision intervals by available R:

1) Less than 200 R and no combo → base is doomed (maintenance will slowly drain resources)
2) More than 70 R with at least one combo → can deploy 4G and launch prospecting; a single transport return brings the base above 250 R
3) More than 270 R → create 4G (-49 R) + 1 prospector (-10 R) + 2 robots to drain a deposit (-200 R) + 11 R left for maintenance
4) Between 200 and 270 R with no combo → send only one prospector until a deposit is found, then send a combo; deploy 4G only after a transport has returned

## Algorithmic overview (class `Simulation`)

- Update neighbors: for each base, build the neighbor list (connection graph) and visual links; only robots from the same base are considered neighbors
- Connectivity: traverse the graph from the central communication robot; mark connected robots via recursion; keep centralized info in a single `robots_base` array
- Maintenance: reset counters of robots overlapping with the base at the cost `0.0005 × distance traveled`; always performed given the low cost
- Creation: (1) decide if/when to complete 4G, (2) send up to 4 prospectors, (3) if a connected prospector finds a deposit, decide whether to create a combo; robots are created strictly on demand
- Updates: `updates_remote` and `update_autonome` call robot virtual methods `mode_remote` / `mode_autonome`
- Robots update: build an aggregated view of all robots to ease some global operations
- Bases update: remove bases that become non-viable autonomous ones (less than 200 R without a combo, or 0 R)

## Robustness and issues

- Robust strategy because prospectors choose random goals for both sides; 4G maximizes survival chances
- Most frequent issue: segmentation faults in mid-simulation; mitigated via dichotomic search and targeted fixes

## Code structure

- Models: `geomod.*`, `gisement.*`, `robot.*`, `base.*`, `simulation.*`
- UI/graphics: `graphic.*`, `graphic_gui.h`, `gui.*`, `scroll.*`, `message.*`
- Entry point: `projet.cc`
- Misc: `constantes.h`, `Makefile`, scenario files `rendu3_01.txt`, `rendu3_02.txt`

## Prerequisites

- g++ (C++11)
- pkg-config
- GTKmm 3.0

macOS (Homebrew) — install dependencies:

```bash
brew install pkg-config gtkmm3
```

Linux (Debian/Ubuntu):

```bash
sudo apt-get update
sudo apt-get install -y build-essential pkg-config libgtkmm-3.0-dev
```

## Build

The `Makefile` builds an executable named `projet`.

```bash
make
```

Clean build artifacts:

```bash
make clean
```

## Run

The application launches a GTK window. You can provide a scenario file as an argument to initialize the simulation.

```bash
./projet                 # launch UI without an explicit scenario
./projet rendu3_01.txt   # run with scenario 1
./projet rendu3_02.txt   # run with scenario 2
```

Runtime note (from `projet.cc`): if a file path is passed as an argument, `Simulation::lecture()` reads the scenario before showing the window. Default window size is 900×900.

## Provided scenarios

- `rendu3_01.txt`: “rebouclement” — 3 deposits and 1 base; observe 4G setup after first transport return and rapid discovery of other deposits
- `rendu3_02.txt`: a base with no resources is destroyed at the end of the first update; includes 1 deposit and 3 bases with contrasting states

## Debugging tips

- Compile with `-Wall -std=c++11` (already enabled in the Makefile)
- Run often and use asserts to track memory issues
- If crashes occur late, isolate steps via dichotomic search (technique used during the project)

## Work split

- Modeling: Georg (`geomod`, `gisement`, `robot`, `base`, `simulation`)
- UI and integration: Daniel (`graphic`, `graphic_gui`, `gui`, `scroll`, `projet`, `Makefile`)
- Tests: dedicated files and ad-hoc scenarios

## License

Academic project (EPFL BA2) — educational use.
