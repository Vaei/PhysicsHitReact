# Physics Hit React <img align="right" width=128, height=128 src="https://github.com/Vaei/PhysicsHitReact/blob/main/Resources/Icon128.png">

> [!IMPORTANT]
> **Procedural physics-driven hit reactions for skeletal meshes!**
> <br>High levels of customization and extendability
> <br>Fully extendable in Blueprint
> <br>And its **Free!**

> [!TIP]
> Suitable for both singleplayer and multiplayer games

## Watch Me
TODO Showcase

TODO Overview

## Why Make a Hit Reaction Plugin?

> [!NOTE]
> Existing solutions and tutorials have severe limitations:

  * Visually disruptive when multiple hit reactions overlap
  * Lacks throttling to prevent frequent re-application of effects
  * No built-in handling for rapid re-application scenarios
  * Child bones’ blend weights are often overridden by parent bones
  * No option to disable blend weights or physics simulation on individual bones
  * Lacks support for overriding physics on arms when wielding a weapon
  * Re-simulation of an already active bone is not managed
  * Designed for single reactions, leading to instability and visual disruption with repeated hits
  * Limited consideration for real-world application in complex projects

> [!NOTE]
> PhysicsHitReact addresses all these limitations, delivering a stable, production-ready framework capable of commercial game development.

## Features
### Impulses
Supports Linear, Angular, and Radial impulses

Supports applying impulses to bones separate from the simulated bone

### Per-Bone Tuning
Supports disabling physics or using custom blend weights on child bones of the simulated bone

This means we can disable physics only on the arms for our character who is aiming a rifle!

### Profiles
Supports extendable profiles, simply specify the profile you want to use when triggering a Hit React

TODO

## How to Use
> [!IMPORTANT]
> [Read the Wiki to Learn How to use Hit React](https://github.com/Vaei/PhysicsHitReact/wiki)

## Changelog

### 1.4.0-beta
* Completely rebuilt the interpolation to better handle multiple states
* Completely rebuilt the global toggle
* All interpolation values are time based instead of rate based now
* Decay works properly, full support for Hold state
* Bones are sorted so child bones are processed last, allowing them to maintain their own blend weights
* Added new built-in blend profiles
	* Added TakeShot Unarmed/Armed profiles designed for rapid reapplication
	* Added TakeMelee Unarmed/Armed profiles designed for slower reapplication

### 1.3.0-beta
* Introduced the concept of interpolation decay, to handle reapplication of in-progress hit reacts
	* Getting hit repeatedly can now smoothly rewind the blend system partially!
	* WIP system that will become fully fledged in 1.4.0
* Overhauled application of hit reacts based on real-world usage
* Overhauled default profiles for great starting point parameters
	* Added more profiles
* Added PreActivate as a convenient point to cast and cache the owner in derived UHitReactComponent
* Add BlacklistBones and RemapBones for both simulated and impulse bones
* Added intensive data validation to UHitReactComponent to ensure coherent data
	* This is only really intended to avoid user-error resulting in undesired outcomes, hit react itself doesn't need it
* Improved debugging capability with p.HitReact.Debug.BlendWeights
* Fixed bug with cooldowns not applying
* Fixed bug with collision settings not updating
* Fixed edge case where completed hit reacts were not removed

### 1.2.1-beta
* Added global disable CVar

### 1.2.0-beta
* Restructure and unify properties and parameters based on tested use-cases
	* Introduce FHitReactApplyParams for passing around the required data to apply a hit react
	* Update UHitReactComponent::HitReact() to use this
* Expose the blend params -- oops
* Refactor properties>params for consistency
* Add net serialization to FHitReactImpulseParams and FHitReactImpulseWorldParams and all contained types
* Add BlueprintCosmetic where appropriate

### 1.1.2-beta
* Improve tick settings
* Improve dedi server handling
* Add PhysicsHitReactEditor module
* Add details customization to hide properties that shouldn't be touched
	* Tick in particular, because the system must handle it internally

### 1.1.1-beta
* Default profile if none provided to HitReact()
* Separate transient data from ImpulseParams into new WorldSpaceParams
* Improved failure debug logging
* Added check for physics asset

### 1.1.0-beta
* Add support to include GameplayAbilities as optional plugin
* Add support for ability tags to disable/enable the system
* Fix missing null check for optional PhysicalAnimationComponent

### 1.0.0-beta
* Initial Release
