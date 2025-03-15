#include <gb/gb.h>
#include <gbdk/platform.h>
#include "vm.h"
#include "camera.h"
#include "scroll.h"
#include "actor.h"

UINT8 infinite_scroll_reverse = 0;

// The VBL handler now updates our infinite scroll variable.
void vbl_update() {
    if (infinite_scroll_reverse) {
        infinite_background_scroll -= infinite_scroll_speed;
    } else {
        infinite_background_scroll += infinite_scroll_speed;
    }
}

// Plugin command to enable infinite background scrolling.
void script_cmd_infinite_background_scroll(SCRIPT_CTX* THIS) OLDCALL __banked {
    // Pop arguments from the stack:
    // First argument: fixed-point speed (e.g. 5 means 5/16 pixels per frame).
    // Second argument: scroll direction (0 = horizontal, 1 = vertical).
	infinite_scroll_reverse   = vm_pop(THIS, 1);
    infinite_scroll_direction = vm_pop(THIS, 1);
    infinite_scroll_speed = vm_pop(THIS, 1);

  for (int i = 0; i < MAX_ACTORS; i++) {
        actors[i].pinned = 1;
        actors[i].collision_enabled = 1;
    }
    // Activate infinite scrolling mode.
    infinite_scroll_active = 1;

    // Lock the camera so the engine won't override our scroll.
camera_settings |= CAMERA_LOCK_FLAG;
camera_x = (SCREEN_WIDTH >> 1) << 4;
camera_y = (SCREEN_HEIGHT >> 1) << 4;


    // Register our VBL handler and enable interrupts.
    add_VBL(vbl_update);
    enable_interrupts();
}
