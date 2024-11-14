# Zápočtový program - Space Shooter
O hře
Space Shooter je akční arkádová hra, kde cílem hráče je ovládat vesmírnou loď, vyhýbat se nepřátelům a překážkám, zatímco sestřeluje nepřátelské mimozemšťany. Hra se odehrává v nekonečném vesmíru, kde se hráč snaží dosáhnout co nejvyššího skóre, nabízí progresivní obtížnost přes více levelů, každý s unikátními výzvami a nepřáteli.

## Pravidla a průběh hry
Hráč začíná hru s omezeným počtem životů a za každého sestřeleného nepřítele získává body. Počet nepřátel potřebných k postupu do dalšího levelu se zvyšuje. Hra končí, když hráč ztratí všechny životy. Cílem je dosáhnout co nejvyššího skóre a úrovně.

## Spuštění hry a instalace
Pro spuštění hry je potřeba mít nainstalovaný framework SFML. Postup instalace SFML je specifický pro každý operační systém, proto doporučujeme navštívit oficiální dokumentaci SFML pro podrobné instrukce.
Níže je uvedený podrobnější návod pro instalaci na systém Windows.

### Instalace hry na systém Windows

Ke spuštění hry je potřeba stáhnout knihovnu SFML, postup na systému Windows:

1) Nejdříve stáhneme (pokud nemáme) správce balíčků pro Windows vcpkg:

```
git clone https://github.com/Microsoft/vcpkg.git
```

2) Přejdeme do složky a spustíme bootstrap-vcpkg.bat

```
.\vcpkg\bootstrap-vcpkg.bat
```

3) Stáhneme a nainstalujeme knihovnu SFML

```
.\vcpkg\vcpkg install sfml
```

4) Po instalaci knihoven je nutné integrovat vcpkg s Vaším systémem sestavení,
aby cmake mohl najít nainstalované knihovny

```
.\vcpkg\vcpkg integrate install
```

Po spuštění integračního příkazu vcpkg vám bude zobrazena cesta, kterou byste měli předat CMake při konfiguraci projektu, abyste zajistili, že CMake použije knihovny nainstalované pomocí vcpkg.

(pokud nemáme CMake, je nutné ho stáhnout a nainstalovat, zde je odkaz: https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-windows-x86_64.msi - je důležité přidat cestu k binárnímu souboru CMake (obvykle umístěnému v bin složce v adresáři, kde je CMake nainstalován) do systémové proměnné PATH. To umožní spustit CMake z příkazové řádky z jakéhokoli adresáře, což je velmi užitečné pro práci s projekty v C++. Tuhle možnost dostanete při instalaci. Přidání CMake do PATH umožňuje jednoduše zadat cmake do příkazové řádky bez nutnosti uvádět plnou cestu k jeho spustitelnému souboru.)

-----------------------------------------------------------------------------

Nyní přejdeme do kořenového adresáře projektu, který se nachází v project/src, a spustíme následující příkazy CMake k sestavení projektu. Předpokládá se, že kořenový adresář pro konfiguraci CMake je na této úrovni:

```
cd project/src
cmake -B ../cmake-build-debug -S . -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build ../cmake-build-debug
```

Poznámka: Tento příklad předpokládá, že sestavujete projekt v adresáři project/src/debug, který je vytvořen o úroveň výše než vaše zdrojové soubory, což je běžná praxe, aby zdrojové soubory nebyly smíchány se sestavenými soubory. Příkaz cd project/src je potřebný k přesunu do adresáře, kde se nachází CMake konfigurační soubory a zdrojové soubory projektu.

Příkaz cmake -B ../debug -S . říká CMake, aby sestavil projekt do adresáře ../debug relativně k aktuálnímu adresáři (project/src), kde -S . specifikuje, že zdrojové soubory jsou v aktuálním adresáři.

Ještě před spuštěním bude potřeba přesunout adresář "resources" z adresáře /src do právě nově vytvořeného adresáře src/debug.

Následné spuštění sestaveného projektu se může mírně lišit v závislosti na tom, kam přesně byl výstupní soubor umístěn, ale pokud byl sestaven v project/src/debug, pak by příkaz pro spuštění mohl vypadat takto:

```
.\debug\Debug\SpaceShooter.exe
```

## Nastavení a ovládání

Pohyb: W, A, S, D
Střelba: mezerník
Pauza: Esc
Hráč může ovládat loď pomocí klávesnice. Pohybem lodě se vyhýbá nepřátelům a střelbou je ničí.

