/* star3d1r_abft_v1_9_60_60_60.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_9_60_60_60 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 9 and -1 - w <= i <= 60 + w and -1 - w <= j <= 60 + w and -1 - w <= k <= 60 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 9 and -1 - w <= i <= 60 + w and -1 - w <= j <= 60 + w and -1 - w <= k <= 60 + w }
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
 *	 			{: w = 0 and 0 <= i <= 59 and 0 <= j <= 59 and 0 <= k <= 59 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 60ti <= i <= 59 + 60ti and 60tj <= j <= 59 + 60tj and 60tk <= k <= 59 + 60tk } : Y[9tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[9,p,q,r] * Y[9tt-9,60ti+p,60tj+q,60tk+r]));
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
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[tt]; SC2[tt,ti,tj,tk,p,q,r]->[tt-1]; SI[tt,ti,tj,tk]->[tt]; SY_cb0[t,i,j,k]->[t/9]; SY_cb1[t,i,j,k]->[t/9]; SY_cb2[t,i,j,k]->[t/9] }, \
 *         	{ SC1[tt,ti,tj,tk,i,j,k]->[9tt]; SC2[tt,ti,tj,tk,p,q,r]->[9tt-9]; SI[tt,ti,tj,tk]->[9tt]; SY_cb0[t,i,j,k]->[t]; SY_cb1[t,i,j,k]->[t]; SY_cb2[t,i,j,k]->[t] } \
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
#define mem_patch(w,i,j,k) patch[(w)-(0)][(i)-(-10)][(j)-(-10)][(k)-(-10)]
#define mem_patch_NR(w,i,j,k) patch_NR[(w)-(1)][(i)-(-10)][(j)-(-10)][(k)-(-10)]

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

void inject_star3d1r_abft_v1_9_60_60_60(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_9_60_60_60(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_9_60_60_60(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-27) + T >= ((double)0) && ((double)-130) + N >= ((double)0)) ? ((((((((double)100007244) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N) - ((double)5824008) * floord(T, ((double)9))) + ((((double)3225600) + ((double)153600) * N) + (((double)-1612800) - ((double)76800) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60)) + ((((double)-4184640) + ((double)40320) * N + ((double)960) * N*N) + (((double)2092320) - ((double)20160) * N - ((double)480) * N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)-1191078) - ((double)54954) * N + ((double)126) * N*N + ((double)2) * N*N*N) + (((double)595539) + ((double)27477) * N - ((double)63) * N*N - N*N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)784620) - ((double)7560) * N - ((double)180) * N*N) + (((double)-392310) + ((double)3780) * N + ((double)90) * N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)113400) + ((double)5400) * N) + (((double)-56700) - ((double)2700) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + (((double)-54000) + ((double)27000) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))) + (((((double)-20697624) - ((double)153600) * N) + (((double)10348812) + ((double)76800) * N) * floord(T, ((double)9))) + ((((double)-4072320) - ((double)234240) * N - ((double)1920) * N*N) + (((double)2036160) + ((double)117120) * N + ((double)960) * N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60)) + ((((double)5550354) + ((double)29502) * N - ((double)858) * N*N - ((double)6) * N*N*N) + (((double)-2775177) - ((double)14751) * N + ((double)429) * N*N + ((double)3) * N*N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)763560) + ((double)43920) * N + ((double)360) * N*N) + (((double)-381780) - ((double)21960) * N - ((double)180) * N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)-545400) - ((double)5400) * N) + (((double)272700) + ((double)2700) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))) * floord(((double)59) + N, ((double)60)) + (((((double)16992972) + ((double)193920) * N + ((double)960) * N*N) + (((double)-8496486) - ((double)96960) * N - ((double)480) * N*N) * floord(T, ((double)9))) + ((((double)2494926) + ((double)144258) * N + ((double)1338) * N*N + ((double)6) * N*N*N) + (((double)-1247463) - ((double)72129) * N - ((double)669) * N*N - ((double)3) * N*N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60)) + ((((double)-3484800) - ((double)28800) * N) + (((double)1742400) + ((double)14400) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + ((((double)-226800) - ((double)10800) * N) + (((double)113400) + ((double)5400) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60)) + (((double)162000) - ((double)81000) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))) * floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60)) + (((((double)-8310204) - ((double)118806) * N - ((double)606) * N*N - ((double)2) * N*N*N) + (((double)4155102) + ((double)59403) * N + ((double)303) * N*N + N*N*N) * floord(T, ((double)9))) + ((((double)-763560) - ((double)43920) * N - ((double)360) * N*N) + (((double)381780) + ((double)21960) * N + ((double)180) * N*N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60)) + ((((double)1090800) + ((double)10800) * N) + (((double)-545400) - ((double)5400) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))) * floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60)) + (((((double)2700180) + ((double)36360) * N + ((double)180) * N*N) + (((double)-1350090) - ((double)18180) * N - ((double)90) * N*N) * floord(T, ((double)9))) + ((((double)113400) + ((double)5400) * N) + (((double)-56700) - ((double)2700) * N) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60)) + (((double)-162000) + ((double)81000) * floord(T, ((double)9))) * floord(((double)50) + N, ((double)60))*floord(((double)50) + N, ((double)60))) * floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60)) + ((((double)-545400) - ((double)5400) * N) + (((double)272700) + ((double)2700) * N) * floord(T, ((double)9))) * floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60)) + (((double)54000) - ((double)27000) * floord(T, ((double)9))) * floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60))*floord(((double)59) + N, ((double)60)))) : (((double)-27) + T >= ((double)0) && ((double)-121) + N >= ((double)0) && ((double)129) - N >= ((double)0)) ? ((((((double)88162524) + T) + (((double)-14403) + ((double)3) * T) * N + (((double)297) + ((double)3) * T) * N*N + (((double)-1) + T) * N*N*N) + (((double)98352) + ((double)7203) * N - ((double)147) * N*N + N*N*N) * floord(T, ((double)9)))) : ((((double)-27) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)120) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)26) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)88359228) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
	float**** patch = (float****)(calloc((10),sizeof(float***)));
	for (int w=0; w<(10); w++) {
		patch[w] = (float***)(calloc((80),sizeof(float**)));
		for (int i=0; i<(80); i++) {
			patch[w][i] = (float**)(calloc((80),sizeof(float*)));
			for (int j=0; j<(80); j++) {
				patch[w][i][j] = (float*)(calloc((80),sizeof(float)));
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
	
	float**** I = (float****)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((9),sizeof(float***)));
	for (int w=0; w<(9); w++) {
		patch_NR[w] = (float***)(calloc((80),sizeof(float**)));
		for (int i=0; i<(80); i++) {
			patch_NR[w][i] = (float**)(calloc((80),sizeof(float*)));
			for (int j=0; j<(80); j++) {
				patch_NR[w][i][j] = (float*)(calloc((80),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((9*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((9),((p)),((q)),((r)))) * (Y((-9 + 9*(tt)),(60*(ti) + (p)),(60*(tj) + (q)),(60*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==9*(tt_INJ-1)+1 && i==60*ti_INJ+30 && j==60*tj_INJ+30 && k==60*tk_INJ+30) inject_star3d1r_abft_v1_9_60_60_60(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((59 - i) >= (0))) && ((j) >= (0))) && ((59 - j) >= (0))) && ((k) >= (0))) && ((59 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 9 and p >= -1 and -59 - w + i <= p <= 1 and p <= w + i and q >= -1 and -59 - w + j <= q <= 1 and q <= w + j and r >= -1 and -59 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 9 and -1 - w <= i <= 60 + w and -1 - w <= j <= 60 + w and -1 - w <= k <= 60 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N and -10 <= p <= 69 and p <= N - 60ti and -10 <= q <= 69 and q <= N - 60tj and -10 <= r <= 69 and r <= N - 60tk; SI[tt, ti, tj, tk] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N; SC1[tt, ti, tj, tk, i, j, k] : tt >= 2 and 9tt <= -9 + T and ti > 0 and 60ti <= -61 + N and tj > 0 and 60tj <= -61 + N and tk > 0 and 60tk <= -61 + N and 60ti <= i <= 59 + 60ti and 60tj <= j <= 59 + 60tj and 60tk <= k <= 59 + 60tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ Spatch_NR[w, i, j, k, p, q, r]; Spatch[w, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, j, k, p, q, r] -> [(w)]; Spatch[w, i, j, k] -> [(w)] }]"
	 *   - filter: "{ SC1[tt, ti, tj, tk, i, j, k]; SI[tt, ti, tj, tk]; SC2[tt, ti, tj, tk, p, q, r]; SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb1[t, i, j, k] -> [(floor((t)/9))]; SC2[tt, ti, tj, tk, p, q, r] -> [(-1 + tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(tt)]; SI[tt, ti, tj, tk] -> [(tt)]; SY_cb0[t, i, j, k] -> [(floor((t)/9))]; SY_cb2[t, i, j, k] -> [(floor((t)/9))] }, { SY_cb1[t, i, j, k] -> [(t)]; SC2[tt, ti, tj, tk, p, q, r] -> [(-9 + 9tt)]; SC1[tt, ti, tj, tk, i, j, k] -> [(9tt)]; SI[tt, ti, tj, tk] -> [(9tt)]; SY_cb0[t, i, j, k] -> [(t)]; SY_cb2[t, i, j, k] -> [(t)] }]"
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
	for (int c0 = 0; c0 <= 9; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 60; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 60; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 60; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 59); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 59); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 59); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 60; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 60; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 60; c4 += 1) {
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
	for (int c0 = 0; c0 <= T / 9; c0 += 1) {
	  for (int c1 = max(2, 9 * c0); c1 <= min(T, 9 * c0 + 8); c1 += 1) {
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
	    if (T >= 9 * c0 + 18 && c1 == 9 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 60; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 60; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 60; c5 += 1) {
	            for (int c6 = -10; c6 <= min(69, N - 60 * c3); c6 += 1) {
	              for (int c7 = -10; c7 <= min(69, N - 60 * c4); c7 += 1) {
	                for (int c8 = -10; c8 <= min(69, N - 60 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 9 * c0 + 9 && c1 == 9 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 60; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 60; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 60; c5 += 1) {
	            for (int c6 = 60 * c3; c6 <= 60 * c3 + 59; c6 += 1) {
	              for (int c7 = 60 * c4; c7 <= 60 * c4 + 59; c7 += 1) {
	                for (int c8 = 60 * c5; c8 <= 60 * c5 + 59; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 60; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 60; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 60; c5 += 1) {
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
	
	for (int tt = 2; tt < T / 9; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 60; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 60; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 60; tk += 1) {
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
	for (int w=0; w<(10); w++) {
		for (int i=0; i<(80); i++) {
			for (int j=0; j<(80); j++) {
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
	
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(9); w++) {
		for (int i=0; i<(80); i++) {
			for (int j=0; j<(80); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(T, 9))) : 0); tt++) {
		for (int ti=0; ti<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); ti++) {
			for (int tj=0; tj<((-27 + T >= 0 && -121 + N >= 0) ? ((-2 + floord(59 + N, 60))) : 0); tj++) {
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
