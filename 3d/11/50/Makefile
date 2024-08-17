FLAGS := -O3 -lm
all: bin/star3d1r.11.50.50.50.time bin/star3d1r.11.50.50.50.inj bin/star3d1r.11.50.50.50.complexity

mkbin:
	mkdir -p bin

src/time.o: src/time.c mkbin
	gcc -c $(FLAGS) -o $@ $<


src/star3d1r.complexity.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v1_11_50_50_50.complexity.o: src/star3d1r_abft_v1_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
src/star3d1r_abft_v2_11_50_50_50.complexity.o: src/star3d1r_abft_v2_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DREPORT_COMPLEXITY_ONLY
bin/star3d1r.11.50.50.50.complexity: src/star3d1r-wrapper.c src/star3d1r.complexity.o src/time.o src/star3d1r_abft_v1_11_50_50_50.complexity.o src/star3d1r_abft_v2_11_50_50_50.complexity.o
	gcc $(FLAGS) -o $@ $^ -DREPORT_COMPLEXITY_ONLY


src/star3d1r.time.o: src/star3d1r.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v1_11_50_50_50.time.o: src/star3d1r_abft_v1_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
src/star3d1r_abft_v2_11_50_50_50.time.o: src/star3d1r_abft_v2_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DTIMING
bin/star3d1r.11.50.50.50.time: src/star3d1r-wrapper.c src/star3d1r.time.o src/time.o src/star3d1r_abft_v1_11_50_50_50.time.o src/star3d1r_abft_v2_11_50_50_50.time.o
	gcc $(FLAGS) -o $@ $^ -DTIMING


src/star3d1r_abft_v1_11_50_50_50.inj.o: src/star3d1r_abft_v1_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $< -DERROR_INJECTION
src/star3d1r_abft_v2_11_50_50_50.inj.o: src/star3d1r_abft_v2_11_50_50_50.c mkbin
	gcc -c $(FLAGS) -o $@ $<  -DERROR_INJECTION
bin/star3d1r.11.50.50.50.inj: src/star3d1r-wrapper.c src/star3d1r.o src/time.o src/star3d1r_abft_v1_11_50_50_50.inj.o src/star3d1r_abft_v2_11_50_50_50.inj.o
	gcc $(FLAGS) -o $@ $^ -DERROR_INJECTION



clean:
	rm -f src/*.o bin/*
