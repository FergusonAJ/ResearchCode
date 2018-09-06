// Configuration file for simple EA vs EcoEA testing
// 8/20/18
// Austin Ferguson

#define GEN_SIZE 250
#define NUM_GENS 500
#define TRIM_HELPER ((int)(NUM_GENS / 100))
#define DATA_TRIM_FACTOR (TRIM_HELPER == 0 ? 1 : TRIM_HELPER)

#define PCT_CARRY 0.1
#define PCT_MUT 0.5
#define PCT_CROSS 0.2
#define MUT_RATE (1/100)

#define INFLOW 1000
#define OUTFLOW 0.1
#define INIT_STEPS 3
#define MAX_AMOUNT 200
#define CONSUMPTION_FRAC 0.05
#define SPECIATION_FACTOR 1

#define ALPHABET_START 'A'
#define ALPHABET_END 'D'
#define TASK_PCT 1

#define NUM_ROWS 21
#define NUM_COLS 21
#define ELECTRON_ROW 11
#define ELECTRON_COL 11
#define EMPTY '.'
#define WIRE 'X'
#define HEAD 'O'
#define TAIL '!'
#define INIT_WIRE_PCT 0.75
#define NUM_TICKS 50
#define SCORE_BASE 1.0415


#define RESOURCE_NORTH "NORTH"
#define RESOURCE_SOUTH "SOUTH"
#define RESOURCE_EAST "EAST"
#define RESOURCE_WEST "WEST"

