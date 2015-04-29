//The C main file for a ROSS model
//This file includes:
// - command line argument setup
// - a main function

//includes
#include "ross.h"
#include "model_main.h"
#include "../tnt_main/models/neuron_model.h"
#include "../../../tnt_main/models/neuron_model.h"
//add your command line opts

tw_lptype model_lps[] = {

		{

				(init_f) neuron_init,
				(pre_run_f) pre_run,
				(event_f) neuron_event,
				(revent_f) neuron_reverse,
				(final_f) neuron_final,
				(map_f) NULL, //TODO: Check with Elsa about setting this to null for linear mapping.
				sizeof(neuronState)
		},
		{

				(init_f) synapse_init,
				(pre_run_f) pre_run,
				(event_f) synapse_event,
				(revent_f) synapse_reverse,
				(final_f) synapse_final,
				(map_f) NULL,
				sizeof(synapseState)
		},
		{0}


};
//for doxygen
#define model_main main
/*********************************************************************************************'
 * Main function definitions. Based on the prototype tnt_main
 * this model implements the neuromorphic baseline benchmark.
 * */
void neuron_init(neuronState *s, tw_lp *lp) {
	tw_lpid self = lp->gid;
	s->coreID = CORE(gid);
	s->neuronID = LOC(gid);
	s->prVoltage = 0;

}

// Function for bitwise switches from local to non local && back.


/**Mapping and Location Functions */
void getLocalIDs(gid_t global, regid_t * core, regid_t *local ){
	(*core) = CORE(global);
	(*local)= LOC(global);
}
gid_t globalID(regid_t core, regid_t local){
	gid_t returnVal = 0;
	returnVal = ((uint64_t)core << 32) | local;
	return returnVal;
}



///////////////MAIN///////////////////////
int model_main (int argc, char* argv[]) {
	int i;
	int num_lps_per_pe;

	tw_opt_add(app_opt);
	tw_init(&argc, &argv);

	//Do some error checking?
	//Print out some settings?

	//Custom Mapping
	/*
	g_tw_mapping = CUSTOM;
	g_tw_custom_initial_mapping = &model_custom_mapping;
	g_tw_custom_lp_global_to_local_map = &model_mapping_to_lp;
	*/

	//Useful ROSS variables and functions
	// tw_nnodes() : number of nodes/processors defined
	// g_tw_mynode : my node/processor id (mpi rank)

	//Useful ROSS variables (set from command line)
	// g_tw_events_per_pe
	// g_tw_lookahead
	// g_tw_nlp
	// g_tw_nkp
	// g_tw_synchronization_protocol

	//set up LPs within ROSS

	// g_tw_nlp gets set by tw_define_lps

	for (i = 0; i < g_tw_nlp; i++) {
		tw_lp_settype(i, &model_lps[0]);
	}

	// Do some file I/O here? on a per-node (not per-LP) basis

	tw_run();

	tw_end();

	return 0;
}
