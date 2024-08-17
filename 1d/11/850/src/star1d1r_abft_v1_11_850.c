/* star1d1r_abft_v1_11_850.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star1d1r_abft_v1_11_850 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i]: 0 <= i <= N }
 *	 	outputs
 *	 		Y : {[t, i]: 0 <= t <= T and 0 <= i <= N }
 *	 	locals
 *	 		W : {[i]: -1 <= i <= 1 }
 *	 		C1 : {[tt, ti]: tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N }
 *	 		C2 : {[tt, ti]: tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N }
 *	 		I : {[tt, ti]: tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N }
 *	 		patch : {[w, i]: 0 <= w <= 11 and -1 - w <= i <= 850 + w }
 *	 		patch_NR : {[w, i]: 0 < w <= 11 and -1 - w <= i <= 850 + w }
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
 *	 		patch[w,i] = case  {
 *	 			{: w > 0 } : patch_NR;
 *	 			{: w = 0 and 0 <= i <= 849 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		C1[tt,ti] = reduce(+, (tt,ti,i->tt,ti), {: 850ti <= i <= 849 + 850ti } : Y[11tt,i]);
 *	 		
 *	 		C2[tt,ti] = reduce(+, (tt,ti,p->tt,ti), (patch[11,p] * Y[11tt-11,850ti+p]));
 *	 		
 *	 		I[tt,ti] = ((C2 - C1) / C1);
 *	 		
 *	 		patch_NR[w,i] = reduce(+, (w,i,p->w,i), (patch[w-1,i-p] * W[p]));
 *	 .
 *
 * Uses the memory map:
 *	 Y(t,i) -> Y(t - 2*floord(t, 2),i)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i] }"
 *     - filter: "{ Spatch[w,i]; Spatch_NR[w,i,p] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { Spatch[w,i]->[w]; Spatch_NR[w,i,p]->[w]} \
 *         ]"
 *     - filter: "{ SI[tt,ti]; SC1[tt,ti,i]; SC2[tt,ti,p]; SY_cb0[t,i]; SY_cb1[t,i]; SY_cb2[t,i] }"
 *       child:
 *         schedule: "[T,N]->[\
 *         	{ SC1[tt,ti,i]->[tt]; SC2[tt,ti,p]->[tt-1]; SI[tt,ti]->[tt]; SY_cb0[t,i]->[t/11]; SY_cb1[t,i]->[t/11]; SY_cb2[t,i]->[t/11] }, \
 *         	{ SC1[tt,ti,i]->[11tt]; SC2[tt,ti,p]->[11tt-11]; SI[tt,ti]->[11tt]; SY_cb0[t,i]->[t]; SY_cb1[t,i]->[t]; SY_cb2[t,i]->[t] } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i]; SY_cb1[t,i]; SY_cb2[t,i] }"
 *           - filter: "{ SC1[tt,ti,i]; SC2[tt,ti,p] }"
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
#define mem_C2(tt,ti) C2[(tt)-(2)][(ti)-(1)]
#define mem_I(tt,ti) I[(tt)-(2)][(ti)-(1)]
#define mem_patch(w,i) patch[(w)-(0)][(i)-(-12)]
#define mem_patch_NR(w,i) patch_NR[(w)-(1)][(i)-(-12)]

// Memory access functions
#define X(i) mem_X(((i)))
#define Y(t,i) mem_Y(((t) - 2*floord((t), 2)),((i)))
#define W(i) mem_W(((i)))
#define C1(tt,ti) mem_C1(((tt)),((ti)))
#define C2(tt,ti) mem_C2(((tt)),((ti)))
#define I(tt,ti) mem_I(((tt)),((ti)))
#define patch(w,i) mem_patch(((w)),((i)))
#define patch_NR(w,i) mem_patch_NR(((w)),((i)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int BIT;

void inject_star1d1r_abft_v1_11_850(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star1d1r_abft_v1_11_850(double T, double N, float *X, float **Y)
#else
struct Result star1d1r_abft_v1_11_850(long T, long N, float *X, float **Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)1) + T) * N)) : ((double)0));
	double total_card = ((((double)-33) + T >= ((double)0) && ((double)-1712) + N >= ((double)0)) ? ((((((((double)45706) + T) + (((double)1) + T) * N) - ((double)3450) * floord(T, ((double)11))) + ((((double)828) + ((double)2) * N) + (((double)-414) - N) * floord(T, ((double)11))) * floord(((double)838) + N, ((double)850)) + (((double)-850) + ((double)425) * floord(T, ((double)11))) * floord(((double)838) + N, ((double)850))*floord(((double)838) + N, ((double)850))) + ((((double)-4278) - ((double)2) * N) + (((double)2139) + N) * floord(T, ((double)11))) * floord(((double)849) + N, ((double)850)) + (((double)850) - ((double)425) * floord(T, ((double)11))) * floord(((double)849) + N, ((double)850))*floord(((double)849) + N, ((double)850)))) : (((double)-33) + T >= ((double)0) && ((double)-1701) + N >= ((double)0) && ((double)1711) - N >= ((double)0)) ? ((((((double)38778) + T) + (((double)-1) + T) * N) + (((double)14) + N) * floord(T, ((double)11)))) : ((((double)-33) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)1700) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)32) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)38806) + T) + (((double)1) + T) * N)) : ((double)0));
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
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float** patch = (float**)(calloc((12),sizeof(float*)));
	for (int w=0; w<(12); w++) {
		patch[w] = (float*)(calloc((874),sizeof(float)));
	}
	
	float* W = (float*)(calloc((3),sizeof(float)));
	
	float** I = (float**)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		I[tt] = (float*)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(849 + N, 850))) : 0),sizeof(float)));
	}
	
	float** patch_NR = (float**)(calloc((11),sizeof(float*)));
	for (int w=0; w<(11); w++) {
		patch_NR[w] = (float*)(calloc((874),sizeof(float)));
	}
	
	float** C1 = (float**)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		C1[tt] = (float*)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(849 + N, 850))) : 0),sizeof(float)));
	}
	
	float** C2 = (float**)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0),sizeof(float*)));
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		C2[tt] = (float*)(calloc(((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(849 + N, 850))) : 0),sizeof(float)));
	}

	#define SC1(tt,ti,i) C1(tt,ti) += Y((11*(tt)),((i)))
	#define SC2(tt,ti,p) C2(tt,ti) += (patch((11),((p)))) * (Y((-11 + 11*(tt)),(850*(ti) + (p))))
	#define SI(tt,ti) I(tt,ti) = ((C2(tt,ti)) - (C1(tt,ti))) / (C1(tt,ti))
	#define SW(i) W(i) = ((-1 + i) == (0)) ? (0.33) : (((1 + i) == (0)) ? (0.3332) : (0.3333))
	#define SY_cb0(t,i) Y(t,i) = X(((i)))
	#define SY_cb1(t,i) Y(t,i) = Y((-1 + (t)),((i)))
	#define SY_cb2_hook(t,i) Y(t,i) = (((0.3332) * (Y((-1 + (t)),(-1 + (i))))) + ((0.3333) * (Y((-1 + (t)),((i)))))) + ((0.33) * (Y((-1 + (t)),(1 + (i)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i) do { SY_cb2_hook(t,i); if (t==11*(tt_INJ-1)+1 && i==850*ti_INJ+425) inject_star1d1r_abft_v1_11_850(&Y(t,i)); } while(0)
	#else
	#define SY_cb2(t,i) SY_cb2_hook(t,i)
	#endif
	#define Spatch(w,i) patch(w,i) = ((-1 + w) >= (0)) ? (patch_NR(w,i)) : (((((w) == (0)) && ((i) >= (0))) && ((849 - i) >= (0))) ? (1) : (0))
	#define Spatch_NR(w,i,p) patch_NR(w,i) += (patch((-1 + (w)),((i) - (p)))) * (W(((p))))

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SY_cb0[t, i] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N; SI[tt, ti] : tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N; SC1[tt, ti, i] : tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N and 850ti <= i <= 849 + 850ti; SC2[tt, ti, p] : tt >= 2 and 11tt <= -11 + T and ti > 0 and 850ti <= -851 + N and -12 <= p <= 861 and p <= N - 850ti; Spatch_NR[w, i, p] : T >= 10 and N >= 20 and 0 < w <= 11 and p >= -1 and -849 - w + i <= p <= 1 and p <= w + i; Spatch[w, i] : T >= 10 and N >= 20 and 0 <= w <= 11 and -1 - w <= i <= 850 + w; SY_cb2[t, i] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N; SY_cb1[t, i = N] : T >= 10 and N >= 20 and 2 <= t <= T; SY_cb1[t, i = 0] : T >= 10 and N >= 20 and 2 <= t <= T; SW[i] : T >= 10 and N >= 20 and -1 <= i <= 1 }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i] }"
	 *   - filter: "{ Spatch[w, i]; Spatch_NR[w, i, p] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ Spatch_NR[w, i, p] -> [(w)]; Spatch[w, i] -> [(w)] }]"
	 *   - filter: "{ SI[tt, ti]; SY_cb2[t, i]; SC2[tt, ti, p]; SY_cb0[t, i]; SY_cb1[t, i]; SC1[tt, ti, i] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SI[tt, ti] -> [(tt)]; SY_cb0[t, i] -> [(floor((t)/11))]; SC1[tt, ti, i] -> [(tt)]; SC2[tt, ti, p] -> [(-1 + tt)]; SY_cb2[t, i] -> [(floor((t)/11))]; SY_cb1[t, i] -> [(floor((t)/11))] }, { SI[tt, ti] -> [(11tt)]; SY_cb0[t, i] -> [(t)]; SC1[tt, ti, i] -> [(11tt)]; SC2[tt, ti, p] -> [(-11 + 11tt)]; SY_cb2[t, i] -> [(t)]; SY_cb1[t, i] -> [(t)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb2[t, i]; SY_cb0[t, i]; SY_cb1[t, i] }"
	 *         - filter: "{ SC2[tt, ti, p]; SC1[tt, ti, i] }"
	 *         - filter: "{ SI[tt, ti] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  SW(c0);
	}
	for (int c0 = 0; c0 <= 11; c0 += 1) {
	  if (c0 >= 1) {
	    for (int c2 = -c0 - 1; c2 <= c0 + 850; c2 += 1) {
	      for (int c3 = max(-1, -c0 + c2 - 849); c3 <= min(1, c0 + c2); c3 += 1) {
	        Spatch_NR(c0, c2, c3);
	      }
	    }
	  }
	  for (int c2 = -c0 - 1; c2 <= c0 + 850; c2 += 1) {
	    Spatch(c0, c2);
	  }
	}
	for (int c1 = 0; c1 <= 1; c1 += 1) {
	  for (int c3 = 0; c3 <= N; c3 += 1) {
	    SY_cb0(c1, c3);
	  }
	}
	for (int c0 = 0; c0 <= T / 11; c0 += 1) {
	  for (int c1 = max(2, 11 * c0); c1 <= min(T, 11 * c0 + 10); c1 += 1) {
	    SY_cb1(c1, 0);
	    SY_cb1(c1, N);
	    for (int c3 = 1; c3 < N; c3 += 1) {
	      SY_cb2(c1, c3);
	    }
	    if (T >= 11 * c0 + 22 && c1 == 11 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 850; c3 += 1) {
	        for (int c4 = -12; c4 <= min(861, N - 850 * c3); c4 += 1) {
	          SC2(c0 + 1, c3, c4);
	        }
	      }
	    }
	    if (c0 >= 2 && T >= 11 * c0 + 11 && c1 == 11 * c0) {
	      for (int c3 = 1; c3 < (N - 1) / 850; c3 += 1) {
	        for (int c4 = 850 * c3; c4 <= 850 * c3 + 849; c4 += 1) {
	          SC1(c0, c3, c4);
	        }
	      }
	      for (int c3 = 1; c3 < (N - 1) / 850; c3 += 1) {
	        SI(c0, c3);
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
	struct INJ inj = { tt_INJ, ti_INJ };
	struct Result result = new_result();
	result.bit = BIT;
	result.inj = inj;
	result.noise = -1;
	
	const char* verbose = getenv("VERBOSE");
	
	#define print_SI(tt,ti) printf("v1_I(%d,%d) = %E\n",tt,ti, fabs(I(tt,ti)))
	#define acc_noise(tt,ti) result.noise = max(result.noise, fabs(I(tt,ti)))
	#define SI(tt,ti) do { if (verbose != NULL && fabs(I(tt,ti))>=threshold) print_SI(tt,ti); acc_noise(tt,ti); if (tt==tt_INJ && ti==ti_INJ) { if (fabs(I(tt,ti))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 11; tt += 1) {
	  for (int ti = 1; ti < (N - 1) / 850; ti += 1) {
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
	for (int w=0; w<(12); w++) {
		 free(patch[w]);
	}
	free(patch);
	
	 free(W);
	
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		 free(I[tt]);
	}
	free(I);
	
	for (int w=0; w<(11); w++) {
		 free(patch_NR[w]);
	}
	free(patch_NR);
	
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		 free(C1[tt]);
	}
	free(C1);
	
	for (int tt=0; tt<((-33 + T >= 0 && -1701 + N >= 0) ? ((-2 + floord(T, 11))) : 0); tt++) {
		 free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
