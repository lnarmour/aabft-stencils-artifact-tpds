FLAGS := -O3 -lm
all: bin/star3d1r.16.40.40.40.time bin/star3d1r.16.40.40.40.inj bin/star3d1r.16.40.40.40.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star3d1r.complexity.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v1_16_40_40_40.complexity.o: src/star3d1r_abft_v1_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v2_16_40_40_40.complexity.o: src/star3d1r_abft_v2_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star3d1r.16.40.40.40.complexity: src/star3d1r-wrapper.c src/star3d1r.complexity.o src/time.o src/star3d1r_abft_v1_16_40_40_40.complexity.o src/star3d1r_abft_v2_16_40_40_40.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star3d1r.time.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v1_16_40_40_40.time.o: src/star3d1r_abft_v1_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v2_16_40_40_40.time.o: src/star3d1r_abft_v2_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star3d1r.16.40.40.40.time: src/star3d1r-wrapper.c src/star3d1r.time.o src/time.o src/star3d1r_abft_v1_16_40_40_40.time.o src/star3d1r_abft_v2_16_40_40_40.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star3d1r_abft_v1_16_40_40_40.inj.o: src/star3d1r_abft_v1_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star3d1r_abft_v2_16_40_40_40.inj.o: src/star3d1r_abft_v2_16_40_40_40.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star3d1r.16.40.40.40.inj: src/star3d1r-wrapper.c src/star3d1r.o src/time.o src/star3d1r_abft_v1_16_40_40_40.inj.o src/star3d1r_abft_v2_16_40_40_40.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
