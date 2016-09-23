#include "draw.hh"

#include "app.hh"

namespace vitapp {

draw::draw() {
    app *a = app::get();
    if (!a->is_font_inited())
        a->init_font(nullptr);
}

draw::~draw() {
}

}