## O programu

Space Shooter je napsán v C++ s využitím multiplatformního frameworku SFML na tvorbu grafických aplikací. Hra demontruje použití objektově orientovaného programování, práci s grafikou, obsluhu událostí a další.

## Programová dekompozice

### Game.cpp
Game.cpp je centrální bod celé hry. Zde je přehled jejích hlavních funkcí a zodpovědností:

- Načítá textury a fonty pro použití v hře.
- Nastavuje základní herní prvky, jako jsou zdraví hráče, ukazatel zabitých mimozemšťanů a level.
- Vytváří hráčovu postavu, nastavuje její velikost a počáteční pozici.
- Připravuje herní kameru, která sleduje pohyb hráče.
- Inicializuje herní menu a jeho položky.
- Řídí zpracování událostí, jako je zavření okna nebo stisknutí klávesy.
- Zobrazuje herní menu, když je to potřeba.
- Aktualizuje stav hry, zahrnující pozadí, střely, mimozemšťany a lékarničky.
- Spravuje interakce mezi různými herními objekty, jako jsou kolize a střelba.
- Kontroluje postup hráče mezi úrovněmi a spravuje zvyšování obtížnosti hry.
- Vykresluje herní pozadí, hráče, mimozemšťany, střely a lékarničky.
- Zajišťuje, že se všechny grafické prvky vykreslují správně v herním okně.
- Nastavuje a aktualizuje grafické zobrazení zdraví hráče a počtu zabitých mimozemšťanů.
- Spravuje logiku přechodu mezi různými stavy hry, jako je hraní a zobrazení herního menu.
- Řídí ukončení hry a zobrazuje zprávu "GAME OVER", když hráč prohraje.
- Reaguje na vstup od hráče pomocí klávesnice pro pohyb, střelbu a navigaci v herním menu.
- Umožňuje hráči pozastavit hru a ovládat položky v herním menu.
- Periodicky spawnuje mimozemšťany a lékarničky v závislosti na časovačích a pravidlech hry.
- Udržuje stálý pohyb a logiku ve hře, jako je pohyb hráče a AI nepřátel.
- Zvyšuje úroveň hry na základě počtu zabitých nepřátel a upravuje hru, aby byla náročnější.

### Menu.cpp
Hlavní menu.

- Konstruktor nastavuje okno, ve kterém bude menu vykresleno, a použité fonty.
- Vytváří textové objekty pro položky menu ("Play", "Settings", "Exit") a zarovnává je na střed okna.
- handleInput reaguje na stisky kláves od uživatele. Pokud je stisknuta klávesa nahoru nebo dolů, mění vybranou položku v menu. Pokud je stisknuto Enter, vrátí akci odpovídající vybrané položce.
- draw metoda prochází seznamem položek menu a vykresluje je do okna. Položka, která je aktuálně vybrána, je zvýrazněna.
- moveUp a moveDown metody mění vybranou položku v menu, přičemž zvýrazňují aktivní položku a odznačují předchozí položku.
- Action enum poskytuje seznam možných akcí, které mohou být provedeny v menu (hrát hru, změnit nastavení, ukončit hru).

### Player.cpp
Reprezentuje hráčovu vesmírnou loď, její pohyb a střelbu. Třída poskytuje všechny funkcionality a stavové informace týkající se hráčovy vesmírné lodi. Zde je několik hlavních aspektů této třídy:

- Konstruktor inicializuje hráče s maximálním zdravím, výchozím úhlem, rychlostí otáčení a dalšími základními nastaveními.
- update metoda zpracovává pohyb a otáčení hráče v reakci na vstupy od uživatele, a to pomocí kláves W, A, S, D pro pohyb a mezerníku pro střelbu. Taktéž zajišťuje hladké otáčení hráčovy lodi směrem k cíli.
- shoot metoda kontroluje, zda je stisknut mezerník a zda uplynula dostatečná doba od posledního výstřelu. Pokud ano, vytvoří novou střelu ve směru, kam je hráč aktuálně natočen.
- handleInput zjišťuje, jaké klávesy byly stisknuty, a na základě toho aktualizuje cílový úhel pro otáčení hráčovy lodi.
- decrementHealth snižuje zdraví hráče při zasažení nepřátelským ohněm nebo kolizí, zatímco incrementHealth zvyšuje zdraví hráče při sběru lékárniček.
- draw vykresluje hráčovu loď na aktuální pozici s aktuálním natočením.
- getCollisionMask poskytuje obdélníkovou oblast, která reprezentuje hranice hráčovy lodi pro detekci kolizí.
- Třída spravuje hráčův zásobník (který se po vyprázdněný po čase dobije), kvůli němuž má hráč omezený počet střel a hra je tudíž obtížnější.

