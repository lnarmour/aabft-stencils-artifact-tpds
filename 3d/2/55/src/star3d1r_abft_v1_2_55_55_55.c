/* star3d1r_abft_v1_2_55_55_55.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_2_55_55_55 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 2 and -1 - w <= i <= 55 + w and -1 - w <= j <= 55 + w and -1 - w <= k <= 55 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 2 and -1 - w <= i <= 55 + w and -1 - w <= j <= 55 + w and -1 - w <= k <= 55 + w }
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
 *	 			{: w = 0 and 0 <= i <= 54 and 0 <= j <= 54 and 0 <= k <= 54 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 55ti <= i <= 54 + 55ti and 55tj <= j <= 54 + 55tj and 55tk <= k <= 54 + 55tk } : Y[2tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[2,p,q,r] * Y[2tt-2,55ti+p,55tj+q,55tk+r]));
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
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[tt]; SC2[tt,ti,tj,tk,p,q,r]->[tt-1]; SI[tt,ti,tj,tk]->[tt]; SY_cb0[t,i,j,k]->[t/2]; SY_cb1[t,i,j,k]->[t/2]; SY_cb2[t,i,j,k]->[t/2] }, \
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[2tt]; SC2[tt,ti,tj,tk,p,q,r]->[2tt-2]; SI[tt,ti,tj,tk]->[2tt]; SY_cb0[t,i,j,k]->[t]; SY_cb1[t,i,j,k]->[t]; SY_cb2[t,i,j,k]->[t] } \
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
#define mem_patch(w,i,j,k) patch[(w)-(0)][(i)-(-3)][(j)-(-3)][(k)-(-3)]
#define mem_patch_NR(w,i,j,k) patch_NR[(w)-(1)][(i)-(-3)][(j)-(-3)][(k)-(-3)]

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

void inject_star3d1r_abft_v1_2_55_55_55(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_2_55_55_55(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_2_55_55_55(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-10) + T >= ((double)0) && ((double)-112) + N >= ((double)0)) ? (((((((((double)139653896) + ((double)8) * T) + (((double)24) + ((double)24) * T) * N + (((double)24) + ((double)24) * T) * N*N + (((double)8) + ((double)8) * T) * N*N*N) - ((double)25174848) * floord(T, ((double)2))) + ((((double)18218016) + ((double)714432) * N) + (((double)-9109008) - ((double)357216) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55)) + ((((double)-15839016) + ((double)298656) * N + ((double)5856) * N*N) + (((double)7919508) - ((double)149328) * N - ((double)2928) * N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)-7947738) - ((double)290868) * N + ((double)1224) * N*N + ((double)16) * N*N*N) + (((double)3973869) + ((double)145434) * N - ((double)612) * N*N - ((double)8) * N*N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)3570270) - ((double)67320) * N - ((double)1320) * N*N) + (((double)-1785135) + ((double)33660) * N + ((double)660) * N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)925650) + ((double)36300) * N) + (((double)-462825) - ((double)18150) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + (((double)-332750) + ((double)166375) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))) + (((((double)-93742560) - ((double)714432) * N) + (((double)46871280) + ((double)357216) * N) * floord(T, ((double)2))) + ((((double)-25833744) - ((double)1311744) * N - ((double)11712) * N*N) + (((double)12916872) + ((double)655872) * N + ((double)5856) * N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55)) + ((((double)25160082) + ((double)79116) * N - ((double)6600) * N*N - ((double)48) * N*N*N) + (((double)-12580041) - ((double)39558) * N + ((double)3300) * N*N + ((double)24) * N*N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)5823180) + ((double)295680) * N + ((double)2640) * N*N) + (((double)-2911590) - ((double)147840) * N - ((double)1320) * N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)-3139950) - ((double)36300) * N) + (((double)1569975) + ((double)18150) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))) * floord(((double)54) + N, ((double)55)) + (((((double)79435032) + ((double)1013088) * N + ((double)5856) * N*N) + (((double)-39717516) - ((double)506544) * N - ((double)2928) * N*N) * floord(T, ((double)2))) + ((((double)17371314) + ((double)892980) * N + ((double)9528) * N*N + ((double)48) * N*N*N) + (((double)-8685657) - ((double)446490) * N - ((double)4764) * N*N - ((double)24) * N*N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55)) + ((((double)-17875440) - ((double)161040) * N) + (((double)8937720) + ((double)80520) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + ((((double)-1851300) - ((double)72600) * N) + (((double)925650) + ((double)36300) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55)) + (((double)998250) - ((double)499125) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))) * floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55)) + (((((double)-40877370) - ((double)681228) * N - ((double)4152) * N*N - ((double)16) * N*N*N) + (((double)20438685) + ((double)340614) * N + ((double)2076) * N*N + ((double)8) * N*N*N) * floord(T, ((double)2))) + ((((double)-5823180) - ((double)295680) * N - ((double)2640) * N*N) + (((double)2911590) + ((double)147840) * N + ((double)1320) * N*N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55)) + ((((double)6279900) + ((double)72600) * N) + (((double)-3139950) - ((double)36300) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))) * floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55)) + (((((double)14305170) + ((double)228360) * N + ((double)1320) * N*N) + (((double)-7152585) - ((double)114180) * N - ((double)660) * N*N) * floord(T, ((double)2))) + ((((double)925650) + ((double)36300) * N) + (((double)-462825) - ((double)18150) * N) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55)) + (((double)-998250) + ((double)499125) * floord(T, ((double)2))) * floord(((double)52) + N, ((double)55))*floord(((double)52) + N, ((double)55))) * floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55)) + ((((double)-3139950) - ((double)36300) * N) + (((double)1569975) + ((double)18150) * N) * floord(T, ((double)2))) * floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55)) + (((double)332750) - ((double)166375) * floord(T, ((double)2))) * floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))*floord(((double)54) + N, ((double)55))))/((double)8)) : (((double)-111) + N == ((double)0) && ((double)-10) + T >= ((double)0)) ? (((((double)11803200) + ((double)1404928) * T) + ((double)382376) * floord(T, ((double)2)))) : (((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)110) - N >= ((double)0)) ? (((((double)11163025) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
	float**** patch = (float****)(calloc((3),sizeof(float***)));
	for (int w=0; w<(3); w++) {
		patch[w] = (float***)(calloc((61),sizeof(float**)));
		for (int i=0; i<(61); i++) {
			patch[w][i] = (float**)(calloc((61),sizeof(float*)));
			for (int j=0; j<(61); j++) {
				patch[w][i][j] = (float*)(calloc((61),sizeof(float)));
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
	
	float**** I = (float****)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((2),sizeof(float***)));
	for (int w=0; w<(2); w++) {
		patch_NR[w] = (float***)(calloc((61),sizeof(float**)));
		for (int i=0; i<(61); i++) {
			patch_NR[w][i] = (float**)(calloc((61),sizeof(float*)));
			for (int j=0; j<(61); j++) {
				patch_NR[w][i][j] = (float*)(calloc((61),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((2*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((2),((p)),((q)),((r)))) * (Y((-2 + 2*(tt)),(55*(ti) + (p)),(55*(tj) + (q)),(55*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==2*(tt_INJ-1)+1 && i==55*ti_INJ+27 && j==55*tj_INJ+27 && k==55*tk_INJ+27) inject_star3d1r_abft_v1_2_55_55_55(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((54 - i) >= (0))) && ((j) >= (0))) && ((54 - j) >= (0))) && ((k) >= (0))) && ((54 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 2 and p >= -1 and -54 - w + i <= p <= 1 and p <= w + i and q >= -1 and -54 - w + j <= q <= 1 and q <= w + j and r >= -1 and -54 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 2 and -1 - w <= i <= 55 + w and -1 - w <= j <= 55 + w and -1 - w <= k <= 55 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : T >= 10 and tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N and -3 <= p <= 57 and p <= N - 55ti and -3 <= q <= 57 and q <= N - 55tj and -3 <= r <= 57 and r <= N - 55tk; SI[tt, ti, tj, tk] : T >= 10 and tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N; SC1[tt, ti, tj, tk, i, j, k] : T >= 10 and tt >= 2 and 2tt <= -2 + T and ti > 0 and 55ti <= -56 + N and tj > 0 and 55tj <= -56 + N and tk > 0 and 55tk <= -56 + N and 55ti <= i <= 54 + 55ti and 55tj <= j <= 54 + 55tj and 55tk <= k <= 54 + 55tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ Spatch_NR[w, i, j, k, p, q, r]; Spatch[w, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, j, k, p, q, r] -> [(w)]; Spatch[w, i, j, k] -> [(w)] }]"
	 *   - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SI[tt, ti, tj, tk]; SC2[tt, ti, tj, tk, p, q, r]; SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb1[t, i, j, k] -> [(floor((t)/2))]; SC2[tt, ti, tj, tk, p, q, r] -> [(-1 + tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(tt)]; SI[tt, ti, tj, tk] -> [(tt)]; SY_cb0[t, i, j, k] -> [(floor((t)/2))]; SY_cb2[t, i, j, k] -> [(floor((t)/2))] }, { SY_cb1[t, i, j, k] -> [(t)]; SC2[tt, ti, tj, tk, p, q, r] -> [(-2 + 2tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(2tt)]; SI[tt, ti, tj, tk] -> [(2tt)]; SY_cb0[t, i, j, k] -> [(t)]; SY_cb2[t, i, j, k] -> [(t)] }]"
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
	for (int c0 = 0; c0 <= 2; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 55; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 55; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 55; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 54); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 54); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 54); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 55; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 55; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 55; c4 += 1) {
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
	for (int c0 = 1; c0 <= T / 2; c0 += 1) {
	  for (int c1 = 2 * c0; c1 <= min(T, 2 * c0 + 1); c1 += 1) {
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
	    if (T >= 2 * c0 + 4 && c1 == 2 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 55; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 55; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 55; c5 += 1) {
	            for (int c6 = -3; c6 <= min(57, N - 55 * c3); c6 += 1) {
	              for (int c7 = -3; c7 <= min(57, N - 55 * c4); c7 += 1) {
	                for (int c8 = -3; c8 <= min(57, N - 55 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 2 * c0 + 2 && c1 == 2 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 55; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 55; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 55; c5 += 1) {
	            for (int c6 = 55 * c3; c6 <= 55 * c3 + 54; c6 += 1) {
	              for (int c7 = 55 * c4; c7 <= 55 * c4 + 54; c7 += 1) {
	                for (int c8 = 55 * c5; c8 <= 55 * c5 + 54; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 55; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 55; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 55; c5 += 1) {
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
	
	for (int tt = 2; tt < T / 2; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 55; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 55; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 55; tk += 1) {
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
	for (int w=0; w<(3); w++) {
		for (int i=0; i<(61); i++) {
			for (int j=0; j<(61); j++) {
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
	
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(2); w++) {
		for (int i=0; i<(61); i++) {
			for (int j=0; j<(61); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(T, 2))) : 0); tt++) {
		for (int ti=0; ti<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); ti++) {
			for (int tj=0; tj<((-6 + T >= 0 && -111 + N >= 0) ? ((-2 + floord(54 + N, 55))) : 0); tj++) {
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
