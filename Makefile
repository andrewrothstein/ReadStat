
CC=cc
PREFIX=/usr/local
RAGEL=/usr/bin/ragel
DYLIB=obj/libreadstat.so

all:
	@mkdir -p obj
	[ -x $(RAGEL) ] && $(RAGEL) src/readstat_por_parse.rl -G2
	[ -x $(RAGEL) ] && $(RAGEL) src/readstat_sav_parse.rl -G2
	[ -x $(RAGEL) ] && $(RAGEL) src/readstat_spss_parse.rl -G2
	$(CC) -Os src/*.c -rdynamic -shared -fPIC -o $(DYLIB) -llzma -lz -lm -Wall -Wno-multichar -pedantic -DHAVE_LZMA
	$(CC) -Os src/*.c to_csv/to_csv.c -o to_csv/to_csv -llzma -lz -lm -Wall -Wno-multichar -pedantic -DHAVE_LZMA

install: all
	@mkdir -p $(PREFIX)/lib
	@cp $(DYLIB) $(PREFIX)/lib/
	@mkdir -p $(PREFIX)/include
	@cp src/readstat.h $(PREFIX)/include/

clean:
	rm -rf obj
