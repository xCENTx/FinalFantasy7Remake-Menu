# FinalFantasy7Remake-Menu
> [!Important]
> - This cheat menu is intended for educational and single-player use only.
> - Use cheats responsibly and respect the terms of use of the games you are modifying.

> [!Note]
> **[STEAM VERSION](https://store.steampowered.com/app/1462040/FINAL_FANTASY_VII_REMAKE_INTERGRADE/)**
## 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cbc3882304214812965baa36ff662de7)](https://www.codacy.com/gh/xCENTx/FF7RemakeInternal/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xCENTx/FF7RemakeInternal&amp;utm_campaign=Badge_Grade) 
![Static Badge](https://img.shields.io/badge/NightFyre%20DX11%20Base%20Hook-query?style=flat&logo=github&logoSize=auto&labelColor=0D1117&link=https%3A%2F%2Fgithub.com%2FNightFyre%2FDX11-ImGui-Internal-Hook)
![image](https://user-images.githubusercontent.com/80198020/174692162-279ded07-3844-46bd-b00a-3290cac2fbaf.png)

## FEATURES
- Party Stats Manager
- Basic Cheats

## USAGE
- Compile Solution ( DLL ) 
- Launch FF7 Remake Integrade as you normally would
- Inject DLL with program of choice ( CheatEngine, Process Hacker, GH Injector . . . )
- A beep will announce the success of the hooking of dx11 and a welcome message will be displayed.
- Navigate the menu with controller , keyboard and/or mouse

## UPDATING
- Main Class  
-- qword_1457B9268
  
<details>
  <summary>Pause Game</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L264-L307
</details>

<details>
  <summary>Gamepad Input</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L249-L261
</details>

<details>
  <summary>Infinite Health</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L310-L385
</details>

<details>
  <summary>Infinite Mana</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L388-L488
</details>

<details>
  <summary>Infinite Items</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L491-L692
</details>

<details>
  <summary>Enemy Stats</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L695-L751
</details>

<details>
  <summary>Enemy Stagger</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/2e5157693049e2f4597509ce1ed24129686ad7d7/src/Game.cpp#L754-L764
</details>

## CONTRIBUTING
- Issues are to be used for programming error only such as application crashing induced by methods in the module. Please refrain from opening issues in regards to outdated offsets.
- Pull requests are welcome , please adhere to the coding guidlines as outlined below
<details>
  <summary>GUIDELINES</summary>
  https://github.com/xCENTx/FF7RemakeInternal/blob/e612bcb671b6558d44d3addc26331aa9fba8b200/include/Game.h#L7-L22
</details>

### References & Credits
[Dear ImGui](https://github.com/ocornut/imgui)  
[MinHook](https://github.com/TsudaKageyu/minhook)  
[DX11-Internal-Base](https://github.com/NightFyre/DX11-ImGui-Internal-Hook)  
