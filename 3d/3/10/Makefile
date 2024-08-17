FLAGS := -O3 -lm
all: bin/star3d1r.3.10.10.10.time bin/star3d1r.3.10.10.10.inj bin/star3d1r.3.10.10.10.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star3d1r.complexity.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v1_3_10_10_10.complexity.o: src/star3d1r_abft_v1_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v2_3_10_10_10.complexity.o: src/star3d1r_abft_v2_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star3d1r.3.10.10.10.complexity: src/star3d1r-wrapper.c src/star3d1r.complexity.o src/time.o src/star3d1r_abft_v1_3_10_10_10.complexity.o src/star3d1r_abft_v2_3_10_10_10.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star3d1r.time.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v1_3_10_10_10.time.o: src/star3d1r_abft_v1_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v2_3_10_10_10.time.o: src/star3d1r_abft_v2_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star3d1r.3.10.10.10.time: src/star3d1r-wrapper.c src/star3d1r.time.o src/time.o src/star3d1r_abft_v1_3_10_10_10.time.o src/star3d1r_abft_v2_3_10_10_10.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star3d1r_abft_v1_3_10_10_10.inj.o: src/star3d1r_abft_v1_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star3d1r_abft_v2_3_10_10_10.inj.o: src/star3d1r_abft_v2_3_10_10_10.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star3d1r.3.10.10.10.inj: src/star3d1r-wrapper.c src/star3d1r.o src/time.o src/star3d1r_abft_v1_3_10_10_10.inj.o src/star3d1r_abft_v2_3_10_10_10.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
