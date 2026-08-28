/*
#include <zephyr/kernel.h>
#include "output.h"
#include "../assets/custom_fonts.h"

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "USB");
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "NULL");
}

static void draw_ble_connected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "BLE");
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
    switch (state->selected_endpoint.transport) {
        case ZMK_TRANSPORT_USB:
            draw_usb_connected(canvas);
            break;
        case ZMK_TRANSPORT_BLE:
            draw_ble_connected(canvas);
            break;
        default:
            draw_ble_disconnected(canvas);
            break;
    }
}
*/

#include <zephyr/kernel.h>
#include "output.h"
#include "../assets/custom_fonts.h"

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    // This displays when plugged into your desktop via USB
    lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "USB PC");
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "SEARCHING");
}

// Pass the active profile index into the BLE drawing function
static void draw_ble_connected(lv_obj_t *canvas, uint8_t profile_index) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
    
    // Map the ZMK Bluetooth Profile slots (0-4) to your custom names
    switch (profile_index) {
        case 0:
            lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "Laptop");
            break;
        case 1:
            lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "MAC");
            break;
        case 3:
            lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "iOS");
            break;
        case 4:
            lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "STEAM");
            break;
        default:
            lv_canvas_draw_text(canvas, 12, 140, SCREEN_WIDTH-8, &label_dsc, "BT SPARE");
            break;
    }
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
    switch (state->selected_endpoint.transport) {
        case ZMK_TRANSPORT_USB:
            draw_usb_connected(canvas);
            break;
        case ZMK_TRANSPORT_BLE:
            // Pass the active profile index into the renderer
            draw_ble_connected(canvas, state->selected_endpoint.profile_index);
            break;
        default:
            draw_ble_disconnected(canvas);
            break;
    }
}
