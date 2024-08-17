/* star3d1r_abft_v1_4_75_75_75.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_4_75_75_75 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 4 and -1 - w <= i <= 75 + w and -1 - w <= j <= 75 + w and -1 - w <= k <= 75 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 4 and -1 - w <= i <= 75 + w and -1 - w <= j <= 75 + w and -1 - w <= k <= 75 + w }
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
 *	 			{: w = 0 and 0 <= i <= 74 and 0 <= j <= 74 and 0 <= k <= 74 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 75ti <= i <= 74 + 75ti and 75tj <= j <= 74 + 75tj and 75tk <= k <= 74 + 75tk } : Y[4tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[4,p,q,r] * Y[4tt-4,75ti+p,75tj+q,75tk+r]));
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
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[tt]; SC2[tt,ti,tj,tk,p,q,r]->[tt-1]; SI[tt,ti,tj,tk]->[tt]; SY_cb0[t,i,j,k]->[t/4]; SY_cb1[t,i,j,k]->[t/4]; SY_cb2[t,i,j,k]->[t/4] }, \
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[4tt]; SC2[tt,ti,tj,tk,p,q,r]->[4tt-4]; SI[tt,ti,tj,tk]->[4tt]; SY_cb0[t,i,j,k]->[t]; SY_cb1[t,i,j,k]->[t]; SY_cb2[t,i,j,k]->[t] } \
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
#define mem_patch(w,i,j,k) patch[(w)-(0)][(i)-(-5)][(j)-(-5)][(k)-(-5)]
#define mem_patch_NR(w,i,j,k) patch_NR[(w)-(1)][(i)-(-5)][(j)-(-5)][(k)-(-5)]

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

void inject_star3d1r_abft_v1_4_75_75_75(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_4_75_75_75(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_4_75_75_75(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-12) + T >= ((double)0) && ((double)-155) + N >= ((double)0)) ? (((((((((double)597348552) + ((double)8) * T) + (((double)24) + ((double)24) * T) * N + (((double)24) + ((double)24) * T) * N*N + (((double)8) + ((double)8) * T) * N*N*N) - ((double)66304064) * floord(T, ((double)4))) + ((((double)46471200) + ((double)1387200) * N) + (((double)-23235600) - ((double)693600) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75)) + ((((double)-42862440) + ((double)546720) * N + ((double)8160) * N*N) + (((double)21431220) - ((double)273360) * N - ((double)4080) * N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)-19900474) - ((double)558132) * N + ((double)1608) * N*N + ((double)16) * N*N*N) + (((double)9950237) + ((double)279066) * N - ((double)804) * N*N - ((double)8) * N*N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)9454950) - ((double)120600) * N - ((double)1800) * N*N) + (((double)-4727475) + ((double)60300) * N + ((double)900) * N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)2261250) + ((double)67500) * N) + (((double)-1130625) - ((double)33750) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + (((double)-843750) + ((double)421875) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))) + (((((double)-245383392) - ((double)1387200) * N) + (((double)122691696) + ((double)693600) * N) * floord(T, ((double)4))) + ((((double)-64786320) - ((double)2480640) * N - ((double)16320) * N*N) + (((double)32393160) + ((double)1240320) * N + ((double)8160) * N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75)) + ((((double)66138642) + ((double)177036) * N - ((double)8904) * N*N - ((double)48) * N*N*N) + (((double)-33069321) - ((double)88518) * N + ((double)4452) * N*N + ((double)24) * N*N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)14291100) + ((double)547200) * N + ((double)3600) * N*N) + (((double)-7145550) - ((double)273600) * N - ((double)1800) * N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)-7998750) - ((double)67500) * N) + (((double)3999375) + ((double)33750) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))) * floord(((double)74) + N, ((double)75)) + (((((double)207104856) + ((double)1933920) * N + ((double)8160) * N*N) + (((double)-103552428) - ((double)966960) * N - ((double)4080) * N*N) * floord(T, ((double)4))) + ((((double)43081938) + ((double)1667124) * N + ((double)12984) * N*N + ((double)48) * N*N*N) + (((double)-21540969) - ((double)833562) * N - ((double)6492) * N*N - ((double)24) * N*N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75)) + ((((double)-46206000) - ((double)306000) * N) + (((double)23103000) + ((double)153000) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + ((((double)-4522500) - ((double)135000) * N) + (((double)2261250) + ((double)67500) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75)) + (((double)2531250) - ((double)1265625) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))) * floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75)) + (((((double)-105896122) - ((double)1286028) * N - ((double)5688) * N*N - ((double)16) * N*N*N) + (((double)52948061) + ((double)643014) * N + ((double)2844) * N*N + ((double)8) * N*N*N) * floord(T, ((double)4))) + ((((double)-14291100) - ((double)547200) * N - ((double)3600) * N*N) + (((double)7145550) + ((double)273600) * N + ((double)1800) * N*N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75)) + ((((double)15997500) + ((double)135000) * N) + (((double)-7998750) - ((double)67500) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))) * floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75)) + (((((double)36751050) + ((double)426600) * N + ((double)1800) * N*N) + (((double)-18375525) - ((double)213300) * N - ((double)900) * N*N) * floord(T, ((double)4))) + ((((double)2261250) + ((double)67500) * N) + (((double)-1130625) - ((double)33750) * N) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75)) + (((double)-2531250) + ((double)1265625) * floord(T, ((double)4))) * floord(((double)70) + N, ((double)75))*floord(((double)70) + N, ((double)75))) * floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75)) + ((((double)-7998750) - ((double)67500) * N) + (((double)3999375) + ((double)33750) * N) * floord(T, ((double)4))) * floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75)) + (((double)843750) - ((double)421875) * floord(T, ((double)4))) * floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))*floord(((double)74) + N, ((double)75))))/((double)8)) : (((double)-12) + T >= ((double)0) && ((double)-151) + N >= ((double)0) && ((double)154) - N >= ((double)0)) ? ((((((double)57905819) + T) + (((double)-28563) + ((double)3) * T) * N + (((double)417) + ((double)3) * T) * N*N + (((double)-1) + T) * N*N*N) + (((double)93367) + ((double)14283) * N - ((double)207) * N*N + N*N*N) * floord(T, ((double)4)))) : ((((double)-12) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)150) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)11) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)58092553) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
	float**** patch = (float****)(calloc((5),sizeof(float***)));
	for (int w=0; w<(5); w++) {
		patch[w] = (float***)(calloc((85),sizeof(float**)));
		for (int i=0; i<(85); i++) {
			patch[w][i] = (float**)(calloc((85),sizeof(float*)));
			for (int j=0; j<(85); j++) {
				patch[w][i][j] = (float*)(calloc((85),sizeof(float)));
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
	
	float**** I = (float****)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((4),sizeof(float***)));
	for (int w=0; w<(4); w++) {
		patch_NR[w] = (float***)(calloc((85),sizeof(float**)));
		for (int i=0; i<(85); i++) {
			patch_NR[w][i] = (float**)(calloc((85),sizeof(float*)));
			for (int j=0; j<(85); j++) {
				patch_NR[w][i][j] = (float*)(calloc((85),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((4*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((4),((p)),((q)),((r)))) * (Y((-4 + 4*(tt)),(75*(ti) + (p)),(75*(tj) + (q)),(75*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==4*(tt_INJ-1)+1 && i==75*ti_INJ+37 && j==75*tj_INJ+37 && k==75*tk_INJ+37) inject_star3d1r_abft_v1_4_75_75_75(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((74 - i) >= (0))) && ((j) >= (0))) && ((74 - j) >= (0))) && ((k) >= (0))) && ((74 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 4 and p >= -1 and -74 - w + i <= p <= 1 and p <= w + i and q >= -1 and -74 - w + j <= q <= 1 and q <= w + j and r >= -1 and -74 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 4 and -1 - w <= i <= 75 + w and -1 - w <= j <= 75 + w and -1 - w <= k <= 75 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N and -5 <= p <= 79 and p <= N - 75ti and -5 <= q <= 79 and q <= N - 75tj and -5 <= r <= 79 and r <= N - 75tk; SI[tt, ti, tj, tk] : tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N; SC1[tt, ti, tj, tk, i, j, k] : tt >= 2 and 4tt <= -4 + T and ti > 0 and 75ti <= -76 + N and tj > 0 and 75tj <= -76 + N and tk > 0 and 75tk <= -76 + N and 75ti <= i <= 74 + 75ti and 75tj <= j <= 74 + 75tj and 75tk <= k <= 74 + 75tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ Spatch_NR[w, i, j, k, p, q, r]; Spatch[w, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, j, k, p, q, r] -> [(w)]; Spatch[w, i, j, k] -> [(w)] }]"
	 *   - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SI[tt, ti, tj, tk]; SC2[tt, ti, tj, tk, p, q, r]; SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb1[t, i, j, k] -> [(floor((t)/4))]; SC2[tt, ti, tj, tk, p, q, r] -> [(-1 + tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(tt)]; SI[tt, ti, tj, tk] -> [(tt)]; SY_cb0[t, i, j, k] -> [(floor((t)/4))]; SY_cb2[t, i, j, k] -> [(floor((t)/4))] }, { SY_cb1[t, i, j, k] -> [(t)]; SC2[tt, ti, tj, tk, p, q, r] -> [(-4 + 4tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(4tt)]; SI[tt, ti, tj, tk] -> [(4tt)]; SY_cb0[t, i, j, k] -> [(t)]; SY_cb2[t, i, j, k] -> [(t)] }]"
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
	for (int c0 = 0; c0 <= 4; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 75; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 75; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 75; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 74); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 74); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 74); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 75; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 75; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 75; c4 += 1) {
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
	for (int c0 = 0; c0 <= T / 4; c0 += 1) {
	  for (int c1 = max(2, 4 * c0); c1 <= min(T, 4 * c0 + 3); c1 += 1) {
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
	    if (T >= 4 * c0 + 8 && c1 == 4 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 75; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 75; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 75; c5 += 1) {
	            for (int c6 = -5; c6 <= min(79, N - 75 * c3); c6 += 1) {
	              for (int c7 = -5; c7 <= min(79, N - 75 * c4); c7 += 1) {
	                for (int c8 = -5; c8 <= min(79, N - 75 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 4 * c0 + 4 && c1 == 4 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 75; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 75; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 75; c5 += 1) {
	            for (int c6 = 75 * c3; c6 <= 75 * c3 + 74; c6 += 1) {
	              for (int c7 = 75 * c4; c7 <= 75 * c4 + 74; c7 += 1) {
	                for (int c8 = 75 * c5; c8 <= 75 * c5 + 74; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 75; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 75; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 75; c5 += 1) {
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
	
	for (int tt = 2; tt < T / 4; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 75; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 75; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 75; tk += 1) {
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
	for (int w=0; w<(5); w++) {
		for (int i=0; i<(85); i++) {
			for (int j=0; j<(85); j++) {
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
	
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(4); w++) {
		for (int i=0; i<(85); i++) {
			for (int j=0; j<(85); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(T, 4))) : 0); tt++) {
		for (int ti=0; ti<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); ti++) {
			for (int tj=0; tj<((-12 + T >= 0 && -151 + N >= 0) ? ((-2 + floord(74 + N, 75))) : 0); tj++) {
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
