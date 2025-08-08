# Bonsly Raytracer 
**Bonsly Raytracer** is a raytracing rendering done by Togla Onay and me for the lecture [Computer Graphics](https://graphics.cg.uni-saarland.de/courses/cg1-2024/index.html) during the winter semester 2024/2025 at Saarland University. The lecture team provided the Lightwave framework, and students are supposed to implement many different features above it. Many things such as perspective camera model, point light and directional light, as well as denoising are handled by our renderer.

More about Lightwave framework can be found [here](https://github.com/Wycole/Bonsly/blob/main/docs/README.md).

Also, visit our project website [yoldas](https://wycole.github.io/yoldas-website/) for more information!

## Submission for the Rendering Competition


## Features
* Perspective camera model
* Triangle meshes(polygon), rectangle, and sphere primtives
* Diffuse, conductor, dielectric, and principled BSDFs
* Image and checkerboard textures
* Shading Normals
* Alpha masking

And there are some highlighted features with images shown below.
* Thin lens camera
<table>
<tr>
  <td align="center">with Perspective Camera</td>
  <td align="center">with Thin Lens Camera</td>
</tr>
<tr>
    <td><img src="features/thinlens/camera_perspective.png"</td>
    <td><img src="features/website_images/camera_thinlens.png"</td>
</tr>
</table>

* Halton sampler
<table>
<tr>
  <td align="center">Independent Sampling</td>
  <td align="center">Halton Sampling</td>
</tr>
<tr>
    <td><img src="features/website_images/halton_sampler_bunny_ref.jpg"</td>
    <td><img src="features/website_images/halton_sampler_bunny_test.jpg"</td>
</tr>
</table>

* Image denoising
<table>
<tr>
  <td align="center">Noisy</td>
  <td align="center">Denoised</td>
</tr>
<tr>
    <td><img src="features/website_images/denoise_without.png"</td>
    <td><img src="features/website_images/denoising.jpg"</td>
</tr>
</table>

* Rough dielectric
<table>
<tr>
  <td align="center">Forsted Glass (roughness = 0.3) </td>
  <td align="center">Clear Glass (roughness = 0.0) </td>
</tr>
<tr>
    <td><img src="features/website_images/roughDielectric_frosted_envmap1_expos0.png"</td>
    <td><img src="features/website_images/roughDielectric_glass_envmap1_expos0.png"</td>
</tr>
</table>

## How to run
After building the project with CMake you can either run all local tests:
```bash
  python ./run_tests.py
```
or render your own XML scene file using:
```bash
  <path/to/scene> scene.xml
```

## Copyright and Credits
Lightwave was written by [Alexander Rath](https://graphics.cg.uni-saarland.de/people/rath.html), with contributions from [Ömercan Yazici](https://graphics.cg.uni-saarland.de/people/yazici.html) and [Philippe Weier](https://graphics.cg.uni-saarland.de/people/weier.html).
Many of our design decisions were heavily inspired by [Nori](https://wjakob.github.io/nori/), a great educational renderer developed by Wenzel Jakob.
We would also like to thank the teams behind our dependencies: [ctpl](https://github.com/vit-vit/CTPL), [miniz](https://github.com/richgel999/miniz), [stb](https://github.com/nothings/stb), [tinyexr](https://github.com/syoyo/tinyexr), [tinyformat](https://github.com/c42f/tinyformat), [pcg32](https://github.com/wjakob/pcg32), and [catch2](https://github.com/catchorg/Catch2).
