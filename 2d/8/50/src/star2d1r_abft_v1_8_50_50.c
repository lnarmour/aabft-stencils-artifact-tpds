/* star2d1r_abft_v1_8_50_50.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star2d1r_abft_v1_8_50_50 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j]: 0 <= i <= N and 0 <= j <= N }
 *	 	outputs
 *	 		Y : {[t, i, j]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N }
 *	 	locals
 *	 		W : {[i, j]: -1 <= i <= 1 and -1 <= j <= 1 }
 *	 		C1 : {[tt, ti, tj]: tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N }
 *	 		C2 : {[tt, ti, tj]: tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N }
 *	 		I : {[tt, ti, tj]: tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N }
 *	 		patch : {[w, i, j]: 0 <= w <= 8 and -1 - w <= i <= 50 + w and -1 - w <= j <= 50 + w }
 *	 		patch_NR : {[w, i, j]: 0 < w <= 8 and -1 - w <= i <= 50 + w and -1 - w <= j <= 50 + w }
 *	 	when {  : T >= 10 and N >= 20 } let
 *	 		Y[t,i,j] = case  {
 *	 			{: 0 <= t <= 1 } : X[i,j];
 *	 			{: j = N and t >= 2  or  i = N and t >= 2  or  j = 0 and t >= 2  or  i = 0 and t >= 2 } : Y[t-1,i,j];
 *	 			{: t >= 2 and 0 < i < N and 0 < j < N } : (((((0.5002[] * Y[t-1,i,j]) + (0.1247[] * Y[t-1,i-1,j])) + (0.1249[] * Y[t-1,i+1,j])) + (0.125[] * Y[t-1,i,j-1])) + (0.1251[] * Y[t-1,i,j+1]));
 *	 		};
 *	 		
 *	 		W[i,j] = case  {
 *	 			{: i = 1 and j = 0 } : 0.1249[];
 *	 			{: i = 0 and j = -1 } : 0.125[];
 *	 			{: i = 0 and j = 0 } : 0.5002[];
 *	 			{: i = -1 and j = 0 } : 0.1247[];
 *	 			{: i = 0 and j = 1 } : 0.1251[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		patch[w,i,j] = case  {
 *	 			{: w > 0 } : patch_NR;
 *	 			{: w = 0 and 0 <= i <= 49 and 0 <= j <= 49 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj] = reduce(+, (tt,ti,tj,i,j->tt,ti,tj), {: 50ti <= i <= 49 + 50ti and 50tj <= j <= 49 + 50tj } : Y[8tt,i,j]);
 *	 		
 *	 		C2[tt,ti,tj] = reduce(+, (tt,ti,tj,p,q->tt,ti,tj), (patch[8,p,q] * Y[8tt-8,50ti+p,50tj+q]));
 *	 		
 *	 		I[tt,ti,tj] = ((C2 - C1) / C1);
 *	 		
 *	 		patch_NR[w,i,j] = reduce(+, (w,i,j,p,q->w,i,j), (patch[w-1,i-p,j-q] * W[p,q]));
 *	 .
 *
 * Uses the memory map:
 *	 Y(t,i,j) -> Y(t - 2*floord(t, 2),i,j)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i,j] }"
 *     - filter: "{ Spatch[w,i,j]; Spatch_NR[w,i,j,p,q] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { Spatch[w,i,j]->[w]; Spatch_NR[w,i,j,p,q]->[w]} \
 *         ]"
 *     - filter: "{ SI[tt,ti,tj]; SC1[tt,ti,tj,i,j]; SC2[tt,ti,tj,p,q]; SY_cb0[t,i,j]; SY_cb1[t,i,j]; SY_cb2[t,i,j] }"
 *       child:
 *         schedule: "[T,N]->[\
 *         	{ SC1[tt,ti,tj,i,j]->[tt]; SC2[tt,ti,tj,p,q]->[tt-1]; SI[tt,ti,tj]->[tt]; SY_cb0[t,i,j]->[t/8]; SY_cb1[t,i,j]->[t/8]; SY_cb2[t,i,j]->[t/8] }, \
 *         	{ SC1[tt,ti,tj,i,j]->[8tt]; SC2[tt,ti,tj,p,q]->[8tt-8]; SI[tt,ti,tj]->[8tt]; SY_cb0[t,i,j]->[t]; SY_cb1[t,i,j]->[t]; SY_cb2[t,i,j]->[t] } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i,j]; SY_cb1[t,i,j]; SY_cb2[t,i,j] }"
 *           - filter: "{ SC1[tt,ti,tj,i,j]; SC2[tt,ti,tj,p,q] }"
 *           - filter: "{ SI[tt,ti,tj] }"
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))
#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
#define mallocCheck(v,s,d) if ((v) == NULL) { printf("Failed to allocate memory for %s : size=%lu\n", "sizeof(d)*(s)", sizeof(d)*(s)); exit(-1); }
#define new_result() { .valid=0, .TP=0L, .FP=0L, .TN=0L, .FN=0L, .TPR=0.0f, .FPR=0.0f, .FNR=0.0f, .bit=0, .inj={.tt=0, .ti=0, .tj=0, .tk=0}, .result=0.0f, .noise=0.0f }

void initialize_timer();
void reset_timer();
void start_timer();
void stop_timer();
double elapsed_time();

struct INJ {
	int tt;
	int ti;
	int tj;
	int tk;
};

struct Result {
	int valid;
	long TP;
	long FP;
	long TN;
	long FN;
	float TPR;
	float FPR;
	float FNR;
	int bit;
	struct INJ inj;
	double result;
	double noise;
};

// Memory mapped targets
#define mem_X(i,j) X[(i)-(0)][(j)-(0)]
#define mem_Y(t,i,j) Y[(t)-(0)][(i)-(0)][(j)-(0)]
#define mem_W(i,j) W[(i)-(-1)][(j)-(-1)]
#define mem_C1(tt,ti,tj) C1[(tt)-(2)][(ti)-(1)][(tj)-(1)]
#define mem_C2(tt,ti,tj) C2[(tt)-(2)][(ti)-(1)][(tj)-(1)]
#define mem_I(tt,ti,tj) I[(tt)-(2)][(ti)-(1)][(tj)-(1)]
#define mem_patch(w,i,j) patch[(w)-(0)][(i)-(-9)][(j)-(-9)]
#define mem_patch_NR(w,i,j) patch_NR[(w)-(1)][(i)-(-9)][(j)-(-9)]

// Memory access functions
#define X(i,j) mem_X(((i)),((j)))
#define Y(t,i,j) mem_Y(((t) - 2*floord((t), 2)),((i)),((j)))
#define W(i,j) mem_W(((i)),((j)))
#define C1(tt,ti,tj) mem_C1(((tt)),((ti)),((tj)))
#define C2(tt,ti,tj) mem_C2(((tt)),((ti)),((tj)))
#define I(tt,ti,tj) mem_I(((tt)),((ti)),((tj)))
#define patch(w,i,j) mem_patch(((w)),((i)),((j)))
#define patch_NR(w,i,j) mem_patch_NR(((w)),((i)),((j)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int tj_INJ;
int BIT;

void inject_star2d1r_abft_v1_8_50_50(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star2d1r_abft_v1_8_50_50(double T, double N, float **X, float ***Y)
#else
struct Result star2d1r_abft_v1_8_50_50(long T, long N, float **X, float ***Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
	double total_card = ((((double)-24) + T >= ((double)0) && ((double)-109) + N >= ((double)0)) ? ((((((((double)227794) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N) + ((double)28500) * floord(T, ((double)8))) + ((((double)-9248) - ((double)544) * N) + (((double)4624) + ((double)272) * N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50)) + ((((double)13022) - ((double)68) * N - ((double)2) * N*N) + (((double)-6511) + ((double)34) * N + N*N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50)) + ((((double)1700) + ((double)100) * N) + (((double)-850) - ((double)50) * N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50)) + (((double)-1250) + ((double)625) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))) + (((((double)66248) + ((double)544) * N) + (((double)-33124) - ((double)272) * N) * floord(T, ((double)8))) + ((((double)5780) + ((double)408) * N + ((double)4) * N*N) + (((double)-2890) - ((double)204) * N - ((double)2) * N*N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50)) + ((((double)-8500) - ((double)100) * N) + (((double)4250) + ((double)50) * N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))) * floord(((double)49) + N, ((double)50)) + (((((double)-33052) - ((double)340) * N - ((double)2) * N*N) + (((double)16526) + ((double)170) * N + N*N) * floord(T, ((double)8))) + ((((double)-1700) - ((double)100) * N) + (((double)850) + ((double)50) * N) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50)) + (((double)2500) - ((double)1250) * floord(T, ((double)8))) * floord(((double)41) + N, ((double)50))*floord(((double)41) + N, ((double)50))) * floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50)) + ((((double)8500) + ((double)100) * N) + (((double)-4250) - ((double)50) * N) * floord(T, ((double)8))) * floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50)) + (((double)-1250) + ((double)625) * floord(T, ((double)8))) * floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50))*floord(((double)49) + N, ((double)50)))) : (((double)-24) + T >= ((double)0) && ((double)-101) + N >= ((double)0) && ((double)108) - N >= ((double)0)) ? ((((((double)276592) + T) + (((double)162) + ((double)2) * T) * N + (((double)-1) + T) * N*N) + (((double)4101) - ((double)80) * N + N*N) * floord(T, ((double)8)))) : ((((double)-24) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)100) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)23) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)284794) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
	double expected_overhead = total_card / Y_card;
	printf("v1 (Y,C,overhead): %0.0lf,%0.0lf,%0.2lf\n", Y_card, total_card, expected_overhead);
	
	#undef ceild
	#undef floord
	#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
	#else
	#if defined ERROR_INJECTION
	// Error injection configuration
	tt_INJ = getenv("tt_INJ") != NULL ? atoi(getenv("tt_INJ")) : -1;
	ti_INJ = getenv("ti_INJ") != NULL ? atoi(getenv("ti_INJ")) : -1;
	tj_INJ = getenv("tj_INJ") != NULL ? atoi(getenv("tj_INJ")) : -1;
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float*** patch = (float***)(calloc((9),sizeof(float**)));
	for (int w=0; w<(9); w++) {
		patch[w] = (float**)(calloc((68),sizeof(float*)));
		for (int i=0; i<(68); i++) {
			patch[w][i] = (float*)(calloc((68),sizeof(float)));
		}
	}
	
	float** W = (float**)(calloc((3),sizeof(float*)));
	for (int i=0; i<(3); i++) {
		W[i] = (float*)(calloc((3),sizeof(float)));
	}
	
	float*** I = (float***)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		I[tt] = (float**)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			I[tt][ti] = (float*)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float)));
		}
	}
	
	float*** patch_NR = (float***)(calloc((8),sizeof(float**)));
	for (int w=0; w<(8); w++) {
		patch_NR[w] = (float**)(calloc((68),sizeof(float*)));
		for (int i=0; i<(68); i++) {
			patch_NR[w][i] = (float*)(calloc((68),sizeof(float)));
		}
	}
	
	float*** C1 = (float***)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		C1[tt] = (float**)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			C1[tt][ti] = (float*)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float)));
		}
	}
	
	float*** C2 = (float***)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		C2[tt] = (float**)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			C2[tt][ti] = (float*)(calloc(((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0),sizeof(float)));
		}
	}

	#define SC1(tt,ti,tj,i,j) C1(tt,ti,tj) += Y((8*(tt)),((i)),((j)))
	#define SC2(tt,ti,tj,p,q) C2(tt,ti,tj) += (patch((8),((p)),((q)))) * (Y((-8 + 8*(tt)),(50*(ti) + (p)),(50*(tj) + (q))))
	#define SI(tt,ti,tj) I(tt,ti,tj) = ((C2(tt,ti,tj)) - (C1(tt,ti,tj))) / (C1(tt,ti,tj))
	#define SW(i,j) W(i,j) = (((j) == (0)) && ((-1 + i) == (0))) ? (0.1249) : ((((1 + j) == (0)) && ((i) == (0))) ? (0.125) : ((((j) == (0)) && ((i) == (0))) ? (0.5002) : ((((j) == (0)) && ((1 + i) == (0))) ? (0.1247) : ((((-1 + j) == (0)) && ((i) == (0))) ? (0.1251) : (0)))))
	#define SY_cb0(t,i,j) Y(t,i,j) = X(((i)),((j)))
	#define SY_cb1(t,i,j) Y(t,i,j) = Y((-1 + (t)),((i)),((j)))
	#define SY_cb2_hook(t,i,j) Y(t,i,j) = (((((0.5002) * (Y((-1 + (t)),((i)),((j))))) + ((0.1247) * (Y((-1 + (t)),(-1 + (i)),((j)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)))))) + ((0.1251) * (Y((-1 + (t)),((i)),(1 + (j)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j) do { SY_cb2_hook(t,i,j); if (t==8*(tt_INJ-1)+1 && i==50*ti_INJ+25 && j==50*tj_INJ+25) inject_star2d1r_abft_v1_8_50_50(&Y(t,i,j)); } while(0)
	#else
	#define SY_cb2(t,i,j) SY_cb2_hook(t,i,j)
	#endif
	#define Spatch(w,i,j) patch(w,i,j) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j)) : (((((((w) == (0)) && ((i) >= (0))) && ((49 - i) >= (0))) && ((j) >= (0))) && ((49 - j) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,p,q) patch_NR(w,i,j) += (patch((-1 + (w)),((i) - (p)),((j) - (q)))) * (W(((p)),((q))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SC1[tt, ti, tj, i, j] : tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N and 50ti <= i <= 49 + 50ti and 50tj <= j <= 49 + 50tj; SC2[tt, ti, tj, p, q] : tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N and -9 <= p <= 58 and p <= N - 50ti and -9 <= q <= 58 and q <= N - 50tj; SY_cb0[t, i, j] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N; Spatch[w, i, j] : T >= 10 and N >= 20 and 0 <= w <= 8 and -1 - w <= i <= 50 + w and -1 - w <= j <= 50 + w; SW[i, j] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1; SI[tt, ti, tj] : tt >= 2 and 8tt <= -8 + T and ti > 0 and 50ti <= -51 + N and tj > 0 and 50tj <= -51 + N; Spatch_NR[w, i, j, p, q] : T >= 10 and N >= 20 and 0 < w <= 8 and p >= -1 and -49 - w + i <= p <= 1 and p <= w + i and q >= -1 and -49 - w + j <= q <= 1 and q <= w + j; SY_cb2[t, i, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N; SY_cb1[t, i, j = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = N, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N; SY_cb1[t, i, j = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = 0, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j] }"
	 *   - filter: "{ Spatch[w, i, j]; Spatch_NR[w, i, j, p, q] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch[w, i, j] -> [(w)]; Spatch_NR[w, i, j, p, q] -> [(w)] }]"
	 *   - filter: "{ SY_cb2[t, i, j]; SC1[tt, ti, tj, i, j]; SY_cb1[t, i, j]; SI[tt, ti, tj]; SC2[tt, ti, tj, p, q]; SY_cb0[t, i, j] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SC1[tt, ti, tj, i, j] -> [(tt)]; SC2[tt, ti, tj, p, q] -> [(-1 + tt)]; SY_cb0[t, i, j] -> [(floor((t)/8))]; SI[tt, ti, tj] -> [(tt)]; SY_cb2[t, i, j] -> [(floor((t)/8))]; SY_cb1[t, i, j] -> [(floor((t)/8))] }, { SC1[tt, ti, tj, i, j] -> [(8tt)]; SC2[tt, ti, tj, p, q] -> [(-8 + 8tt)]; SY_cb0[t, i, j] -> [(t)]; SI[tt, ti, tj] -> [(8tt)]; SY_cb2[t, i, j] -> [(t)]; SY_cb1[t, i, j] -> [(t)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb2[t, i, j]; SY_cb1[t, i, j]; SY_cb0[t, i, j] }"
	 *         - filter: "{ SC1[tt, ti, tj, i, j]; SC2[tt, ti, tj, p, q] }"
	 *         - filter: "{ SI[tt, ti, tj] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  for (int c1 = -1; c1 <= 1; c1 += 1) {
	    SW(c0, c1);
	  }
	}
	for (int c0 = 0; c0 <= 8; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 50; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 50; c3 += 1) {
	        for (int c4 = max(-1, -c0 + c2 - 49); c4 <= min(1, c0 + c2); c4 += 1) {
	          for (int c5 = max(-1, -c0 + c3 - 49); c5 <= min(1, c0 + c3); c5 += 1) {
	            Spatch_NR(c0, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 50; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 50; c3 += 1) {
	      Spatch(c0, c2, c3);
	    }
	  }
	}
	for (int c1 = 0; c1 <= 1; c1 += 1) {
	  for (int c3 = 0; c3 <= N; c3 += 1) {
	    for (int c4 = 0; c4 <= N; c4 += 1) {
	      SY_cb0(c1, c3, c4);
	    }
	  }
	}
	for (int c0 = 0; c0 <= T / 8; c0 += 1) {
	  for (int c1 = max(2, 8 * c0); c1 <= min(T, 8 * c0 + 7); c1 += 1) {
	    for (int c3 = 1; c3 < N; c3 += 1) {
	      for (int c4 = 1; c4 < N; c4 += 1) {
	        SY_cb2(c1, c3, c4);
	      }
	    }
	    for (int c3 = 0; c3 <= N; c3 += 1) {
	      if (c3 >= 1 && N >= c3 + 1) {
	        SY_cb1(c1, c3, 0);
	      } else {
	        if (c3 == 0) {
	          for (int c4 = 0; c4 < N; c4 += 1) {
	            SY_cb1(c1, 0, c4);
	          }
	        } else {
	          for (int c4 = 0; c4 < N; c4 += 1) {
	            SY_cb1(c1, N, c4);
	          }
	        }
	      }
	      SY_cb1(c1, c3, N);
	    }
	    if (c0 >= 2 && T >= 8 * c0 + 8 && c1 == 8 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 50; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 50; c4 += 1) {
	          for (int c5 = 50 * c3; c5 <= 50 * c3 + 49; c5 += 1) {
	            for (int c6 = 50 * c4; c6 <= 50 * c4 + 49; c6 += 1) {
	              SC1(c0, c3, c4, c5, c6);
	            }
	          }
	        }
	      }
	    }
	    if (T >= 8 * c0 + 16 && c1 == 8 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 50; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 50; c4 += 1) {
	          for (int c5 = -9; c5 <= min(58, N - 50 * c3); c5 += 1) {
	            for (int c6 = -9; c6 <= min(58, N - 50 * c4); c6 += 1) {
	              SC2(c0 + 1, c3, c4, c5, c6);
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 8 * c0 + 8 && c1 == 8 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 50; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 50; c4 += 1) {
	          SI(c0, c3, c4);
	        }
	      }
	    }
	  }
	}

	stop_timer();
	execution_time = elapsed_time();

	#undef SY
	#undef SW
	#undef Spatch
	#undef SC1
	#undef SC2
	#undef SI
	#undef Spatch_NR

	#if defined TIMING
	struct Result result = new_result();
	result.result = execution_time;
	
	#elif defined ERROR_INJECTION
	// Count checksum difference above THRESHOLD
	struct INJ inj = { tt_INJ, ti_INJ, tj_INJ };
	struct Result result = new_result();
	result.bit = BIT;
	result.inj = inj;
	result.noise = -1;
	
	const char* verbose = getenv("VERBOSE");
	
	#define print_SI(tt,ti,tj) printf("v1_I(%d,%d,%d) = %E\n",tt,ti,tj, fabs(I(tt,ti,tj)))
	#define acc_noise(tt,ti,tj) result.noise = max(result.noise, fabs(I(tt,ti,tj)))
	#define SI(tt,ti,tj) do { if (verbose != NULL && fabs(I(tt,ti,tj))>=threshold) print_SI(tt,ti,tj); acc_noise(tt,ti,tj); if (tt==tt_INJ && ti==ti_INJ && tj==tj_INJ) { if (fabs(I(tt,ti,tj))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti,tj))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 8; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 50; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 50; tj += 1) {
	      SI(tt, ti, tj);
	    }
	  }
	}
	
	{
		long N = result.FP + result.TN;
		long P = result.FN + result.TP;
		if (P != 0 && N != 0) {
			result.TPR = 100 * ((float)result.TP) / P;
			result.FPR = 100 * ((float)result.FP) / N;
			result.FNR = 100 * ((float)result.FN) / P;
		}
	}
	#undef SI
	
	#endif

	// Free local memory allocation
	for (int w=0; w<(9); w++) {
		for (int i=0; i<(68); i++) {
			 free(patch[w][i]);
		}
		free(patch[w]);
	}
	free(patch);
	
	for (int i=0; i<(3); i++) {
		 free(W[i]);
	}
	free(W);
	
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			 free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(8); w++) {
		for (int i=0; i<(68); i++) {
			 free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			 free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(T, 8))) : 0); tt++) {
		for (int ti=0; ti<((-24 + T >= 0 && -101 + N >= 0) ? ((-2 + floord(49 + N, 50))) : 0); ti++) {
			 free(C2[tt][ti]);
		}
		free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
