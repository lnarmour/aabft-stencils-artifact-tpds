FLAGS := -O3 -lm
all: bin/star1d1r.8.850.time bin/star1d1r.8.850.inj bin/star1d1r.8.850.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star1d1r.complexity.o: src/star1d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star1d1r_abft_v1_8_850.complexity.o: src/star1d1r_abft_v1_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star1d1r_abft_v2_8_850.complexity.o: src/star1d1r_abft_v2_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star1d1r.8.850.complexity: src/star1d1r-wrapper.c src/star1d1r.complexity.o src/time.o src/star1d1r_abft_v1_8_850.complexity.o src/star1d1r_abft_v2_8_850.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star1d1r.time.o: src/star1d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star1d1r_abft_v1_8_850.time.o: src/star1d1r_abft_v1_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star1d1r_abft_v2_8_850.time.o: src/star1d1r_abft_v2_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star1d1r.8.850.time: src/star1d1r-wrapper.c src/star1d1r.time.o src/time.o src/star1d1r_abft_v1_8_850.time.o src/star1d1r_abft_v2_8_850.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star1d1r_abft_v1_8_850.inj.o: src/star1d1r_abft_v1_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star1d1r_abft_v2_8_850.inj.o: src/star1d1r_abft_v2_8_850.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star1d1r.8.850.inj: src/star1d1r-wrapper.c src/star1d1r.o src/time.o src/star1d1r_abft_v1_8_850.inj.o src/star1d1r_abft_v2_8_850.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
