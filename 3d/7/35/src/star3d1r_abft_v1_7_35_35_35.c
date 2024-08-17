/* star3d1r_abft_v1_7_35_35_35.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v1_7_35_35_35 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N }
 *	 		C2 : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N }
 *	 		patch : {[w, i, j, k]: 0 <= w <= 7 and -1 - w <= i <= 35 + w and -1 - w <= j <= 35 + w and -1 - w <= k <= 35 + w }
 *	 		patch_NR : {[w, i, j, k]: 0 < w <= 7 and -1 - w <= i <= 35 + w and -1 - w <= j <= 35 + w and -1 - w <= k <= 35 + w }
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
 *	 			{: w = 0 and 0 <= i <= 34 and 0 <= j <= 34 and 0 <= k <= 34 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 35ti <= i <= 34 + 35ti and 35tj <= j <= 34 + 35tj and 35tk <= k <= 34 + 35tk } : Y[7tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), (patch[7,p,q,r] * Y[7tt-7,35ti+p,35tj+q,35tk+r]));
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

void inject_star3d1r_abft_v1_7_35_35_35(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v1_7_35_35_35(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v1_7_35_35_35(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-21) + T >= ((double)0) && ((double)-78) + N >= ((double)0)) ? (((((((((double)151432216) + ((double)8) * T) + (((double)24) + ((double)24) * T) * N + (((double)24) + ((double)24) * T) * N*N + (((double)8) + ((double)8) * T) * N*N*N) - ((double)11233728) * floord(T, ((double)7))) + ((((double)5243616) + ((double)499392) * N) + (((double)-2621808) - ((double)249696) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35)) + ((((double)-8199576) + ((double)102816) * N + ((double)4896) * N*N) + (((double)4099788) - ((double)51408) * N - ((double)2448) * N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)-1780758) - ((double)166068) * N + ((double)504) * N*N + ((double)16) * N*N*N) + (((double)890379) + ((double)83034) * N - ((double)252) * N*N - ((double)8) * N*N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)1406790) - ((double)17640) * N - ((double)840) * N*N) + (((double)-703395) + ((double)8820) * N + ((double)420) * N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)154350) + ((double)14700) * N) + (((double)-77175) - ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + (((double)-85750) + ((double)42875) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))) + (((((double)-38944800) - ((double)499392) * N) + (((double)19472400) + ((double)249696) * N) * floord(T, ((double)7))) + ((((double)-6323184) - ((double)705024) * N - ((double)9792) * N*N) + (((double)3161592) + ((double)352512) * N + ((double)4896) * N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35)) + ((((double)10213182) + ((double)104076) * N - ((double)3960) * N*N - ((double)48) * N*N*N) + (((double)-5106591) - ((double)52038) * N + ((double)1980) * N*N + ((double)24) * N*N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)1084860) + ((double)120960) * N + ((double)1680) * N*N) + (((double)-542430) - ((double)60480) * N - ((double)840) * N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)-904050) - ((double)14700) * N) + (((double)452025) + ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))) * floord(((double)34) + N, ((double)35)) + (((((double)31373352) + ((double)602208) * N + ((double)4896) * N*N) + (((double)-15686676) - ((double)301104) * N - ((double)2448) * N*N) * floord(T, ((double)7))) + ((((double)3705534) + ((double)414900) * N + ((double)6408) * N*N + ((double)48) * N*N*N) + (((double)-1852767) - ((double)207450) * N - ((double)3204) * N*N - ((double)24) * N*N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35)) + ((((double)-6083280) - ((double)85680) * N) + (((double)3041640) + ((double)42840) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + ((((double)-308700) - ((double)29400) * N) + (((double)154350) + ((double)14700) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35)) + (((double)257250) - ((double)128625) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))) * floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35)) + (((((double)-14946390) - ((double)352908) * N - ((double)2952) * N*N - ((double)16) * N*N*N) + (((double)7473195) + ((double)176454) * N + ((double)1476) * N*N + ((double)8) * N*N*N) * floord(T, ((double)7))) + ((((double)-1084860) - ((double)120960) * N - ((double)1680) * N*N) + (((double)542430) + ((double)60480) * N + ((double)840) * N*N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35)) + ((((double)1808100) + ((double)29400) * N) + (((double)-904050) - ((double)14700) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))) * floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35)) + (((((double)4676490) + ((double)103320) * N + ((double)840) * N*N) + (((double)-2338245) - ((double)51660) * N - ((double)420) * N*N) * floord(T, ((double)7))) + ((((double)154350) + ((double)14700) * N) + (((double)-77175) - ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35)) + (((double)-257250) + ((double)128625) * floord(T, ((double)7))) * floord(((double)27) + N, ((double)35))*floord(((double)27) + N, ((double)35))) * floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35)) + ((((double)-904050) - ((double)14700) * N) + (((double)452025) + ((double)7350) * N) * floord(T, ((double)7))) * floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35)) + (((double)85750) - ((double)42875) * floord(T, ((double)7))) * floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))*floord(((double)34) + N, ((double)35))))/((double)8)) : (((double)-21) + T >= ((double)0) && ((double)-71) + N >= ((double)0) && ((double)77) - N >= ((double)0)) ? ((((((double)16069995) + T) + (((double)-4053) + ((double)3) * T) * N + (((double)159) + ((double)3) * T) * N*N + (((double)-1) + T) * N*N*N) + (((double)25300) + ((double)2028) * N - ((double)78) * N*N + N*N*N) * floord(T, ((double)7)))) : ((((double)-21) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)70) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)20) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)16120595) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
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
		patch[w] = (float***)(calloc((51),sizeof(float**)));
		for (int i=0; i<(51); i++) {
			patch[w][i] = (float**)(calloc((51),sizeof(float*)));
			for (int j=0; j<(51); j++) {
				patch[w][i][j] = (float*)(calloc((51),sizeof(float)));
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
	
	float**** I = (float****)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** patch_NR = (float****)(calloc((7),sizeof(float***)));
	for (int w=0; w<(7); w++) {
		patch_NR[w] = (float***)(calloc((51),sizeof(float**)));
		for (int i=0; i<(51); i++) {
			patch_NR[w][i] = (float**)(calloc((51),sizeof(float*)));
			for (int j=0; j<(51); j++) {
				patch_NR[w][i][j] = (float*)(calloc((51),sizeof(float)));
			}
		}
	}
	
	float**** C1 = (float****)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** C2 = (float****)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		C2[tt] = (float***)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			C2[tt][ti] = (float**)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
				C2[tt][ti][tj] = (float*)(calloc(((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0),sizeof(float)));
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((7*(tt)),((i)),((j)),((k)))
	#define SC2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk) += (patch((7),((p)),((q)),((r)))) * (Y((-7 + 7*(tt)),(35*(ti) + (p)),(35*(tj) + (q)),(35*(tk) + (r))))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((C2(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==7*(tt_INJ-1)+1 && i==35*ti_INJ+17 && j==35*tj_INJ+17 && k==35*tk_INJ+17) inject_star3d1r_abft_v1_7_35_35_35(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif
	#define Spatch(w,i,j,k) patch(w,i,j,k) = ((-1 + w) >= (0)) ? (patch_NR(w,i,j,k)) : (((((((((w) == (0)) && ((i) >= (0))) && ((34 - i) >= (0))) && ((j) >= (0))) && ((34 - j) >= (0))) && ((k) >= (0))) && ((34 - k) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,j,k,p,q,r) patch_NR(w,i,j,k) += (patch((-1 + (w)),((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; Spatch_NR[w, i, j, k, p, q, r] : T >= 10 and N >= 20 and 0 < w <= 7 and p >= -1 and -34 - w + i <= p <= 1 and p <= w + i and q >= -1 and -34 - w + j <= q <= 1 and q <= w + j and r >= -1 and -34 - w + k <= r <= 1 and r <= w + k; Spatch[w, i, j, k] : T >= 10 and N >= 20 and 0 <= w <= 7 and -1 - w <= i <= 35 + w and -1 - w <= j <= 35 + w and -1 - w <= k <= 35 + w; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2[tt, ti, tj, tk, p, q, r] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N and -8 <= p <= 42 and p <= N - 35ti and -8 <= q <= 42 and q <= N - 35tj and -8 <= r <= 42 and r <= N - 35tk; SI[tt, ti, tj, tk] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N; SC1[tt, ti, tj, tk, i, j, k] : tt >= 2 and 7tt <= -7 + T and ti > 0 and 35ti <= -36 + N and tj > 0 and 35tj <= -36 + N and tk > 0 and 35tk <= -36 + N and 35ti <= i <= 34 + 35ti and 35tj <= j <= 34 + 35tj and 35tk <= k <= 34 + 35tk; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N }"
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
	    for (int c2 = -c0 - 1; c2 <= c0 + 35; c2 += 1) {
	      for (int c3 = -c0 - 1; c3 <= c0 + 35; c3 += 1) {
	        for (int c4 = -c0 - 1; c4 <= c0 + 35; c4 += 1) {
	          for (int c5 = max(-1, -c0 + c2 - 34); c5 <= min(1, c0 + c2); c5 += 1) {
	            for (int c6 = max(-1, -c0 + c3 - 34); c6 <= min(1, c0 + c3); c6 += 1) {
	              for (int c7 = max(-1, -c0 + c4 - 34); c7 <= min(1, c0 + c4); c7 += 1) {
	                Spatch_NR(c0, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 35; c2 += 1) {
	    for (int c3 = -c0 - 1; c3 <= c0 + 35; c3 += 1) {
	      for (int c4 = -c0 - 1; c4 <= c0 + 35; c4 += 1) {
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
	      for (int c3 = 1; c3 < (N - 1) / 35; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 35; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 35; c5 += 1) {
	            for (int c6 = -8; c6 <= min(42, N - 35 * c3); c6 += 1) {
	              for (int c7 = -8; c7 <= min(42, N - 35 * c4); c7 += 1) {
	                for (int c8 = -8; c8 <= min(42, N - 35 * c5); c8 += 1) {
	                  SC2(c0 + 1, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 7 * c0 + 7 && c1 == 7 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 35; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 35; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 35; c5 += 1) {
	            for (int c6 = 35 * c3; c6 <= 35 * c3 + 34; c6 += 1) {
	              for (int c7 = 35 * c4; c7 <= 35 * c4 + 34; c7 += 1) {
	                for (int c8 = 35 * c5; c8 <= 35 * c5 + 34; c8 += 1) {
	                  SC1(c0, c3, c4, c5, c6, c7, c8);
	                }
	              }
	            }
	          }
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 35; c3 += 1) {
	        for (int c4 = 1; c4 < (N - 1) / 35; c4 += 1) {
	          for (int c5 = 1; c5 < (N - 1) / 35; c5 += 1) {
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
	  for (int ti = 1; ti < (N - 1) / 35; ti += 1) {
	    for (int tj = 1; tj < (N - 1) / 35; tj += 1) {
	      for (int tk = 1; tk < (N - 1) / 35; tk += 1) {
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
		for (int i=0; i<(51); i++) {
			for (int j=0; j<(51); j++) {
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
	
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(7); w++) {
		for (int i=0; i<(51); i++) {
			for (int j=0; j<(51); j++) {
				 free(patch_NR[w][i][j]);
			}
			free(patch_NR[w][i]);
		}
		free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(T, 7))) : 0); tt++) {
		for (int ti=0; ti<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); ti++) {
			for (int tj=0; tj<((-21 + T >= 0 && -71 + N >= 0) ? ((-2 + floord(34 + N, 35))) : 0); tj++) {
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
