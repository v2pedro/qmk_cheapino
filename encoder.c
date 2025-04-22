#include "matrix.h"
#include "quantum.h"

#define COL_SHIFTER ((uint16_t)1)

#define ENC_ROW 3
#define ENC_A_COL 2
#define ENC_B_COL 4
#define ENC_BUTTON_COL 0

#define ENCODER_RESOLUTION 2

static bool lastA = false;
static bool lastB = false;
//static bool lastDirection = false; // Track last direction to avoid double presses

//static bool colABPressed   = false;
//static bool encoderPressed = false;

void clicked(void) {
    tap_code(KC_MUTE);
}

void turned(bool clockwise) {
    if (IS_LAYER_ON(6)) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (IS_LAYER_ON(3)) {
        tap_code16(clockwise ? KC_PGDN : KC_PGUP);
    } else if (IS_LAYER_ON(5)) {
        tap_code16(clockwise ? LGUI(KC_Y) : LGUI(KC_Z));
    } else if (IS_LAYER_ON(1)) {
        tap_code16(clockwise ? KC_DOWN : KC_UP);
    } else {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    }
}

void fix_encoder_action(matrix_row_t current_matrix[]) {


    matrix_row_t encoder_row = current_matrix[ENC_ROW];

    // Read encoder states
    bool colA = encoder_row & (COL_SHIFTER << ENC_A_COL);
    bool colB = encoder_row & (COL_SHIFTER << ENC_B_COL);

    if (colA != lastA) {
        if  (colB != colA) {
            turned(true);
        } else {
            turned(false);
        }
    }
/*
    // Detect rotation direction properly
    if (colA != lastA) {  
        if (colB != colA) {  
            if (lastDirection != true) {  // Ensure no duplicate presses
                turned(true);  // Clockwise
                lastDirection = true;
            }
        }
    } else if (colB != lastB) {  
        if (colA == colB) {  
            if (lastDirection != false) {  // Ensure no duplicate presses
                turned(false);  // Counterclockwise
                lastDirection = false;
            }
        }
    }
*/
    // Update last known states
    lastA = colA;
    lastB = colB;

    // Clear only encoder-related keys in the matrix
    current_matrix[ENC_ROW] &= ~(COL_SHIFTER << ENC_A_COL);
    current_matrix[ENC_ROW] &= ~(COL_SHIFTER << ENC_B_COL);
}

