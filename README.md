# Proc Hit React <img align="right" width=128, height=128 src="https://github.com/Vaei/ProcHitReact/blob/main/Resources/Icon128.png">

> [!IMPORTANT]
> **Procedural physics-driven hit reactions for skeletal meshes!**
> <br>High levels of customization and extendability
> <br>Fully extendable in Blueprint
> <br>And its **Free!**

> [!TIP]
> Suitable for both singleplayer and multiplayer games
> <br>Supports UE5.2+

## Watch Me
TODO Showcase

TODO Overview

## How to Use
> [!IMPORTANT]
> [Read the Wiki to Learn How to use Hit React](https://github.com/Vaei/ProcHitReact/wiki)

## Why Make a Hit Reaction Plugin?

> [!NOTE]
> ProcHitReact addresses all these common limitations:

  * Visually disruptive when multiple hit reactions overlap
  * Lacks throttling to prevent frequent re-application of effects
  * No built-in handling for rapid re-application scenarios
  * Child bones’ blend weights are often overridden by parent bones
  * No option to disable blend weights or physics simulation on individual bones
  * Lacks support for overriding physics on arms when wielding a weapon
  * Re-simulation of an already active bone is not managed
  * Designed for single reactions, leading to instability and visual disruption with repeated hits
  * Limited consideration for real-world application in complex projects

## Features
### Ease of Use
In many cases, all it takes is putting a component on your character and calling HitReact on it.

When setting up something out of the ordinary, like the turret in the videos, further setup is necessary, but it can be done even in blueprint.

### Impulses
Supports Linear, Angular, and Radial impulses.
TODO

### Per-Bone Tuning
Supports disabling physics or using custom blend weights on child bones of the simulated bone.

This means we can disable physics only on the arms for our character who is aiming a rifle!

Blacklist bones that don't simulate well, or remap them onto other bones. Don't want your pelvis to simulate because it offsets the entire mesh? Remap it to spine_01.

You can override per-bone application parameters, perhaps the standard impulse being provided for a shot is too strong for your clavicles? Simply add the clavicle to the overrides, and change the scaling.

### Profiles
Supports extendable profiles, simply specify the profile you want to use when triggering a Hit React.

The included HitReactComponent has many profiles setup for you out of the box with good defaults.

### Global Toggle
You can toggle the entire system on and off, with or without interpolation.

If you have the Gameplay Abilities (GAS) plugin enabled in your project, you can use tags to enable and disable the system. This is an optional dependency, ProcHitReact does not require that your project uses GAS and will not enable it for you.

### Sleep & Wake
The system automatically stops itself from ticking when it doesn't need to.

### Powerful Blending
Featuring a purpose-built interpolation framework, you can customize the blending to your liking.

The available states are: Blend In, Hold, and Blend Out. Hold will maintain your physics at full blend weight for the duration.

There is also Decay. When a hit react is already in progress, reapplying it will decay the simulation, making it interpolate backwards. Other systems either reinitialize physics from 0 causing a snap, or simply let it continue causing poor results under continuous application. Decay is the answer to that.

Reapplication can be throttled by setting a Cooldown.

Child bones are always simulated last so that the parent bones don't overwrite their simulation.

### Networking
Generally hit reacts are entirely cosmetic and should be applied via gameplay cues or other generalized multicast/replication events.

The data types used by ProcHitReact, including the application parameters, are net serialized for you, so you can replicate these too.

Dedicated servers don't process hit reacts, unless you enable the setting.

ProcHitReact was designed with multiplayer games in mind.

### Data Validation
ProcHitReact has reasonably stringent data validation to aid users who make a mess of the settings, further improving ease of use.

### Debugging Capability
See the [debugging section on the Wiki](https://github.com/Vaei/ProcHitReact/wiki/Debugging) to learn how to Debug ProcHitReact.

## Changelog

### 1.0.0
* Initial Release