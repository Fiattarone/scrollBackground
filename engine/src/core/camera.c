#pragma bank 255

#include "camera.h"
#include "actor.h"    // if needed for player position updates
#include "scroll.h"   // if you use additional scroll logic

INT16 camera_x;
INT16 camera_y;
BYTE camera_offset_x;
BYTE camera_offset_y;
BYTE camera_deadzone_x;
BYTE camera_deadzone_y;
UBYTE camera_settings;
INT16 initial_camera_x;
INT16 initial_camera_y;

void camera_init(void) BANKED {
    // Set initial values and fully lock the camera
    camera_settings = CAMERA_LOCK_FLAG;  // Locks both X and Y (0x01 | 0x02)
    initial_camera_x = 0;
    initial_camera_y = 18*16;
    camera_reset();
}

void camera_update(void) NONBANKED {
    // If both axes are locked, don't update the camera at all.
    if ((camera_settings & CAMERA_LOCK_FLAG) == CAMERA_LOCK_FLAG) {
        return;
    }

    // Otherwise, update camera position based on player position.
    // (This is your normal camera update logic.)
    if (camera_settings & CAMERA_LOCK_X_FLAG) {
        UWORD a_x = PLAYER.pos.x + SCREEN_WIDTH_HALF;
        // Example: update camera_x using deadzone and offset adjustments.
        if (camera_x < a_x - (camera_deadzone_x << 4) - (camera_offset_x << 4)) {
            camera_x = a_x - (camera_deadzone_x << 4) - (camera_offset_x << 4);
        } else if (camera_x > a_x + (camera_deadzone_x << 4) - (camera_offset_x << 4)) {
            camera_x = a_x + (camera_deadzone_x << 4) - (camera_offset_x << 4);
        }
    }
    if (camera_settings & CAMERA_LOCK_Y_FLAG) {
        UWORD a_y = PLAYER.pos.y + SCREEN_HEIGHT_HALF;
        // Example: update camera_y using deadzone and offset adjustments.
        if (camera_y < a_y - (camera_deadzone_y << 4) - (camera_offset_y << 4)) {
            camera_y = a_y - (camera_deadzone_y << 4) - (camera_offset_y << 4);
        } else if (camera_y > a_y + (camera_deadzone_y << 4) - (camera_offset_y << 4)) {
            camera_y = a_y + (camera_deadzone_y << 4) - (camera_offset_y << 4);
        }
    }
}
