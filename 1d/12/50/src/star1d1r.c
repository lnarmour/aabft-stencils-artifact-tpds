/* star1d1r.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star1d1r [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i]: 0 <= i <= N }
 *	 	outputs
 *	 		Y : {[t, i]: 0 <= t <= T and 0 <= i <= N }
 *	 	when {  : T >= 10 and N >= 20 } let
 *	 		Y[t,i] = case  {
 *	 			{: 0 <= t <= 1 } : X[i];
 *	 			{: i = N and t >= 2  or  i = 0 and t >= 2 } : Y[t-1,i];
 *	 			{: t >= 2 and 0 < i < N } : (((0.3332[] * Y[t-1,i-1]) + (0.3333[] * Y[t-1,i])) + (0.33[] * Y[t-1,i+1]));
 *	 		};
 *	 .
 *
 * Uses the memory map:
 *	 Y(t,i) -> Y(t - 2*floord(t, 2),i)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SY_cb0[t,i]; SY_cb1[t,i]; SY_cb2[t,i] }"
 *       child:
 *         schedule: "[T,N]->[\
 *         	{ SY_cb0[t,i]->[t]; SY_cb1[t,i]->[t]; SY_cb2[t,i]->[t] } \
 *         ]"
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

// Memory access functions
#define X(i) mem_X(((i)))
#define Y(t,i) mem_Y(((t) - 2*floord((t), 2)),((i)))

#if defined REPORT_COMPLEXITY_ONLY
void star1d1r(double T, double N, float *X, float **Y)
#else
struct Result star1d1r(long T, long N, float *X, float **Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#else
		

	#define SY_cb0(t,i) Y(t,i) = X(((i)))
	#define SY_cb1(t,i) Y(t,i) = Y((-1 + (t)),((i)))
	#define SY_cb2_hook(t,i) Y(t,i) = (((0.3332) * (Y((-1 + (t)),(-1 + (i))))) + ((0.3333) * (Y((-1 + (t)),((i)))))) + ((0.33) * (Y((-1 + (t)),(1 + (i)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i) do { SY_cb2_hook(t,i); if (t==12*(tt_INJ-1)+1 && i==26*ti_INJ+25) inject_star1d1r(&Y(t,i)); } while(0)
	#else
	#define SY_cb2(t,i) SY_cb2_hook(t,i)
	#endif

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb0[t, i] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N; SY_cb2[t, i] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N; SY_cb1[t, i = N] : T >= 10 and N >= 20 and 2 <= t <= T; SY_cb1[t, i = 0] : T >= 10 and N >= 20 and 2 <= t <= T }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SY_cb2[t, i]; SY_cb0[t, i]; SY_cb1[t, i] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SY_cb0[t, i] -> [(t)]; SY_cb2[t, i] -> [(t)]; SY_cb1[t, i] -> [(t)] }]"
	 */
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
	}

	stop_timer();
	execution_time = elapsed_time();

	#undef SY

	struct Result result = new_result(); 
	result.result = execution_time;

	
	return result;
	#endif
}
