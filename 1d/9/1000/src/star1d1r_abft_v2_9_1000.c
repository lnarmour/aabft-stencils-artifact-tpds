/* star1d1r_abft_v2_9_1000.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star1d1r_abft_v2_9_1000 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i]: 0 <= i <= N }
 *	 	outputs
 *	 		Y : {[t, i]: 0 <= t <= T and 0 <= i <= N }
 *	 	locals
 *	 		W : {[i]: -1 <= i <= 1 }
 *	 		C1 : {[tt, ti]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N }
 *	 		C2 : {[tt, ti, p]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and -2 <= p <= 2 }
 *	 		I : {[tt, ti]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N }
 *	 		WKernel : {[i]: -2 <= i <= 2 }
 *	 		WCombos : {[i]: -2 <= i <= 2 }
 *	 		WAll : {[w]: 0 < w <= 9 }
 *	 		C2_NR : {[tt, ti, p]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and -2 <= p < 0 }
 *	 		C2_NR2 : {[tt, ti, p]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and 0 < p <= 2 }
 *	 		C2_NR3 : {[tt, ti, p]: p = 0 and tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N }
 *	 		I_NR : {[tt, ti]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N }
 *	 	when {  : T >= 10 and N >= 20 } let
 *	 		Y[t,i] = case  {
 *	 			{: 0 <= t <= 1 } : X[i];
 *	 			{: i = N and t >= 2  or  i = 0 and t >= 2 } : Y[t-1,i];
 *	 			{: t >= 2 and 0 < i < N } : (((0.3332[] * Y[t-1,i-1]) + (0.3333[] * Y[t-1,i])) + (0.33[] * Y[t-1,i+1]));
 *	 		};
 *	 		
 *	 		W[i] = case  {
 *	 			{: i = 1 } : 0.33[];
 *	 			{: i = -1 } : 0.3332[];
 *	 			{: i = 0 } : 0.3333[];
 *	 		};
 *	 		
 *	 		WKernel[i] = case  {
 *	 			{: -1 <= i <= 1 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		WCombos[i] = reduce(+, (i,p->i), (WKernel[i-p] * W[p]));
 *	 		
 *	 		WAll[w] = case  {
 *	 			{: w = 1 } : 1[];
 *	 			{: w >= 2 } : (WAll[w-1] * WCombos[0]);
 *	 		};
 *	 		
 *	 		C1[tt,ti] = reduce(+, (tt,ti,i->tt,ti), {: 1000ti <= i <= 1017 + 1000ti } : Y[9tt,i]);
 *	 		
 *	 		C2[tt,ti,p] = case  {
 *	 			(WCombos[p] * C2_NR);
 *	 			(WCombos[p] * C2_NR2);
 *	 			(WCombos[p] * C2_NR3);
 *	 		};
 *	 		
 *	 		I[tt,ti] = ((I_NR - C1) / C1);
 *	 		
 *	 		C2_NR[tt,ti,p] = reduce(+, (tt,ti,p,w->tt,ti,p), (WAll[w] * Y[9tt-w,1000ti+p+w]));
 *	 		
 *	 		C2_NR2[tt,ti,p] = reduce(+, (tt,ti,p,w->tt,ti,p), (WAll[w] * Y[9tt-w,1000ti+p-w+1017]));
 *	 		
 *	 		C2_NR3[tt,ti,p] = reduce(+, (tt,ti,p,w,i->tt,ti,p), {: w = 9 and 9 + 1000ti <= i <= 1008 + 1000ti } : (WAll[w] * Y[9tt-w,i]));
 *	 		
 *	 		I_NR[tt,ti] = reduce(+, (tt,ti,p->tt,ti), C2);
 *	 .
 *
 * Uses the memory map:
 *	 C2_NR(tt,ti,p) -> C2(tt,ti,p)
 *	 C2_NR2(tt,ti,p) -> C2(tt,ti,p)
 *	 C2_NR3(tt,ti,p) -> C2(tt,ti,0)
 *	 Y(t,i) -> Y(t - 2*floord(t, 2),i)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i] }"
 *     - filter: "{ SWKernel[i] }"
 *     - filter: "{ SWCombos[i,p] }"
 *     - filter: "{ SWAll[w] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { SWAll[w]->[w] } \
 *         ]"
 *     - filter: "{ \
 *         SY_cb0[t,i]; \
 *         SY_cb1[t,i]; \
 *         SY_cb2[t,i]; \
 *         SC1[tt,ti,i]; \
 *         SC2_NR[tt,ti,p,w]; \
 *         SC2_NR2[tt,ti,p,w]; \
 *         SC2_NR3[tt,ti,p,w,i]; \
 *         SC2_cb0[tt,ti,p]; \
 *         SC2_cb1[tt,ti,p]; \
 *         SC2_cb2[tt,ti,p]; \
 *         SI_NR[tt,ti,p]; \
 *         SI[tt,ti] \
 *       }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { \
 *             SY_cb0[t,i]->[t]; \
 *             SY_cb1[t,i]->[t]; \
 *             SY_cb2[t,i]->[t]; \
 *             SC1[tt,ti,i]->[9tt]; \
 *             SC2_cb0[tt,ti,p]->[9tt]; \
 *             SC2_cb1[tt,ti,p]->[9tt]; \
 *             SC2_cb2[tt,ti,p]->[9tt]; \
 *             SC2_NR[tt,ti,p,w]->[9tt-w]; \
 *             SC2_NR2[tt,ti,p,w]->[9tt-w]; \
 *             SC2_NR3[tt,ti,p,w,i]->[9tt-w]; \
 *             SI[tt,ti]->[9tt]; \
 *             SI_NR[tt,ti,p]->[9tt] \
 *           } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i]; SY_cb1[t,i]; SY_cb2[t,i] }"
 *           - filter: "{ SC1[tt,ti,i]; SC2_NR[tt,ti,p,w]; SC2_NR2[tt,ti,p,w]; SC2_NR3[tt,ti,p,w,i] }"
 *           - filter: "{ SC2_cb0[tt,ti,p]; SC2_cb1[tt,ti,p]; SC2_cb2[tt,ti,p] }"
 *           - filter: "{ SI_NR[tt,ti,p] }"
 *           - filter: "{ SI[tt,ti] }"
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
#define mem_X(i) X[(i)-(0)]
#define mem_Y(t,i) Y[(t)-(0)][(i)-(0)]
#define mem_W(i) W[(i)-(-1)]
#define mem_C1(tt,ti) C1[(tt)-(2)][(ti)-(1)]
#define mem_C2(tt,ti,p) C2[(tt)-(2)][(ti)-(1)][(p)-(-2)]
#define mem_I(tt,ti) I[(tt)-(2)][(ti)-(1)]
#define mem_WKernel(i) WKernel[(i)-(-2)]
#define mem_WCombos(i) WCombos[(i)-(-2)]
#define mem_WAll(w) WAll[(w)-(1)]
#define mem_I_NR(tt,ti) I_NR[(tt)-(2)][(ti)-(1)]

// Memory access functions
#define X(i) mem_X(((i)))
#define Y(t,i) mem_Y(((t) - 2*floord((t), 2)),((i)))
#define W(i) mem_W(((i)))
#define C1(tt,ti) mem_C1(((tt)),((ti)))
#define C2(tt,ti,p) mem_C2(((tt)),((ti)),((p)))
#define I(tt,ti) mem_I(((tt)),((ti)))
#define WKernel(i) mem_WKernel(((i)))
#define WCombos(i) mem_WCombos(((i)))
#define WAll(w) mem_WAll(((w)))
#define C2_NR(tt,ti,p) mem_C2(((tt)),((ti)),((p)))
#define C2_NR2(tt,ti,p) mem_C2(((tt)),((ti)),((p)))
#define C2_NR3(tt,ti,p) mem_C2(((tt)),((ti)),(0))
#define I_NR(tt,ti) mem_I_NR(((tt)),((ti)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int BIT;

void inject_star1d1r_abft_v2_9_1000(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star1d1r_abft_v2_9_1000(double T, double N, float *X, float **Y)
#else
struct Result star1d1r_abft_v2_9_1000(long T, long N, float *X, float **Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)1) + T) * N)) : ((double)0));
	double total_card = ((((double)-27) + T >= ((double)0) && ((double)-2019) + N >= ((double)0)) ? (((((((double)8291) + T) + (((double)1) + T) * N) - ((double)4130) * floord(T, ((double)9))) + (((double)-4130) + ((double)2065) * floord(T, ((double)9))) * floord(((double)981) + N, ((double)1000)))) : ((((double)-27) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)2018) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)26) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)31) + T) + (((double)1) + T) * N)) : ((double)0));
	double expected_overhead = total_card / Y_card;
	printf("v2 (Y,C,overhead): %0.0lf,%0.0lf,%0.2lf\n", Y_card, total_card, expected_overhead);
	
	#undef ceild
	#undef floord
	#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
	#else
	#if defined ERROR_INJECTION
	// Error injection configuration
	tt_INJ = getenv("tt_INJ") != NULL ? atoi(getenv("tt_INJ")) : -1;
	ti_INJ = getenv("ti_INJ") != NULL ? atoi(getenv("ti_INJ")) : -1;
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float* WAll = (float*)(calloc((9),sizeof(float)));
	
	float* W = (float*)(calloc((3),sizeof(float)));
	
	float** I_NR = (float**)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		I_NR[tt] = (float*)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0),sizeof(float)));
	}
	
	float** I = (float**)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		I[tt] = (float*)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0),sizeof(float)));
	}
	
	float* WKernel = (float*)(calloc((5),sizeof(float)));
	
	float** C1 = (float**)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		C1[tt] = (float*)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0),sizeof(float)));
	}
	
	float* WCombos = (float*)(calloc((5),sizeof(float)));
	
	float*** C2 = (float***)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		C2[tt] = (float**)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0); ti++) {
			C2[tt][ti] = (float*)(calloc(((-27 + T >= 0 && -2019 + N >= 0) ? (5) : 0),sizeof(float)));
		}
	}

	#define SC1(tt,ti,i) C1(tt,ti) += Y((9*(tt)),((i)))
	#define SC2_NR(tt,ti,p,w) C2_NR(tt,ti,p) += (WAll(((w)))) * (Y((9*(tt) - (w)),(1000*(ti) + (p) + (w))))
	#define SC2_NR2(tt,ti,p,w) C2_NR2(tt,ti,p) += (WAll(((w)))) * (Y((9*(tt) - (w)),(1017 + 1000*(ti) + (p) - (w))))
	#define SC2_NR3(tt,ti,p,w,i) C2_NR3(tt,ti,p) += (WAll(((w)))) * (Y((9*(tt) - (w)),((i))))
	#define SC2_cb0(tt,ti,p) C2(tt,ti,p) = (WCombos(((p)))) * (C2_NR(tt,ti,p))
	#define SC2_cb1(tt,ti,p) C2(tt,ti,p) = (WCombos(((p)))) * (C2_NR2(tt,ti,p))
	#define SC2_cb2(tt,ti,p) C2(tt,ti,p) = (WCombos(((p)))) * (C2_NR3(tt,ti,p))
	#define SI(tt,ti) I(tt,ti) = ((I_NR(tt,ti)) - (C1(tt,ti))) / (C1(tt,ti))
	#define SI_NR(tt,ti,p) I_NR(tt,ti) += C2(tt,ti,p)
	#define SW(i) W(i) = ((-1 + i) == (0)) ? (0.33) : (((1 + i) == (0)) ? (0.3332) : (0.3333))
	#define SWAll(w) WAll(w) = ((-1 + w) == (0)) ? (1) : ((WAll((-1 + (w)))) * (WCombos((0))))
	#define SWCombos(i,p) WCombos(i) += (WKernel(((i) - (p)))) * (W(((p))))
	#define SWKernel(i) WKernel(i) = (((1 + i) >= (0)) && ((1 - i) >= (0))) ? (1) : (0)
	#define SY_cb0(t,i) Y(t,i) = X(((i)))
	#define SY_cb1(t,i) Y(t,i) = Y((-1 + (t)),((i)))
	#define SY_cb2_hook(t,i) Y(t,i) = (((0.3332) * (Y((-1 + (t)),(-1 + (i))))) + ((0.3333) * (Y((-1 + (t)),((i)))))) + ((0.33) * (Y((-1 + (t)),(1 + (i)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i) do { SY_cb2_hook(t,i); if (t==9*(tt_INJ-1)+1 && i==1000*ti_INJ+509) inject_star1d1r_abft_v2_9_1000(&Y(t,i)); } while(0)
	#else
	#define SY_cb2(t,i) SY_cb2_hook(t,i)
	#endif

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb0[t, i] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N; SWKernel[i] : T >= 10 and N >= 20 and -2 <= i <= 2; SC1[tt, ti, i] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and 1000ti <= i <= 1017 + 1000ti; SI[tt, ti] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N; SC2_cb2[tt, ti, p = 0] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N; SY_cb2[t, i] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N; SC2_cb1[tt, ti, p] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and 0 < p <= 2; SY_cb1[t, i = N] : T >= 10 and N >= 20 and 2 <= t <= T; SY_cb1[t, i = 0] : T >= 10 and N >= 20 and 2 <= t <= T; SC2_cb0[tt, ti, p] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and -2 <= p < 0; SI_NR[tt, ti, p] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and -2 <= p <= 2; SW[i] : T >= 10 and N >= 20 and -1 <= i <= 1; SWCombos[i, p] : T >= 10 and N >= 20 and -2 <= i <= 2 and p >= -2 + i and -1 <= p <= 1 and p <= 2 + i; SC2_NR2[tt, ti, p, w] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and 0 < p <= 2 and 0 < w <= 9; SC2_NR3[tt, ti, p = 0, w = 9, i] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and 9 + 1000ti <= i <= 1008 + 1000ti; SWAll[w] : T >= 10 and N >= 20 and 0 < w <= 9; SC2_NR[tt, ti, p, w] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 1000ti <= -1019 + N and -2 <= p < 0 and 0 < w <= 9 }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i] }"
	 *   - filter: "{ SWKernel[i] }"
	 *   - filter: "{ SWCombos[i, p] }"
	 *   - filter: "{ SWAll[w] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SWAll[w] -> [(w)] }]"
	 *   - filter: "{ SC2_NR2[tt, ti, p, w]; SC2_cb0[tt, ti, p]; SC2_cb1[tt, ti, p]; SI[tt, ti]; SY_cb2[t, i]; SC2_NR3[tt, ti, p, w, i]; SI_NR[tt, ti, p]; SC2_NR[tt, ti, p, w]; SY_cb0[t, i]; SY_cb1[t, i]; SC2_cb2[tt, ti, p]; SC1[tt, ti, i] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb0[t, i] -> [(t)]; SC2_cb2[tt, ti, p] -> [(9tt)]; SC1[tt, ti, i] -> [(9tt)]; SI[tt, ti] -> [(9tt)]; SY_cb2[t, i] -> [(t)]; SC2_cb1[tt, ti, p] -> [(9tt)]; SY_cb1[t, i] -> [(t)]; SC2_cb0[tt, ti, p] -> [(9tt)]; SI_NR[tt, ti, p] -> [(9tt)]; SC2_NR2[tt, ti, p, w] -> [(9tt - w)]; SC2_NR3[tt, ti, p, w, i] -> [(9tt - w)]; SC2_NR[tt, ti, p, w] -> [(9tt - w)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb2[t, i]; SY_cb0[t, i]; SY_cb1[t, i] }"
	 *         - filter: "{ SC2_NR2[tt, ti, p, w]; SC2_NR3[tt, ti, p, w, i]; SC2_NR[tt, ti, p, w]; SC1[tt, ti, i] }"
	 *         - filter: "{ SC2_cb0[tt, ti, p]; SC2_cb1[tt, ti, p]; SC2_cb2[tt, ti, p] }"
	 *         - filter: "{ SI_NR[tt, ti, p] }"
	 *         - filter: "{ SI[tt, ti] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  SW(c0);
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  SWKernel(c0);
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  for (int c1 = max(-1, c0 - 2); c1 <= min(1, c0 + 2); c1 += 1) {
	    SWCombos(c0, c1);
	  }
	}
	for (int c0 = 1; c0 <= 9; c0 += 1) {
	  SWAll(c0);
	}
	for (int c0 = 0; c0 <= 1; c0 += 1) {
	  for (int c2 = 0; c2 <= N; c2 += 1) {
	    SY_cb0(c0, c2);
	  }
	}
	for (int c0 = 2; c0 <= T; c0 += 1) {
	  SY_cb1(c0, 0);
	  SY_cb1(c0, N);
	  for (int c2 = 1; c2 < N; c2 += 1) {
	    SY_cb2(c0, c2);
	  }
	  if (T >= c0 + 18 && c0 % 9 == 0) {
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c5 = 1000 * c2 + 9; c5 <= 1000 * c2 + 1008; c5 += 1) {
	        SC2_NR3((c0 / 9) + 1, c2, 0, 9, c5);
	      }
	    }
	  }
	  if (c0 >= 9 && (c0 % 9) + T >= c0 + 18) {
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = 1; c3 <= 2; c3 += 1) {
	        SC2_NR2((c0 + 9) / 9, c2, c3, -(c0 % 9) + 9);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = -2; c3 < 0; c3 += 1) {
	        SC2_NR((c0 + 9) / 9, c2, c3, -(c0 % 9) + 9);
	      }
	    }
	  }
	  if (c0 >= 18 && T >= c0 + 9 && c0 % 9 == 0) {
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = 1000 * c2; c3 <= 1000 * c2 + 1017; c3 += 1) {
	        SC1(c0 / 9, c2, c3);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      SC2_cb2(c0 / 9, c2, 0);
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = -2; c3 < 0; c3 += 1) {
	        SC2_cb0(c0 / 9, c2, c3);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = 1; c3 <= 2; c3 += 1) {
	        SC2_cb1(c0 / 9, c2, c3);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      for (int c3 = -2; c3 <= 2; c3 += 1) {
	        SI_NR(c0 / 9, c2, c3);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 19) / 1000; c2 += 1) {
	      SI(c0 / 9, c2);
	    }
	  }
	}

	stop_timer();
	execution_time = elapsed_time();

	#undef SY
	#undef SW
	#undef SWKernel
	#undef SWCombos
	#undef SWAll
	#undef SC1
	#undef SC2
	#undef SI
	#undef SC2_NR
	#undef SC2_NR2
	#undef SC2_NR3
	#undef SI_NR

	#if defined TIMING
	struct Result result = new_result();
	result.result = execution_time;
	
	#elif defined ERROR_INJECTION
	// Count checksum difference above THRESHOLD
	struct INJ inj = { tt_INJ, ti_INJ };
	struct Result result = new_result();
	result.bit = BIT;
	result.inj = inj;
	result.noise = -1;
	
	const char* verbose = getenv("VERBOSE");
	
	#define print_SI(tt,ti) printf("v2_I(%d,%d) = %E\n",tt,ti, fabs(I(tt,ti)))
	#define acc_noise(tt,ti) result.noise = max(result.noise, fabs(I(tt,ti)))
	#define SI(tt,ti) do { if (verbose != NULL && fabs(I(tt,ti))>=threshold) print_SI(tt,ti); acc_noise(tt,ti); if (tt==tt_INJ && ti==ti_INJ) { if (fabs(I(tt,ti))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 9; tt += 1) {
	  for (int ti = 1; ti < (N - 19) / 1000; ti += 1) {
	    SI(tt, ti);
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
	 free(WAll);
	
	 free(W);
	
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		 free(I_NR[tt]);
	}
	free(I_NR);
	
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		 free(I[tt]);
	}
	free(I);
	
	 free(WKernel);
	
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		 free(C1[tt]);
	}
	free(C1);
	
	 free(WCombos);
	
	for (int tt=0; tt<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		for (int ti=0; ti<((-27 + T >= 0 && -2019 + N >= 0) ? ((-2 + floord(981 + N, 1000))) : 0); ti++) {
			 free(C2[tt][ti]);
		}
		free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
