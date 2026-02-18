# Introduktion
Detta är ett simpelt program skrivet i C som simulerar Linux/Unix-kommandot/verktyget **du (disk usage)**. Verktyget används för att visa hur mycket diskutrymme som används av filer och kataloger i Linux/Unix-baserade system.

## Användning
Kompilera programmet via 'Makefile' där funktionerna make och clean är definerade.
Programmet kräver GCC, math library och pthread library för att fungera.

Starta programmet:
```bash
./mdu optional: -j (amount of threads to be used.) Files separated with space.

## Nedanstående rad startar programmet med 100 trådar som beräknar diskutrymmet i katalogen 'min_katalog'.
./mdu -j 100 min_katalog
```

## Lösning
Programmet är flertrådat och använder sig av rekursion för att beräkna diskutrymmet för antingen en fil eller en katalog med filer och underkataloger. Om programmet hittar en underkatalog kommer en ny tråd skapas och räkna ut storleken på den katalogen. Detta sker så länge det finns underkataloger.
