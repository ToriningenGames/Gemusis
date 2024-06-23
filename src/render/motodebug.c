#include "inc/motodebug.h"

#define STACKWIDTH 220
#define STACKHEIGHT 220
#define COMMANDHEIGHT 40

static bool codeselect[65536];
static int selectedline;
static char cmdbuf[80];

void motodebuginit(struct window *this, struct iohub *data)
{
        (void)data;
        if (this->window) {
                //Bring the window back to fore
                SDL_RaiseWindow(this->window);
                SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                return;
        }
        this->object = malloc(sizeof(*this->object));
        //NK init
        this->window = SDL_CreateWindow("68000 Debugger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        this->windowid = SDL_GetWindowID(this->window);
        this->context = nk_sdl_init(this->object, this->window, this->renderer);
        //Font init
        struct nk_font *font = fontinit(this->object);
        nk_style_set_font(this->context, &font->handle);
        //Custom style init
        this->context->style.window.spacing = nk_vec2(0,0);
        selectedline = -1;
        cmdbuf[0] = '\0';
}

struct windowResult motodebugdraw(struct window *this, struct iohub *data)
{
        (void)data;
        struct windowResult results = {0};
        if (!this->window)
                return results;         //Nothing to draw
        int width, height;
        SDL_GetWindowSize(this->window, &width, &height);
        //Main code view
        if (nk_begin(this->context, "Code", nk_rect(0,0,width-STACKWIDTH,height-COMMANDHEIGHT),0)) {
                nk_layout_row_dynamic(this->context, 15, 1);
                for (int i = 0; i < 65535; i++) {
                        nk_selectable_label(this->context, "item", NK_TEXT_LEFT, codeselect+i);
                        if (i == selectedline && !codeselect[i]) {
                                selectedline = -1;
                        }
                        if (codeselect[i] && i != selectedline) {
                                if (selectedline >= 0)
                                        codeselect[selectedline] = 0;
                                selectedline = i;
                                codeselect[selectedline] = 1;
                        }
                }
        }
        nk_end(this->context);
        //Register view
        if (nk_begin(this->context, "Registers", nk_rect(width-STACKWIDTH,0,STACKWIDTH,STACKHEIGHT),0)) {
                nk_layout_row_dynamic(this->context, 20, 2);
                char regline[22];
                sprintf(regline, "D0: $%08X", data->motoRegs.D0);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A0: $%08X", data->motoRegs.A0);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D1: $%08X", data->motoRegs.D1);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A1: $%08X", data->motoRegs.A1);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D2: $%08X", data->motoRegs.D2);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A2: $%08X", data->motoRegs.A2);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D3: $%08X", data->motoRegs.D3);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A3: $%08X", data->motoRegs.A3);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D4: $%08X", data->motoRegs.D4);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A4: $%08X", data->motoRegs.A4);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D5: $%08X", data->motoRegs.D5);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A5: $%08X", data->motoRegs.A5);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D6: $%08X", data->motoRegs.D6);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A6: $%08X", data->motoRegs.A6);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "D7: $%08X", data->motoRegs.D7);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "A7: $%08X", data->motoRegs.A7);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                nk_layout_row_dynamic(this->context, 20, 1);
                sprintf(regline, "PC: $%08X", data->motoRegs.PC);
                nk_label(this->context, regline, NK_TEXT_CENTERED);
                sprintf(regline, "SSR: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
                        data->motoRegs.SSR.trace ? 'T' : 't',
                        data->motoRegs.SSR.b14 ? '1' : '0',
                        data->motoRegs.SSR.supervisor ? 'M' : 'm',
                        data->motoRegs.SSR.b12 ? '1' : '0',
                        data->motoRegs.SSR.b11 ? '1' : '0',
                        data->motoRegs.SSR.interrupt & 1 ? '1' : '0',
                        data->motoRegs.SSR.interrupt & 2 ? '1' : '0',
                        data->motoRegs.SSR.interrupt & 4 ? '1' : '0',
                        data->motoRegs.SSR.b7 ? '1' : '0',
                        data->motoRegs.SSR.b6 ? '1' : '0',
                        data->motoRegs.SSR.b5 ? '1' : '0',
                        data->motoRegs.SSR.extend ? 'X' : 'x',
                        data->motoRegs.SSR.negative ? 'N' : 'n',
                        data->motoRegs.SSR.zero ? 'Z' : 'z',
                        data->motoRegs.SSR.overflow ? 'O' : 'o',
                        data->motoRegs.SSR.carry ? 'C' : 'c');
                nk_label(this->context, regline, NK_TEXT_CENTERED);
        }
        nk_end(this->context);
        //Stack view
        if (nk_begin(this->context, "Stack", nk_rect(width-STACKWIDTH,STACKHEIGHT,STACKWIDTH,height-STACKHEIGHT-COMMANDHEIGHT),0)) {
                nk_layout_row_dynamic(this->context, 20, 1);
                nk_label(this->context, "Stack goes here", NK_TEXT_CENTERED);
        }
        nk_end(this->context);
        //Command line
        if (nk_begin(this->context, "Command", nk_rect(0,height-COMMANDHEIGHT,width,COMMANDHEIGHT),0)) {
                nk_layout_row_begin(this->context, NK_DYNAMIC, COMMANDHEIGHT-15, 2);
                nk_layout_row_push(this->context, 0.90f);
                nk_edit_string_zero_terminated(this->context,
                        NK_EDIT_AUTO_SELECT | NK_EDIT_ALWAYS_INSERT_MODE | NK_EDIT_SELECTABLE | NK_EDIT_SIG_ENTER,
                        cmdbuf,
                        sizeof(cmdbuf),
                        0);
                nk_layout_row_push(this->context, 0.10f);
                nk_button_label(this->context, "submit");
                nk_layout_row_end(this->context);
        }
        nk_end(this->context);

        //NK render
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        nk_sdl_render(this->object, NK_ANTI_ALIASING_OFF);
        SDL_RenderPresent(this->renderer);
        
        //Processing
        return results;
}

struct window *motodebugGet()
{
        static struct window Options = {
                .window = NULL,
                .init = motodebuginit,
                .close = windowclose,
                .isme = windowisme,
                .eventready = windoweventready,
                .event = windowevent,
                .eventend = windoweventend,
                .draw = motodebugdraw
        };
        return &Options;
}
