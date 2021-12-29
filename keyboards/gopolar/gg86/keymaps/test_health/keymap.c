/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// OLED animation
#include "oled/bongocat.c"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// enum layer_names { };

// enum layer_keycodes { };

enum user_rgb_mode {
    RGB_MODE_ALL,
    RGB_MODE_KEYLIGHT,
    RGB_MODE_UNDERGLOW,
    RGB_MODE_NONE,
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode :8;
    };
} user_config_t;

user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
                   ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
                   │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
                   └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
                   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
                   │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bckspc│ │Hom│Scr│Pse│
                   ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤       ┌─────┐
                   │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │ │End│Scr│Pse│       │     │
       ┌────┬─┐    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘    ┌──┴┐Entr│
       │Caps│ │    │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │                  │ \ │    │
       ├────┼─┴─┐  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐      ┌─┴───┴┬───┤
       │LSft│ \ │  │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │   RShift │     │ ↑ │      │ RSft │ Fn│
       └────┴───┘  ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─────┤ ┌───┼───┼───┐  └──────┴───┘
                   │LCrl │GUI│ LAlt│           Space           │ RAlt│ Fn│ RCrl│ │ ← │ ↓ │ → │
                   └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
                   ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
                   │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │   │
                   └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
                   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
                   │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │ │   │   │   │
                   ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤       ┌─────┐
                   │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │ │   │   │   │       │     │
       ┌────┬─┐    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘    ┌──┴┐    │
       │Caps│ │    │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │                  │ | │    │
       ├────┼─┴─┐  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐      ┌─┴───┴┬───┤
       │LSft│ | │  │ LShift │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │   RShift │     │   │      │ RSft │   │
       └────┴───┘  ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─────┤ ┌───┼───┼───┐  └──────┴───┘
                   │     │   │     │                           │     │   │     │ │   │   │   │
                   └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3      4      5       6      7      8      9        10       11       12       13       14       15       16      */
	[0] = LAYOUT_tkl_ansi_tsangan_split_lrshift(
                KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5,  KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUSE,
                KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,   KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
                KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
                KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                KC_LSFT, KC_NUBS, KC_Z,    KC_X,  KC_C,  KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,          KC_UP,
                KC_LCTL, KC_LGUI, KC_LALT,               KC_SPC,                               KC_RALT, MO(1),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RIGHT
    ),

/*
                   ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
                   │Slp│   │M_T│F13│F14│F15│ │F16│Rfh│Stp│   │ │   │   │   │Est│ │   │VoD│VoU│
                   └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
                   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
                   │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │Hui│Sai│Spi│
                   ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤       ┌─────┐
                   │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │Hud│Sad│Spd│       │     │
       ┌────┬─┐    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘    ┌──┴┐ Tog│
       │    │ │    │      │   │   │   │   │   │   │   │   │   │   │   │ RGB_Tog│                  │   │    │
       ├────┼─┴─┐  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐      ┌─┴───┴┬───┤
       │    │   │  │        │   │   │Cal│   │   │   │   │   │   │   │          │     │Vai│      │      │   │
       └────┴───┘  ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─────┤ ┌───┼───┼───┐  └──────┴───┘
                   │     │   │     │                           │     │   │     │ │Rod│Vad│Mod│
                   └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15       16     */
	[1] = LAYOUT_tkl_ansi_tsangan_split_lrshift(
                KC_SLEP, RGB_M_T, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_WREF, KC_WSTP, _______, _______, _______, _______, EEP_RST,          _______,  KC_VOLD, KC_VOLU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,  RGB_SAI, RGB_SPI,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,  RGB_SAD, RGB_SPD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RGB_VAI,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RGB_RMOD, RGB_VAD, RGB_MOD
    ),
};

void keyboard_post_init_kb(void) {
    user_config.raw = eeconfig_read_user();
    switch (user_config.rgb_mode) {
        case RGB_MODE_ALL:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
        case RGB_MODE_KEYLIGHT:
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_NONE:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                        user_config.rgb_mode = RGB_MODE_KEYLIGHT;
                    }
                    break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        user_config.rgb_mode = RGB_MODE_UNDERGLOW;
                    }
                    break;
                    case (LED_FLAG_UNDERGLOW): {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        user_config.rgb_mode = RGB_MODE_NONE;
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        user_config.rgb_mode = RGB_MODE_ALL;
                    }
                    break;
                }
                eeconfig_update_user(user_config.raw);
            }
            return false;
	}

    return true;
}

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        led_t led_usb_state = host_keyboard_led_state();

        render_bongocat();
        oled_set_cursor(14, 0);                                // sets cursor to (column, row) using charactar spacing (4 rows on 128x32 screen, anything more will overflow back to the top)
        oled_write_P(PSTR("WPM:"), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false); // writes wpm on top right corner of string
        oled_set_cursor(17, 2);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
        oled_set_cursor(17, 3);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRL") : PSTR("    "), false);

        return true;
    }
#endif
