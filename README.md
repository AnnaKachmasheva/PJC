# Hra Mario

## POPIS

--TODO

Program automaticky vyhodnotí výsledek hry a tyto imformace zobrazí na terminál.

## KOMPILACE PROGRAMU
Program lze zkompilovat následujícím příkazem:
```bash
cmake -Bcmake-build-debug -H. -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debug
```

## SPUŠTĚNÍ A PŘEPÍNAČE
Hra se spouští z příkazové řádky.
Parametry nastavení programu:
- -c (-coins) - počet minci,
- -e (-enemies) - počet nepřateli,
- -l (-lives) - počet životů.

Pokud nejsou parametry programuza dány, jsou využity předefinované hodnoty: c = 10, e = 10, l = 5.

Příklady spuštění programu: 
```bash
Mario
Mario -c 5 -h 5 -c 5
```

## OVLÁDÁNÍ PROGRAMU

- `w` - UP
- `a` - LEFT
- `d` - RIGHT
- `q` - QUITE GAME
- `p` - PAUSE GAME
- `r` - RUN GAME

## UKONČENÍ PROGRAMU
Program se automaticky ukončí, když hráč dosáhne konce pole napravo nebo ztratí všechny životy.

Program je možné kdykoliv ukončit klávesou `q`.

## TESTOVÁNÍ PROGRAMU

--TODO

[//]: # ()
[//]: # (### Příklad testů pro hru Piškvorky &#40;rozměry 3x3&#41;:)

[//]: # (-	`q`)

[//]: # (-	`1q`)

[//]: # (-	`12q`)

[//]: # (-	`112233q`)

[//]: # (-	`1121223133`		- vyhrává kolečko &#40;hlavní diagonála&#41;)

[//]: # (-	`122113112231`		- vyhrává křížek &#40;sloupec vlevo&#41;)

[//]: # (-	`1221223233111331`	- vyhrává křížek &#40;sloupec vlevo&#41;)

[//]: # (-	`112112223123`		- vyhrává křížek &#40;prostřední řádek&#41;)

[//]: # (-	`311122213113`		- vyhrává kolečko &#40;vedlejší diagonála&#41;, kolečko – chybné zadání)

[//]: # (-	`11121321222331`	- vyhrává kolečko &#40;vedlejší diagonála&#41;)

[//]: # (-	`111222333121321323`	- remíza)

[//]: # (-	`1121311233222332`	- vyhrává křížek &#40;prostřední sloupec&#41;)

[//]: # (-	`13s2223z1133`		- vyhrává kolečko &#40;sloupec vpravo&#41;)

[//]: # (-	`1121122213`		- vyhrává kolečko &#40;horní řádek&#41;)

[//]: # (-	`3122211133132232` 	- vyhrává kolečko &#40;dolní řádek&#41;, kolečko – chybné zadání)

[//]: # (-	`1122213113123223`	- remíza)

[//]: # (### Příklad testů pro hru Piškvorky &#40;rozměry 7x5, 4 značky v řadě&#41;:)

[//]: # (-	`112212132333344521445553463526154325`		- vyhrává křížek)

[//]: # (-	`112212231314243515173351162644534352544527`	- remíza)

[//]: # (### Příklad testů pro hru Piškvorky &#40;rozměry 7x5, 5 značek v řadě&#41;:)

[//]: # (-	`11221223212431252613415133353246574217522753544337474445151634`	- remíza)

[//]: # (-	`1122122321243125261341513335324657421752275354433747441516453455`	- vyhrává křížek)

[//]: # (-	`1122122313142435151733511626445343525445273442`			- vyhrává kolečko)
