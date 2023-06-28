#include "pnet_il.h"
#include "str.h"

#define BUFFER_SIZE 200

// labels
#define ALWAYS 	8000
#define INITIAL_RE 	8002

typedef enum{
	arc_type_weighted_pos,	
	arc_type_weighted_neg,	
	arc_type_reset,	
}arc_type_t;

typedef struct{
	arc_type_t type;
	size_t place;
	size_t weight;
}arc_t;

// compiler
char *pnet_compile_il_weg_tpw04(pnet_t *pnet, int input_offset, int output_offset, int transition_offset, int place_offset, int timer_offset, int timer_min, int jump_offset);
if(pnet == NULL) return NULL;
string_t *buffer = string_new(0);	

// initial tokens
// LD M8001 MOV K1 D000
for(size_t place = 0; place < pnet->num_places; place++){
	if(pnet->places_init->m[0][place]){
		string_cat_fmt(buffer, "LD M%u\nMOV K%u D%u\n", BUFFER_SIZE, INITIAL_RE, pnet->places_init->m[0][place], place + place_offset);
	}
}

// transition trigger
// LDP X000 OUT M000
for(size_t transition = 0; transition < pnet->num_transitions; transition++){

size_t input;
pnet_event_t input_evt = pnet_event_none;
if(pnet->inputs_map != NULL){
	for(input = 0; input < pnet->num_inputs; input++){
		if(pnet->inputs_map->m[input][transition] != pnet_event_none){
			input_evt = pnet->inputs_map->m[input][transition];
			break;
		}
	}
}

size_t delay =	
	pnet->transitions_delay != NULL ?
	pnet->transitions_delay->m[0][transition] :
	0;

switch(input_evt){	
	case pnet_event_pos_edge:
		string_cat_fmt(buffer, "LDP X%u\n", BUFFER_SIZE, input + input_offset);
	break;

	case pnet_event_neg_edge:
		string_cat_fmt(buffer, "LDF X%u\n", BUFFER_SIZE, input + input_offset);
	break;

	case pnet_event_any_edge:
		string_cat_fmt(buffer, "LDF X%u\nORP X%u\n", BUFFER_SIZE, input + input_offset, input + input_offset);
	break;

	default:
	case pnet_event_none:
		string_cat_fmt(buffer, "LD M%u\n", BUFFER_SIZE, ALWAYS);
	break;
}
	
// add retentive memory to count after event and reset after count
if(delay){
	string_cat_fmt(buffer, "OR M%u\nANI T%u\n", BUFFER_SIZE, transition + pnet->num_transitions + transition_offset, transition + timer_offset);
}

for(size_t place = 0; place < pnet->num_places; place++){
	if(
		pnet->inhibit_arcs_map != NULL &&
		pnet->inhibit_arcs_map->m[place][transition]
	){
		string_cat_fmt(buffer, "AND= D%u K0\n", BUFFER_SIZE, place + place_offset);
	}

	if(
		pnet->neg_arcs_map != NULL &&
		pnet->neg_arcs_map->m[place][transition]
	){
		string_cat_fmt(buffer, "AND>= D%u K%u\n", BUFFER_SIZE, place + place_offset, -pnet->neg_arcs_map->m[place][transition]);
	}
}

// add timer, retentive memory and load timer output
if(delay){
	string_cat_fmt(buffer, "MPS\nOUT T%u K%u\n", BUFFER_SIZE, transition + timer_offset, delay / timer_min);
	string_cat_fmt(buffer, "MPP\nOUT M%u\n", BUFFER_SIZE, transition + pnet->num_transitions + transition_offset);
	string_cat_fmt(buffer, "LD T%u\n", BUFFER_SIZE, transition + timer_offset);
}

string_cat_fmt(buffer, "OUT M%u\n", BUFFER_SIZE, transition + transition_offset);
}

// pnet move tokens
// LD (M00 | M8000) MPS ADD D000 K000 D000 MRD ... MPP SUB D000 K000 D000    
arc_t *arcs = malloc(pnet->num_places * 3 * sizeof(arc_t));
size_t arc = 0;
for(size_t transition = 0; transition < pnet->num_transitions; transition++){

	// run through places and save arcs
	for(size_t place = 0; place < pnet->num_places; place++){
		if(
			pnet->neg_arcs_map != NULL && 
			pnet->neg_arcs_map->m[place][transition]
		){
			arcs[arc].type = arc_type_weighted_neg;
			arcs[arc].place = place;
			arcs[arc].weight = pnet->neg_arcs_map->m[place][transition];
			arc++;
		}

		if(
			pnet->pos_arcs_map != NULL && 
			pnet->pos_arcs_map->m[place][transition]
		){
			arcs[arc].type = arc_type_weighted_pos;
			arcs[arc].place = place;
			arcs[arc].weight = pnet->pos_arcs_map->m[place][transition];
			arc++;
		}

		if(
			pnet->reset_arcs_map != NULL && 
			pnet->reset_arcs_map->m[place][transition]
		){
			arcs[arc].type = arc_type_reset;
			arcs[arc].place = place;
			arc++;
		}
	}

	// write arcs
	if(arc > 0){
		string_cat_fmt(buffer, "LD M%u\n", BUFFER_SIZE, transition + transition_offset);

		for(size_t fire = 0; fire < arc; fire++){
			if(arc > 1){
				if(fire == 0)
					string_cat_raw(buffer, "MPS\n");
				// else if(fire == (arc - 1))
				// 	string_cat_raw(buffer, "MPP\n");
				else
					string_cat_raw(buffer, "MRD\n");
			}
			
			switch(arcs[fire].type){
				case arc_type_weighted_neg:
					string_cat_fmt(buffer, "SUB D%u K%u D%u\n", BUFFER_SIZE, arcs[fire].place + place_offset, -arcs[fire].weight, arcs[fire].place + place_offset);
				break;

				case arc_type_weighted_pos:
					string_cat_fmt(buffer, "ADD D%u K%u D%u\n", BUFFER_SIZE, arcs[fire].place + place_offset, arcs[fire].weight, arcs[fire].place + place_offset);
				break;

				case arc_type_reset:
					string_cat_fmt(buffer, "MOV K%u D%u\n", BUFFER_SIZE, 0, arcs[fire].place + place_offset);
				break;
			}
		}

		string_cat_fmt(buffer, "MPP\nCJ P%u\n", BUFFER_SIZE, jump_offset);
	}

	arc = 0;
}

free(arcs);

string_cat_fmt(buffer, "P%u\n", BUFFER_SIZE, jump_offset);

// outputs
if(pnet->outputs_map != NULL){
	for(size_t place = 0; place < pnet->num_places; place++){
		for(size_t output = 0; output < pnet->num_outputs; output++){
			if(pnet->outputs_map->m[place][output])
				string_cat_fmt(buffer, "LD>= D%u K%u\nOUT Y%u\n", BUFFER_SIZE, place + place_offset, pnet->outputs_map->m[place][output], output + output_offset);
		}
	}
}

return string_unwrap(buffer);
}