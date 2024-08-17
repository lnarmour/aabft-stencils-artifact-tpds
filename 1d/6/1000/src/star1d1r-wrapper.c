// star1d1r-wrapper.c

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))
#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
#define mallocCheck(v,s,d) if ((v) == NULL) { printf("Failed to allocate memory for %s : size=%lu\n", "sizeof(d)*(s)", sizeof(d)*(s)); exit(-1); }
#define new_result() { .valid=0, .TP=0L, .FP=0L, .TN=0L, .FN=0L, .TPR=0.0f, .FPR=0.0f, .FNR=0.0f, .bit=0, .inj={.tt=0, .ti=0, .tj=0, .tk=0}, .result=0.0f, .noise=0.0f}
#define new_result_summary() { .TP=0L, .FP=0L, .TN=0L, .FN=0L, .TPR=0.0f, .FPR=0.0f, .FNR=0.0f, .bit=0, .nb_detected=0L, .nb_results=0L, .result=0.0f, .noise=0.0f, .max_error=0.0f}

// External system declarations
struct Result star1d1r(long T, long N, float *X, float **Y);
#if defined REPORT_COMPLEXITY_ONLY
void star1d1r_abft_v1_6_1000(double T, double N, float *X, float **Y);
void star1d1r_abft_v2_6_1000(double T, double N, float *X, float **Y);
#else
struct Result star1d1r_abft_v1_6_1000(long T, long N, float *X, float **Y);
struct Result star1d1r_abft_v2_6_1000(long T, long N, float *X, float **Y);
#endif

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

struct ResultsSummary {
	float TP;
	float FP;
	float TN;
	float FN;
	float TPR;
	float FPR;
	float FNR;
	int bit;
	long nb_detected;
	long nb_results;
	double result;
	double noise;
	double max_error;
};

// Memory mapped targets
#define mem_X(i) X[(i)-(0)]
#define mem_Y(t,i) Y[(t)-(0)][(i)-(0)]
#if defined ERROR_INJECTION
#define mem_Y_GOLD(t,i) Y_GOLD[(t)-(0)][(i)-(0)]
#endif

// Memory access functions
#define X(i) mem_X(((i)))
#define Y(t,i) mem_Y(((t) - 2*floord((t), 2)),((i)))
#if defined ERROR_INJECTION
#define Y_GOLD(t,i) mem_Y_GOLD(((t) - 2*floord((t), 2)),((i)))
#endif

#ifdef ERROR_INJECTION
static int tBox;
static int sBox;
static int rBox;
static int runBox;
static char eol[2];
static int run;
static int R;
static int log_flag;

void printHeader() {
	int S = 300;
	char header_str[S];
	sprintf(header_str, "   %*s : (%*s,%*s) : (%*s,%*s,%*s,%*s) : %*s, %*s, %*s, %*s", 4, "bit", tBox, "inj.tt", sBox, "inj.ti", rBox, "TP", rBox, "FP", rBox, "TN", rBox, "FN", 12, "Detected (%)", 7, "FPR (%)", 14, "Max rel. error", 2 * runBox + 1, "Runs");
	char header_bar[S]; for (int i=0; i<S; i++) header_bar[i] = '-';
	fprintf(stdout, "%.*s\n", (int)strlen(header_str), header_bar);
	fprintf(stdout, "%s\n", header_str);
	fprintf(stdout, "%.*s\n", (int)strlen(header_str), header_bar);
}

void print(int version, struct Result r, double max_error) {
	if (!log_flag) {
		return;
	}
	int detected = r.TP > 0 ? 1 : 0;
    printf("v%d,%*d : (%*d,%*d) : (%*ld,%*ld,%*ld,%*ld) : %*d, %*.2f, %*E, %*d/%d%s", version, 4, r.bit, tBox, r.inj.tt, sBox, r.inj.ti, rBox, r.TP, rBox, r.FP, rBox, r.TN, rBox, r.FN, 12, detected, 7, r.FPR, 14, max_error, runBox, run, R, eol);
    fflush(stdout);
}