### Alien.cpp
Třída Alien slouží jako abstraktní základ pro všechny nepřátelské mimozemšťany ve hře. Definuje společné rozhraní, které musí být implementováno všemi konkrétními třídami mimozemšťanů, jako je například BasicAlien nebo AdvancedAlien.

- Virtuální destruktor umožňuje správné uvolnění zdrojů při odstraňování objektů odvozených tříd.
- Update - čistě virtuální metoda update slouží k aktualizaci stavu mimozemšťana. Každý mimozemšťan musí implementovat logiku pro pohyb a interakci s hráčem nebo prostředím na základě pozice hráče.
- Metoda draw zodpovídá za vykreslení mimozemšťana na obrazovku.
- takeDamage umožňuje mimozemšťanovi přijmout určité množství poškození, což může vést k jeho zničení.
- getBoundingBox vrací ohraničující obdélník mimozemšťana, který se používá pro detekci kolizí s ostatními objekty ve hře.
- isAlive označuje, zda je mimozemšťan stále naživu. To je výchozí implementace, která lze přepsat v odvozených třídách, pokud je to potřeba.
- shoot definuje, jak a kdy mimozemšťan vystřeluje na hráče. Je to čistě virtuální metoda, takže každý typ mimozemšťana může implementovat vlastní střelecké chování.
- setPosition umožňuje nastavit pozici mimozemšťana v herním světě.

### BasicAlien.cpp
Konkrétní implementace základních mimozemšťanů, kteří útočí na hráče (odvozené od abstraktní třídy Alien.h). Zahrnuje následující funkcionality:

- Konstruktor nastavuje texturu, škálu, rychlost, zdraví a další počáteční stavy pro základního mimozemšťana.
- Metoda takeDamage snižuje zdraví mimozemšťana podle zadaného poškození a nastavuje jej na "neživého", pokud jeho zdraví klesne na nulu nebo níže.
- Metoda draw zajišťuje vykreslení mimozemšťana v herním okně.
- Metoda update zajišťuje pohyb mimozemšťana směrem k hráčově poloze, čímž ho činí agresivní a nebezpečnou překážkou pro hráče.
- Metoda shoot zkontroluje, zda uplynul dostatečný čas od posledního výstřelu, a pokud ano, vytvoří novou nepřátelskou střelu směřující k hráči.
- Metoda getBoundingBox poskytuje obdélníkovou oblast, která reprezentuje hranice mimozemšťana pro detekci kolizí.
- Metoda isAlive poskytuje informaci o tom, zda je mimozemšťan stále "živý", tedy zda má zdraví vyšší než nula a je třeba se ho hráč dále snažit zneškodnit.

### AdvancedAlien.cpp
Vylepšená verze Alienů (odvozené od abstraktní třídy Alien.h). (funkcionality jsou stejné jako u BasicAlien, pouze jsou jinak nastaveny parametry)

### Bullet.cpp
Reprezentuje střely vystřelené hráčem.

- Konstruktor inicializuje střelu s danou počáteční pozicí a úhlem, který určuje směr letu střely. Úhel je převeden z stupňů na radiány, aby mohl být použit ve výpočtech směru.
- Metoda update zajišťuje pohyb střely v prostoru hry na základě její rychlosti a směru, a to v závislosti na uplynulém čase (deltaTime).
- Metoda draw vykresluje střelu v herním okně.
- Metoda getPosition poskytuje aktuální pozici střely v herním světě.
- Metoda isTooFarFrom zjišťuje, zda je střela příliš daleko od dané pozice (typicky od hráče), což může být použito k určení, zda je třeba střelu odstranit z herního světa, pokud je mimo oblast hráčova pohybu.
- Metoda getBoundingBox poskytuje obdélníkovou oblast, která reprezentuje hranice střely pro detekci kolizí.
- Metoda markForDeletion označuje střelu jako připravenou ke smazání, typicky poté, co zasáhne cíl nebo opustí herní prostor.
- Metoda isMarkedForDeletion poskytuje informaci, zda byla střela označena ke smazání.

### EnemyBullet.cpp
Střely vystřelené nepřáteli.

