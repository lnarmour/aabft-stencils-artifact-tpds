FLAGS := -O3 -lm
all: bin/star2d1r.2.350.350.time bin/star2d1r.2.350.350.inj bin/star2d1r.2.350.350.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star2d1r.complexity.o: src/star2d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star2d1r_abft_v1_2_350_350.complexity.o: src/star2d1r_abft_v1_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star2d1r_abft_v2_2_350_350.complexity.o: src/star2d1r_abft_v2_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star2d1r.2.350.350.complexity: src/star2d1r-wrapper.c src/star2d1r.complexity.o src/time.o src/star2d1r_abft_v1_2_350_350.complexity.o src/star2d1r_abft_v2_2_350_350.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star2d1r.time.o: src/star2d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star2d1r_abft_v1_2_350_350.time.o: src/star2d1r_abft_v1_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star2d1r_abft_v2_2_350_350.time.o: src/star2d1r_abft_v2_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star2d1r.2.350.350.time: src/star2d1r-wrapper.c src/star2d1r.time.o src/time.o src/star2d1r_abft_v1_2_350_350.time.o src/star2d1r_abft_v2_2_350_350.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star2d1r_abft_v1_2_350_350.inj.o: src/star2d1r_abft_v1_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star2d1r_abft_v2_2_350_350.inj.o: src/star2d1r_abft_v2_2_350_350.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star2d1r.2.350.350.inj: src/star2d1r-wrapper.c src/star2d1r.o src/time.o src/star2d1r_abft_v1_2_350_350.inj.o src/star2d1r_abft_v2_2_350_350.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
