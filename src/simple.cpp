#include <emscripten.h>
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Flex.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_PNG_Image.H>

int main() {
  Fl::background(55, 55, 55);
  Fl::background2(70, 70, 70);
  Fl::foreground(255, 255, 255);
  Fl::scheme("plastic");
  Fl::set_font(FL_SYMBOL, " Brush Script MT");
  auto *png = new Fl_PNG_Image("FL200.png");
  auto *window = new Fl_Double_Window(100, 100, "Simple GUI Example");
  auto *col = new Fl_Flex(5, 5, 630, 470, Fl_Flex::COLUMN);
  col->gap(10);
  auto *row1 = new Fl_Flex(Fl_Flex::ROW);
  col->fixed(row1, 30);
  auto *label = new Fl_Box(0, 0, 0, 0, "Enter text");
  row1->fixed(label, 100);
  auto *inp = new Fl_Input(0, 0, 0, 0);
  inp->when(FL_WHEN_CHANGED);
  row1->box(FL_FLAT_BOX);
  row1->end();
  auto *row2 = new Fl_Flex(Fl_Flex::ROW);
  auto *col1 = new Fl_Flex(Fl_Flex::COLUMN);
  col1->margin(10, 10, 10, 10);
  row2->fixed(col1, 150);
  new Fl_Box(0, 0, 0, 0);
  auto *scheme = new Fl_Choice(0, 0, 0, 0);
  scheme->add("base|gtk+|plastic|gleam|oxy");
  scheme->tooltip("Toggle schemes");
  scheme->value(2);
  scheme->color(fl_darker(FL_RED));
  col1->fixed(scheme, 30);
  new Fl_Box(0, 0, 0, 0);
  auto *color_btn = new Fl_Button(0, 0, 0, 0, "Next Color");
  color_btn->color(fl_darker(FL_RED));
  color_btn->selection_color(fl_darker(FL_GREEN));
  col1->fixed(color_btn, 30);
  new Fl_Box(0, 0, 0, 0);
  auto *font_btn = new Fl_Button(0, 0, 0, 0, "Next Font");
  font_btn->color(fl_darker(FL_RED));
  font_btn->selection_color(fl_darker(FL_GREEN));
  col1->fixed(font_btn, 30);
  new Fl_Box(0, 0, 0, 0);
  col1->end();
  auto *col2 = new Fl_Flex(Fl_Flex::COLUMN);
  auto *disp = new Fl_Box(0, 0, 0, 0, "The fox jumps over the dog!");
  disp->labelsize(18);
  disp->color(FL_WHITE);
  disp->labelcolor(FL_BLACK);
  disp->box(FL_RFLAT_BOX);
  disp->image(png);
  auto *row3 = new Fl_Flex(Fl_Flex::ROW);
  row3->box(FL_FLAT_BOX);
  col2->fixed(row3, 30);
  new Fl_Box(0, 0, 0, 0);
  auto *labelszup = new Fl_Button(0, 0, 0, 0, "+");
  labelszup->labelsize(18);
  auto *labelszdown = new Fl_Button(0, 0, 0, 0, "-");
  labelszdown->labelsize(18);
  row3->fixed(labelszup, 30);
  row3->fixed(labelszdown, 30);
  new Fl_Box(0, 0, 0, 0);
  row3->end();
  col2->end();
  row2->end();
  col->end();
  window->box(FL_FLAT_BOX);
  window->end();
  window->show();
  window->resize(0, 0, 640, 480);

  scheme->callback(
      [](auto *m, auto *) {
        auto *c = (Fl_Choice *)m;
        Fl::scheme(c->mvalue()->label());
      },
      nullptr);
  color_btn->callback(
      [](Fl_Widget *w, void *arg) {
        auto *disp = (Fl_Box *)arg;
        disp->color(disp->color() - 1);
        disp->redraw();
      },
      disp);
  font_btn->callback(
      [](Fl_Widget *w, void *arg) {
        auto *disp = (Fl_Box *)arg;
        auto val = disp->labelfont() + 1;
        if (val == FL_FREE_FONT)
          val = 0;
        disp->labelfont(val);
        disp->redraw();
      },
      disp);
  inp->callback(
      [](Fl_Widget *w, void *arg) {
        auto *inp = (Fl_Input *)w;
        auto *disp = (Fl_Box *)arg;
        disp->label(inp->value());
      },
      disp);
  labelszup->callback(
      [](Fl_Widget *w, void *arg) {
        auto *disp = (Fl_Box *)arg;
        disp->labelsize(disp->labelsize() + 1);
        disp->redraw();
      },
      disp);
  labelszdown->callback(
      [](Fl_Widget *w, void *arg) {
        auto *disp = (Fl_Box *)arg;
        disp->labelsize(disp->labelsize() - 1);
        disp->redraw();
      },
      disp);

  return Fl::run();
}