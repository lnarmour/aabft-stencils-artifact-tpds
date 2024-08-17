FLAGS := -O3 -lm
all: bin/star2d1r.16.50.50.time bin/star2d1r.16.50.50.inj bin/star2d1r.16.50.50.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star2d1r.complexity.o: src/star2d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star2d1r_abft_v1_16_50_50.complexity.o: src/star2d1r_abft_v1_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star2d1r_abft_v2_16_50_50.complexity.o: src/star2d1r_abft_v2_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star2d1r.16.50.50.complexity: src/star2d1r-wrapper.c src/star2d1r.complexity.o src/time.o src/star2d1r_abft_v1_16_50_50.complexity.o src/star2d1r_abft_v2_16_50_50.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star2d1r.time.o: src/star2d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star2d1r_abft_v1_16_50_50.time.o: src/star2d1r_abft_v1_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star2d1r_abft_v2_16_50_50.time.o: src/star2d1r_abft_v2_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star2d1r.16.50.50.time: src/star2d1r-wrapper.c src/star2d1r.time.o src/time.o src/star2d1r_abft_v1_16_50_50.time.o src/star2d1r_abft_v2_16_50_50.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star2d1r_abft_v1_16_50_50.inj.o: src/star2d1r_abft_v1_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star2d1r_abft_v2_16_50_50.inj.o: src/star2d1r_abft_v2_16_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star2d1r.16.50.50.inj: src/star2d1r-wrapper.c src/star2d1r.o src/time.o src/star2d1r_abft_v1_16_50_50.inj.o src/star2d1r_abft_v2_16_50_50.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