void print_summary(int version, struct ResultsSummary *s) {
	s->TP = s->TP / s->nb_results;
	s->FP = s->FP / s->nb_results;
	s->TN = s->TN / s->nb_results;
	s->FN = s->FN / s->nb_results;
	s->TPR = s->TPR / s->nb_results;
	s->FPR = s->FPR / s->nb_results;
	s->FNR = s->FNR / s->nb_results;
	float detected_rate =100 * s->nb_detected / s->nb_results;
	
	printf("v%d,%*d : (%*s,%*s) : (%*.2f,%*.2f,%*.2f,%*.2f) : %*.2f, %*.2f, %*E, %*d/%d\n", version, 4, s->bit, tBox, "-", sBox, "-", rBox, s->TP, rBox, s->FP, rBox, s->TN, rBox, s->FN, 12, detected_rate, 7, s->FPR, 14, s->max_error, runBox, run, R);
}

void accumulate_result(struct ResultsSummary *acc, struct Result r) {
	acc->TP += r.TP;
	acc->FP += r.FP;
	acc->TN += r.TN;
	acc->FN += r.FN;
	acc->TPR += r.TPR;
	acc->FPR += r.FPR;
	acc->FNR += r.FNR;
	acc->bit = r.bit;
	if (r.TP > 0) {
		acc->nb_detected++;
	}
	acc->nb_results++;
}
#endif

