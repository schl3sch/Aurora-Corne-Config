#include <zmk/display/status_screen.h>
#include <zmk/battery.h>
#include <lvgl.h>

// ==========================================================================
// TEIL 1: DEINE BILD-DATEN (Aus deiner kodama.c übernommen)
// ==========================================================================

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

// Deine Bild-Daten (Kodama)
const LV_ATTRIBUTE_MEM_ALIGN uint8_t kodama_map[] = {
  // Farb-Palette (wird bei 1-Bit oft ignoriert, aber wir lassen sie drin)
  0xf6, 0xf9, 0xf6, 0xff, 	/*Color of index 0*/
  0x84, 0x8c, 0x83, 0xff, 	/*Color of index 1*/

  // Die Pixel-Daten
  0x00, 0x02, 0xa0, 0x00, 
  0x00, 0x0c, 0x18, 0x00, 
  0x00, 0x1e, 0x04, 0x00, 
  0x00, 0x1e, 0x02, 0x00, 
  0x00, 0x2e, 0x01, 0x00, 
  0x00, 0x40, 0x41, 0x00, 
  0x00, 0x40, 0x00, 0x80, 
  0x00, 0x00, 0x00, 0x80, 
  0x00, 0x80, 0x0f, 0x40, 
  0x00, 0x00, 0x0f, 0x40, 
  0x00, 0x80, 0x1f, 0x40, 
  0x00, 0x00, 0x0f, 0x80, 
  0x00, 0x8c, 0x06, 0x40, 
  0x00, 0x8e, 0x00, 0x80, 
  0x00, 0x8c, 0x15, 0x00, 
  0x00, 0x20, 0x06, 0x00, 
  0x00, 0x1a, 0xb8, 0x00, 
  0x00, 0x15, 0x60, 0x00, 
  0x00, 0x20, 0x10, 0x00, 
  0x00, 0x20, 0x20, 0x00, 
  0x00, 0x40, 0x18, 0x00, 
  0x00, 0x10, 0x28, 0x00, 
  0x00, 0x28, 0x28, 0x00, 
  0x00, 0x5e, 0xf8, 0x80, 
  0x00, 0x52, 0x88, 0x00, 
  0x00, 0x23, 0x88, 0x00, 
  0x00, 0x51, 0x09, 0x00, 
  0x00, 0x31, 0x08, 0x00, 
  0x00, 0x51, 0x9c, 0x00, 
  0x01, 0xf9, 0x97, 0x80, 
  0x03, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0x40, 
};

// Die Bild-Beschreibung
const lv_img_dsc_t kodama = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT, // WICHTIG: Korrektes Format
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 32,
  .header.h = 32,
  .data_size = 136,
  .data = kodama_map,
};

// ==========================================================================
// TEIL 2: LOGIK FÜR DAS DISPLAY
// ==========================================================================

// Funktion, die von ZMK aufgerufen wird, um den Screen zu bauen
lv_obj_t *zmk_display_status_screen() {
    
    // 1. Basis-Screen erstellen
    lv_obj_t *screen = lv_obj_create(NULL);

    // ---------------------------------------------------------------
    // ELEMENT A: Der Kodama (Bild)
    // ---------------------------------------------------------------
    lv_obj_t *icon = lv_img_create(screen);
    lv_img_set_src(icon, &kodama);
    
    // Positionierung:
    // LV_ALIGN_CENTER = Genau in der Mitte
    // 0, 10 = X=0, Y=10 (etwas nach unten verschoben, damit Platz für Akku ist)
    lv_obj_align(icon, LV_ALIGN_CENTER, 0, 10);


    // ---------------------------------------------------------------
    // ELEMENT B: Der Akku-Stand (Text)
    // ---------------------------------------------------------------
    lv_obj_t *batt_label = lv_label_create(screen);
    
    // Holt den aktuellen Akkustand (0-100)
    uint8_t battery_level = zmk_battery_state_of_charge();
    
    // Setzt den Text (z.B. "85%")
    lv_label_set_text_fmt(batt_label, "%d%%", battery_level);
    
    // Positionierung: Ganz oben zentriert
    lv_obj_align(batt_label, LV_ALIGN_TOP_MID, 0, 0);

    return screen;
}