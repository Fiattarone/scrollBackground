#include <gb/gb.h>
#include <gbdk/platform.h>
#include "vm.h"
#include "camera.h"
#include "scroll.h"
#include "actor.h"



// Plugin command to enable infinite background scrolling.
void script_cmd_if_actor_destroyed(SCRIPT_CTX* THIS) OLDCALL __banked {
	int16_t actor_idx = *(int16_t*)VM_REF_TO_PTR(-1); // actor idx
	THIS->stack_ptr--;
	// int16_t debug_actor_idx = *(int16_t*)VM_REF_TO_PTR(FN_ARG2); // actor idx
	script_memory[1] = actor_idx;

	// for (int i = 0; i < MAX_ACTORS; i++) {
		if (!actors[actor_idx].active) {
			 // variable, true if actor active
			script_memory[*(int16_t*)VM_REF_TO_PTR(-1)] = 0;
			THIS->stack_ptr--;
		}
	// }
}
