#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "./paintbox.h"
#include "./gtkknob.h"

#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#include "./gx_saturate.h"

struct gx_args;

typedef struct {
    LV2UI_Write_Function write;
    LV2UI_Controller     controller;

    GtkWidget* pbox;
    GtkWidget* box;
    GtkWidget* hbox;
    GtkWidget* vbox;
    GtkWidget* logo;
    GtkWidget* vkbox[2];
    GtkObject* adj[2];
    GtkWidget* knob[2];
    GtkWidget* label[2];
    struct gx_args *args[2];
    GtkWidget* window;  /* For optional show interface. */
} gx_saturateUI;

struct gx_args {
    gx_saturateUI* ui;
    int port_index;
} ;

static void ref_value_changed(GtkAdjustment *adj, gpointer* args) {

	gx_args * arg = (gx_args*)args;
	gx_saturateUI* ui = (gx_saturateUI*)arg->ui;
	int port_index = arg->port_index;
	float value = gtk_adjustment_get_value(adj);
	ui->write(ui->controller, (PortIndex)port_index, sizeof(float), 0,
                                    (void*)&value);
}

static LV2UI_Handle instantiate(const LV2UI_Descriptor*   descriptor,
            const char*               plugin_uri,
            const char*               bundle_path,
            LV2UI_Write_Function      write_function,
            LV2UI_Controller          controller,
            LV2UI_Widget*             widget,
            const LV2_Feature* const* features) {

    gx_saturateUI* ui = (gx_saturateUI*)malloc(sizeof(gx_saturateUI));
    ui->write       = write_function;
    ui->controller  = controller;
    ui->pbox        = NULL;
    ui->box         = NULL;
    ui->hbox        = NULL;
    ui->vbox        = NULL;
    ui->window      = NULL;
    for (int i = 0; i<2;i++) {
        ui->vkbox[i]   = NULL;
        ui->knob[i]    = NULL;
        ui->label[i]   = NULL;
    }

    *widget = NULL;

    const char* plug_name = "GxSaturator" ;
    ui->logo = gtk_label_new(plug_name);
    GdkColor color;
    gdk_color_parse("#666666", &color);
    gtk_widget_modify_fg (ui->logo, GTK_STATE_NORMAL, &color);
    GtkStyle *style = gtk_widget_get_style(ui->logo);
    pango_font_description_set_size(style->font_desc, 24*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->logo, style->font_desc);

    ui->pbox = gx_paint_box_new(GTK_ORIENTATION_VERTICAL,false, 0);
    set_expose_func(GX_PAINT_BOX(ui->pbox),"pedal_expose");
    ui->box = gtk_vbox_new(FALSE, 4);
    ui->hbox = gtk_hbox_new(TRUE, 40);
    gtk_container_set_border_width(GTK_CONTAINER(ui->hbox),25);
    ui->vbox = gtk_vbox_new(TRUE, 0);

    gtk_box_pack_start(GTK_BOX(ui->pbox), ui->box, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->hbox, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->vbox, TRUE, TRUE, 100);
    gtk_box_pack_end(GTK_BOX(ui->pbox), ui->logo, FALSE, FALSE, 0);
    gdk_color_parse("#888888", &color);

    ui->adj[0] = gtk_adjustment_new( 6.0, 1.0, 1e+01, 0.01, 0.01*10.0, 0);
    ui->knob[0] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[0]));
    ui->label[0] = gtk_label_new("INTENSITY");
    ui->vkbox[0] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[0], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[0]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[0], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->knob[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->label[0], FALSE, FALSE, 0);
    ui->args[0] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[0]->ui = ui;
    ui->args[0]->port_index = (int)INTENSITY;
    g_signal_connect_data(G_OBJECT(ui->adj[0]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[0], (GClosureNotify)free, G_CONNECT_AFTER);

    ui->adj[1] = gtk_adjustment_new( 6e+01, 0.0, 1e+02, 1.0, 1.0*10.0, 0);
    ui->knob[1] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[1]));
    ui->label[1] = gtk_label_new("SATURATE");
    ui->vkbox[1] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[1], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[1]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[1], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->knob[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->label[1], FALSE, FALSE, 0);
    ui->args[1] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[1]->ui = ui;
    ui->args[1]->port_index = (int)SATURATE;
    g_signal_connect_data(G_OBJECT(ui->adj[1]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[1], (GClosureNotify)free, G_CONNECT_AFTER);



    *widget = ui->pbox;

    return ui;
}

static void cleanup(LV2UI_Handle handle) {

    gx_saturateUI* ui = (gx_saturateUI*)handle;
    if (GTK_IS_WIDGET(ui->pbox)) {
        for(int i = 0;i<2;i++) {
            gtk_widget_destroy(ui->knob[i]);
            gtk_widget_destroy(ui->label[i]);
            gtk_widget_destroy(ui->vkbox[i]);
        }

        gtk_widget_destroy(ui->vbox);
        gtk_widget_destroy(ui->hbox);
        gtk_widget_destroy(ui->box);
        gtk_widget_destroy(ui->pbox);
        if (GTK_IS_WINDOW(ui->window)) {
            gtk_widget_destroy(ui->window);
        }
        for(int i = 0;i<2;i++) {
            free(ui->args[i]);
        }
        free(ui);
    }

}

static void port_event(LV2UI_Handle handle,
                   uint32_t     port_index,
                   uint32_t     buffer_size,
                   uint32_t     format,
                   const void*  buffer) {

    gx_saturateUI* ui = (gx_saturateUI*)handle;
	if ( format == 0 ) {
        float *value = (float*)buffer;
        gtk_adjustment_set_value(GTK_ADJUSTMENT(ui->adj[port_index-2]), (gdouble) (*value));
    }

}

/* Optional non-embedded UI show interface. */
static int ui_show(LV2UI_Handle handle) {

    gx_saturateUI* ui = (gx_saturateUI*)handle;

    int argc = 0;
    gtk_init(&argc, NULL);

    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(ui->window), ui->pbox);
    gtk_widget_show_all(ui->window);
    gtk_window_present(GTK_WINDOW(ui->window));

    return 0;
}

/* Optional non-embedded UI hide interface. */
static int ui_hide(LV2UI_Handle handle) {

    cleanup( handle);
    return 0;

}

/* Idle interface for optional non-embedded UI. */
static int ui_idle(LV2UI_Handle handle) {

    gx_saturateUI* ui = (gx_saturateUI*)handle;
    if (ui->window) {
        g_main_context_iteration (NULL, true);
    }
    return 0;

}

static const void* extension_data(const char* uri) {

    static const LV2UI_Show_Interface show = { ui_show, ui_hide };
    static const LV2UI_Idle_Interface idle = { ui_idle };
    if (!strcmp(uri, LV2_UI__showInterface)) {
        return &show;
    } else if (!strcmp(uri, LV2_UI__idleInterface)) {
        return &idle;
    }
    return NULL;

}

static const LV2UI_Descriptor descriptor = {
    GXPLUGIN_UI_URI,
    instantiate,
    cleanup,
    port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {

    switch (index) {
    case 0:
        return &descriptor;
    default:
        return NULL;
    }

}
