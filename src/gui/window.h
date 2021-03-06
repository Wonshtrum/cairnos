#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "utils/types.h"
#include "gui/config.h"
#include "gui/color.h"
#include "gui/widget.h"


class Window: public Composite_widget {
private:
	bool dragged;

	void start_drag();
	void stop_drag();

public:
	Window(int32_t x, int32_t y, int32_t width, int32_t height, Color color);
	~Window();

	virtual void focus(Widget* widget) override;

	virtual void on_mouse_down(int32_t x, int32_t y, uint8_t button) override;
	virtual void on_mouse_up(int32_t x, int32_t y, uint8_t button) override;
	virtual void on_mouse_leave(int32_t x, int32_t y) override;
	virtual void on_mouse_move(int32_t ox, int32_t oy, int32_t nx, int32_t ny) override;

	virtual void draw(Graphics_context* ctx, Bounding_box box) override;
};


#endif
