#include "mouse_event.h"


enum states {
    START,
    FIRST_LINE,
    VERTIX,
    SECOND_LINE,
    FINISH
};

bool state_machine_process(struct packet p, uint8_t x_len, uint8_t tolerance) {
    static enum states state = START;

    static int64_t acc_x = 0;
    static int64_t acc_y = 0;

    bool r_pressed = p.rb;
    bool m_pressed = p.mb;
    bool l_pressed = p.lb;

    int16_t x = p.delta_x;
    int16_t y = p.delta_y;

    // static enum states _debug_previous_state = START;

    // if (state != _debug_previous_state) {
    //     printf("State transition: ");
    //     switch (_debug_previous_state)
    //     {
    //     case START:
    //         printf("START");
    //         break;
    //     case FIRST_LINE:
    //         printf("FIRST_LINE");
    //         break;
    //     case VERTIX:
    //         printf("VERTIX");
    //         break;
    //     case SECOND_LINE:
    //         printf("SECOND_LINE");
    //         break;
    //     case FINISH:
    //         printf("FINISH");
    //         break;
    //     }

    //     printf(" to ");

    //     switch (state)
    //     {
    //     case START:
    //         printf("START");
    //         break;
    //     case FIRST_LINE:
    //         printf("FIRST_LINE");
    //         break;
    //     case VERTIX:
    //         printf("VERTIX");
    //         break;
    //     case SECOND_LINE:
    //         printf("SECOND_LINE");
    //         break;
    //     case FINISH:
    //         printf("FINISH");
    //         break;
    //     }

    //     printf("\n");
    // }

    // _debug_previous_state = state;

    switch (state) {
        case START:
            acc_x = 0;
            acc_y = 0;

            if (l_pressed && !m_pressed && !r_pressed) {
                state = FIRST_LINE;
            }
            return false;
        
        case FIRST_LINE:
            if (!l_pressed) {

                if (acc_x < x_len) {
                    state = START;
                    return false;
                }

                if ((acc_y / acc_x) >= 1) {
                    state = VERTIX;
                    return false;
                } else {
                    state = START;
                    return false;
                }
            }

            if ((x < -tolerance) || (y < -tolerance)) {
                state = START;
                return false;
            } else {
                acc_x += x;
                acc_y += y;
                state = FIRST_LINE;
                return false;
            }
        
        case VERTIX:
            acc_x = 0;
            acc_y = 0;

            if (m_pressed || l_pressed) {
                state = START;
                return false;
            }

            if (r_pressed) {
                state = SECOND_LINE;
                return false;
            }

            if ((abs(x) > tolerance) || (abs(y) > tolerance)) {
                state = START;
                return false;
            } else {
                state = VERTIX;
                return false;
            }

        case SECOND_LINE:
            if (!r_pressed) {
                if (acc_x < x_len) {
                    state = START;
                    return false;
                }

                if ((acc_y / acc_x) <= -1) {
                    state = FINISH;
                    return true;
                } else {
                    state = START;
                    printf("HI\n");
                    return false;
                }
            }

            if ((x < -tolerance) || (y > tolerance)) {
                state = START;
                return false;
            } else {
                acc_x += x;
                acc_y += y;
                state = SECOND_LINE;
                return false;
            }

        case FINISH:
            return true;

    }
}
