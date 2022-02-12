all:
  gcc bot/main.c bot/methods.c bot/print.c bot/read.c bot/grid.c bot/output.c bot/ia.c -o bot_C && gcc bot/main.c bot/methods.c bot/print.c bot/read.c bot/grid.c bot/output.c bot/ia.c -o bot_B && gcc bot/main.c bot/methods.c bot/print.c bot/read.c bot/grid.c bot/output.c bot/ia.c -o bot_A
one:
  gcc bot/main.c bot/methods.c bot/print.c bot/read.c bot/grid.c bot/output.c bot/ia.c -o bot_C
