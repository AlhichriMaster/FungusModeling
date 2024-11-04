# Project: Procedural Modeling of Fungus and Mushroom Surface Patterns

## S1. Group Members
1. Youssuf Hichri
2. Momin Khan

## S2. Main Idea
The primary focus of this project is to create detailed procedural models of fungi and mushrooms, with particular emphasis on surface patterns and structural details. Rather than focusing on basic shapes, we will concentrate on capturing the intricate surface features that make fungi visually distinct, such as:

- The complex ribbed patterns on the underside of mushroom caps
- The varying textures of the cap surface (scaly, smooth, or warted)
- The intricate network of mycelial threads at the base
- The rings and patches on the stem (annulus and volva features)

Reference Species for Modeling:
1. Amanita muscaria (Fly agaric)
   - Notable features: White warts on red cap, prominent ring on stem
   - Challenge: Procedural generation of regularly spaced wart patterns
   
2. Trametes versicolor (Turkey tail)
   - Notable features: Concentric zones of different colors, thin shelving structure
   - Challenge: Generating coherent zone patterns and color variations

3. Pleurotus ostreatus (Oyster mushroom)
   - Notable features: Overlapping shelf-like clusters, gill patterns
   - Challenge: Modeling the relationship between multiple caps in a cluster

## S3. Graphics Focus
This project will concentrate on advanced procedural modeling techniques:

1. Implicit Surface Modeling
   - Using metaballs and implicit functions for organic form generation
   - Blending functions for smooth transitions between features
   
2. Surface Pattern Generation
   - Procedural texture generation for specific fungal features
   - Voronoi patterns for crack and scale effects
   - Custom shader development for surface detail rendering

## S4. Resources and Precedent
Our research will focus on:
- Mycological documentation for accurate structural reference
- Papers on implicit surface modeling in biological contexts
- Research on procedural pattern generation, particularly for natural structures
- Studies on biological pattern formation (e.g., Turing patterns) for surface detail generation

## S5. Breakdown of Objectives
1. Develop base implicit surface representation for primary fungal forms
2. Implement procedural generation of:
   - Cap surface patterns (warts, scales, zones)
   - Gill or pore structures
   - Stem textures and features
   - Mycelial networks
3. Create parameter system for controlling:
   - Pattern density and distribution
   - Surface feature prominence
   - Overall form variations
4. Implement realistic surface shading including:
   - Subsurface scattering effects
   - Micro-surface detail
   - Material variation

## S6. Midterm Goal
By October 28th, we aim to complete:
1. Basic implicit surface framework for main fungal forms
2. Initial implementation of one major surface pattern type
3. Prototype of parameter control system
4. Basic shader implementation

## S7. Tools and Software
- OpenFrameworks for core implementation
- Custom GLSL shaders for surface detail rendering
- Potentially Unity for additional shader development
- Blender for reference visualization and testing

## S8. Optional Stretch Goals
If time permits:
1. Implementation of multiple pattern types within single specimens
2. Advanced material effects (translucency, iridescence)
3. Generation of cluster formations
4. Integration of natural variation parameters
