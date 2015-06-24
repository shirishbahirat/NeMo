//
//  model_main.h
//  ROSS_TOP
//
//  Created by Mark Plagge on 6/17/15.
//
//

#ifndef __ROSS_TOP__model_main__
#define __ROSS_TOP__model_main__

#include <stdio.h>
#include "assist.h"
#include "ross.h"
#include "models/axon.h"
#include "models/neuron.h"
#include "models/synapse.h"
#include "input_simulator.h"
#include "mapping.h"
#include <math.h>

#include <stdbool.h>

        // Variable holders for command lne params & external variables
/**
 *  Number of neurons per core.
 */
int NEURONS_IN_CORE = 256;
/** number of synapses per core. Calculated value, needs to be neurons * axons */
int SYNAPSES_IN_CORE = 0;
/** Number of axions per core. Generally is set to 1-1 with neurons in core */
int AXONS_IN_CORE = 256;
/* Given number of cores in simulation */
int CORES_IN_SIM = 2;

/// Memory Tuning
int eventAlloc = 2;
unsigned int GEN_ON = 1;///< Is the input generator enabled?

bool GEN_RND = 1; //!< Generator random mode flag
unsigned int RND_MODE = 0;
unsigned int GEN_PROB = 50;
unsigned int GEN_FCT = 5;
unsigned int GEN_OUTBOUND = 0;
unsigned int GEN_SEL_MODE = 0;
unsigned int SP_DBG = 0;
extern tw_lpid* myGIDs;


/**  Determines the maximum thresholds for a neuron to fire.
 */
_threshT THRESHOLD_MAX = 100;

 _threshT NEG_THRESHOLD_MAX = 100;
/**
 *  Minimum threshold. @see THRESHOLD_MAX
 */
_threshT THRESHOLD_MIN = 10;

_threshT NEG_THRESHOLD_MIN = 1;


_voltT RESET_VOLTAGE_MAX = 100;
_voltT RESET_VOLTAGE_MIN = -100;

_threshT RAND_RANGE_MIN = 1;
_threshT RAND_RANGE_MAX = 31;


/**
 *	Each neuron is connected to the synapses (inputs) within the core it is running in.
 *	These parameters adjust the input weight given to each synapse. */
int32_t SYNAPSE_WEIGHT_MAX = 10;
/** Minimum synapse weight. @see SYNAPSE_WEIGHT_MAX */
int32_t SYNAPSE_WEIGHT_MIN = -10;
tw_stime PER_SYNAPSE_DET_P = .50;


	//Simulation Variables
/**CORE_SIZE is equal to the number of axions * number of aneurons + num neurons + num axions */
int CORE_SIZE;

/* **** Model Main Function */
/**
 * @brief createLPs will create the LPs needed for the simulation on this PE.
 * Call once during model init.
 */
void createLPs();
/**
 * @brief pre_run Not used - placeholder function for compatibility.
 * In future revisions, this is where file IO will occur.
 *
 */
void pre_run();

/**
 * @brief neuron_init Neuron lp initialization.
 * @param s
 * @param lp
 */
void neuron_init(neuronState *s, tw_lp *lp);
/**
 * @brief setSynapseWeight is called from \a neuron_init and sets up the weights
 * of a neuron. Keeping it as a seperate function. Eventually will read in file map data.
 * @param s
 * @param lp
 * @param synapseID
 */

//Command line options:
const tw_optdef app_opt[]= {
  TWOPT_GROUP("Randomized Neuron Parameters"),
  TWOPT_UINT("th_min", THRESHOLD_MIN, "minimum threshold for neurons"),
    TWOPT_UINT("th_max", THRESHOLD_MAX, "maximum threshold for neurons"),
    TWOPT_UINT("wt_min", SYNAPSE_WEIGHT_MIN, "minimum synapse weight"),
    TWOPT_UINT("wt_max", SYNAPSE_WEIGHT_MAX, "maximum synapse weight"),
    {TWOPT_END()}

  };
void setSynapseWeight(neuronState *s, tw_lp *lp, int synapseID);
void neuron_event(neuronState *s, tw_bf *CV, Msg_Data *M, tw_lp *lp);
void neuron_reverse(neuronState *, tw_bf *, Msg_Data *, tw_lp *);
void neuron_final(neuronState *s, tw_lp *lp);

void synapse_init(synapseState *s, tw_lp *lp);
void synapse_event(synapseState *s, tw_bf *, Msg_Data *M, tw_lp *lp);
void synapse_reverse(synapseState *, tw_bf *, Msg_Data *M, tw_lp *);
void synapse_final(synapseState *s, tw_lp *lp);

void axon_init(axonState *s, tw_lp *lp);
void axon_event(axonState *s, tw_bf *, Msg_Data *M, tw_lp *lp);
void axon_reverse(axonState *, tw_bf *, Msg_Data *M, tw_lp *);
void axon_final(axonState *s, tw_lp *lp);



#endif /* defined(__ROSS_TOP__model_main__) */
