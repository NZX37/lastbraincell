# LastBraincell: devlog

> An e-paper device with joystick and buttons to write down reminders, a to-do list and basic references(like resistor table) as well as a calendar!

| Week | Tier | Hours logged | Entries |
| --- | --- | --- | --- |
| Week 4 | Tier 2 | 22h | 4 |

## Contents

1. [2026-10-30: # Schematics!](#2026-10-30-schematics)
2. [2026-10-31: # PCB](#2026-10-31-pcb)
3. [2026-10-31: # Exporting files and BOM](#2026-10-31-exporting-files-and-bom)
4. [2026-11-01: # Fixes and microSD](#2026-11-01-fixes-and-microsd)

## Design

### 2026-10-30: # Schematics!

**6h**

# Schematics!

## tl;dr
I finished the schematic and footprint assignment for the project

## Joystick

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/a775c29e9efb9753b5238b4d52f2a292bd29ceb46e8d627e49a150d8e24a6734.png)
I downloaded this off [snapEDA](https://www.snapeda.com/parts/COM-09032/SparkFun/view-part/) and used a [basic schematic](https://cdn.sparkfun.com/datasheets/BreakoutBoards/Joystick-Breakout-v12b.pdf)

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/23ea109ebf2fb56e1a2690be2ccead0307f3acdff8617b3c2b00e861e867eb74.png)

## ESP32
I am using a dev kit so its two rows of headers.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/6ec9611dbc815806d94d067b9af1ad4fd8827303c29b03c1016f6fed7a6a2c78.png)

## Modules

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/1dedc90eb3a103594c019dbd7144c6da9c3794d2610ca7d651579861d8e2982a.png)
These are basic wirings for the other components needed.

## Footprints

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/e90e60892b1fdc75b11dbdfd22858df953af46464f8cb3f46070ac0db701fcc1.png)
Also quite simple, except the original footprint file gave me issues on first download, I had to "retry" to get it to work.

## To Do
PCBs

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/d9e1eadeb726e3893d71909918fd1a03fd6b6f11b08e77ff8a59639808736d6c.png)

### 2026-10-31: # PCB

**7h**

# PCB

## Routing
This was basically just connecting with tracks, using filled zones for anything power related and a big ground fill!
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/1120829295609281b305ba69ad6953f25eac678659724b4c4a44c7fa851c3189.png)

## Silkscreen and Edgecut

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/3f5c1f4808dd017b69df27ef05778375a0e4918002f34faf658e26092129b847.png)
Just a few fixes.

## CAD
I planned on using the screen below but could not find a 3D model
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/9918cf361f4c381c6e9d141eae37db7f4c55307a8d7c88f990b65452ee436fd5.png)

So I decided to just use a rectangle body in Fusion. I calculated the length and width based off resolution ratio and diagonal length.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/4b5ae2dbe950ccd0bf474b01937789c31f5ec479311971aad4c17be727e2209f.png)
Mesh bodies I used to model the case!

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/81dbef4867e61c4f0bfc417a430f12ac82eb8cc5073335e7de3a44770dad7b7a.png)

Case done!!

## Quick screen fix

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/c6ba948f9b61b7eb160f446d0d619a8dabf7b78142679fd4f0c2ec0264d42c38.png)

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/2dcfd727d4d0a1b8b1258453f537d5316ee163f5d03662f26ec1f25641a4f05a.png)
The screen was rotated the wrong way so quick fix!

### 2026-10-31: # Exporting files and BOM

**2h**

# Exporting files and BOM

## Exporting CAD files

I exported the .stl, .step and fusion editor files and git commit to the repo.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/c40a17d1d8993b1c0f1c90bfee242b5168403c38ea864aabfbeda30b11d3a1d0.png)
## Exporting PCB

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/ed10f05284797bd2689759cb79c65215ca9d1575a2761f29ab4e0526d0e39e9e.png)
I used the JLCPCB plugin to export gerbers in a zip.

## Full Mockup

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/8731a82664585f893fad2b380118e6af1454f7255bf276ed16d5d31ffcf9969f.png)
This is in the fusion file which was also put into the repo.

### 2026-11-01: # Fixes and microSD

**7h**

# Fixes and microSD

## MicroSD
I previously used a prebuilt module as a stand in, but now switched to using the smd component with some resistors.
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/caf1e92be081aafd68d12e33c18efcb22e769dc17d07315b8b4da3a6f8d6309b.png)
Schematic View
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/92ed853d4d452823ed67d3082b7010579c9f6c79bb65ddb845a17ad22df72cb9.png)
PCB View
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/27db8bc612bd7357eecbb68789cfa3970ce08631aad6f8fcc488fe1d7fea1542.png)
3D viewer
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/558095199bb063c6c01baea2d34b07b0c19f3954b1f9a9c96fa1b1443ebe533e.png)

## CAD
With the module, I had to add a space for the microsd module to protrude in the case files.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/558095199bb063c6c01baea2d34b07b0c19f3954b1f9a9c96fa1b1443ebe533e.png)

## Costs of PCB
Using JLCPCB, I calculate the cost to be $3.50. The below graphic is from JLCPCB.
![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/b4d74a78f115c523aad522c25404914652127c20226aba601d88ab3a6083ed9f.png)

## Readme

Just following the guides. I did add this cool PCB button that i previously glossed over.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/2a5c57cddd88c1590382411f1964a88055c32fc2c883928985772f62d4f6fb91.png)

## Code

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/ed5dcf2aa07efe7bb4c76602137e1998f3e8c977e4364e17a86a1f2f58ebab46.png)

This code tests that the screen and calendar functions work, since I cannot really implement the full system without testing it out on the PCB and I typically do not do firmware before getting the actual boards.

![image](https://halflife.hackclub-assets.com/sessions/u4daV3AON4Vg7wKuOmDpozDubBrsNyfk/431ad625891cbe35745408061f68838ea5bed95ffd361cac8b0bb7b516515cd6.png)

Full github repo!
