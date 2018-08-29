// Configuration file for simple EA vs EcoEA testing
// 3/20/18
// Austin Ferguson

#define NUM_STRINGS 3
#define STRING_LENGTH  15
#define GEN_SIZE 500
#define NUM_GENS 50000
#define INIT_STEPS 3
#define TRIM_HELPER ((int)(NUM_GENS / 100))
#define DATA_TRIM_FACTOR (TRIM_HELPER == 0 ? 1 : TRIM_HELPER)
#define TASK_PCT 1 //((STRING_LENGTH - 1)/STRING_LENGTH) - 0.01

#define PCT_CARRY 0.1
#define PCT_MUT 0.5
#define PCT_CROSS 0.2
#define MUT_RATE (1/STRING_LENGTH)

#define INFLOW 100
#define OUTFLOW 0.1
#define MAX_AMOUNT (STRING_LENGTH / NUM_STRINGS)
#define CONSUMPTION_FRAC 0.05
#define SPECIATION_FACTOR 1

#define ALPHABET_START 'A'
#define ALPHABET_END 'J'
