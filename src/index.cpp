#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Flex.H>

#include <emscripten/val.h>

using namespace emscripten;

int main() {
  Fl::scheme("oxy");
  Fl::background(55, 55, 55);
  Fl::background2(70, 70, 70);
  Fl::foreground(255, 255, 255);
  auto *win = new Fl_Double_Window(Fl::w() / 2 - 200, Fl::h() / 2 - 150, 400,
                                   300, "index");
  auto *col = new Fl_Flex(0, 0, 400, 300);
  col->margin(20, 30, 20, 30);
  col->gap(15);
  col->type(Fl_Flex::COLUMN);
  auto *box =
      new Fl_Box(0, 0, 0, 0, "This is an FLTK window running in the browser!");
  auto *simple = new Fl_Button(0, 0, 0, 0, "Simple example");
  simple->color(fl_darker(FL_RED));
  auto *unittests = new Fl_Button(0, 0, 0, 0, "Unit tests");
  unittests->color(fl_darker(FL_RED));
  col->end();
  win->end();
  win->show();

  simple->callback(
      [](auto, auto) {
        auto window = val::global("window");
        window.set("location", "simple.html");
      },
      nullptr);
  unittests->callback(
      [](auto, auto) {
        auto window = val::global("window");
        window.set("location", "unittests.html");
      },
      nullptr);

  return Fl::run();
}