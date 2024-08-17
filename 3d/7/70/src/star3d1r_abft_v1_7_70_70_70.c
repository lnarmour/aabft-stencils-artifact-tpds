/* star3d1r_abft_v1_7_70_70_70.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_7_70_70_70 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 7 and -1 - w <= i <= 70 + w and -1 - w <= j <= 70 + w and -1 - w <= k <= 70 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 7 and -1 - w <= i <= 70 + w and -1 - w <= j <= 70 + w and -1 - w <= k <= 70 + w }
 *	 	when {  : T >= 10 and N >= 20 } let
 *	 		Y[t,i,j,k] = case  {
 *	 			{: 0 <= t <= 1 } : X[i,j,k];
 *	 			{: k = N and t >= 2  or  j = N and t >= 2  or  i = N and t >= 2  or  k = 0 and t >= 2  or  j = 0 and t >= 2  or  i = 0 and t >= 2 } : Y[t-1,i,j,k];
 *	 			{: t >= 2 and 0 < i < N and 0 < j < N and 0 < k < N } : (((((((0.25[] * Y[t-1,i,j,k]) + (0.1248[] * Y[t-1,i-1,j,k])) + (0.1249[] * Y[t-1,i+1,j,k])) + (0.125[] * Y[t-1,i,j-1,k])) + (0.125[] * Y[t-1,i,j+1,k])) + (0.1251[] * Y[t-1,i,j,k-1])) + (0.1252[] * Y[t-1,i,j,k+1]));
 *	 		};
 *	 		
 *	 		W[i,j,k] = case  {
 *	 			{: i = 1 and j = 0 and k = 0 } : 0.1249[];
 *	 			{: i = 0 and j = -1 and k = 0 } : 0.125[];
 *	 			{: i = 0 and j = 0 and k = 1 } : 0.1252[];
 *	 			{: i = -1 and j = 0 and k = 0 } : 0.1248[];
 *	 			{: i = 0 and j = 1 and k = 0 } : 0.125[];
 *	 			{: i = 0 and j = 0 and k = -1 } : 0.1251[];
 *	 			{: i = 0 and j = 0 and k = 0 } : 0.25[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		patch[w,i,j,k] = case  {
 *	 			{: w > 0 } : patch_NR;
 *	 			{: w = 0 and 0 <= i <= 69 and 0 <= j <= 69 and 0 <= k <= 69 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 70ti <= i <= 69 + 70ti and 70tj <= j <= 69 + 70tj and 70tk <= k <= 69 + 70tk } : Y[7tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[7,p,q,r] * Y[7tt-7,70ti+p,70tj+q,70tk+r]));
 *	 		
 *	 		I[tt,ti,tj,tk] = ((C2 - C1) / C1);
 *	 		
 *	 		patch_NR[w,i,j,k] = reduce(+, (w,i,j,k,p,q,r->w,i,j,k), (patch[w-1,i-p,j-q,k-r] * W[p,q,r]));
 *	 .
 *
 * Uses the memory map:
 *	 Y(t,i,j,k) -> Y(t - 2*floord(t, 2),i,j,k)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i,j,k] }"
 *     - filter: "{ Spatch[w,i,j,k]; Spatch_NR[w,i,j,k,p,q,r] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { Spatch[w,i,j,k]->[w]; Spatch_NR[w,i,j,k,p,q,r]->[w]} \
 *         ]"
 *     - filter: "{ SI[tt,ti,tj,tk]; SC1[tt,ti,tj,tk,i,j,k]; SC2[tt,ti,tj,tk,p,q,r]; SY_cb0[t,i,j,k]; SY_cb1[t,i,j,k]; SY_cb2[t,i,j,k] }"
 *       child:
 *         schedule: "[T,N]->[\
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[tt]; SC2[tt,ti,tj,tk,p,q,r]->[tt-1]; SI[tt,ti,tj,tk]->[tt]; SY_cb0[t,i,j,k]->[t/7]; SY_cb1[t,i,j,k]->[t/7]; SY_cb2[t,i,j,k]->[t/7] }, \
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[7tt]; SC2[tt,ti,tj,tk,p,q,r]->[7tt-7]; SI[tt,ti,tj,tk]->[7tt]; SY_cb0[t,i,j,k]->[t]; SY_cb1[t,i,j,k]->[t]; SY_cb2[t,i,j,k]->[t] } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i,j,k]; SY_cb1[t,i,j,k]; SY_cb2[t,i,j,k] }"
 *           - filter: "{ SC1[tt,ti,tj,tk,i,j,k]; SC2[tt,ti,tj,tk,p,q,r] }"
 *           - filter: "{ SI[tt,ti,tj,tk] }"
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
#define mem_X(i,j,k) X[(i)-(0)][(j)-(0)][(k)-(0)]
#define mem_Y(t,i,j,k) Y[(t)-(0)][(i)-(0)][(j)-(0)][(k)-(0)]
#define mem_W(i,j,k) W[(i)-(-1)][(j)-(-1)][(k)-(-1)]
#define mem_C1(tt,ti,tj,tk) C1[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]
#define mem_C2(tt,ti,tj,tk) C2[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]
#define mem_I(tt,ti,tj,tk) I[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]
#define mem_patch(w,i,j,k) patch[(w)-(0)][(i)-(-8)][(j)-(-8)][(k)-(-8)]
#define mem_patch_NR(w,i,j,k) patch_NR[(w)-(1)][(i)-(-8)][(j)-(-8)][(k)-(-8)]

// Memory access functions
#define X(i,j,k) mem_X(((i)),((j)),((k)))
#define Y(t,i,j,k) mem_Y(((t) - 2*floord((t), 2)),((i)),((j)),((k)))
#define W(i,j,k) mem_W(((i)),((j)),((k)))
#define C1(tt,ti,tj,tk) mem_C1(((tt)),((ti)),((tj)),((tk)))
#define C2(tt,ti,tj,tk) mem_C2(((tt)),((ti)),((tj)),((tk)))
#define I(tt,ti,tj,tk) mem_I(((tt)),((ti)),((tj)),((tk)))
#define patch(w,i,j,k) mem_patch(((w)),((i)),((j)),((k)))
#define patch_NR(w,i,j,k) mem_patch_NR(((w)),((i)),((j)),((k)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int tj_INJ;
int tk_INJ;
int BIT;

void inject_star3d1r_abft_v1_7_70_70_70(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_7_70_70_70(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_7_70_70_70(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-21) + T >= ((double)0) && ((double)-148) + N >= ((double)0)) ? ((((((((double)110047012) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N) - ((double)7832456) * floord(T, ((double)7))) + ((((double)4970112) + ((double)177504) * N) + (((double)-2485056) - ((double)88752) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70)) + ((((double)-5403552) + ((double)57792) * N + ((double)1032) * N*N) + (((double)2701776) - ((double)28896) * N - ((double)516) * N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)-1978816) - ((double)67536) * N + ((double)168) * N*N + ((double)2) * N*N*N) + (((double)989408) + ((double)33768) * N - ((double)84) * N*N - N*N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)1099560) - ((double)11760) * N - ((double)210) * N*N) + (((double)-549780) + ((double)5880) * N + ((double)105) * N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)205800) + ((double)7350) * N) + (((double)-102900) - ((double)3675) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + (((double)-85750) + ((double)42875) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))) + (((((double)-28467480) - ((double)177504) * N) + (((double)14233740) + ((double)88752) * N) * floord(T, ((double)7))) + ((((double)-6588288) - ((double)293088) * N - ((double)2064) * N*N) + (((double)3294144) + ((double)146544) * N + ((double)1032) * N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70)) + ((((double)7699104) + ((double)29232) * N - ((double)1020) * N*N - ((double)6) * N*N*N) + (((double)-3849552) - ((double)14616) * N + ((double)510) * N*N + ((double)3) * N*N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)1340640) + ((double)59640) * N + ((double)420) * N*N) + (((double)-670320) - ((double)29820) * N - ((double)210) * N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)-837900) - ((double)7350) * N) + (((double)418950) + ((double)3675) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))) * floord(((double)69) + N, ((double)70)) + (((((double)23740524) + ((double)235296) * N + ((double)1032) * N*N) + (((double)-11870262) - ((double)117648) * N - ((double)516) * N*N) * floord(T, ((double)7))) + ((((double)4206048) + ((double)188520) * N + ((double)1536) * N*N + ((double)6) * N*N*N) + (((double)-2103024) - ((double)94260) * N - ((double)768) * N*N - ((double)3) * N*N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70)) + ((((double)-5092920) - ((double)36120) * N) + (((double)2546460) + ((double)18060) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + ((((double)-411600) - ((double)14700) * N) + (((double)205800) + ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70)) + (((double)257250) - ((double)128625) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))) * floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70)) + (((((double)-11884450) - ((double)150216) * N - ((double)684) * N*N - ((double)2) * N*N*N) + (((double)5942225) + ((double)75108) * N + ((double)342) * N*N + N*N*N) * floord(T, ((double)7))) + ((((double)-1340640) - ((double)59640) * N - ((double)420) * N*N) + (((double)670320) + ((double)29820) * N + ((double)210) * N*N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70)) + ((((double)1675800) + ((double)14700) * N) + (((double)-837900) - ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))) * floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70)) + (((((double)3993360) + ((double)47880) * N + ((double)210) * N*N) + (((double)-1996680) - ((double)23940) * N - ((double)105) * N*N) * floord(T, ((double)7))) + ((((double)205800) + ((double)7350) * N) + (((double)-102900) - ((double)3675) * N) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70)) + (((double)-257250) + ((double)128625) * floord(T, ((double)7))) * floord(((double)62) + N, ((double)70))*floord(((double)62) + N, ((double)70))) * floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70)) + ((((double)-837900) - ((double)7350) * N) + (((double)418950) + ((double)3675) * N) * floord(T, ((double)7))) * floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70)) + (((double)85750) - ((double)42875) * floord(T, ((double)7))) * floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70))*floord(((double)69) + N, ((double)70)))) : (((double)-21) + T >= ((double)0) && ((double)-141) + N >= ((double)0) && ((double)147) - N >= ((double)0)) ? ((((((double)94150060) + T) + (((double)-22323) + ((double)3) * T) * N + (((double)369) + ((double)3) * T) * N*N + (((double)-1) + T) * N*N*N) + (((double)116020) + ((double)11163) * N - ((double)183) * N*N + N*N*N) * floord(T, ((double)7)))) : ((((double)-21) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)140) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)20) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)94382100) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
	tk_INJ = getenv("tk_INJ") != NULL ? atoi(getenv("tk_INJ")) : -1;
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float**** patch = (float****)(calloc((8),sizeof(float***)));
	for (int w=0; w<(8); w++) {
		patch[w] = (float***)(calloc((86),sizeof(float**)));
		for (int i=0; i<(86); i++) {
			patch[w][i] = (float**)(calloc((86),sizeof(float*)));
			for (int j=0; j<(86); j++) {
				patch[w][i][j] = (float*)(calloc((86),sizeof(float)));
			}
		}
	}
	
	float*** W = (float***)(calloc((3),sizeof(float**)));
	for (int i=0; i<(3); i++) {
		W[i] = (float**)(calloc((3),sizeof(float*)));
		for (int j=0; j<(3); j++) {
			W[i][j] = (float*)(calloc((3),sizeof(float)));
		}
	}
	
	float**** I = (float****)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((7),sizeof(float***)));
	for (int w=0; w<(7); w++) {
		patch_NR[w] = (float***)(calloc((86),sizeof(float**)));
		for (int i=0; i<(86); i++) {
			patch_NR[w][i] = (float**)(calloc((86),sizeof(float*)));
			for (int j=0; j<(86); j++) {
				patch_NR[w][i][j] = (float*)(calloc((86),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((7*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((7),((p)),((q)),((r)))) * (Y((-7 + 7*(tt)),(70*(ti) + (p)),(70*(tj) + (q)),(70*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==7*(tt_INJ-1)+1 && i==70*ti_INJ+35 && j==70*tj_INJ+35 && k==70*tk_INJ+35) inject_star3d1r_abft_v1_7_70_70_70(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((69 - i) >= (0))) && ((j) >= (0))) && ((69 - j) >= (0))) && ((k) >= (0))) && ((69 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 7 and p >= -1 and -69 - w + i <= p <= 1 and p <= w + i and q >= -1 and -69 - w + j <= q <= 1 and q <= w + j and r >= -1 and -69 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 7 and -1 - w <= i <= 70 + w and -1 - w <= j <= 70 + w and -1 - w <= k <= 70 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N and -8 <= p <= 77 and p <= N - 70ti and -8 <= q <= 77 and q <= N - 70tj and -8 <= r <= 77 and r <= N - 70tk; SI[tt, ti, tj, tk] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N; SC1[tt, ti, tj, tk, i, j, k] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 70ti <= -71 + N and tj > 0 and 70tj <= -71 + N and tk > 0 and 70tk <= -71 + N and 70ti <= i <= 69 + 70ti and 70tj <= j <= 69 + 70tj and 70tk <= k <= 69 + 70tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ Spatch_NR[w, i, j, k, p, q, r]; Spatch[w, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, j, k, p, q, r] -> [(w)]; Spatch[w, i, j, k] -> [(w)] }]"
	 *   - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SI[tt, ti, tj, tk]; SC2[tt, ti, tj, tk, p, q, r]; SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb1[t, i, j, k] -> [(floor((t)/7))]; SC2[tt, ti, tj, tk, p, q, r] -> [(-1 + tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(tt)]; SI[tt, ti, tj, tk] -> [(tt)]; SY_cb0[t, i, j, k] -> [(floor((t)/7))]; SY_cb2[t, i, j, k] -> [(floor((t)/7))] }, { SY_cb1[t, i, j, k] -> [(t)]; SC2[tt, ti, tj, tk, p, q, r] -> [(-7 + 7tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(7tt)]; SI[tt, ti, tj, tk] -> [(7tt)]; SY_cb0[t, i, j, k] -> [(t)]; SY_cb2[t, i, j, k] -> [(t)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *         - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SC2[tt, ti, tj, tk, p, q, r] }"
	 *         - filter: "{ SI[tt, ti, tj, tk] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  for (int c1 = -1; c1 <= 1; c1 += 1) {
	    for (int c2 = -1; c2 <= 1; c2 += 1) {
	      SW(c0, c1, c2);
	    }
	  }
	}
	for (int c0 = 0; c0 <= 7; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 70; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 70; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 70; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 69); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 69); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 69); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 70; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 70; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 70; c4 += 1) {
	        Spatch(c0, c2, c3, c4);
	      }
	    }
	  }
	}
	for (int c1 = 0; c1 <= 1; c1 += 1) {
	  for (int c3 = 0; c3 <= N; c3 += 1) {
	    for (int c4 = 0; c4 <= N; c4 += 1) {
	      for (int c5 = 0; c5 <= N; c5 += 1) {
	        SY_cb0(c1, c3, c4, c5);
	      }
	    }
	  }
	}
	for (int c0 = 0; c0 <= T / 7; c0 += 1) {
	  for (int c1 = max(2, 7 * c0); c1 <= min(T, 7 * c0 + 6); c1 += 1) {
	    for (int c3 = 1; c3 < N; c3 += 1) {
	      for (int c4 = 1; c4 < N; c4 += 1) {
	        for (int c5 = 1; c5 < N; c5 += 1) {
	          SY_cb2(c1, c3, c4, c5);
	        }
	      }
	    }
	    for (int c3 = 0; c3 <= N; c3 += 1) {
	      for (int c4 = 0; c4 <= N; c4 += 1) {
	        if (c3 >= 1 && N >= c3 + 1 && c4 >= 1 && N >= c4 + 1) {
	          SY_cb1(c1, c3, c4, 0);
	        } else {
	          if (c3 >= 1 && N >= c3 + 1 && c4 == 0) {
	            for (int c5 = 0; c5 < N; c5 += 1) {
	              SY_cb1(c1, c3, 0, c5);
	            }
	          } else {
	            if (c3 == 0 && N >= c4 + 1) {
	              for (int c5 = 0; c5 < N; c5 += 1) {
	                SY_cb1(c1, 0, c4, c5);
	              }
	            } else {
	              if (c3 == N && N >= c4 + 1) {
	                for (int c5 = 0; c5 < N; c5 += 1) {
	                  SY_cb1(c1, N, c4, c5);
	                }
	              } else {
	                for (int c5 = 0; c5 < N; c5 += 1) {
	                  SY_cb1(c1, c3, N, c5);
	                }
	              }
	            }
	          }
	        }
	        SY_cb1(c1, c3, c4, N);
	      }
	    }
	    if (T >= 7 * c0 + 14 && c1 == 7 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 70; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 70; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 70; c5 += 1) {
	            for (int c6 = -8; c6 <= min(77, N - 70 * c3); c6 += 1) {
	              for (int c7 = -8; c7 <= min(77, N - 70 * c4); c7 += 1) {
	                for (int c8 = -8; c8 <= min(77, N - 70 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 7 * c0 + 7 && c1 == 7 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 70; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 70; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 70; c5 += 1) {
	            for (int c6 = 70 * c3; c6 <= 70 * c3 + 69; c6 += 1) {
	              for (int c7 = 70 * c4; c7 <= 70 * c4 + 69; c7 += 1) {
	                for (int c8 = 70 * c5; c8 <= 70 * c5 + 69; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 70; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 70; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 70; c5 += 1) {
	            SI(c0, c3, c4, c5);
	          }
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
	struct INJ inj = { tt_INJ, ti_INJ, tj_INJ, tk_INJ };
	struct Result result = new_result();
	result.bit = BIT;
	result.inj = inj;
	result.noise = -1;
	
	const char* verbose = getenv("VERBOSE");
	
	#define print_SI(tt,ti,tj,tk) printf("v1_I(%d,%d,%d,%d) = %E\n",tt,ti,tj,tk, fabs(I(tt,ti,tj,tk)))
	#define acc_noise(tt,ti,tj,tk) result.noise = max(result.noise, fabs(I(tt,ti,tj,tk)))
	#define SI(tt,ti,tj,tk) do { if (verbose != NULL && fabs(I(tt,ti,tj,tk))>=threshold) print_SI(tt,ti,tj,tk); acc_noise(tt,ti,tj,tk); if (tt==tt_INJ && ti==ti_INJ && tj==tj_INJ && tk==tk_INJ) { if (fabs(I(tt,ti,tj,tk))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti,tj,tk))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 7; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 70; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 70; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 70; tk += 1) {
	        SI(tt, ti, tj, tk);
	      }
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
	for (int w=0; w<(8); w++) {
		for (int i=0; i<(86); i++) {
			for (int j=0; j<(86); j++) {
				 free(patch[w][i][j]);
			}
			free(patch[w][i]);
		}
		free(patch[w]);
	}
	free(patch);
	
	for (int i=0; i<(3); i++) {
		for (int j=0; j<(3); j++) {
			 free(W[i][j]);
		}
		free(W[i]);
	}
	free(W);
	
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(7); w++) {
		for (int i=0; i<(86); i++) {
			for (int j=0; j<(86); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -141 + N >= 0) ? ((-2 + floord(69 + N, 70))) : 0); tj++) {
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
