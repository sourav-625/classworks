# TODO: Fix and Polish timber1.cpp (Timberman Game)

## Information Gathered
- timber1.cpp is functional SFML game with branches, player chop, death, sounds.
- Bugs: Redundant srand calls (fixed in Step 1), Enter restart spam, input edge issues, uniform bees.

## Detailed Update Plan
1. Global RNG init, remove per-frame srand.
2. Add randomFloat helper (later).
3. Fix Enter to single start.
4. Edge detect for inputs.
5. Vary bees/clouds.
6. Tweak visuals/physics.
7. HUD fixes.

## Progress
- [x] Created TODO.md
- [ ] Step 1: RNG fixes
- [ ] Step 2: Paths (already good)
- [ ] Step 3: Random function
- [ ] Step 4: Enter input fix
- [ ] Step 5: Input edge
- [ ] Step 6: Bee variety
- [ ] Step 7: HUD center
- [ ] Complete & test

Followup: g++ timber1.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o timber1 && ./timber1

