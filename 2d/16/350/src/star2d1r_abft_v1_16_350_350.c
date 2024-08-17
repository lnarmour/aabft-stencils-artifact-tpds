/* star2d1r_abft_v1_16_350_350.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star2d1r_abft_v1_16_350_350 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j]: 0 <= i <= N and 0 <= j <= N }
 *	 	outputs
 *	 		Y : {[t, i, j]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N }
 *	 	locals
 *	 		W : {[i, j]: -1 <= i <= 1 and -1 <= j <= 1 }
 *	 		C1 : {[tt, ti, tj]: tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N }
 *	 		C2 : {[tt, ti, tj]: tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N }
 *	 		I : {[tt, ti, tj]: tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N }
 *	 		patch : {[w, i, j]: 0 <= w <= 16 and -1 - w <= i <= 350 + w and -1 - w <= j <= 350 + w }
 *	 		patch_NR : {[w, i, j]: 0 < w <= 16 and -1 - w <= i <= 350 + w and -1 - w <= j <= 350 + w }
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
 *	 			{: w = 0 and 0 <= i <= 349 and 0 <= j <= 349 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj] = reduce(+, (tt,ti,tj,i,j->tt,ti,tj), {: 350ti <= i <= 349 + 350ti and 350tj <= j <= 349 + 350tj } : Y[16tt,i,j]);
 *	 		
 *	 		C2[tt,ti,tj] = reduce(+, (tt,ti,tj,p,q->tt,ti,tj), (patch[16,p,q] * Y[16tt-16,350ti+p,350tj+q]));
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
 *         	{ SC1[tt,ti,tj,i,j]->[tt]; SC2[tt,ti,tj,p,q]->[tt-1]; SI[tt,ti,tj]->[tt]; SY_cb0[t,i,j]->[t/16]; SY_cb1[t,i,j]->[t/16]; SY_cb2[t,i,j]->[t/16] }, \
 *         	{ SC1[tt,ti,tj,i,j]->[16tt]; SC2[tt,ti,tj,p,q]->[16tt-16]; SI[tt,ti,tj]->[16tt]; SY_cb0[t,i,j]->[t]; SY_cb1[t,i,j]->[t]; SY_cb2[t,i,j]->[t] } \
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
#define mem_patch(w,i,j) patch[(w)-(0)][(i)-(-17)][(j)-(-17)]
#define mem_patch_NR(w,i,j) patch_NR[(w)-(1)][(i)-(-17)][(j)-(-17)]

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

void inject_star2d1r_abft_v1_16_350_350(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star2d1r_abft_v1_16_350_350(double T, double N, float **X, float ***Y)
#else
struct Result star2d1r_abft_v1_16_350_350(long T, long N, float **X, float ***Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
	double total_card = ((((double)-48) + T >= ((double)0) && ((double)-717) + N >= ((double)0)) ? ((((((((double)19551650) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N) + ((double)1079828) * floord(T, ((double)16))) + ((((double)-488448) - ((double)3072) * N) + (((double)244224) + ((double)1536) * N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350)) + ((((double)487038) - ((double)636) * N - ((double)2) * N*N) + (((double)-243519) + ((double)318) * N + N*N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350)) + ((((double)111300) + ((double)700) * N) + (((double)-55650) - ((double)350) * N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350)) + (((double)-61250) + ((double)30625) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))) + (((((double)2648104) + ((double)3072) * N) + (((double)-1324052) - ((double)1536) * N) * floord(T, ((double)16))) + ((((double)345348) + ((double)2808) * N + ((double)4) * N*N) + (((double)-172674) - ((double)1404) * N - ((double)2) * N*N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350)) + ((((double)-380100) - ((double)700) * N) + (((double)190050) + ((double)350) * N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))) * floord(((double)349) + N, ((double)350)) + (((((double)-1372300) - ((double)2172) * N - ((double)2) * N*N) + (((double)686150) + ((double)1086) * N + N*N) * floord(T, ((double)16))) + ((((double)-111300) - ((double)700) * N) + (((double)55650) + ((double)350) * N) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350)) + (((double)122500) - ((double)61250) * floord(T, ((double)16))) * floord(((double)333) + N, ((double)350))*floord(((double)333) + N, ((double)350))) * floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350)) + ((((double)380100) + ((double)700) * N) + (((double)-190050) - ((double)350) * N) * floord(T, ((double)16))) * floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350)) + (((double)-61250) + ((double)30625) * floord(T, ((double)16))) * floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350))*floord(((double)349) + N, ((double)350)))) : (((double)-48) + T >= ((double)0) && ((double)-701) + N >= ((double)0) && ((double)716) - N >= ((double)0)) ? ((((((double)21245856) + T) + (((double)1330) + ((double)2) * T) * N + (((double)-1) + T) * N*N) + (((double)232725) - ((double)664) * N + N*N) * floord(T, ((double)16)))) : ((((double)-48) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)700) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)47) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)21711306) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
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
	float*** patch = (float***)(calloc((17),sizeof(float**)));
	for (int w=0; w<(17); w++) {
		patch[w] = (float**)(calloc((384),sizeof(float*)));
		for (int i=0; i<(384); i++) {
			patch[w][i] = (float*)(calloc((384),sizeof(float)));
		}
	}
	
	float** W = (float**)(calloc((3),sizeof(float*)));
	for (int i=0; i<(3); i++) {
		W[i] = (float*)(calloc((3),sizeof(float)));
	}
	
	float*** I = (float***)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		I[tt] = (float**)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			I[tt][ti] = (float*)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float)));
		}
	}
	
	float*** patch_NR = (float***)(calloc((16),sizeof(float**)));
	for (int w=0; w<(16); w++) {
		patch_NR[w] = (float**)(calloc((384),sizeof(float*)));
		for (int i=0; i<(384); i++) {
			patch_NR[w][i] = (float*)(calloc((384),sizeof(float)));
		}
	}
	
	float*** C1 = (float***)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		C1[tt] = (float**)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			C1[tt][ti] = (float*)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float)));
		}
	}
	
	float*** C2 = (float***)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		C2[tt] = (float**)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			C2[tt][ti] = (float*)(calloc(((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0),sizeof(float)));
		}
	}

	#define SC1(tt,ti,tj,i,j) C1(tt,ti,tj) += Y((16*(tt)),((i)),((j)))
	#define SC2(tt,ti,tj,p,q) C2(tt,ti,tj) += (patch((16),((p)),((q)))) * (Y((-16 + 16*(tt)),(350*(ti) + (p)),(350*(tj) + (q))))
	#define SI(tt,ti,tj) I(tt,ti,tj) = ((C2(tt,ti,tj)) - (C1(tt,ti,tj))) / (C1(tt,ti,tj))
	#define SW(i,j) W(i,j) = (((j) == (0)) && ((-1 + i) == (0))) ? (0.1249) : ((((1 + j) == (0)) && ((i) == (0))) ? (0.125) : ((((j) == (0)) && ((i) == (0))) ? (0.5002) : ((((j) == (0)) && ((1 + i) == (0))) ? (0.1247) : ((((-1 + j) == (0)) && ((i) == (0))) ? (0.1251) : (0)))))
	#define SY_cb0(t,i,j) Y(t,i,j) = X(((i)),((j)))
	#define SY_cb1(t,i,j) Y(t,i,j) = Y((-1 + (t)),((i)),((j)))
	#define SY_cb2_hook(t,i,j) Y(t,i,j) = (((((0.5002) * (Y((-1 + (t)),((i)),((j))))) + ((0.1247) * (Y((-1 + (t)),(-1 + (i)),((j)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)))))) + ((0.1251) * (Y((-1 + (t)),((i)),(1 + (j)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j) do { SY_cb2_hook(t,i,j); if (t==16*(tt_INJ-1)+1 && i==350*ti_INJ+175 && j==350*tj_INJ+175) inject_star2d1r_abft_v1_16_350_350(&Y(t,i,j)); } while(0)
	#else
	#define SY_cb2(t,i,j) SY_cb2_hook(t,i,j)
	#endif
	#define Spatch(w,i,j) patch(w,i,j) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j)) : (((((((w) == (0)) && ((i) >= (0))) && ((349 - i) >= (0))) && ((j) >= (0))) && ((349 - j) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,p,q) patch_NR(w,i,j) += (patch((-1 + (w)),((i) - (p)),((j) - (q)))) * (W(((p)),((q))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SC1[tt, ti, tj, i, j] : tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N and 350ti <= i <= 349 + 350ti and 350tj <= j <= 349 + 350tj; SC2[tt, ti, tj, p, q] : tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N and -17 <= p <= 366 and p <= N - 350ti and -17 <= q <= 366 and q <= N - 350tj; SY_cb0[t, i, j] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N; Spatch[w, i, j] : T >= 10 and N >= 20 and 0 <= w <= 16 and -1 - w <= i <= 350 + w and -1 - w <= j <= 350 + w; SW[i, j] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1; SI[tt, ti, tj] : tt >= 2 and 16tt <= -16 + T and ti > 0 and 350ti <= -351 + N and tj > 0 and 350tj <= -351 + N; Spatch_NR[w, i, j, p, q] : T >= 10 and N >= 20 and 0 < w <= 16 and p >= -1 and -349 - w + i <= p <= 1 and p <= w + i and q >= -1 and -349 - w + j <= q <= 1 and q <= w + j; SY_cb2[t, i, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N; SY_cb1[t, i, j = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = N, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N; SY_cb1[t, i, j = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = 0, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j] }"
	 *   - filter: "{ Spatch[w, i, j]; Spatch_NR[w, i, j, p, q] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch[w, i, j] -> [(w)]; Spatch_NR[w, i, j, p, q] -> [(w)] }]"
	 *   - filter: "{ SY_cb2[t, i, j]; SC1[tt, ti, tj, i, j]; SY_cb1[t, i, j]; SI[tt, ti, tj]; SC2[tt, ti, tj, p, q]; SY_cb0[t, i, j] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SC1[tt, ti, tj, i, j] -> [(tt)]; SC2[tt, ti, tj, p, q] -> [(-1 + tt)]; SY_cb0[t, i, j] -> [(floor((t)/16))]; SI[tt, ti, tj] -> [(tt)]; SY_cb2[t, i, j] -> [(floor((t)/16))]; SY_cb1[t, i, j] -> [(floor((t)/16))] }, { SC1[tt, ti, tj, i, j] -> [(16tt)]; SC2[tt, ti, tj, p, q] -> [(-16 + 16tt)]; SY_cb0[t, i, j] -> [(t)]; SI[tt, ti, tj] -> [(16tt)]; SY_cb2[t, i, j] -> [(t)]; SY_cb1[t, i, j] -> [(t)] }]"
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
	for (int c0 = 0; c0 <= 16; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 350; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 350; c3 += 1) {
	        for (int c4 = max(-1, -c0 + c2 - 349); c4 <= min(1, c0 + c2); c4 += 1) {
	          for (int c5 = max(-1, -c0 + c3 - 349); c5 <= min(1, c0 + c3); c5 += 1) {
	            Spatch_NR(c0, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 350; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 350; c3 += 1) {
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
	for (int c0 = 0; c0 <= T / 16; c0 += 1) {
	  for (int c1 = max(2, 16 * c0); c1 <= min(T, 16 * c0 + 15); c1 += 1) {
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
	    if (c0 >= 2 && T >= 16 * c0 + 16 && c1 == 16 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 350; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 350; c4 += 1) {
	          for (int c5 = 350 * c3; c5 <= 350 * c3 + 349; c5 += 1) {
	            for (int c6 = 350 * c4; c6 <= 350 * c4 + 349; c6 += 1) {
	              SC1(c0, c3, c4, c5, c6);
	            }
	          }
	        }
	      }
	    }
	    if (T >= 16 * c0 + 32 && c1 == 16 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 350; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 350; c4 += 1) {
	          for (int c5 = -17; c5 <= min(366, N - 350 * c3); c5 += 1) {
	            for (int c6 = -17; c6 <= min(366, N - 350 * c4); c6 += 1) {
	              SC2(c0 + 1, c3, c4, c5, c6);
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 16 * c0 + 16 && c1 == 16 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 350; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 350; c4 += 1) {
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
	
	for (int tt = 2; tt < T / 16; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 350; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 350; tj += 1) {
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
	for (int w=0; w<(17); w++) {
		for (int i=0; i<(384); i++) {
			 free(patch[w][i]);
		}
		free(patch[w]);
	}
	free(patch);
	
	for (int i=0; i<(3); i++) {
		 free(W[i]);
	}
	free(W);
	
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			 free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(16); w++) {
		for (int i=0; i<(384); i++) {
			 free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			 free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(T, 16))) : 0); tt++) {
		for (int ti=0; ti<((-48 + T >= 0 && -701 + N >= 0) ? ((-2 + floord(349 + N, 350))) : 0); ti++) {
			 free(C2[tt][ti]);
		}
		free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
