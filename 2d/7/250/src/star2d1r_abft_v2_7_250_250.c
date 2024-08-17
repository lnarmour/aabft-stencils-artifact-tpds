/* star2d1r_abft_v2_7_250_250.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star2d1r_abft_v2_7_250_250 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j]: 0 <= i <= N and 0 <= j <= N }
 *	 	outputs
 *	 		Y : {[t, i, j]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N }
 *	 	locals
 *	 		W : {[i, j]: -1 <= i <= 1 and -1 <= j <= 1 }
 *	 		C1 : {[tt, ti, tj]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N }
 *	 		C2 : {[tt, ti, tj, p, q]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p <= 2 and -2 <= q <= 2 }
 *	 		I : {[tt, ti, tj]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N }
 *	 		WKernel : {[i, j]: -2 <= i <= 2 and -2 <= j <= 2 }
 *	 		WCombos : {[i, j]: -2 <= i <= 2 and -2 <= j <= 2 }
 *	 		WAll : {[w]: 0 < w <= 7 }
 *	 		C2_NR : {[tt, ti, tj, p, q]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and -2 <= q < 0 }
 *	 		C2_NR2 : {[tt, ti, tj, p, q]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and -2 <= q < 0 }
 *	 		C2_NR3 : {[tt, ti, tj, p, q]: p = 0 and tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= q < 0 }
 *	 		C2_NR4 : {[tt, ti, tj, p, q]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and 0 < q <= 2 }
 *	 		C2_NR5 : {[tt, ti, tj, p, q]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and 0 < q <= 2 }
 *	 		C2_NR6 : {[tt, ti, tj, p, q]: p = 0 and tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < q <= 2 }
 *	 		C2_NR7 : {[tt, ti, tj, p, q]: q = 0 and tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 }
 *	 		C2_NR8 : {[tt, ti, tj, p, q]: q = 0 and tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 }
 *	 		C2_NR9 : {[tt, ti, tj, p, q]: p = 0 and q = 0 and tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N }
 *	 		I_NR : {[tt, ti, tj]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N }
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
 *	 		WKernel[i,j] = case  {
 *	 			{: -1 <= i <= 1 and -1 <= j <= 1 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		WCombos[i,j] = reduce(+, (i,j,p,q->i,j), (WKernel[i-p,j-q] * W[p,q]));
 *	 		
 *	 		WAll[w] = case  {
 *	 			{: w = 1 } : 1[];
 *	 			{: w >= 2 } : (WAll[w-1] * WCombos[0,0]);
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj] = reduce(+, (tt,ti,tj,i,j->tt,ti,tj), {: 250ti <= i <= 263 + 250ti and 250tj <= j <= 263 + 250tj } : Y[7tt,i,j]);
 *	 		
 *	 		C2[tt,ti,tj,p,q] = case  {
 *	 			(WCombos[p,q] * C2_NR);
 *	 			(WCombos[p,q] * C2_NR2);
 *	 			(WCombos[p,q] * C2_NR3);
 *	 			(WCombos[p,q] * C2_NR4);
 *	 			(WCombos[p,q] * C2_NR5);
 *	 			(WCombos[p,q] * C2_NR6);
 *	 			(WCombos[p,q] * C2_NR7);
 *	 			(WCombos[p,q] * C2_NR8);
 *	 			(WCombos[p,q] * C2_NR9);
 *	 		};
 *	 		
 *	 		I[tt,ti,tj] = ((I_NR - C1) / C1);
 *	 		
 *	 		C2_NR[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w->tt,ti,tj,p,q), (WAll[w] * Y[7tt-w,250ti+p+w,250tj+q+w]));
 *	 		
 *	 		C2_NR2[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w->tt,ti,tj,p,q), (WAll[w] * Y[7tt-w,250ti+p-w+263,250tj+q+w]));
 *	 		
 *	 		C2_NR3[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w,i->tt,ti,tj,p,q), {: 0 < w <= 7 and 250ti + w <= i <= 263 + 250ti - w } : (WAll[w] * Y[7tt-w,i,250tj+q+w]));
 *	 		
 *	 		C2_NR4[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w->tt,ti,tj,p,q), (WAll[w] * Y[7tt-w,250ti+p+w,250tj+q-w+263]));
 *	 		
 *	 		C2_NR5[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w->tt,ti,tj,p,q), (WAll[w] * Y[7tt-w,250ti+p-w+263,250tj+q-w+263]));
 *	 		
 *	 		C2_NR6[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w,i->tt,ti,tj,p,q), {: 0 < w <= 7 and 250ti + w <= i <= 263 + 250ti - w } : (WAll[w] * Y[7tt-w,i,250tj+q-w+263]));
 *	 		
 *	 		C2_NR7[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w,j->tt,ti,tj,p,q), {: 0 < w <= 7 and 250tj + w <= j <= 263 + 250tj - w } : (WAll[w] * Y[7tt-w,250ti+p+w,j]));
 *	 		
 *	 		C2_NR8[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w,j->tt,ti,tj,p,q), {: 0 < w <= 7 and 250tj + w <= j <= 263 + 250tj - w } : (WAll[w] * Y[7tt-w,250ti+p-w+263,j]));
 *	 		
 *	 		C2_NR9[tt,ti,tj,p,q] = reduce(+, (tt,ti,tj,p,q,w,i,j->tt,ti,tj,p,q), {: w = 7 and 7 + 250ti <= i <= 256 + 250ti and 7 + 250tj <= j <= 256 + 250tj } : (WAll[w] * Y[7tt-w,i,j]));
 *	 		
 *	 		I_NR[tt,ti,tj] = reduce(+, (tt,ti,tj,p,q->tt,ti,tj), C2);
 *	 .
 *
 * Uses the memory map:
 *	 C2_NR(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,q)
 *	 C2_NR2(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,q)
 *	 C2_NR3(tt,ti,tj,p,q) -> C2(tt,ti,tj,0,q)
 *	 C2_NR4(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,q)
 *	 C2_NR5(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,q)
 *	 C2_NR6(tt,ti,tj,p,q) -> C2(tt,ti,tj,0,q)
 *	 C2_NR7(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,0)
 *	 C2_NR8(tt,ti,tj,p,q) -> C2(tt,ti,tj,p,0)
 *	 C2_NR9(tt,ti,tj,p,q) -> C2(tt,ti,tj,0,0)
 *	 Y(t,i,j) -> Y(t - 2*floord(t, 2),i,j)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i,j] }"
 *     - filter: "{ SWKernel[i,j] }"
 *     - filter: "{ SWCombos[i,j,p,q] }"
 *     - filter: "{ SWAll[w] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { SWAll[w]->[w] } \
 *         ]"
 *     - filter: "{ \
 *         SY_cb0[t,i,j]; \
 *         SY_cb1[t,i,j]; \
 *         SY_cb2[t,i,j]; \
 *         SC1[tt,ti,tj,i,j]; \
 *         SC2_NR[tt,ti,tj,p,q,w]; \
 *         SC2_NR2[tt,ti,tj,p,q,w]; \
 *         SC2_NR3[tt,ti,tj,p,q,w,i]; \
 *         SC2_NR4[tt,ti,tj,p,q,w]; \
 *         SC2_NR5[tt,ti,tj,p,q,w]; \
 *         SC2_NR6[tt,ti,tj,p,q,w,i]; \
 *         SC2_NR7[tt,ti,tj,p,q,w,j]; \
 *         SC2_NR8[tt,ti,tj,p,q,w,j]; \
 *         SC2_NR9[tt,ti,tj,p,q,w,i,j]; \
 *         SC2_cb0[tt,ti,tj,p,q]; \
 *         SC2_cb1[tt,ti,tj,p,q]; \
 *         SC2_cb2[tt,ti,tj,p,q]; \
 *         SC2_cb3[tt,ti,tj,p,q]; \
 *         SC2_cb4[tt,ti,tj,p,q]; \
 *         SC2_cb5[tt,ti,tj,p,q]; \
 *         SC2_cb6[tt,ti,tj,p,q]; \
 *         SC2_cb7[tt,ti,tj,p,q]; \
 *         SC2_cb8[tt,ti,tj,p,q]; \
 *         SI_NR[tt,ti,tj,p,q]; \
 *         SI[tt,ti,tj] \
 *       }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { \
 *             SY_cb0[t,i,j]->[t]; \
 *             SY_cb1[t,i,j]->[t]; \
 *             SY_cb2[t,i,j]->[t]; \
 *             SC1[tt,ti,tj,i,j]->[7tt]; \
 *             SC2_cb0[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb1[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb2[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb3[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb4[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb5[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb6[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb7[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_cb8[tt,ti,tj,p,q]->[7tt]; \
 *             SC2_NR[tt,ti,tj,p,q,w]->[7tt-w]; \
 *             SC2_NR2[tt,ti,tj,p,q,w]->[7tt-w]; \
 *             SC2_NR3[tt,ti,tj,p,q,w,i]->[7tt-w]; \
 *             SC2_NR4[tt,ti,tj,p,q,w]->[7tt-w]; \
 *             SC2_NR5[tt,ti,tj,p,q,w]->[7tt-w]; \
 *             SC2_NR6[tt,ti,tj,p,q,w,i]->[7tt-w]; \
 *             SC2_NR7[tt,ti,tj,p,q,w,j]->[7tt-w]; \
 *             SC2_NR8[tt,ti,tj,p,q,w,j]->[7tt-w]; \
 *             SC2_NR9[tt,ti,tj,p,q,w,i,j]->[7tt-w]; \
 *             SI[tt,ti,tj]->[7tt]; \
 *             SI_NR[tt,ti,tj,p,q]->[7tt] \
 *           } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i,j]; SY_cb1[t,i,j]; SY_cb2[t,i,j] }"
 *           - filter: "{ SC1[tt,ti,tj,i,j]; SC2_NR[tt,ti,tj,p,q,w]; SC2_NR2[tt,ti,tj,p,q,w]; SC2_NR3[tt,ti,tj,p,q,w,i]; SC2_NR4[tt,ti,tj,p,q,w]; SC2_NR5[tt,ti,tj,p,q,w]; SC2_NR6[tt,ti,tj,p,q,w,i]; SC2_NR7[tt,ti,tj,p,q,w,j]; SC2_NR8[tt,ti,tj,p,q,w,j]; SC2_NR9[tt,ti,tj,p,q,w,i,j] }"
 *           - filter: "{ SC2_cb0[tt,ti,tj,p,q]; SC2_cb1[tt,ti,tj,p,q]; SC2_cb2[tt,ti,tj,p,q]; SC2_cb3[tt,ti,tj,p,q]; SC2_cb4[tt,ti,tj,p,q]; SC2_cb5[tt,ti,tj,p,q]; SC2_cb6[tt,ti,tj,p,q]; SC2_cb7[tt,ti,tj,p,q]; SC2_cb8[tt,ti,tj,p,q] }"
 *           - filter: "{ SI_NR[tt,ti,tj,p,q] }"
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
#define mem_C2(tt,ti,tj,p,q) C2[(tt)-(2)][(ti)-(1)][(tj)-(1)][(p)-(-2)][(q)-(-2)]
#define mem_I(tt,ti,tj) I[(tt)-(2)][(ti)-(1)][(tj)-(1)]
#define mem_WKernel(i,j) WKernel[(i)-(-2)][(j)-(-2)]
#define mem_WCombos(i,j) WCombos[(i)-(-2)][(j)-(-2)]
#define mem_WAll(w) WAll[(w)-(1)]
#define mem_I_NR(tt,ti,tj) I_NR[(tt)-(2)][(ti)-(1)][(tj)-(1)]

// Memory access functions
#define X(i,j) mem_X(((i)),((j)))
#define Y(t,i,j) mem_Y(((t) - 2*floord((t), 2)),((i)),((j)))
#define W(i,j) mem_W(((i)),((j)))
#define C1(tt,ti,tj) mem_C1(((tt)),((ti)),((tj)))
#define C2(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),((q)))
#define I(tt,ti,tj) mem_I(((tt)),((ti)),((tj)))
#define WKernel(i,j) mem_WKernel(((i)),((j)))
#define WCombos(i,j) mem_WCombos(((i)),((j)))
#define WAll(w) mem_WAll(((w)))
#define C2_NR(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),((q)))
#define C2_NR2(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),((q)))
#define C2_NR3(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),(0),((q)))
#define C2_NR4(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),((q)))
#define C2_NR5(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),((q)))
#define C2_NR6(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),(0),((q)))
#define C2_NR7(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),(0))
#define C2_NR8(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),((p)),(0))
#define C2_NR9(tt,ti,tj,p,q) mem_C2(((tt)),((ti)),((tj)),(0),(0))
#define I_NR(tt,ti,tj) mem_I_NR(((tt)),((ti)),((tj)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int tj_INJ;
int BIT;

void inject_star2d1r_abft_v2_7_250_250(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star2d1r_abft_v2_7_250_250(double T, double N, float **X, float ***Y)
#else
struct Result star2d1r_abft_v2_7_250_250(long T, long N, float **X, float ***Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
	double total_card = ((((double)-21) + T >= ((double)0) && ((double)-515) + N >= ((double)0)) ? (((((((double)-1173349) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N) + ((double)586780) * floord(T, ((double)7))) + (((double)1173560) - ((double)586780) * floord(T, ((double)7))) * floord(((double)235) + N, ((double)250)) + (((double)-293390) + ((double)146695) * floord(T, ((double)7))) * floord(((double)235) + N, ((double)250))*floord(((double)235) + N, ((double)250)))) : ((((double)-21) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)514) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)20) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)211) + T) + (((double)2) + ((double)2) * T) * N + (((double)1) + T) * N*N)) : ((double)0));
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
	tj_INJ = getenv("tj_INJ") != NULL ? atoi(getenv("tj_INJ")) : -1;
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float* WAll = (float*)(calloc((7),sizeof(float)));
	
	float** W = (float**)(calloc((3),sizeof(float*)));
	for (int i=0; i<(3); i++) {
		W[i] = (float*)(calloc((3),sizeof(float)));
	}
	
	float*** I_NR = (float***)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		I_NR[tt] = (float**)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			I_NR[tt][ti] = (float*)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float)));
		}
	}
	
	float*** I = (float***)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		I[tt] = (float**)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			I[tt][ti] = (float*)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float)));
		}
	}
	
	float** WKernel = (float**)(calloc((5),sizeof(float*)));
	for (int i=0; i<(5); i++) {
		WKernel[i] = (float*)(calloc((5),sizeof(float)));
	}
	
	float*** C1 = (float***)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float**)));
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C1[tt] = (float**)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float*)));
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			C1[tt][ti] = (float*)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float)));
		}
	}
	
	float** WCombos = (float**)(calloc((5),sizeof(float*)));
	for (int i=0; i<(5); i++) {
		WCombos[i] = (float*)(calloc((5),sizeof(float)));
	}
	
	float***** C2 = (float*****)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float****)));
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C2[tt] = (float****)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float***)));
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			C2[tt][ti] = (float***)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0),sizeof(float**)));
			for (int tj=0; tj<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); tj++) {
				C2[tt][ti][tj] = (float**)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? (5) : 0),sizeof(float*)));
				for (int p=0; p<((-21 + T >= 0 && -515 + N >= 0) ? (5) : 0); p++) {
					C2[tt][ti][tj][p] = (float*)(calloc(((-21 + T >= 0 && -515 + N >= 0) ? (5) : 0),sizeof(float)));
				}
			}
		}
	}

	#define SC1(tt,ti,tj,i,j) C1(tt,ti,tj) += Y((7*(tt)),((i)),((j)))
	#define SC2_NR(tt,ti,tj,p,q,w) C2_NR(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(250*(ti) + (p) + (w)),(250*(tj) + (q) + (w))))
	#define SC2_NR2(tt,ti,tj,p,q,w) C2_NR2(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(263 + 250*(ti) + (p) - (w)),(250*(tj) + (q) + (w))))
	#define SC2_NR3(tt,ti,tj,p,q,w,i) C2_NR3(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),((i)),(250*(tj) + (q) + (w))))
	#define SC2_NR4(tt,ti,tj,p,q,w) C2_NR4(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(250*(ti) + (p) + (w)),(263 + 250*(tj) + (q) - (w))))
	#define SC2_NR5(tt,ti,tj,p,q,w) C2_NR5(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(263 + 250*(ti) + (p) - (w)),(263 + 250*(tj) + (q) - (w))))
	#define SC2_NR6(tt,ti,tj,p,q,w,i) C2_NR6(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),((i)),(263 + 250*(tj) + (q) - (w))))
	#define SC2_NR7(tt,ti,tj,p,q,w,j) C2_NR7(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(250*(ti) + (p) + (w)),((j))))
	#define SC2_NR8(tt,ti,tj,p,q,w,j) C2_NR8(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),(263 + 250*(ti) + (p) - (w)),((j))))
	#define SC2_NR9(tt,ti,tj,p,q,w,i,j) C2_NR9(tt,ti,tj,p,q) += (WAll(((w)))) * (Y((7*(tt) - (w)),((i)),((j))))
	#define SC2_cb0(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR(tt,ti,tj,p,q))
	#define SC2_cb1(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR2(tt,ti,tj,p,q))
	#define SC2_cb2(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR3(tt,ti,tj,p,q))
	#define SC2_cb3(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR4(tt,ti,tj,p,q))
	#define SC2_cb4(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR5(tt,ti,tj,p,q))
	#define SC2_cb5(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR6(tt,ti,tj,p,q))
	#define SC2_cb6(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR7(tt,ti,tj,p,q))
	#define SC2_cb7(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR8(tt,ti,tj,p,q))
	#define SC2_cb8(tt,ti,tj,p,q) C2(tt,ti,tj,p,q) = (WCombos(((p)),((q)))) * (C2_NR9(tt,ti,tj,p,q))
	#define SI(tt,ti,tj) I(tt,ti,tj) = ((I_NR(tt,ti,tj)) - (C1(tt,ti,tj))) / (C1(tt,ti,tj))
	#define SI_NR(tt,ti,tj,p,q) I_NR(tt,ti,tj) += C2(tt,ti,tj,p,q)
	#define SW(i,j) W(i,j) = (((j) == (0)) && ((-1 + i) == (0))) ? (0.1249) : ((((1 + j) == (0)) && ((i) == (0))) ? (0.125) : ((((j) == (0)) && ((i) == (0))) ? (0.5002) : ((((j) == (0)) && ((1 + i) == (0))) ? (0.1247) : ((((-1 + j) == (0)) && ((i) == (0))) ? (0.1251) : (0)))))
	#define SWAll(w) WAll(w) = ((-1 + w) == (0)) ? (1) : ((WAll((-1 + (w)))) * (WCombos((0),(0))))
	#define SWCombos(i,j,p,q) WCombos(i,j) += (WKernel(((i) - (p)),((j) - (q)))) * (W(((p)),((q))))
	#define SWKernel(i,j) WKernel(i,j) = (((((1 + i) >= (0)) && ((1 - i) >= (0))) && ((1 + j) >= (0))) && ((1 - j) >= (0))) ? (1) : (0)
	#define SY_cb0(t,i,j) Y(t,i,j) = X(((i)),((j)))
	#define SY_cb1(t,i,j) Y(t,i,j) = Y((-1 + (t)),((i)),((j)))
	#define SY_cb2_hook(t,i,j) Y(t,i,j) = (((((0.5002) * (Y((-1 + (t)),((i)),((j))))) + ((0.1247) * (Y((-1 + (t)),(-1 + (i)),((j)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)))))) + ((0.1251) * (Y((-1 + (t)),((i)),(1 + (j)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j) do { SY_cb2_hook(t,i,j); if (t==7*(tt_INJ-1)+1 && i==250*ti_INJ+132 && j==250*tj_INJ+132) inject_star2d1r_abft_v2_7_250_250(&Y(t,i,j)); } while(0)
	#else
	#define SY_cb2(t,i,j) SY_cb2_hook(t,i,j)
	#endif

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SC2_cb3[tt, ti, tj, p, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and 0 < q <= 2; SC2_cb8[tt, ti, tj, p = 0, q = 0] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N; SC2_cb5[tt, ti, tj, p = 0, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < q <= 2; SC1[tt, ti, tj, i, j] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 250ti <= i <= 263 + 250ti and 250tj <= j <= 263 + 250tj; SC2_cb2[tt, ti, tj, p = 0, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= q < 0; SC2_NR6[tt, ti, tj, p = 0, q, w, i] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < q <= 2 and 0 < w <= 7 and 250ti + w <= i <= 263 + 250ti - w; SC2_NR[tt, ti, tj, p, q, w] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and -2 <= q < 0 and 0 < w <= 7; SC2_NR8[tt, ti, tj, p, q = 0, w, j] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and 0 < w <= 7 and 250tj + w <= j <= 263 + 250tj - w; SC2_cb4[tt, ti, tj, p, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and 0 < q <= 2; SY_cb1[t, i, j = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = N, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N; SY_cb1[t, i, j = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N; SY_cb1[t, i = 0, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N; SC2_NR9[tt, ti, tj, p = 0, q = 0, w = 7, i, j] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 7 + 250ti <= i <= 256 + 250ti and 7 + 250tj <= j <= 256 + 250tj; SWAll[w] : T >= 10 and N >= 20 and 0 < w <= 7; SC2_cb7[tt, ti, tj, p, q = 0] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2; SI[tt, ti, tj] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N; SY_cb2[t, i, j] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N; SC2_NR2[tt, ti, tj, p, q, w] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and -2 <= q < 0 and 0 < w <= 7; SC2_cb6[tt, ti, tj, p, q = 0] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0; SWKernel[i, j] : T >= 10 and N >= 20 and -2 <= i <= 2 and -2 <= j <= 2; SC2_NR7[tt, ti, tj, p, q = 0, w, j] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and 0 < w <= 7 and 250tj + w <= j <= 263 + 250tj - w; SWCombos[i, j, p, q] : T >= 10 and N >= 20 and -2 <= i <= 2 and -2 <= j <= 2 and p >= -2 + i and -1 <= p <= 1 and p <= 2 + i and q >= -2 + j and -1 <= q <= 1 and q <= 2 + j; SC2_NR3[tt, ti, tj, p = 0, q, w, i] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= q < 0 and 0 < w <= 7 and 250ti + w <= i <= 263 + 250ti - w; SY_cb0[t, i, j] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N; SC2_NR4[tt, ti, tj, p, q, w] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and 0 < q <= 2 and 0 < w <= 7; SC2_cb1[tt, ti, tj, p, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and -2 <= q < 0; SC2_cb0[tt, ti, tj, p, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p < 0 and -2 <= q < 0; SI_NR[tt, ti, tj, p, q] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and -2 <= p <= 2 and -2 <= q <= 2; SC2_NR5[tt, ti, tj, p, q, w] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 250ti <= -265 + N and tj > 0 and 250tj <= -265 + N and 0 < p <= 2 and 0 < q <= 2 and 0 < w <= 7; SW[i, j] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j] }"
	 *   - filter: "{ SWKernel[i, j] }"
	 *   - filter: "{ SWCombos[i, j, p, q] }"
	 *   - filter: "{ SWAll[w] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SWAll[w] -> [(w)] }]"
	 *   - filter: "{ SC2_cb6[tt, ti, tj, p, q]; SY_cb2[t, i, j]; SY_cb1[t, i, j]; SC1[tt, ti, tj, i, j]; SC2_NR4[tt, ti, tj, p, q, w]; SC2_NR5[tt, ti, tj, p, q, w]; SC2_cb5[tt, ti, tj, p, q]; SI[tt, ti, tj]; SC2_NR6[tt, ti, tj, p, q, w, i]; SC2_cb7[tt, ti, tj, p, q]; SC2_NR8[tt, ti, tj, p, q, w, j]; SC2_cb2[tt, ti, tj, p, q]; SC2_cb3[tt, ti, tj, p, q]; SC2_cb8[tt, ti, tj, p, q]; SI_NR[tt, ti, tj, p, q]; SC2_NR7[tt, ti, tj, p, q, w, j]; SC2_NR[tt, ti, tj, p, q, w]; SC2_NR2[tt, ti, tj, p, q, w]; SC2_cb1[tt, ti, tj, p, q]; SC2_NR3[tt, ti, tj, p, q, w, i]; SY_cb0[t, i, j]; SC2_NR9[tt, ti, tj, p, q, w, i, j]; SC2_cb4[tt, ti, tj, p, q]; SC2_cb0[tt, ti, tj, p, q] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SC2_cb3[tt, ti, tj, p, q] -> [(7tt)]; SC1[tt, ti, tj, i, j] -> [(7tt)]; SC2_cb0[tt, ti, tj, p, q] -> [(7tt)]; SC2_NR5[tt, ti, tj, p, q, w] -> [(7tt - w)]; SC2_cb8[tt, ti, tj, p, q] -> [(7tt)]; SC2_NR2[tt, ti, tj, p, q, w] -> [(7tt - w)]; SY_cb0[t, i, j] -> [(t)]; SC2_NR7[tt, ti, tj, p, q, w, j] -> [(7tt - w)]; SI_NR[tt, ti, tj, p, q] -> [(7tt)]; SC2_NR[tt, ti, tj, p, q, w] -> [(7tt - w)]; SC2_cb7[tt, ti, tj, p, q] -> [(7tt)]; SI[tt, ti, tj] -> [(7tt)]; SY_cb2[t, i, j] -> [(t)]; SC2_cb1[tt, ti, tj, p, q] -> [(7tt)]; SY_cb1[t, i, j] -> [(t)]; SC2_cb4[tt, ti, tj, p, q] -> [(7tt)]; SC2_cb5[tt, ti, tj, p, q] -> [(7tt)]; SC2_NR6[tt, ti, tj, p, q, w, i] -> [(7tt - w)]; SC2_NR8[tt, ti, tj, p, q, w, j] -> [(7tt - w)]; SC2_cb6[tt, ti, tj, p, q] -> [(7tt)]; SC2_cb2[tt, ti, tj, p, q] -> [(7tt)]; SC2_NR3[tt, ti, tj, p, q, w, i] -> [(7tt - w)]; SC2_NR4[tt, ti, tj, p, q, w] -> [(7tt - w)]; SC2_NR9[tt, ti, tj, p, q, w, i, j] -> [(7tt - w)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb2[t, i, j]; SY_cb1[t, i, j]; SY_cb0[t, i, j] }"
	 *         - filter: "{ SC2_NR4[tt, ti, tj, p, q, w]; SC1[tt, ti, tj, i, j]; SC2_NR5[tt, ti, tj, p, q, w]; SC2_NR6[tt, ti, tj, p, q, w, i]; SC2_NR8[tt, ti, tj, p, q, w, j]; SC2_NR7[tt, ti, tj, p, q, w, j]; SC2_NR[tt, ti, tj, p, q, w]; SC2_NR2[tt, ti, tj, p, q, w]; SC2_NR3[tt, ti, tj, p, q, w, i]; SC2_NR9[tt, ti, tj, p, q, w, i, j] }"
	 *         - filter: "{ SC2_cb5[tt, ti, tj, p, q]; SC2_cb7[tt, ti, tj, p, q]; SC2_cb2[tt, ti, tj, p, q]; SC2_cb3[tt, ti, tj, p, q]; SC2_cb8[tt, ti, tj, p, q]; SC2_cb1[tt, ti, tj, p, q]; SC2_cb4[tt, ti, tj, p, q]; SC2_cb6[tt, ti, tj, p, q]; SC2_cb0[tt, ti, tj, p, q] }"
	 *         - filter: "{ SI_NR[tt, ti, tj, p, q] }"
	 *         - filter: "{ SI[tt, ti, tj] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  for (int c1 = -1; c1 <= 1; c1 += 1) {
	    SW(c0, c1);
	  }
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  for (int c1 = -2; c1 <= 2; c1 += 1) {
	    SWKernel(c0, c1);
	  }
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  for (int c1 = -2; c1 <= 2; c1 += 1) {
	    for (int c2 = max(-1, c0 - 2); c2 <= min(1, c0 + 2); c2 += 1) {
	      for (int c3 = max(-1, c1 - 2); c3 <= min(1, c1 + 2); c3 += 1) {
	        SWCombos(c0, c1, c2, c3);
	      }
	    }
	  }
	}
	for (int c0 = 1; c0 <= 7; c0 += 1) {
	  SWAll(c0);
	}
	for (int c0 = 0; c0 <= 1; c0 += 1) {
	  for (int c2 = 0; c2 <= N; c2 += 1) {
	    for (int c3 = 0; c3 <= N; c3 += 1) {
	      SY_cb0(c0, c2, c3);
	    }
	  }
	}
	for (int c0 = 2; c0 <= T; c0 += 1) {
	  for (int c2 = 0; c2 <= N; c2 += 1) {
	    if (c2 >= 1 && N >= c2 + 1) {
	      SY_cb1(c0, c2, 0);
	    } else {
	      if (c2 == 0) {
	        for (int c3 = 0; c3 < N; c3 += 1) {
	          SY_cb1(c0, 0, c3);
	        }
	      } else {
	        for (int c3 = 0; c3 < N; c3 += 1) {
	          SY_cb1(c0, N, c3);
	        }
	      }
	    }
	    SY_cb1(c0, c2, N);
	  }
	  for (int c2 = 1; c2 < N; c2 += 1) {
	    for (int c3 = 1; c3 < N; c3 += 1) {
	      SY_cb2(c0, c2, c3);
	    }
	  }
	  if (T >= c0 + 14 && c0 % 7 == 0) {
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c7 = 250 * c2 + 7; c7 <= 250 * c2 + 256; c7 += 1) {
	          for (int c8 = 250 * c3 + 7; c8 <= 250 * c3 + 256; c8 += 1) {
	            SC2_NR9((c0 / 7) + 1, c2, c3, 0, 0, 7, c7, c8);
	          }
	        }
	      }
	    }
	  }
	  if (c0 >= 7 && (c0 % 7) + T >= c0 + 14) {
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            SC2_NR((c0 + 7) / 7, c2, c3, c4, c5, -(c0 % 7) + 7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            SC2_NR4((c0 + 7) / 7, c2, c3, c4, c5, -(c0 % 7) + 7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          for (int c7 = -(c0 % 7) + 250 * c3 + 7; c7 <= (c0 % 7) + 250 * c3 + 256; c7 += 1) {
	            SC2_NR8((c0 + 7) / 7, c2, c3, c4, 0, -(c0 % 7) + 7, c7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          for (int c7 = -(c0 % 7) + 250 * c3 + 7; c7 <= (c0 % 7) + 250 * c3 + 256; c7 += 1) {
	            SC2_NR7((c0 + 7) / 7, c2, c3, c4, 0, -(c0 % 7) + 7, c7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            SC2_NR5((c0 + 7) / 7, c2, c3, c4, c5, -(c0 % 7) + 7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            SC2_NR2((c0 + 7) / 7, c2, c3, c4, c5, -(c0 % 7) + 7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c5 = 1; c5 <= 2; c5 += 1) {
	          for (int c7 = -(c0 % 7) + 250 * c2 + 7; c7 <= (c0 % 7) + 250 * c2 + 256; c7 += 1) {
	            SC2_NR6((c0 + 7) / 7, c2, c3, 0, c5, -(c0 % 7) + 7, c7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c5 = -2; c5 < 0; c5 += 1) {
	          for (int c7 = -(c0 % 7) + 250 * c2 + 7; c7 <= (c0 % 7) + 250 * c2 + 256; c7 += 1) {
	            SC2_NR3((c0 + 7) / 7, c2, c3, 0, c5, -(c0 % 7) + 7, c7);
	          }
	        }
	      }
	    }
	  }
	  if (c0 >= 14 && T >= c0 + 7 && c0 % 7 == 0) {
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 250 * c2; c4 <= 250 * c2 + 263; c4 += 1) {
	          for (int c5 = 250 * c3; c5 <= 250 * c3 + 263; c5 += 1) {
	            SC1(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c5 = -2; c5 < 0; c5 += 1) {
	          SC2_cb2(c0 / 7, c2, c3, 0, c5);
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c5 = 1; c5 <= 2; c5 += 1) {
	          SC2_cb5(c0 / 7, c2, c3, 0, c5);
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            SC2_cb4(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        SC2_cb8(c0 / 7, c2, c3, 0, 0);
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          SC2_cb7(c0 / 7, c2, c3, c4, 0);
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = 1; c4 <= 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            SC2_cb1(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          SC2_cb6(c0 / 7, c2, c3, c4, 0);
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            SC2_cb0(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 < 0; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            SC2_cb3(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        for (int c4 = -2; c4 <= 2; c4 += 1) {
	          for (int c5 = -2; c5 <= 2; c5 += 1) {
	            SI_NR(c0 / 7, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N - 15) / 250; c2 += 1) {
	      for (int c3 = 1; c3 < (N - 15) / 250; c3 += 1) {
	        SI(c0 / 7, c2, c3);
	      }
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
	#undef SC2_NR4
	#undef SC2_NR5
	#undef SC2_NR6
	#undef SC2_NR7
	#undef SC2_NR8
	#undef SC2_NR9
	#undef SI_NR

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
	
	#define print_SI(tt,ti,tj) printf("v2_I(%d,%d,%d) = %E\n",tt,ti,tj, fabs(I(tt,ti,tj)))
	#define acc_noise(tt,ti,tj) result.noise = max(result.noise, fabs(I(tt,ti,tj)))
	#define SI(tt,ti,tj) do { if (verbose != NULL && fabs(I(tt,ti,tj))>=threshold) print_SI(tt,ti,tj); acc_noise(tt,ti,tj); if (tt==tt_INJ && ti==ti_INJ && tj==tj_INJ) { if (fabs(I(tt,ti,tj))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti,tj))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 7; tt += 1) {
	  for (int ti = 1; ti < (N - 15) / 250; ti += 1) {
	    for (int tj = 1; tj < (N - 15) / 250; tj += 1) {
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
	 free(WAll);
	
	for (int i=0; i<(3); i++) {
		 free(W[i]);
	}
	free(W);
	
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			 free(I_NR[tt][ti]);
		}
		free(I_NR[tt]);
	}
	free(I_NR);
	
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			 free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int i=0; i<(5); i++) {
		 free(WKernel[i]);
	}
	free(WKernel);
	
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			 free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int i=0; i<(5); i++) {
		 free(WCombos[i]);
	}
	free(WCombos);
	
	for (int tt=0; tt<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -515 + N >= 0) ? ((-2 + floord(235 + N, 250))) : 0); tj++) {
				for (int p=0; p<((-21 + T >= 0 && -515 + N >= 0) ? (5) : 0); p++) {
					 free(C2[tt][ti][tj][p]);
				}
				free(C2[tt][ti][tj]);
			}
			free(C2[tt][ti]);
		}
		free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
