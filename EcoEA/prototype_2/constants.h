// Configuration file for simple EA vs EcoEA testing
// 3/20/18
// Austin Ferguson

#define NUM_STRINGS 5
#define STRING_LENGTH  15
#define GEN_SIZE 500
#define NUM_GENS 10000
#define INIT_STEPS 3
#define DATA_TRIM_FACTOR 10
#define TASK_PCT 1 //((STRING_LENGTH - 1)/STRING_LENGTH) - 0.01

#define PCT_CARRY 0.1
#define PCT_MUT 0.5
#define PCT_CROSS 0.2
#define MUT_RATE 2*(1/STRING_LENGTH)
#define MATCH_BONUS 10

#define INFLOW 100
#define OUTFLOW 0.1
#define MAX_AMOUNT STRING_LENGTH / NUM_STRINGS
#define CONSUMPTION_FRAC 0.025
#define SPECIATION_FACTOR 1

#define ALPHABET_START 'A'
#define ALPHABET_END 'D'