int main(int argc, char **argv) 
{
	if (argc < 3) {
		printf("usage: %s T N\n", argv[0]);
		return 1;
	}
	
	// Parse parameter sizes
	#if defined REPORT_COMPLEXITY_ONLY
	float T = atof(argv[1]);
	float N = atof(argv[2]);
	#else
	long T = atol(argv[1]);
	long N = atol(argv[2]);
	#endif
	
	// Check parameter values
	if (((9 - T) >= (0)) || (((-10 + T) >= (0)) && ((19 - N) >= (0)))) {
		printf("Illegal parameter values, must be in { [T, N] : T >= 10 and N >= 20 }\n");
		return 1;
	}
	
	#if defined REPORT_COMPLEXITY_ONLY
	float* X;
	float** Y;
	
	#else
	// Local memory allocation
	float* X = (float*)(calloc(((N >= 0) ? ((1 + N)) : 0),sizeof(float)));
	
	float** Y = (float**)(calloc(((N >= 0) ? (2) : 0),sizeof(float*)));
	for (int t=0; t<((N >= 0) ? (2) : 0); t++) {
		Y[t] = (float*)(calloc(((N >= 0) ? ((1 + N)) : 0),sizeof(float)));
	}
	// Local memory allocation
	float** Y_GOLD = (float**)(calloc(((N >= 0) ? (2) : 0),sizeof(float*)));
	for (int t=0; t<((N >= 0) ? (2) : 0); t++) {
		Y_GOLD[t] = (float*)(calloc(((N >= 0) ? ((1 + N)) : 0),sizeof(float)));
	}
	
	srand(time(NULL));
	
	// X initialization
	#define SX(i) X(i) = rand()
	for (int i = 0; i <= N; i += 1) {
	  SX(i);
	}
	#undef SX
	#endif
	
	#if defined TIMING
	
	struct Result r0 = star1d1r(T, N, X, Y);
	printf("v0 time: %0.4f sec\n", r0.result);
	struct Result r1 = star1d1r_abft_v1_6_1000(T, N, X, Y);
	printf("v1 time: %0.4f sec\n", r1.result);
	struct Result r2 = star1d1r_abft_v2_6_1000(T, N, X, Y);
	printf("v2 time: %0.4f sec\n", r2.result);
	
	#elif defined REPORT_COMPLEXITY_ONLY
	star1d1r_abft_v1_6_1000(T, N, X, Y);
	star1d1r_abft_v2_6_1000(T, N, X, Y);
	
	#elif defined ERROR_INJECTION
	tBox = max((int)log10(T) + 1, 7);
	sBox = max((int)log10(N) + 1, 7);
	rBox = (int)log10(2*(T/(float)6)*(N/(float)1000)) + 4;
	if (getenv("VERBOSE") != NULL) {
		strcpy(eol, "\n");
	} else {
		strcpy(eol, "\r");
	}
	
	log_flag = (getenv("LOG") == NULL) ? 1 : 0;
	
	#define export_injs() do { { int ival = (rand() % ((T/6)-2) + 2); sprintf(val, "%d", ival); setenv("tt_INJ", val, 1); } { int ival = (rand() % ((N/1000)-2) + 1); sprintf(val, "%d", ival); setenv("ti_INJ", val, 1); } } while(0)
	
	R = (getenv("NUM_RUNS") != NULL) ? atoi(getenv("NUM_RUNS")) : 100;
	runBox = (int)log10(R) + 1;

	// if THRESHOLD not explicitly set, do short profiling to estimate the
	// noise due to floating point round off errors
	const char* threshold = getenv("THRESHOLD");
	float threshold_v1;
	if (threshold == NULL) {
		struct Result result;
		long input_T = T;
		T = 24;
		
		result = star1d1r_abft_v1_6_1000(T, N, X, Y);
		printf("floating point noise: %E\n", result.noise);
		float thresholds[10] = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10 };
		for (int i=9; i>=0; i--) {
			threshold_v1 = thresholds[i];
			if (threshold_v1 > fabs(result.noise))
				break;
		}
		printf(" threshold_v1 set to: %E\n", threshold_v1);
		T = input_T;
	} else {
		threshold_v1 = atoi(getenv("THRESHOLD"));
	}
	float threshold_v2;
	if (threshold == NULL) {
		struct Result result;
		long input_T = T;
		T = 24;
		
		result = star1d1r_abft_v2_6_1000(T, N, X, Y);
		printf("floating point noise: %E\n", result.noise);
		float thresholds[10] = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10 };
		for (int i=9; i>=0; i--) {
			threshold_v2 = thresholds[i];
			if (threshold_v2 > fabs(result.noise))
				break;
		}
		printf(" threshold_v2 set to: %E\n", threshold_v2);
		T = input_T;
	} else {
		threshold_v2 = atoi(getenv("THRESHOLD"));
	}
	printHeader();
	
	int t_INJ; 
	int i_INJ;
	
	// Get GOLD result, run the input program
	star1d1r(T, N, X, Y_GOLD);
	
	const char* verbose = getenv("VERBOSE");
	const char* single_bit = getenv("BIT");
	char val[50];
	// ABFTv1
	sprintf(val, "%E", threshold_v1); 
	setenv("THRESHOLD", val, 1);
	for (int bit=31; bit>=8; bit--) {
		if (single_bit != NULL && atoi(single_bit) != bit)
			continue;
		char val[50];
		sprintf(val, "%d", bit); 
		setenv("bit", val, 1);
		
		struct ResultsSummary v_avg = new_result_summary();
		
		for (run=0; run<R; run++) {
			export_injs();
			struct Result v = star1d1r_abft_v1_6_1000(T, N, X, Y);
			
			// Compare output with GOLD
			double max_error = 0.0f;
			#define SY(t,i) max_error = max(max_error, fabs((Y(t,i) / Y_GOLD(t,i)) - 1))
			for (int i = 0; i <= N; i += 1) {
			  SY(T, i);
			}
			#undef SY
			v_avg.max_error = max(v_avg.max_error, max_error);
			
			accumulate_result(&v_avg, v);
			print(1, v, max_error);
		}
		print_summary(1, &v_avg);
	}
	printHeader();
	// ABFTv2
	sprintf(val, "%E", threshold_v2); 
	setenv("THRESHOLD", val, 1);
	for (int bit=31; bit>=8; bit--) {
		if (single_bit != NULL && atoi(single_bit) != bit)
			continue;
		char val[50];
		sprintf(val, "%d", bit); 
		setenv("bit", val, 1);
		struct ResultsSummary v_avg = new_result_summary();
		for (run=0; run<R; run++) {
			export_injs();
			struct Result v = star1d1r_abft_v2_6_1000(T, N, X, Y);
			
			// Compare output with GOLD
			double max_error = 0.0f;
			#define SY(t,i) max_error = max(max_error, fabs((Y(t,i) / Y_GOLD(t,i)) - 1))
			for (int i = 0; i <= N; i += 1) {
			  SY(T, i);
			}
			#undef SY
			v_avg.max_error = max(v_avg.max_error, max_error);
			
			accumulate_result(&v_avg, v);
			print(2, v, max_error);
		}
		print_summary(2, &v_avg);
	}
	#endif

	return 0;
}
