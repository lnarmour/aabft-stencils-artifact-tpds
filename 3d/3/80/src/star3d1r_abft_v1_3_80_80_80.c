/* star3d1r_abft_v1_3_80_80_80.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_3_80_80_80 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 3 and -1 - w <= i <= 80 + w and -1 - w <= j <= 80 + w and -1 - w <= k <= 80 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 3 and -1 - w <= i <= 80 + w and -1 - w <= j <= 80 + w and -1 - w <= k <= 80 + w }
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
 *	 			{: w = 0 and 0 <= i <= 79 and 0 <= j <= 79 and 0 <= k <= 79 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 80ti <= i <= 79 + 80ti and 80tj <= j <= 79 + 80tj and 80tk <= k <= 79 + 80tk } : Y[3tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[3,p,q,r] * Y[3tt-3,80ti+p,80tj+q,80tk+r]));
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
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[tt]; SC2[tt,ti,tj,tk,p,q,r]->[tt-1]; SI[tt,ti,tj,tk]->[tt]; SY_cb0[t,i,j,k]->[t/3]; SY_cb1[t,i,j,k]->[t/3]; SY_cb2[t,i,j,k]->[t/3] }, \
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[3tt]; SC2[tt,ti,tj,tk,p,q,r]->[3tt-3]; SI[tt,ti,tj,tk]->[3tt]; SY_cb0[t,i,j,k]->[t]; SY_cb1[t,i,j,k]->[t]; SY_cb2[t,i,j,k]->[t] } \
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
#define mem_patch(w,i,j,k) patch[(w)-(0)][(i)-(-4)][(j)-(-4)][(k)-(-4)]
#define mem_patch_NR(w,i,j,k) patch_NR[(w)-(1)][(i)-(-4)][(j)-(-4)][(k)-(-4)]

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

void inject_star3d1r_abft_v1_3_80_80_80(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_3_80_80_80(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_3_80_80_80(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-10) + T >= ((double)0) && ((double)-164) + N >= ((double)0)) ? ((((((((double)69620652) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N) - ((double)9547784) * floord(T, ((double)3))) + ((((double)6876672) + ((double)185856) * N) + (((double)-3438336) - ((double)92928) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80)) + ((((double)-5988576) + ((double)78144) * N + ((double)1056) * N*N) + (((double)2994288) - ((double)39072) * N - ((double)528) * N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)-3024454) - ((double)76266) * N + ((double)222) * N*N + ((double)2) * N*N*N) + (((double)1512227) + ((double)38133) * N - ((double)111) * N*N - N*N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)1361040) - ((double)17760) * N - ((double)240) * N*N) + (((double)-680520) + ((double)8880) * N + ((double)120) * N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)355200) + ((double)9600) * N) + (((double)-177600) - ((double)4800) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + (((double)-128000) + ((double)64000) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))) + (((((double)-35520024) - ((double)185856) * N) + (((double)17760012) + ((double)92928) * N) * floord(T, ((double)3))) + ((((double)-9768000) - ((double)342144) * N - ((double)2112) * N*N) + (((double)4884000) + ((double)171072) * N + ((double)1056) * N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80)) + ((((double)9533250) + ((double)20766) * N - ((double)1194) * N*N - ((double)6) * N*N*N) + (((double)-4766625) - ((double)10383) * N + ((double)597) * N*N + ((double)3) * N*N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)2220000) + ((double)77760) * N + ((double)480) * N*N) + (((double)-1110000) - ((double)38880) * N - ((double)240) * N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)-1200000) - ((double)9600) * N) + (((double)600000) + ((double)4800) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))) * floord(((double)79) + N, ((double)80)) + (((((double)30078252) + ((double)264000) * N + ((double)1056) * N*N) + (((double)-15039126) - ((double)132000) * N - ((double)528) * N*N) * floord(T, ((double)3))) + ((((double)6594510) + ((double)233730) * N + ((double)1722) * N*N + ((double)6) * N*N*N) + (((double)-3297255) - ((double)116865) * N - ((double)861) * N*N - ((double)3) * N*N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80)) + ((((double)-6800640) - ((double)42240) * N) + (((double)3400320) + ((double)21120) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + ((((double)-710400) - ((double)19200) * N) + (((double)355200) + ((double)9600) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80)) + (((double)384000) - ((double)192000) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))) * floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80)) + (((((double)-15490252) - ((double)178230) * N - ((double)750) * N*N - ((double)2) * N*N*N) + (((double)7745126) + ((double)89115) * N + ((double)375) * N*N + N*N*N) * floord(T, ((double)3))) + ((((double)-2220000) - ((double)77760) * N - ((double)480) * N*N) + (((double)1110000) + ((double)38880) * N + ((double)240) * N*N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80)) + ((((double)2400000) + ((double)19200) * N) + (((double)-1200000) - ((double)9600) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))) * floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80)) + (((((double)5439600) + ((double)60000) * N + ((double)240) * N*N) + (((double)-2719800) - ((double)30000) * N - ((double)120) * N*N) * floord(T, ((double)3))) + ((((double)355200) + ((double)9600) * N) + (((double)-177600) - ((double)4800) * N) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80)) + (((double)-384000) + ((double)192000) * floord(T, ((double)3))) * floord(((double)76) + N, ((double)80))*floord(((double)76) + N, ((double)80))) * floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80)) + ((((double)-1200000) - ((double)9600) * N) + (((double)600000) + ((double)4800) * N) * floord(T, ((double)3))) * floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80)) + (((double)128000) - ((double)64000) * floord(T, ((double)3))) * floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80))*floord(((double)79) + N, ((double)80)))) : (((double)-10) + T >= ((double)0) && ((double)-161) + N >= ((double)0) && ((double)163) - N >= ((double)0)) ? ((((((double)50344832) + T) + (((double)-33747) + ((double)3) * T) * N + (((double)453) + ((double)3) * T) * N*N + (((double)-1) + T) * N*N*N) + (((double)90126) + ((double)16875) * N - ((double)225) * N*N + N*N*N) * floord(T, ((double)3)))) : (((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)160) - N >= ((double)0)) ? (((((double)50525084) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
	float**** patch = (float****)(calloc((4),sizeof(float***)));
	for (int w=0; w<(4); w++) {
		patch[w] = (float***)(calloc((88),sizeof(float**)));
		for (int i=0; i<(88); i++) {
			patch[w][i] = (float**)(calloc((88),sizeof(float*)));
			for (int j=0; j<(88); j++) {
				patch[w][i][j] = (float*)(calloc((88),sizeof(float)));
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
	
	float**** I = (float****)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((3),sizeof(float***)));
	for (int w=0; w<(3); w++) {
		patch_NR[w] = (float***)(calloc((88),sizeof(float**)));
		for (int i=0; i<(88); i++) {
			patch_NR[w][i] = (float**)(calloc((88),sizeof(float*)));
			for (int j=0; j<(88); j++) {
				patch_NR[w][i][j] = (float*)(calloc((88),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((3*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((3),((p)),((q)),((r)))) * (Y((-3 + 3*(tt)),(80*(ti) + (p)),(80*(tj) + (q)),(80*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==3*(tt_INJ-1)+1 && i==80*ti_INJ+40 && j==80*tj_INJ+40 && k==80*tk_INJ+40) inject_star3d1r_abft_v1_3_80_80_80(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((79 - i) >= (0))) && ((j) >= (0))) && ((79 - j) >= (0))) && ((k) >= (0))) && ((79 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 3 and p >= -1 and -79 - w + i <= p <= 1 and p <= w + i and q >= -1 and -79 - w + j <= q <= 1 and q <= w + j and r >= -1 and -79 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 3 and -1 - w <= i <= 80 + w and -1 - w <= j <= 80 + w and -1 - w <= k <= 80 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : T >= 10 and tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N and -4 <= p <= 83 and p <= N - 80ti and -4 <= q <= 83 and q <= N - 80tj and -4 <= r <= 83 and r <= N - 80tk; SI[tt, ti, tj, tk] : T >= 10 and tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N; SC1[tt, ti, tj, tk, i, j, k] : T >= 10 and tt >= 2 and 3tt <= -3 + T and ti > 0 and 80ti <= -81 + N and tj > 0 and 80tj <= -81 + N and tk > 0 and 80tk <= -81 + N and 80ti <= i <= 79 + 80ti and 80tj <= j <= 79 + 80tj and 80tk <= k <= 79 + 80tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ Spatch_NR[w, i, j, k, p, q, r]; Spatch[w, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, j, k, p, q, r] -> [(w)]; Spatch[w, i, j, k] -> [(w)] }]"
	 *   - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SI[tt, ti, tj, tk]; SC2[tt, ti, tj, tk, p, q, r]; SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb1[t, i, j, k] -> [(floor((t)/3))]; SC2[tt, ti, tj, tk, p, q, r] -> [(-1 + tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(tt)]; SI[tt, ti, tj, tk] -> [(tt)]; SY_cb0[t, i, j, k] -> [(floor((t)/3))]; SY_cb2[t, i, j, k] -> [(floor((t)/3))] }, { SY_cb1[t, i, j, k] -> [(t)]; SC2[tt, ti, tj, tk, p, q, r] -> [(-3 + 3tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(3tt)]; SI[tt, ti, tj, tk] -> [(3tt)]; SY_cb0[t, i, j, k] -> [(t)]; SY_cb2[t, i, j, k] -> [(t)] }]"
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
	for (int c0 = 0; c0 <= 3; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 80; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 80; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 80; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 79); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 79); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 79); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 80; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 80; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 80; c4 += 1) {
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
	for (int c0 = 0; c0 <= T / 3; c0 += 1) {
	  for (int c1 = max(2, 3 * c0); c1 <= min(T, 3 * c0 + 2); c1 += 1) {
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
	    if (T >= 3 * c0 + 6 && c1 == 3 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 80; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 80; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 80; c5 += 1) {
	            for (int c6 = -4; c6 <= min(83, N - 80 * c3); c6 += 1) {
	              for (int c7 = -4; c7 <= min(83, N - 80 * c4); c7 += 1) {
	                for (int c8 = -4; c8 <= min(83, N - 80 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 3 * c0 + 3 && c1 == 3 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 80; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 80; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 80; c5 += 1) {
	            for (int c6 = 80 * c3; c6 <= 80 * c3 + 79; c6 += 1) {
	              for (int c7 = 80 * c4; c7 <= 80 * c4 + 79; c7 += 1) {
	                for (int c8 = 80 * c5; c8 <= 80 * c5 + 79; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 80; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 80; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 80; c5 += 1) {
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
	
	for (int tt = 2; tt < T / 3; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 80; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 80; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 80; tk += 1) {
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
	for (int w=0; w<(4); w++) {
		for (int i=0; i<(88); i++) {
			for (int j=0; j<(88); j++) {
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
	
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(3); w++) {
		for (int i=0; i<(88); i++) {
			for (int j=0; j<(88); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(T, 3))) : 0); tt++) {
		for (int ti=0; ti<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); ti++) {
			for (int tj=0; tj<((-9 + T >= 0 && -161 + N >= 0) ? ((-2 + floord(79 + N, 80))) : 0); tj++) {
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
