FLAGS := -O3 -lm
all: bin/star1d1r.14.700.time bin/star1d1r.14.700.inj bin/star1d1r.14.700.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star1d1r.complexity.o: src/star1d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star1d1r_abft_v1_14_700.complexity.o: src/star1d1r_abft_v1_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star1d1r_abft_v2_14_700.complexity.o: src/star1d1r_abft_v2_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star1d1r.14.700.complexity: src/star1d1r-wrapper.c src/star1d1r.complexity.o src/time.o src/star1d1r_abft_v1_14_700.complexity.o src/star1d1r_abft_v2_14_700.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star1d1r.time.o: src/star1d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star1d1r_abft_v1_14_700.time.o: src/star1d1r_abft_v1_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star1d1r_abft_v2_14_700.time.o: src/star1d1r_abft_v2_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star1d1r.14.700.time: src/star1d1r-wrapper.c src/star1d1r.time.o src/time.o src/star1d1r_abft_v1_14_700.time.o src/star1d1r_abft_v2_14_700.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star1d1r_abft_v1_14_700.inj.o: src/star1d1r_abft_v1_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star1d1r_abft_v2_14_700.inj.o: src/star1d1r_abft_v2_14_700.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star1d1r.14.700.inj: src/star1d1r-wrapper.c src/star1d1r.o src/time.o src/star1d1r_abft_v1_14_700.inj.o src/star1d1r_abft_v2_14_700.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
