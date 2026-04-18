# AI-Arena-UE

A combat-focused AI prototype built in Unreal Engine 5, demonstrating behavior-driven enemies using Behavior Trees, AI Perception, and modular combat systems.

---

## Overview

This project is a third-person arena where AI enemies patrol, detect the player, chase, attack, and disengage using a fully structured Behavior Tree system.

The goal of this project was to build a **clean, extensible AI foundation** that can be expanded into more advanced enemy behaviors and combat systems.

---

## Features

### AI Behavior System

* Patrol → Detect → Chase → Attack → Lost → Return to Patrol
* Behavior Trees with modular task nodes
* Blackboard-driven decision making

### AI Perception

* Sight-based detection using Unreal’s AI Perception system
* Dynamic target acquisition and loss handling

### Combat System

* Attack montages (combo-ready structure)
* Damage system with health tracking
* Player knockback on hit
* Attack range validation

### State Debug System

* Real-time enemy state display:

  * PATROLLING
  * CHASING
  * ATTACKING
  * LOST

### Multiple Enemy Support

* Independent AI agents operating simultaneously
* No cross-targeting between enemies
* Scalable behavior architecture

### Player HUD

* Dynamic health bar
* Smooth interpolation
* Color transitions (green → yellow → red)
* Damage feedback flash

---

## Tech Stack

* Unreal Engine 5.7
* C++
* Blueprint (Behavior Trees, UI, AI Tasks)
* AI Perception System
* Animation Montages

---

## Project Structure

```plaintext
Source/
  AI/
    ArenaEnemyCharacter
    ArenaEnemyController

Content/
  AI/
    BehaviorTrees/
    Blackboard/
    Tasks/
    Services/

  Characters/
  UI/
  Maps/
```

---

## Demo

*(....)*

---

## Key Learnings

* Designing AI using Behavior Trees for clarity and scalability
* Integrating C++ systems with Blueprint-driven workflows
* Debugging AI state transitions and perception edge cases
* Structuring reusable AI logic for multiple agents

---

## Future Scope

This project is intended as a **base system for advanced AI development**. Planned upgrades include:

### Combat & Animation

* Player hit reaction animations
* Root-motion attacks with forward momentum
* Combo chaining and attack variety
* Stagger / interruption system

### Advanced AI

* Flanking and group tactics
* Dynamic difficulty adjustment
* Threat-based target prioritization
* Memory system (last seen positions, prediction)

### Enemy Types

* Ranged enemies
* Heavy / tank enemies
* Fast / evasive enemies
* Boss AI with multi-phase behavior

### Systems Expansion

* Damage types and resistances
* Status effects (stun, slow, knockdown)
* Aggro system
* Spawn waves and arena progression

### Polish

* Improved VFX for hits and feedback
* Audio integration (footsteps, attacks, alerts)
* Cinematic camera moments
* Better UI/UX feedback

---

## Setup Instructions

1. Clone the repository
2. Open the `.uproject` file in Unreal Engine 5.7
3. Generate project files if prompted
4. Build (if needed)
5. Open `L_Arena` map and press Play

---

## Author

Jaswinder Singh 
Applied Computer Science Student
Game Development & AI Systems Focus

---

## Notes

This project focuses on **AI systems design and gameplay logic**, with visual polish kept minimal intentionally during development.

---
