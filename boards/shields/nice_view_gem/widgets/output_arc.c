#include <zephyr/kernel.h>
#include "output_arc.h"
#include "../assets/custom_fonts.h"

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_RIGHT);
    lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "USB");
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_RIGHT);
    lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "NULL");
}

/* ========================================================================== */
/* COMMENTED OUT ORIGINAL CODE BLOCK                                          */
/* ========================================================================== */
#if 0
static void draw_ble_connected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_RIGHT);
    lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "BLE");
}
#endif
/* ========================================================================== */

// NEW UPDATED CODE BLOCK WITH CUSTOM CONNECTION NAMES
static void draw_ble_connected(lv_obj_t *canvas, uint8_t profile_index) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_RIGHT);
    
    switch (profile_index) {
        case 0:
            lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "Laptop");
            break;
        case 1:
            lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "MAC");
            break;
        case 2:
            lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "iPhone");
            break;
        case 3:
            lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "SteamDeck");
            break;
        default:
            lv_canvas_draw_text(canvas, -18, 143, SCREEN_WIDTH-8, &label_dsc, "BLE");
            break;
    }
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
    switch (state->selected_endpoint.transport) {
        case ZMK_TRANSPORT_USB:
            draw_usb_connected(canvas);
            break;
        case ZMK_TRANSPORT_BLE:
            // Pass the active profile index from the state structure
            draw_ble_connected(canvas, state->active_profile_index);
            break;
        default:
            draw_ble_disconnected(canvas);
            break;
    }
}