- Nastavuje počáteční pozici a cíl střely, společně s množstvím způsobeného poškození (damageAmount). Vypočítá směr a rychlost střely směrem k cíli.
- Metoda update posouvá střelu podle její rychlosti a směru, založeno na uplynulém čase (deltaTime).
- Metoda draw vykresluje střelu na obrazovku hry.
- Metoda checkCollision kontroluje, zda střela zasáhla hráče, což se hodnotí pomocí kolizních masek.
- Metoda isTooFarFrom zjišťuje, zda je střela příliš daleko od pozice hráče, což může sloužit k jejímu odstranění z hry, když letí mimo herní oblast.
- Metoda markForDeletion označí střelu k odstranění, obvykle po kolizi nebo když se dostane mimo obrazovku.
- Metoda isMarkedForDeletion poskytuje informaci, zda byla střela označena k odstranění.
- Metoda returnDamageAmount vrací množství poškození, které střela způsobí hráči při zásahu.

### HealthKit.cpp
Objekt náhodně se objevující na obrazovce, který hráčovi přidává životy.

- Nastaví pozici a množství zdraví (healthAmount), které lékarnička poskytuje. Načte texturu a nastaví velikost lékarničky.s
- Metoda draw zodpovídá za vykreslení lékarničky na herní obrazovku.
- checkCollisionWithObject kontroluje, zda došlo ke kolizi s hráčem nebo jiným objektem.
- markForDeletion označí lékarničku k odstranění z herního světa, obvykle po tom, co je sebrána hráčem nebo zničena.
- isMarkedForDeletion indikuje, zda byla lékarnička označena ke smazání.
- getHealthAmount vrací množství zdraví, které lékarnička může hráči obnovit.
- setPosition umožňuje změnit pozici lékarničky v herním světě.

## Nedostatky programu a hry samotné
- Třídy Bullet a Enemy bullet nemají abstraktní třídu.
- V třídě Game.cpp je implementováno herní menu, které má podobnou strukturu jako Menu.cpp.
- Hra aktuálně neobsahuje koncovou obrazovku s výsledky.
- Settings zatím není přístupné, není možnost nic modifikovat...
- Chybí implementace power-upů a bonusových předmětů.

## Možné vylepšení a rozšíření

Přestože Space Shooter nabízí zábavnou a poutavou herní zkušenost, existuje řada možných vylepšení a rozšíření, která by mohla hru ještě více obohatit a zvýšit její replay value. Zde jsou některé návrhy:

### Power-upy a vylepšení
Přidání různých power-upů, které hráč může během hry sbírat, by mohlo zvýšit strategickou hloubku hry. Tyto power-upy by mohly dočasně zvýšit útočnou sílu, poskytnout dočasnou nesmrtelnost, nebo umožnit speciální schopnosti, jako je časová zpomalení.

### Různé herní módy
Kromě základního režimu přežití by hra mohla nabídnout další herní módy, jako je časová výzva, kde hráči bojují proti času, aby dosáhli co nejlepšího skóre, nebo módy zaměřené na dokončení určitých úkolů či výzev.

### Boss souboje
Implementace náročných boss soubojů na konci každé úrovně nebo na klíčových milnících by mohla přidat další vrstvu výzvy a uspokojení z hry. Každý boss by mohl mít unikátní slabiny a vzory útoků, což by vyžadovalo od hráčů strategické myšlení a adaptabilitu.

### Příběhová kampaň
Rozvoj příběhové kampaně s narativní hloubkou, včetně postav, dialogů a příběhových zvratů, by mohl hráčům poskytnout větší motivaci pokračovat ve hře a prohloubit jejich zážitek.

### Multiplayer
Přidání online nebo lokálního multiplayeru by umožnilo hráčům sdílet zábavu s přáteli. Možnosti zahrnují kooperativní režim, kde hráči spolupracují proti vlnám nepřátel, nebo konkurenční režim, kde hráči soutěží o nejvyšší skóre.

### Uživatelské úrovně a sdílení
Umožnění hráčům vytvářet a sdílet vlastní úrovně by mohlo výrazně prodloužit životnost hry a podpořit komunitu hráčů.

### Denní a týdenní výzvy
Zavedení denních a týdenních výzev s unikátními cíli a odměnami by mohlo motivovat hráče k pravidelnému návratu do hry.

## Závěr
Space Shooter je jednoduchá, ale zábavná hra, která poskytuje zábavu a představuje dobrý výchozí bod pro další rozvoj. I přes své nedostatky poskytuje pevný základ pro pochopení klíčových konceptů vývoje her v C++ a práci s knihovnou SFML.